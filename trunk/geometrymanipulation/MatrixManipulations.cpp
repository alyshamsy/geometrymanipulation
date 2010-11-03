#include "MatrixManipulations.h"
#include <iostream>

#define PI 3.14159265
using namespace std;

MatrixManipulations::MatrixManipulations() {
	manipulated_vector = new VectorManipulations();
}

MatrixManipulations::~MatrixManipulations() {
	delete manipulated_vector;
	manipulated_vector = NULL;
}

bool MatrixManipulations::is_matrix_square(Matrix& A) {
	if(A.get_rows() == A.get_columns())
		return true;
	else
		return false;
}

Matrix MatrixManipulations::generate_square_matrix(Matrix& current_matrix) {
	int number_of_rows = current_matrix.get_rows();
	int number_of_columns = current_matrix.get_columns();

	int size = min(number_of_rows, number_of_columns);
	
	Matrix square_matrix;
	
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++)
			square_matrix.set_matrix_element(i, j, current_matrix.get_matrix_element(i, j));
	}

	return square_matrix;
}

Matrix MatrixManipulations::generate_identity_matrix(int size) {
	Matrix identity_matrix(0.0, size, size);

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(i == j)
				identity_matrix.set_matrix_element(i, j, 1);
		}
	}

	return identity_matrix;
}

Matrix MatrixManipulations::generate_row_vector(Vertex& current_vertex, int size) {
	Matrix row_vector(0.0, 1, size);

	row_vector.set_matrix_element(0, 0, current_vertex.x);
	row_vector.set_matrix_element(0, 1, current_vertex.y);
	row_vector.set_matrix_element(0, 2, current_vertex.z);

	if(size == 4)
		row_vector.set_matrix_element(0, 3, 1.0);

	return row_vector;
}

Matrix MatrixManipulations::generate_column_vector(Vertex& current_vertex, int size) {
	Matrix column_vector(0.0, size, 1);

	column_vector.set_matrix_element(0, 0, current_vertex.x);
	column_vector.set_matrix_element(1, 0, current_vertex.y);
	column_vector.set_matrix_element(2, 0, current_vertex.z);

	if(size == 4)
		column_vector.set_matrix_element(3, 0, 1.0);

	return column_vector;
}

Matrix MatrixManipulations::get_matrix_transpose(Matrix& current_matrix) {
	int rows = current_matrix.get_rows();
	int columns = current_matrix.get_columns();
	Matrix transpose(0.0, rows, columns);

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++)
			transpose.set_matrix_element(i, j, current_matrix.get_matrix_element(j, i));
	}

	return transpose;
}

double MatrixManipulations::get_dot_product(Matrix& A, Matrix& B) {
	double dot_product = 0.0;
	int rows = A.get_rows();
	int columns = A.get_columns();

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++)
			dot_product += A.get_matrix_element(i, j) * B.get_matrix_element(j, i);
	}

	return dot_product;
}

Matrix MatrixManipulations::get_cross_product(Matrix&A, Matrix& B) {
	Matrix cross_product(0.0, 3, 1);

	double element = (A.get_matrix_element(0, 1)*B.get_matrix_element(0, 2)) - (A.get_matrix_element(0, 2)*B.get_matrix_element(0, 1));
	cross_product.set_matrix_element(0, 0, element);

	element = (A.get_matrix_element(0, 2)*B.get_matrix_element(0, 0)) - (A.get_matrix_element(0, 0)*B.get_matrix_element(0, 2));
	cross_product.set_matrix_element(0, 0, element);

	element = (A.get_matrix_element(0, 2)*B.get_matrix_element(0, 0)) - (A.get_matrix_element(0, 0)*B.get_matrix_element(0, 2));
	cross_product.set_matrix_element(0, 0, element);

	return cross_product;
}

