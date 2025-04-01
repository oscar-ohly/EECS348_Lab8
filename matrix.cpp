#include "matrix.hpp"
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <utility>

Matrix::Matrix(const std::vector<std::vector<int>>& nums) : data(nums) {
    int size = nums.size();
    // Verify matrix is square
    for (const auto& row : nums) {
        if (row.size() != size) {
            throw std::invalid_argument("Matrix must be square");
        }
    }
}

Matrix Matrix::readFromFile(const std::string& filename, std::size_t matrixNum) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    std::size_t N;
    file >> N;

    // Skip lines for previous matrices
    for (std::size_t m = 0; m < matrixNum; ++m) {
        for (std::size_t i = 0; i < N; ++i) {
            std::string line;
            std::getline(file >> std::ws, line);
        }
    }

    // Read current matrix
    std::vector<std::vector<int>> matrixData(N, std::vector<int>(N));
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (!(file >> matrixData[i][j])) {
                throw std::runtime_error("Invalid matrix data in file");
            }
        }
    }

    return Matrix(matrixData);
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    if (size != rhs.size) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix result(size);
    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            result.data[i][j] = data[i][j] + rhs.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    if (size != rhs.size) {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }

    Matrix result(size);
    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            for (std::size_t k = 0; k < size; ++k) {
                result.data[i][j] += data[i][k] * rhs.data[k][j];
            }
        }
    }
    return result;
}

void Matrix::set_value(std::size_t i, std::size_t j, int n) {
    if (i >= size || j >= size) {
        throw std::out_of_range("Matrix indices out of range");
    }
    data[i][j] = n;
}

int Matrix::get_value(std::size_t i, std::size_t j) const {
    if (i >= size || j >= size) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data[i][j];
}

std::size_t Matrix::get_size() const {
    return size;
}

int Matrix::sum_diagonal_major() const {
    int sum = 0;
    for (std::size_t i = 0; i < size; ++i) {
        sum += data[i][i];
    }
    return sum;
}

int Matrix::sum_diagonal_minor() const {
    int sum = 0;
    for (std::size_t i = 0; i < size; ++i) {
        sum += data[i][size - 1 - i];
    }
    return sum;
}

void Matrix::swap_rows(std::size_t r1, std::size_t r2) {
    if (r1 >= size || r2 >= size) {
        throw std::out_of_range("Row indices out of range");
    }
    std::swap(data[r1], data[r2]);
}

void Matrix::swap_cols(std::size_t c1, std::size_t c2) {
    if (c1 >= size || c2 >= size) {
        throw std::out_of_range("Column indices out of range");
    }
    for (std::size_t i = 0; i < size; ++i) {
        std::swap(data[i][c1], data[i][c2]);
    }
}

Matrix::Matrix(std::size_t N) : size(N), data(N, std::vector<int>(N, 0)) {}

void Matrix::print_matrix() const {
    for (const auto& row : data) {
        for (int val : row) {
            std::cout << std::setw(4) << val;
        }
        std::cout << '\n';
    }
}

