#ifndef Matrix_Manipulation_H
#define Matrix_Manipulation_H

#include "Matrix.h"
#include "Vertex.h"
#include "VectorManipulations.h"

/*
This class is used to do all matrix calculations and geometry manipulations

There are methods to:
- generate the identity matrix
- generate row and column vector matrices from vertices
- get matrix transpose
- get the dot and cross products between 2 matrices
- do matrix translation
- do free rotation
- do axis rotation
- do uniform scaling
- also to generate a vertex from a matrix

There are also methods to perform addition, subtraction and multiplication operations
*/

class MatrixManipulations {
public:
	MatrixManipulations();
	~MatrixManipulations();

	bool is_matrix_square(Matrix& A);
	Matrix generate_square_matrix(Matrix& current_matrix);
	Matrix generate_identity_matrix(int size);
	Matrix generate_row_vector(Vertex& current_vertex, int size);
	Matrix generate_column_vector(Vertex& current_vertex, int size);
	Matrix get_matrix_transpose(Matrix& current_matrix);
	double get_dot_product(Matrix& A, Matrix& B);
	Matrix get_cross_product(Matrix&A, Matrix& B);

	friend Matrix operator+(Matrix& A, Matrix& B);
	friend Matrix operator-(Matrix& A, Matrix& B);
	friend Matrix operator*(Matrix& A, Matrix& B);

	void print_matrix(Matrix& A);

	Vertex generate_vertex_from_matrix(Matrix& A);

	void do_uniform_scaling(int scaling_factor, Matrix& A);
	void do_matrix_translation(Vertex& translating_vector, Matrix& A);
	void do_axis_rotation(char axis, double angle, Matrix& A);
	void do_free_rotation(Vertex& arbitrary_axis, double angle, Matrix& A);

	Matrix get_uniform_scaling_matrix(int size, int scaling_factor);
	Matrix get_translation_matrix(int size, Vertex& translating_vector);
	Matrix get_axis_rotation_matrix(int size, char axis, double angle);
	Matrix get_free_rotation_matrix(int size, Vertex& arbitrary_axis, double angle);
private:
	VectorManipulations* manipulated_vector;
};
#endif