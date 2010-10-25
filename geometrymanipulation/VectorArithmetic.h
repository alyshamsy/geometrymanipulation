#include "Vertex.h"

class VectorArithmetic {
public:
	VectorArithmetic();
	~VectorArithmetic();
	Vertex* get_vector_negation(Vertex* A);
	double get_vector_magnitude(Vertex* A);
	Vertex* do_vector_addition(Vertex* A, Vertex* B);
	Vertex* do_vector_subtraction(Vertex* A, Vertex* B);
	Vertex* do_scalar_multiplication(double scalar, Vertex* A);
	Vertex* get_unit_vector(Vertex* A);
	double get_dot_product(Vertex* A, Vertex* B);
	double get_angle_between_vectors(Vertex* A, Vertex* B);
	Vertex* get_cross_product(Vertex* A, Vertex* B);
	Vertex* get_normal_vector(Vertex* A, Vertex* B);
	Vertex* get_normal_vector(Vertex* A, Vertex* B, Vertex* C);
};