#include "regressor_test.h"

extern "C"
JNIEXPORT void JNICALL Java_org_firstinspires_ftc_teamcode_opmodes_RegressorTest_runOpMode(JNIEnv *p_jni, jobject self) {
    (new RegressorTest(p_jni, self))->runOpMode();
}

void RegressorTest::runOpMode() {
    this->robot = new Robot(this);

    this->waitForStart();

    maths::vec3 velocity{};
    std::chrono::duration<double> elapsed;

    auto start = std::chrono::system_clock::now();
    auto last = start;

    maths::vec3 last_position{
        this->robot->odometry->position[0],
        this->robot->odometry->position[1],
        this->robot->odometry->position[2]
    };

    std::vector<double> powers(0);
    std::vector<double> velocities(0);

    while (this->opModeIsActive() && !this->gamepad1->a()) {
        // DATA READING & LOGGING
        auto now = std::chrono::system_clock::now();
        this->robot->odometry->update();

        elapsed = now - start;
        std::chrono::duration<double> delta = now - last;
        
        last = now;

        velocity[0] = (this->robot->odometry->position[0] - last_position[0]) / delta.count();
        velocity[1] = (this->robot->odometry->position[1] - last_position[1]) / delta.count();
        velocity[2] = (this->robot->odometry->position[2] - last_position[2]) / delta.count();

        last_position[0] = this->robot->odometry->position[0];
        last_position[1] = this->robot->odometry->position[1];
        last_position[2] = this->robot->odometry->position[2];    

        this->telemetry->addLine(utils::sprintf(
            "x = %.2f", this->robot->odometry->position[0] / ODOMETRY_TICKS_PER_CM
        ));

        this->telemetry->addLine(utils::sprintf(
            "y = %.2f", this->robot->odometry->position[1] / ODOMETRY_TICKS_PER_CM
        ));

        this->telemetry->addLine(utils::sprintf(
            "theta = %.2f", this->robot->odometry->position[2] / M_PI * 180
        ));

        this->telemetry->addLine();

        this->telemetry->addLine(utils::sprintf(
            "vx = %.2f", velocity[0] / ODOMETRY_TICKS_PER_CM
        ));

        this->telemetry->addLine(utils::sprintf(
            "vy = %.2f", velocity[1] / ODOMETRY_TICKS_PER_CM
        ));

        this->telemetry->addLine(utils::sprintf(
            "v_ang = %.2f", velocity[2] / M_PI * 180
        ));

        this->telemetry->addLine();
        
        this->telemetry->addLine(utils::sprintf(
            "measurements taken = %zu", powers.size()
        ));

        this->telemetry->addLine(utils::sprintf(
            "runtime = %.2fs", elapsed.count()
        ));

        this->telemetry->update();

        // DRIVING
        int full_phase = 5000;
        double phase = std::sin(
            (int) (elapsed.count() * 1000) % full_phase / (double) full_phase *
            2 * M_PI
        );
        double power = phase * 0.3;

        this->robot->drivetrain->drive(maths::vec3{power, 0.0, 0.0});
    
        // SAVING MEASUREMENTS
        powers.push_back(power);
        velocities.push_back(std::hypot(
            velocity[0] / (ODOMETRY_TICKS_PER_CM * 100.0),
            velocity[1] / (ODOMETRY_TICKS_PER_CM * 100.0)
        )); // ms-1
    }

    this->robot->drivetrain->drive(maths::vec3{0.0, 0.0, 0.0});

    // COMPUTE
    maths::mat powers_mat(powers.size(), 1);
    maths::mat mm_mat(powers.size(), 2);

    for (int i = 0; i < powers_mat.get_rows(); i++) {
        powers_mat[i][0] = std::abs(powers[i]);

        mm_mat[i][0] = 1;
        mm_mat[i][1] = velocities[i];
    }

    auto mm_transpose = mm_mat.transpose(); // X'
    auto mm_square = mm_transpose * mm_mat; // X'X
    auto mm_square_inv = mm_square.inverse(); // (X'X)^-1
    
    // Y = XK
    // X'Y = X'XK
    // (X'X)^-1 X' Y = K

    auto computed = mm_square_inv * mm_transpose * powers_mat;

    this->telemetry->addLine(utils::sprintf(
        "measurements taken = %zu", powers.size()
    ));

    this->telemetry->addLine(utils::sprintf(
        "runtime = %.2fs", elapsed.count()
    ));

    this->telemetry->addLine();
    this->telemetry->addLine("computed =");

    for (int row = 0; row < computed.get_rows(); row++) {
        std::string row_text = "[";

        for (int col = 0; col < computed.get_cols(); col++) {
            row_text += std::to_string(computed[row][col]) + ", ";
        }

        row_text = row_text.substr(0, row_text.size() - 2) + "]";
        this->telemetry->addLine(row_text);
    }

    this->telemetry->update();

    while (this->opModeIsActive()) { /* HALT */ }
}