Matrix operator+(Matrix& A, Matrix& B) {
	int rows_a = A.get_rows();
	int columns_a = A.get_columns();

	int rows_b = B.get_rows();
	int columns_b = B.get_columns();

	//if(rows_a == rows_b && columns_a == columns_b) 
	Matrix added_matrix(0.0, rows_a, columns_a);

	for(int i = 0; i < rows_a; i++) {
		for(int j = 0; j < columns_a; j++)
			added_matrix.set_matrix_element(i, j, A.get_matrix_element(i, j)+B.get_matrix_element(i, j));
	}

	return added_matrix;
}

Matrix operator-(Matrix& A, Matrix& B) {
	int rows_a = A.get_rows();
	int columns_a = A.get_columns();

	int rows_b = B.get_rows();
	int columns_b = B.get_columns();

	//if(rows_a == rows_b && columns_a == columns_b) 
	Matrix subtracted_matrix(0.0, rows_a, columns_a);

	for(int i = 0; i < rows_a; i++) {
		for(int j = 0; j < columns_a; j++)
			subtracted_matrix.set_matrix_element(i, j, A.get_matrix_element(i, j)-B.get_matrix_element(i, j));
	}

	return subtracted_matrix;
}

Matrix operator*(Matrix& A, Matrix& B) {
	int rows_a = A.get_rows();
	int columns_a = A.get_columns();

	int rows_b = B.get_rows();
	int columns_b = B.get_columns();

	//if(columns_a == rows_b) 
	double element = 0.0;
	Matrix multiplied_matrix(0.0, rows_a, columns_b);

	for(int i = 0; i < rows_a; i++) {
		for(int j = 0; j <columns_b; j++) {
			for(int k = 0; k < columns_a; k++) {
				element += A.get_matrix_element(i, k) * B.get_matrix_element(k, j);
			}
			multiplied_matrix.set_matrix_element(i, j, element);
			element = 0.0;
		}	
	}

	return multiplied_matrix;
}

void MatrixManipulations::print_matrix(Matrix& A) {
	for(int i = 0; i < A.get_rows(); i++) {
		for(int j = 0; j < A.get_columns(); j++) {
			cout << A.get_matrix_element(i, j) << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}

Vertex MatrixManipulations::generate_vertex_from_matrix(Matrix& A) {
	Vertex converted_vertex;
	double h = 1;

	if(A.get_rows() == 1) {
		if(A.get_columns() == 4)
			h = A.get_matrix_element(0, 3);

		converted_vertex.x = A.get_matrix_element(0, 0)/h;
		converted_vertex.y = A.get_matrix_element(0, 1)/h;
		converted_vertex.z = A.get_matrix_element(0, 2)/h;
	} else {
		if(A.get_rows() == 4)
			h = A.get_matrix_element(3, 0);

		converted_vertex.x = A.get_matrix_element(0, 0)/h;
		converted_vertex.y = A.get_matrix_element(1, 0)/h;
		converted_vertex.z = A.get_matrix_element(2, 0)/h;
	}

	return converted_vertex;
}

void MatrixManipulations::do_uniform_scaling(int scaling_factor, Matrix& A) {
	int rows = A.get_rows();
	A = get_uniform_scaling_matrix(rows, scaling_factor)*A;
}

void MatrixManipulations::do_matrix_translation(Vertex& translating_vector, Matrix& A) {
	int rows = A.get_rows();

	A = get_translation_matrix(rows, translating_vector)*A;
}

void MatrixManipulations::do_axis_rotation(char axis, double angle, Matrix& A) {
	int rows = A.get_rows();

	A = get_axis_rotation_matrix(rows, axis, angle)*A;
}

void MatrixManipulations::do_free_rotation(Vertex& arbitrary_axis, double angle, Matrix& A) {
	int rows = A.get_rows();

	A = get_free_rotation_matrix(rows, arbitrary_axis, angle)*A;
}

Matrix MatrixManipulations::get_uniform_scaling_matrix(int size, int scaling_factor) {
	Matrix scaling_matrix(0.0, size, size);

	if(size == 4)
		scaling_matrix.set_matrix_element(3, 3, 1.0);

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(i == j)
				scaling_matrix.set_matrix_element(i, j, scaling_factor);
		}
	}

	return scaling_matrix;
}

