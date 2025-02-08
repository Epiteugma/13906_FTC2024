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
