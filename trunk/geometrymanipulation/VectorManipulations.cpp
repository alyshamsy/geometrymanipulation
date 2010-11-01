#include <iostream>
#include <math.h>
#include "VectorManipulations.h"

VectorManipulations::VectorManipulations() {
}

VectorManipulations::~VectorManipulations() {
}

void VectorManipulations::get_vector_negation(Vertex& A) {

	A.x = -(A.x);
	A.y = -(A.y);
	A.z = -(A.z);

}

double VectorManipulations::get_vector_magnitude(Vertex& A) {
	double magnitude, x, y, z;

	x = A.x;
	y = A.y;
	z = A.z;

	magnitude = sqrt((x*x) + (y*y) + (z*z));

	return magnitude;
}

Vertex operator+(Vertex& A, Vertex& B) {
	Vertex added_vector;

	added_vector.x = A.x + B.x;
	added_vector.y = A.y + B.y;
	added_vector.z = A.z + B.z;

	return added_vector;
}

Vertex operator-(Vertex& A, Vertex& B) {
	Vertex subtracted_vector;

	subtracted_vector.x = A.x - B.x;
	subtracted_vector.y = A.y - B.y;
	subtracted_vector.z = A.z - B.z;

	return subtracted_vector;
}

Vertex VectorManipulations::get_unit_vector(Vertex& A) {
	Vertex unit_vector;
	double magnitude = get_vector_magnitude(A);

	unit_vector.x = A.x/magnitude;
	unit_vector.y = A.y/magnitude;
	unit_vector.z = A.z/magnitude;

	return unit_vector;
}

double VectorManipulations::get_dot_product(Vertex& A, Vertex& B) {
	double dot_product;

	dot_product = ((A.x*B.x) + (A.y*B.y) + (A.z*B.z));

	return dot_product;
}

double VectorManipulations::get_angle_between_vectors(Vertex& A, Vertex& B) {
	double angle, dot_product, magnitude_A, magnitude_B;

	dot_product = get_dot_product(A, B);
	magnitude_A = get_vector_magnitude(A);
	magnitude_B = get_vector_magnitude(B);

	angle = acos((dot_product)/(magnitude_A*magnitude_B));

	return angle;
}

Vertex VectorManipulations::get_cross_product(Vertex& A, Vertex& B) {
	Vertex cp_vector;

	cp_vector.x = ((A.y*B.z) - (A.z*B.y));
	cp_vector.y = ((A.z*B.x) - (A.x*B.z));
	cp_vector.z = ((A.x*B.y) - (A.y*B.x));

	return cp_vector;
}

Vertex VectorManipulations::get_normal_vector(Vertex& A, Vertex& B) {
	double angle, denominator, magnitude_A, magnitude_B;
	Vertex normal_vector;

	Vertex cross_product = get_cross_product(A, B);
	magnitude_A = get_vector_magnitude(A);
	magnitude_B = get_vector_magnitude(B);
	angle = get_angle_between_vectors(A, B);
	
	denominator = (magnitude_A*magnitude_B*sin(angle));

	normal_vector.x = (cross_product.x)/denominator;
	normal_vector.y = (cross_product.y)/denominator;
	normal_vector.z = (cross_product.z)/denominator;

	return normal_vector;
}

Vertex VectorManipulations::get_normal_vector(Vertex& A, Vertex& B, Vertex& C) {
	//check if any of the 2 vertices are the same then pass an error
	Vertex normal_unit_vector;

	if(A == B || A == C || B == C) {
		normal_unit_vector.x = 0.0;
		normal_unit_vector.y = 0.0;
		normal_unit_vector.z = 0.0;
	} else {
		Vertex X;
		Vertex Y;

		X = A - B;
		Y = B - C;

		normal_unit_vector = get_unit_vector(get_normal_vector(X, Y));
	}

	return normal_unit_vector;
}

void VectorManipulations::do_vector_translation(Vertex& A, Vertex& input_vector) {

	A = A + input_vector;
}
