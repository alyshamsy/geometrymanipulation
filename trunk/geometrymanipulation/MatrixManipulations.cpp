#include "MatrixManipulations.h"
#include <iostream>

#define PI 3.14159265
using namespace std;

/*
the constructor allocates memory to manipulated_vector on the heap
*/
MatrixManipulations::MatrixManipulations() {
	manipulated_vector = new VectorManipulations();
}

/*
The destructor deletes the values pointed to by the pointer and NULLs the pointer
*/
MatrixManipulations::~MatrixManipulations() {
	delete manipulated_vector;
	manipulated_vector = NULL;
}

/*
Generate the identity matrix based on the size provided by checking if the row value equals the column value and setting that to 1
*/
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

/*
Generates a row vector from a vertex and a size provided. 

The advantage of adding the size it to do combined matrix multiplication using homogenous coordinates
*/
Matrix MatrixManipulations::generate_row_vector(Vertex& current_vertex, int size) {
	Matrix row_vector(0.0, 1, size);

	row_vector.set_matrix_element(0, 0, current_vertex.x);
	row_vector.set_matrix_element(0, 1, current_vertex.y);
	row_vector.set_matrix_element(0, 2, current_vertex.z);

	if(size == 4)
		row_vector.set_matrix_element(0, 3, 1.0);

	return row_vector;
}

/*
Generates a column vector from a vertex and a size provided. 

The advantage of adding the size it to do combined matrix multiplication using homogenous coordinates
*/
Matrix MatrixManipulations::generate_column_vector(Vertex& current_vertex, int size) {
	Matrix column_vector(0.0, size, 1);

	column_vector.set_matrix_element(0, 0, current_vertex.x);
	column_vector.set_matrix_element(1, 0, current_vertex.y);
	column_vector.set_matrix_element(2, 0, current_vertex.z);

	if(size == 4)
		column_vector.set_matrix_element(3, 0, 1.0);

	return column_vector;
}

/*
Gets the transpose of the matrix provided, by replacing the values at i, j by the values at j, i
*/
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

/*
calculates the dot product of 2 matrices and return it as a double value
*/
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

/*
calculate the cross product of the 2 matrices
*/
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

/*
The addition operation adds the 2 matrices by adding each element of the matrices at the same location. It assumes that the matrices being passed in are of the same dimension. 
Those checks are done before this method is called
*/
Matrix operator+(Matrix& A, Matrix& B) {
	int rows_a = A.get_rows();
	int columns_a = A.get_columns();

	int rows_b = B.get_rows();
	int columns_b = B.get_columns();
 
	Matrix added_matrix(0.0, rows_a, columns_a);

	for(int i = 0; i < rows_a; i++) {
		for(int j = 0; j < columns_a; j++)
			added_matrix.set_matrix_element(i, j, A.get_matrix_element(i, j)+B.get_matrix_element(i, j));
	}

	return added_matrix;
}

/*
The subtraction operation subtracts the 2 matrices by subtracting each element of the matrices at the same location. It assumes that the matrices being passed in are of the same dimension. 
Those checks are done before this method is called
*/
Matrix operator-(Matrix& A, Matrix& B) {
	int rows_a = A.get_rows();
	int columns_a = A.get_columns();

	int rows_b = B.get_rows();
	int columns_b = B.get_columns();

	Matrix subtracted_matrix(0.0, rows_a, columns_a);

	for(int i = 0; i < rows_a; i++) {
		for(int j = 0; j < columns_a; j++)
			subtracted_matrix.set_matrix_element(i, j, A.get_matrix_element(i, j)-B.get_matrix_element(i, j));
	}

	return subtracted_matrix;
}

/*
The multiplication operation multiplies the 2 matrices. It assumes that the matrices being passed in are of the correct dimension i.e. the number of rows of A should be equal to the number of columns of B. 
Those checks are done before this method is called
*/
Matrix operator*(Matrix& A, Matrix& B) {
	int rows_a = A.get_rows();
	int columns_a = A.get_columns();

	int rows_b = B.get_rows();
	int columns_b = B.get_columns();

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

/*
This method prints the matrix provided
*/
void MatrixManipulations::print_matrix(Matrix& A) {
	for(int i = 0; i < A.get_rows(); i++) {
		for(int j = 0; j < A.get_columns(); j++) {
			cout << A.get_matrix_element(i, j) << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}

/*
generates a vertex from a matrix.

It checks whether the matrix is a row vector or a column vector and how many rows or columns it has.
If there are 4 rows or 4 columns, it divides the value on the first three row or columns by the value of the 4th row or column
*/
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

/*
This performs uniform scaling if provided a scaling factor and a Matrix
*/
void MatrixManipulations::do_uniform_scaling(int scaling_factor, Matrix& A) {
	int rows = A.get_rows();
	A = get_uniform_scaling_matrix(rows, scaling_factor)*A;
}

/*
This method generates the uniform scaling matrix by using the scaling factor and the size of the matrix. If the size of the matrix is 4, it sets the element at 3,3 to be 1
*/
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

/*
This performs matrix translation when provided a translating vector and a matrix
*/
void MatrixManipulations::do_matrix_translation(Vertex& translating_vector, Matrix& A) {
	int rows = A.get_rows();

	A = get_translation_matrix(rows, translating_vector)*A;
}

/*
This method generates the translation matrix by using the translating vector and the size of the matrix. 
It assumes multiplication by a column vector hence assigns the values of the translating vector at the positions 0,3 1,3 and 2,3 of the matrix
*/
Matrix MatrixManipulations::get_translation_matrix(int size, Vertex& translating_vector) {
	Matrix translation_matrix = generate_identity_matrix(size);

	translation_matrix.set_matrix_element(0, 3, translating_vector.x);
	translation_matrix.set_matrix_element(1, 3, translating_vector.y);
	translation_matrix.set_matrix_element(2, 3, translating_vector.z);

	return translation_matrix;
}

/*
This performs rotation about the x, y or z axis using the axis, angle and Matrix values
*/
void MatrixManipulations::do_axis_rotation(char axis, double angle, Matrix& A) {
	int rows = A.get_rows();

	A = get_axis_rotation_matrix(rows, axis, angle)*A;
}

/*
This generates the axis rotation matrix based on the size and the angle and returns the matrix corresponding to the axis provided.

If the size of the matrix is 4, it sets the bottom right (3,3) element as 1.0 and sets the rest of the values of the matrix based on the axis being rotated by. The angle is converted from degrees to radians
*/
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

/*
this performs rotation about an arbitrary axis on the matrix
*/
void MatrixManipulations::do_free_rotation(Vertex& arbitrary_axis, double angle, Matrix& A) {
	int rows = A.get_rows();

	A = get_free_rotation_matrix(rows, arbitrary_axis, angle)*A;
}

/*
this generates the arbitrary axis rotation matrix based on the vertex and the angle. 

It unitizes the vector being passed in before using it and converts the angle from degrees to radians
*/
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