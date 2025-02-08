#include "odometry.h"

Odometry::Odometry(C_DcMotor *left_encoder, C_DcMotor *right_encoder, C_DcMotor *perp_encoder, double track_width, double perp_offset) {
    this->left_encoder = left_encoder;
    this->right_encoder = right_encoder;
    this->perp_encoder = perp_encoder;

    this->track_width = track_width;
    this->perp_offset = perp_offset;
}

void Odometry::update() {
    maths::vec3 encoder_values{
        (double) this->left_encoder->getCurrentPosition(),
        (double) this->right_encoder->getCurrentPosition(),
        (double) (!this->perp_encoder ? 0.0 : this->perp_encoder->getCurrentPosition()),
    };

    maths::vec3 encoder_deltas{
        encoder_values[0] - this->last_encoder_values[0],
        encoder_values[1] - this->last_encoder_values[1],
        encoder_values[2] - this->last_encoder_values[2],
    };

    this->last_encoder_values[0] = encoder_values[0];
    this->last_encoder_values[1] = encoder_values[1];
    this->last_encoder_values[2] = encoder_values[2];

    double phi = (encoder_deltas[0] - encoder_deltas[1]) / this->track_width;

    maths::vec3 deltas{
        encoder_deltas[2] + this->perp_offset * phi,
        (encoder_deltas[0] + encoder_deltas[1]) / 2,
        phi,
    };

    maths::mat integrator(2, 2);

    integrator[0][0] = phi == 0.0 ? 1.0 : -std::sin(phi) / phi;
    integrator[0][1] = phi == 0.0 ? 0.0 : (std::cos(phi) - 1) / phi;
    integrator[1][0] = phi == 0.0 ? 0.0 : (-std::cos(phi) + 1) / phi;
    integrator[1][1] = phi == 0.0 ? 1.0 : -std::sin(phi) / phi;

    maths::vec3 integrated_deltas{
        integrator[0][0] * deltas[0] + integrator[0][1] * deltas[1],
        integrator[1][0] * deltas[0] + integrator[1][1] * deltas[1],
        phi,
    };

    maths::vec3 field_deltas{
        std::cos(this->position[2]) * integrated_deltas[0] - std::sin(this->position[2]) * integrated_deltas[1],
        std::sin(this->position[2]) * integrated_deltas[0] + std::cos(this->position[2]) * integrated_deltas[1],
        phi,
    };

    this->position[0] += field_deltas[0];
    this->position[1] += field_deltas[1];
    this->position[2] += field_deltas[2];
}

void Odometry::reset() {
    this->position[0] = 0.0;
    this->position[1] = 0.0;
    this->position[2] = 0.0;

    this->last_encoder_values[0] = (double) this->left_encoder->getCurrentPosition();
    this->last_encoder_values[1] = (double) this->right_encoder->getCurrentPosition();
    this->last_encoder_values[2] = (double) (!this->perp_encoder ? 0.0 : this->perp_encoder->getCurrentPosition());
}