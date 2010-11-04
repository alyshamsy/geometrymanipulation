#include "Matrix.h"
#include <iostream>
#include <math.h>

using namespace std;

/*
This is the default constructor of the matrix class which takes in 3 parameters initial value, number of rows and columns.
The default value of these are:
- initial value = 0.0
- rows = 3
- columns = 3

The method uses the parameters provided to generate a 2D array on the heap
*/
Matrix::Matrix(double init_value, int rows, int columns):
init_value(init_value),
rows(rows),
columns(columns) {
	matrix = new double* [rows];
	for(int i = 0; i < rows; i++) {
		matrix[i] = new double[columns];
		for(int j = 0; j < columns; j++)
			matrix[i][j] = init_value;
	}
}

/*
This is the destructor which deletes the 2D array
*/
Matrix::~Matrix() {
	for(int i = 0; i < rows; i++) 
		delete [] matrix[i];

	delete [] matrix;
	matrix = NULL;
}

/*
This is the copy constructor which copies the contents of the source matrix to the local matrix
*/
Matrix::Matrix(const Matrix& src):
rows(src.rows), columns(src.columns), matrix(new double*[src.rows])
{
	for(int i = 0; i < rows; ++i) {
		matrix[i] = new double[columns];
		for(int j = 0; j < columns; ++j) {
			matrix[i][j] = src.matrix[i][j];
		}
	}
}

/*
set the matrix element to the value provided at the row and column values
*/
void Matrix::set_matrix_element(int row, int column, double value) {
	matrix[row][column] = value;
}

/*
get the matrix element value from the row and column values provided
*/
double Matrix::get_matrix_element(int row, int column) {
	return (matrix[row][column]);
}

/*
The assignment operator is used to equate the local matrix to the value provided by the parameter and returns the local matrix which is the matrix on the left hand side.

The operation clears the local matrix 2D array and creates a new matrix with the rows and columns values of the parameter matrix and assigns the values of rhs into this
*/
Matrix& Matrix::operator=(const Matrix& rhs) {
	if(this == &rhs)
		return (*this);

	for(int i = 0; i < rows; i++) {
		delete [] matrix[i];
	}
	delete [] matrix;

	matrix = new double* [rhs.rows];
	for(int i = 0; i < rhs.rows; i++) {
		matrix[i] = new double[rhs.columns];
	}

	for(int i = 0; i < rhs.rows; i++) {
		for(int j = 0; j < rhs.columns; j++)
			matrix[i][j] = rhs.matrix[i][j];
	}

	return (*this);
}