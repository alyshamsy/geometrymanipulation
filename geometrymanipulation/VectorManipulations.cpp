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
	Vertex normal_vector;

	Vertex X;
	Vertex Y;

	X = A - B;
	Y = B - C;

	normal_vector = get_normal_vector(X, Y);

	return normal_vector;
}

void VectorManipulations::do_vector_translation(Vertex& A, Vertex& input_vector) {

	A = A + input_vector;
}

/*
Vertex* VectorManipulations::do_uniform_scaling(double scalar, Vertex* A) {
	Vertex* scalar_vector = new Vertex();

	scalar_vector->x = scalar * A->x;
	scalar_vector->y = scalar * A->y;
	scalar_vector->z = scalar * A->z;

	return scalar_vector;
}

Vertex* VectorManipulations::do_axis_scaling(Vertex* A, char axis, double scaling_value) {
	Vertex* axis_scaling = new Vertex();

	if(axis == 'x') {
		axis_scaling->x = scaling_value * A->x;
	} else if(axis == 'y') {
		axis_scaling->y = scaling_value * A->y;
	} else if(axis == 'z') {
		axis_scaling->z = scaling_value * A->z;
	} else {
		return NULL;
	}

	return axis_scaling;
}
*/