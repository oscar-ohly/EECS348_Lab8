#include "matrix.hpp" //gets Matrix class from matrix.hpp
#include <fstream> //gets library containing file-reading operations
#include <iomanip> //gets library containing formatting options for output
#include <stdexcept> //gets library containing exception operations
#include <utility> //gets library containing operations for swapping values
#include <iostream> //gets standard C++ library

Matrix::Matrix(std::size_t N) : size(N), data(N, std::vector<int>(N, 0)) {} //creates constructor for nxn matrix

Matrix::Matrix(const std::vector<std::vector<int>>& nums) //(lines 10-11) creates constructor for existing vector
    : size(nums.size()), data(nums) {
    for (const auto& row : nums) { //runs for number of rows in matrix
        if (row.size() != size) { //runs if size of row doesn't equal size of matrix
            throw std::invalid_argument("Matrix must be square"); //throws error if sizes are unequal and if matrix isn't square
        } //ends if statement
    } //ends for loop
} //ends constructor

Matrix Matrix::readFromFile(const std::string& filename, std::size_t matrixNum) { //new func readFromFile that takes a file and an index of the matrix to read
    std::ifstream file(filename); //opens file with name filename and names it file
    if (!file.is_open()) { //runs if file can't open
        throw std::runtime_error("Unable to open file"); //throws error
    } //ends if statement

    std::size_t N; //initializes size N
    file >> N; //sets N to the first int of file

    for (std::size_t m = 0; m < matrixNum; ++m) { //runs until matrixNum starting at 0 and incrementing by 1
        for (std::size_t i = 0; i < N; ++i) { //runs from i=0 to N, which is the size of the matrix
            for (std::size_t j = 0; j < N; ++j) { //runs from j=0 to N, which is the size of the matrix
                int dummy; //creates dummy variable dummy
                file >> dummy; //sets each int equal to dummy variable
            } //ends for loop
        } //ends for loop
    } //ends for loop

    std::vector<std::vector<int>> matrixData(N, std::vector<int>(N)); //creates vector of vectors matrixData of size N
    for (std::size_t i = 0; i < N; ++i) { //runs from i=0 to N, which is the size of the matrix
        for (std::size_t j = 0; j < N; ++j) { //runs from j=0 to N, which is the size of the matrix
            if (!(file >> matrixData[i][j])) { //saves each int of file to matrixData, runs if statement if it can't
                throw std::runtime_error("Invalid matrix data in file"); //throws error because invalid data
            } //ends if statement
        } //ends for loop
    } //ends for loop

    return Matrix(matrixData); // returns matrix with matrixData
} //ends func definition

Matrix Matrix::operator+(const Matrix& rhs) const { //func operator+ that performs matrix addition between two matrices
    if (size != rhs.size) { //runs if one matrix isn't the same size as the other
        throw std::invalid_argument("Matrix dimensions must match for addition"); //throws error
    } //ends if statement

    Matrix result(size); //initializes new Matrix result
    for (std::size_t i = 0; i < size; ++i) { //runs size amount of times
        for (std::size_t j = 0; j < size; ++j) { //runs size amount of times
            result.data[i][j] = data[i][j] + rhs.data[i][j]; //adds each index of matrices together and saves value in Matrix result
        } //ends for loop
    } //ends for loop
    return result; //returns newly formed Matrix
} //ends func definition

Matrix Matrix::operator*(const Matrix& rhs) const { //func operator* that performs matrix multiplication between two matrices
    if (size != rhs.size) { //runs if one matrix isn't the same size as the other
        throw std::invalid_argument("Matrix dimensions must match for multiplication"); //throws error
    } //ends if statement

    Matrix result(size); //initializes new Matrix result
    for (std::size_t i = 0; i < size; ++i) { //runs size amount of times
        for (std::size_t j = 0; j < size; ++j) { //runs size amount of times
            result.data[i][j] = 0; //sets appropriate index of result Matrix to 0
            for (std::size_t k = 0; k < size; ++k) { //runs size amount of times
                result.data[i][j] += data[i][k] * rhs.data[k][j]; //multiplys rows of matrix one by cols of matrix two and saves data to result Matrix
            } //ends for loop
        } //ends for loop
    } //ends for loop
    return result; //returns final Matrix
} //ends func definition

void Matrix::set_value(std::size_t i, std::size_t j, int n) { //new func set_value that takes two indices and a value n
    if (i >= size || j >= size) { //checks if indices are out of range of matrix
        throw std::out_of_range("Matrix indices out of range"); //throws error
    } //ends if statement
    data[i][j] = n; //sets appropriate data point equal to n
} //ends func definition

int Matrix::get_value(std::size_t i, std::size_t j) const { //new func get_value that takes two indices
    if (i >= size || j >= size) { //checks if indices are out of range of matrix
        throw std::out_of_range("Matrix indices out of range"); //throws error
    } //ends if statement
    return data[i][j]; //returns value at specified indices
} //ends func definition

std::size_t Matrix::get_size() const { //new func get_size that returns size of matrix
    return size; //returns size of Matrix
} //ends func definition

int Matrix::sum_diagonal_major() const { //new func sum_diagonal_major that returns an int
    int sum = 0; //initializes int sum = 0
    for (std::size_t i = 0; i < size; ++i) { //runs size amount of times
        sum += data[i][i]; //adds values of indexes starting at upper left and moving diagonally down to bottom right
    } //ends for loop
    return sum; //returns int sum
} //ends func definition

int Matrix::sum_diagonal_minor() const { //new func sum_diagonal_minor that returns an int
    int sum = 0; //initializes int sum = 0
    for (std::size_t i = 0; i < size; ++i) { //runs size amount of times
        sum += data[i][size - 1 - i]; //adds values of indexes starting at upper right and moving diagonally down to bottom left
    } //ends for loop
    return sum; //returns int sum
} //ends func definition

void Matrix::swap_rows(std::size_t r1, std::size_t r2) { //new func swap_rows that takes two sizes r1 and r2 representing rows of a matrix
    if (r1 >= size || r2 >= size) { //checks if r1 and r2 are within matrix
        throw std::out_of_range("Row indices out of range"); //throws error
    } //ends if statement
    std::swap(data[r1], data[r2]); //swaps values in both rows
} //ends func definition

void Matrix::swap_cols(std::size_t c1, std::size_t c2) { //new func swap_cols that takes two sizes c1 and c2 representing cols of a matrix
    if (c1 >= size || c2 >= size) { //checks if c1 and c2 are within matrix
        throw std::out_of_range("Column indices out of range"); //throws error
    } //ends if statement
    for (std::size_t i = 0; i < size; ++i) { //runs size amount of times
        std::swap(data[i][c1], data[i][c2]); //swaps values in both cols
    } //ends for loop
} //ends func definition

void Matrix::print_matrix() const { //func print_matrix that prints matrix
    for (const auto& row : data) { //runs for as many iterations as there are rows
        for (int val : row) { //runs for as many values are in a row
            std::cout << std::setw(4) << val; //prints value spaced exactly 4 characters apart despite value in matrix
        } //ends for loop
        std::cout << '\n'; //starts new line
    } //ends for loop
} //ends func definition