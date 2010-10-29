#include "Vertex.h"

class VectorManipulations {
public:
	VectorManipulations();
	~VectorManipulations();

	double get_vector_magnitude(Vertex& A);
	double get_dot_product(Vertex& A, Vertex& B);
	double get_angle_between_vectors(Vertex& A, Vertex& B);

	void get_vector_negation(Vertex& A);	
	friend Vertex operator+(Vertex& A, Vertex& B);
	friend Vertex operator-(Vertex& A, Vertex& B);
	Vertex get_unit_vector(Vertex& A);	
	Vertex get_cross_product(Vertex& A, Vertex& B);
	Vertex get_normal_vector(Vertex& A, Vertex& B);
	Vertex get_normal_vector(Vertex& A, Vertex& B, Vertex& C);
	void do_vector_translation(Vertex& A, Vertex& input_vector);
};