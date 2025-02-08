#pragma once
#include <memory>

namespace maths {
    using vec2 = double[2];
    using vec3 = double[3];

    class mat {
        int rows;
        int cols;

        std::unique_ptr<double[]> data;
    public:
        mat(int rows, int cols);

        [[nodiscard]] int get_rows() const;
        [[nodiscard]] int get_cols() const;

        double *operator[](int row);
        const double *operator[](int row) const;
    };
}
