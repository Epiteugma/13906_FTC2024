#include "maths.h"

maths::mat::mat(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;

    this->data = std::unique_ptr<double[]>(new double[rows * cols]);

    for (int i = 0; i < rows * cols; i++) {
        this->data[i] = 0;
    }
}

int maths::mat::get_rows() const {
    return this->rows;
}

int maths::mat::get_cols() const {
    return this->cols;
}

double *maths::mat::operator[](int row) {
    return this->data.get() + row * this->cols;
}

const double *maths::mat::operator[](int row) const {
    return this->data.get() + row * this->cols;
}

maths::mat maths::mat::operator*(maths::mat &other) const {
    mat out(this->rows, other.get_cols());

    if (this->cols != other.get_rows()) return out;

    for (int i = 0; i < out.get_rows() * out.get_cols(); i++) {
        int row = i / out.get_cols();
        int col = i % out.get_cols();

        double out_value = 0.0;

        for (int j = 0; j < this->cols; j++) {
            out_value += this->data[row * this->cols + j] * other[j][col];
        }

        out[row][col] = out_value;
    }

    return out;
}

maths::mat maths::mat::inverse() {
    if (this->rows != this->cols) return {this->rows, this->cols};

    maths::mat augmented(this->rows, this->cols * 2);

    for (int i = 0; i < augmented.get_cols() * augmented.get_rows(); i++) {
        int row = i / augmented.get_cols();
        int col = i % augmented.get_cols();

        if (col < this->cols) {
            augmented[row][col] = this->data[row * this->cols + col];
        } else if (col - this->cols == row) {
            augmented[row][col] = 1.0;
        }
    }

    for (int i = 0; i < augmented.get_rows(); i++) {
        double pivot = augmented[i][i];

        for (int row = 0; row < augmented.get_rows(); row++) {
            if (row == i) continue;

            double mlt = -(augmented[row][i] / pivot);

            for (int col = 0; col < augmented.get_cols(); col++) {
                augmented[row][col] += augmented[i][col] * mlt;
            }
        }
    }

    mat out(this->rows, this->cols);

    for (int row = 0; row < augmented.get_rows(); row++) {
        double div = augmented[row][row];

        for (int col = 0; col < augmented.get_cols(); col++) {
            augmented[row][col] /= div;

            if (col >= this->cols) {
                out[row][col - this->cols] = augmented[row][col];
            }
        }
    }

    return out;
}

maths::mat maths::mat::transpose() {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"

    mat out(this->cols, this->rows);

#pragma clang diagnostic pop

    for (int i = 0; i < this->rows * this->cols; i++) {
        int row = i / this->cols;
        int col = i % this->cols;

        out[col][row] = this->data[row * this->cols + col];
    }

    return out;
}