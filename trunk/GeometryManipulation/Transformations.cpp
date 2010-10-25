#include <iostream>
#include <math.h>
#include "Transformations.h"

using namespace std;

Transformations::Transformations() {
	arithmetic = new VectorArithmetic();
}

Transformations::~Transformations() {
	delete arithmetic;
	arithmetic = NULL;
}

Vertex* Transformations::do_vector_translation(Vertex* A, Vertex* input_vector) {
	Vertex* translated_vector = new Vertex();

	translated_vector = arithmetic->do_vector_addition(A, input_vector);

	return translated_vector;
}

Vertex* Transformations::do_uniform_scaling(double scalar, Vertex* A) {
	Vertex* scalar_vector = new Vertex();

	scalar_vector->x = scalar * A->x;
	scalar_vector->y = scalar * A->y;
	scalar_vector->z = scalar * A->z;

	return scalar_vector;
}

Vertex* do_axis_scaling(Vertex* A, char axis, double scaling_value) {
	Vertex* axis_scaling = new Vertex();

	if(axis == 'x') {
		axis_scaling->x = scaling_value * A->x;
	} else if(axis == 'y') {
		axis_scaling->y = scaling_value * A->y;
	} else if(axis == 'z') {
		axis_scaling->z = scaling_value * A->z;
	} else {
		cout << "Please provide the correct axis to scale by." << endl;
		return NULL;
	}

	return axis_scaling;
}