Matrix MatrixManipulations::get_translation_matrix(int size, Vertex& translating_vector) {
	Matrix translation_matrix = generate_identity_matrix(size);

	translation_matrix.set_matrix_element(0, 3, translating_vector.x);
	translation_matrix.set_matrix_element(1, 3, translating_vector.y);
	translation_matrix.set_matrix_element(2, 3, translating_vector.z);

	return translation_matrix;
}

Matrix MatrixManipulations::get_axis_rotation_matrix(int size, char axis, double angle) {
	Matrix axis_rotation_matrix(0.0, size, size);
	angle = angle*(PI/180);
	double C = cos(angle), S = sin(angle);

	if(size == 4)
		axis_rotation_matrix.set_matrix_element(3, 3, 1.0);
	
	if(axis == 'x') {
		axis_rotation_matrix.set_matrix_element(0, 0, 1.0);
		axis_rotation_matrix.set_matrix_element(1, 1, C);
		axis_rotation_matrix.set_matrix_element(1, 2, -S);
		axis_rotation_matrix.set_matrix_element(2, 1, S);
		axis_rotation_matrix.set_matrix_element(2, 2, C);

		return axis_rotation_matrix;
	} else if(axis == 'y') {
		axis_rotation_matrix.set_matrix_element(0, 0, C);
		axis_rotation_matrix.set_matrix_element(0, 2, S);
		axis_rotation_matrix.set_matrix_element(1, 1, 1.0);
		axis_rotation_matrix.set_matrix_element(2, 0, -S);
		axis_rotation_matrix.set_matrix_element(2, 2, C);

		return axis_rotation_matrix;
	} else {
		axis_rotation_matrix.set_matrix_element(0, 0, C);
		axis_rotation_matrix.set_matrix_element(0, 1, -S);
		axis_rotation_matrix.set_matrix_element(1, 0, S);
		axis_rotation_matrix.set_matrix_element(1, 1, C);
		axis_rotation_matrix.set_matrix_element(2, 2, 1.0);

		return axis_rotation_matrix;
	}
}

Matrix MatrixManipulations::get_free_rotation_matrix(int size, Vertex& arbitrary_axis, double angle) {
	Matrix free_rotation_matrix(0.0, size, size);
	angle = angle*(PI/180);

	if(size == 4)
		free_rotation_matrix.set_matrix_element(3, 3, 1.0);

	Vertex unit_arbitrary_axis_vector;

	unit_arbitrary_axis_vector = manipulated_vector->get_unit_vector(arbitrary_axis);

	double C = cos(angle), S = sin(angle);
	double x = unit_arbitrary_axis_vector.x, y = unit_arbitrary_axis_vector.y, z = unit_arbitrary_axis_vector.z;

	free_rotation_matrix.set_matrix_element(0, 0, C + x*x*(1 - C));
	free_rotation_matrix.set_matrix_element(0, 1, x*y*(1 - C) - z*S);
	free_rotation_matrix.set_matrix_element(0, 2, x*z*(1 - C) + y*S);
	free_rotation_matrix.set_matrix_element(1, 0, x*y*(1 - C) + z*S);
	free_rotation_matrix.set_matrix_element(1, 1, C + y*y*(1 - C));
	free_rotation_matrix.set_matrix_element(1, 2, y*z*(1 - C) - x*S);
	free_rotation_matrix.set_matrix_element(2, 0, x*z*(1 - C) - y*S);
	free_rotation_matrix.set_matrix_element(2, 1, y*z*(1 - C) + x*S);
	free_rotation_matrix.set_matrix_element(2, 2, C + z*z*(1 - C));

	return free_rotation_matrix;
}