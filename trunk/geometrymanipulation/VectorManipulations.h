#ifndef Vector_Manipulation_H
#define Vector_Manipulation_H

#include "Vertex.h"

/*
This class is used to do all the calculations on the vertices

There are methods to:
- calculate the magnitude of the vertices
- get the dot and cross products of two vertices
- get the angle between 2 vectors
- get the unit vector
- get the normal vector

Also there are methods to do addition and subtraction operations between 2 vectors
*/

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
#endif