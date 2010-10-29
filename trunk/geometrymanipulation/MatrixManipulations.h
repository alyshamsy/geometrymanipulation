#include "Matrix.h"
#include "Vertex.h"
#include "VectorManipulations.h"

class MatrixManipulations {
public:
	MatrixManipulations();
	~MatrixManipulations();

	bool is_matrix_square(Matrix& A);
	Matrix generate_square_matrix(Matrix& current_matrix);
	Matrix generate_identity_matrix(int size);
	Matrix generate_row_vector(Vertex& current_vertex);
	Matrix generate_column_vector(Vertex& current_vertex);
	Matrix get_matrix_transpose(Matrix& current_matrix);
	double get_dot_product(Matrix& A, Matrix& B);
	Matrix get_cross_product(Matrix&A, Matrix& B);

	friend Matrix operator+(Matrix& A, Matrix& B);
	friend Matrix operator-(Matrix& A, Matrix& B);
	friend Matrix operator*(Matrix& A, Matrix& B);

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