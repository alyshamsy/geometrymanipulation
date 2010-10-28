#include "Matrix.h"
#include <iostream>
#include <math.h>

using namespace std;

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

Matrix::~Matrix() {
	for(int i = 0; i < rows; i++) 
		delete [] matrix[i];

	delete [] matrix;
	matrix = NULL;
}

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

void Matrix::set_matrix_element(int row, int column, double value) {
	matrix[row][column] = value;
}

double Matrix::get_matrix_element(int row, int column) {
	return (matrix[row][column]);
}

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