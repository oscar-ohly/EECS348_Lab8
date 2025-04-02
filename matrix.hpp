#ifndef __MATRIX_HPP__ //checks if __MATRIX_HPP__ is defined
#define __MATRIX_HPP__ //defines __MATRIX_HPP__

#include <cstddef> //provides size and pointer utilities
#include <vector> //provides array creation utilities
#include <string> //provides string manipulation utilities
#include <iostream> //provides standard C++ library

class Matrix { //defines class Matrix
private: //contains code not accessible outside class definition
    std::size_t size; //stores size of matrix, no memory constraints
    std::vector<std::vector<int>> data; //stores matrix data in a vector of vectors

public: //contains code accessible outside class definition
    explicit Matrix(std::size_t N); //matrix can only be created with std::size_t parameter
    explicit Matrix(const std::vector<std::vector<int>>& nums); //matrix can only be created with std::vector... parameter
    
    static Matrix readFromFile(const std::string& filename, std::size_t matrixNum); //defines func readFromFile that takes a string and size

    Matrix operator+(const Matrix& rhs) const; //defines func operator+ that takes a matrix and returns a matrix
    Matrix operator*(const Matrix& rhs) const; //defines func operator* that takes a matrix and returns a matrix
    void set_value(std::size_t i, std::size_t j, int n); //defines func set_value that takes two indices of a matrix and an int
    int get_value(std::size_t i, std::size_t j) const; //defines func get_value that takes two indices of a matrix
    std::size_t get_size() const; //defines func get_size that returns a matrix size
    int sum_diagonal_major() const; //defines func sum_diagonal_major that returns an int
    int sum_diagonal_minor() const; //defines func sum_diagonal_minor that returns an int
    void swap_rows(std::size_t r1, std::size_t r2); //defines func swap_rows that takes two sizes
    void swap_cols(std::size_t c1, std::size_t c2); //defines func swap_cols that takes two sizes
    void print_matrix() const; //defines func print_matrix
};

#endif //ends __MATRIX_HPP__ definition