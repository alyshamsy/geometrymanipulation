#include <iostream>
#include <math.h>
#include "VectorManipulations.h"

/*
The default constructor
*/
VectorManipulations::VectorManipulations() {
}

/*
The default destructor
*/
VectorManipulations::~VectorManipulations() {
}

/*
returns the negation of the vertex provided as the paramete
*/
void VectorManipulations::get_vector_negation(Vertex& A) {

	A.x = -(A.x);
	A.y = -(A.y);
	A.z = -(A.z);

}

/*
returns the magnitude of the vertex by using the pythagorean formula
*/
double VectorManipulations::get_vector_magnitude(Vertex& A) {
	double magnitude, x, y, z;

	x = A.x;
	y = A.y;
	z = A.z;

	magnitude = sqrt((x*x) + (y*y) + (z*z));

	return magnitude;
}

/*
the addition operation adds the 2 vertices provided and returns a vertex with the respective x, y and z variables added
*/
Vertex operator+(Vertex& A, Vertex& B) {
	Vertex added_vector;

	added_vector.x = A.x + B.x;
	added_vector.y = A.y + B.y;
	added_vector.z = A.z + B.z;

	return added_vector;
}

/*
the subtraction operation subtracts the 2 vertices provided and returns the vertex with the respective x, y and z variablessubtracted
*/
Vertex operator-(Vertex& A, Vertex& B) {
	Vertex subtracted_vector;

	subtracted_vector.x = A.x - B.x;
	subtracted_vector.y = A.y - B.y;
	subtracted_vector.z = A.z - B.z;

	return subtracted_vector;
}

/*
return the unit vector of the parameter vertex provided by calculating the magnitude of the vertex and dividing each of the coordinates by the magnitude
*/
Vertex VectorManipulations::get_unit_vector(Vertex& A) {
	Vertex unit_vector;
	double magnitude = get_vector_magnitude(A);

	unit_vector.x = A.x/magnitude;
	unit_vector.y = A.y/magnitude;
	unit_vector.z = A.z/magnitude;

	return unit_vector;
}

/*
returns the dot product as a double value of the 2 vertices by multiplying the respective components
*/
double VectorManipulations::get_dot_product(Vertex& A, Vertex& B) {
	double dot_product;

	dot_product = ((A.x*B.x) + (A.y*B.y) + (A.z*B.z));

	return dot_product;
}

/*
returns the angle between the 2 vertices as a double value by calculating the dot product and the magnitudes and getting the arc cos of the dot product divided by the multiplication of the magnitudes of the 2 vertices
*/
double VectorManipulations::get_angle_between_vectors(Vertex& A, Vertex& B) {
	double angle, dot_product, magnitude_A, magnitude_B;

	dot_product = get_dot_product(A, B);
	magnitude_A = get_vector_magnitude(A);
	magnitude_B = get_vector_magnitude(B);

	angle = acos((dot_product)/(magnitude_A*magnitude_B));

	return angle;
}

/*
calculates the cross product of the 2 vertices and returns a vertex
*/
Vertex VectorManipulations::get_cross_product(Vertex& A, Vertex& B) {
	Vertex cp_vector;

	cp_vector.x = ((A.y*B.z) - (A.z*B.y));
	cp_vector.y = ((A.z*B.x) - (A.x*B.z));
	cp_vector.z = ((A.x*B.y) - (A.y*B.x));

	return cp_vector;
}

/*
calculates the normal vector of the 2 vertices provided by calculating the cross product and angle between them and their respective magnitudes
*/
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

/*
uses method overloading

calculates the normal of the 3 vertices provided. It first checks if any 2 vertices are the same. if yes then returns 0, 0, 0 else calculates 2 vertices and getting the normal vector between 2 vertices
*/
Vertex VectorManipulations::get_normal_vector(Vertex& A, Vertex& B, Vertex& C) {
	Vertex normal_unit_vector;

	if(!(A == B || A == C || B == C)) {
		Vertex X;
		Vertex Y;

		X = A - B;
		Y = B - C;

		normal_unit_vector = get_unit_vector(get_normal_vector(X, Y));
	}

	return normal_unit_vector;
}

/*
computes vector translation by adding the 2 vertices provided
*/
void VectorManipulations::do_vector_translation(Vertex& A, Vertex& input_vector) {
	A = A + input_vector;
}
