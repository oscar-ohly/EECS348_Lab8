#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Function to read matrix from file
void readMatricesFromFile(const string& filename, int& N, vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file");
    }

    file >> N; // Read matrix size

    // Read first matrix
    matrix1.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> matrix1[i][j];
        }
    }

    // Read second matrix
    matrix2.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> matrix2[i][j];
        }
    }

    file.close();
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << setw(3) << val << " ";
        }
        cout << endl;
    }
}

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& m1, const vector<vector<int>>& m2) {
    int N = m1.size();
    vector<vector<int>> result(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}

// Corrected function to multiply two matrices
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& m1, const vector<vector<int>>& m2) {
    int N = m1.size();
    vector<vector<int>> result(N, vector<int>(N, 0));
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}

// Function to get diagonal sums
pair<int, int> getDiagonalSums(const vector<vector<int>>& matrix) {
    int N = matrix.size();
    int mainSum = 0, secondarySum = 0;
    for (int i = 0; i < N; ++i) {
        mainSum += matrix[i][i];
        secondarySum += matrix[i][N - 1 - i];
    }
    return {mainSum, secondarySum};
}

// Function to swap rows
void swapRows(vector<vector<int>>& matrix, int row1, int row2) {
    int N = matrix.size();
    if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N) {
        throw out_of_range("Row indices out of bounds");
    }
    swap(matrix[row1], matrix[row2]);
}

// Function to swap columns
void swapColumns(vector<vector<int>>& matrix, int col1, int col2) {
    int N = matrix.size();
    if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N) {
        throw out_of_range("Column indices out of bounds");
    }
    for (int i = 0; i < N; ++i) {
        swap(matrix[i][col1], matrix[i][col2]);
    }
}

// Function to update matrix element
void updateElement(vector<vector<int>>& matrix, int row, int col, int value) {
    int N = matrix.size();
    if (row < 0 || row >= N || col < 0 || col >= N) {
        throw out_of_range("Indices out of bounds");
    }
    matrix[row][col] = value;
}

int main() {
    try {
        int N;
        vector<vector<int>> matrix1, matrix2;
        
        // Read matrices from file
        readMatricesFromFile("input.txt", N, matrix1, matrix2);
        
        cout << "Matrix 1:" << endl;
        printMatrix(matrix1);
        
        cout << "\nMatrix 2:" << endl;
        printMatrix(matrix2);
        
        // Matrix addition
        cout << "\nMatrix Addition Result:" << endl;
        vector<vector<int>> addResult = addMatrices(matrix1, matrix2);
        printMatrix(addResult);
        
        // Correct matrix multiplication
        cout << "\nMatrix Multiplication Result:" << endl;
        vector<vector<int>> multResult = multiplyMatrices(matrix1, matrix2);
        printMatrix(multResult);
        
        // Diagonal sums
        auto [mainSum, secondarySum] = getDiagonalSums(matrix1);
        cout << "\nMatrix 1 Diagonal Sums:" << endl;
        cout << "Main Diagonal: " << mainSum << endl;
        cout << "Secondary Diagonal: " << secondarySum << endl;
        
        // Swap rows (swap row 0 and row 1)
        cout << "\nAfter swapping rows 0 and 1 of Matrix 1:" << endl;
        vector<vector<int>> rowSwapMatrix = matrix1;
        swapRows(rowSwapMatrix, 0, 1);
        printMatrix(rowSwapMatrix);
        
        // Swap columns (swap column 0 and column 1)
        cout << "\nAfter swapping columns 0 and 1 of Matrix 1:" << endl;
        vector<vector<int>> colSwapMatrix = matrix1;
        swapColumns(colSwapMatrix, 0, 1);
        printMatrix(colSwapMatrix);
        
        // Update element (set element at 0,0 to 99)
        cout << "\nAfter updating element at (0,0) to 99 in Matrix 1:" << endl;
        vector<vector<int>> updateMatrix = matrix1;
        updateElement(updateMatrix, 0, 0, 99);
        printMatrix(updateMatrix);
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}