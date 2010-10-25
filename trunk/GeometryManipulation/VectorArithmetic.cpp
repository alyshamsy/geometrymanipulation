#include <iostream>
#include <math.h>
#include "VectorArithmetic.h"

VectorArithmetic::VectorArithmetic() {
}

VectorArithmetic::~VectorArithmetic() {
}

Vertex* VectorArithmetic::get_vector_negation(Vertex* A) {
	Vertex* negative_vector = new Vertex();

	negative_vector->x = -(A->x);
	negative_vector->y = -(A->y);
	negative_vector->z = -(A->z);

	return negative_vector;
}

double VectorArithmetic::get_vector_magnitude(Vertex* A) {
	double magnitude, x, y, z;
	x = A->x;
	y = A->y;
	z = A->z;

	magnitude = sqrt((x*x) + (y*y) + (z*z));

	return magnitude;
}

Vertex* VectorArithmetic::do_vector_addition(Vertex* A, Vertex* B) {
	Vertex* added_vector = new Vertex();

	added_vector->x = A->x + B->x;
	added_vector->y = A->y + B->y;
	added_vector->z = A->z + B->z;

	return added_vector;
}

Vertex* VectorArithmetic::do_vector_subtraction(Vertex* A, Vertex* B) {
	Vertex* subtracted_vector = new Vertex();

	subtracted_vector->x = A->x - B->x;
	subtracted_vector->y = A->y - B->y;
	subtracted_vector->z = A->z - B->z;

	return subtracted_vector;
}

Vertex* VectorArithmetic::do_scalar_multiplication(double scalar_value, Vertex* A) {
	Vertex* scalar_vector = new Vertex;

	scalar_vector->x = scalar_value * A->x;
	scalar_vector->y = scalar_value * A->y;
	scalar_vector->z = scalar_value * A->z;

	return scalar_vector;
}

Vertex* VectorArithmetic::get_unit_vector(Vertex* A) {
	Vertex* unit_vector = new Vertex();
	double magnitude = get_vector_magnitude(A);
	unit_vector->x = A->x/magnitude;
	unit_vector->y = A->y/magnitude;
	unit_vector->z = A->z/magnitude;

	return unit_vector;
}

double VectorArithmetic::get_dot_product(Vertex* A, Vertex* B) {
	double dot_product;

	dot_product = ((A->x*B->x) + (A->y*B->y) + (A->z*B->z));

	return dot_product;
}

double VectorArithmetic::get_angle_between_vectors(Vertex* A, Vertex* B) {
	double angle, dot_product, magnitude_A, magnitude_B;

	dot_product = get_dot_product(A, B);
	magnitude_A = get_vector_magnitude(A);
	magnitude_B = get_vector_magnitude(B);

	angle = acos((dot_product)/(magnitude_A*magnitude_B));

	return angle;
}

Vertex* VectorArithmetic::get_cross_product(Vertex* A, Vertex* B) {
	Vertex* cp_vector = new Vertex();

	cp_vector->x = ((A->y*B->z) - (A->z*B->y));
	cp_vector->y = ((A->z*B->x) - (A->x*B->z));
	cp_vector->z = ((A->x*B->y) - (A->y*B->x));

	return cp_vector;
}

Vertex* VectorArithmetic::get_normal_vector(Vertex* A, Vertex* B) {
	double angle, denominator, magnitude_A, magnitude_B;
	Vertex* normal_vector = new Vertex();

	Vertex* cross_product = get_cross_product(A, B);
	magnitude_A = get_vector_magnitude(A);
	magnitude_B = get_vector_magnitude(B);
	angle = get_angle_between_vectors(A, B);
	
	denominator = (magnitude_A*magnitude_B*sin(angle));

	normal_vector->x = (cross_product->x)/denominator;
	normal_vector->y = (cross_product->y)/denominator;
	normal_vector->z = (cross_product->z)/denominator;

	return normal_vector;
}

Vertex* VectorArithmetic::get_normal_vector(Vertex* A, Vertex* B, Vertex* C) {
	Vertex* normal_vector = new Vertex();

	Vertex* X;
	Vertex* Y;

	X = do_vector_subtraction(A, B);
	Y = do_vector_subtraction(B, C);

	normal_vector = get_normal_vector(X, Y);

	return normal_vector;
}