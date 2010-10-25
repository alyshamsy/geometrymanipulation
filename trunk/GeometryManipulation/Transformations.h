#include "VectorArithmetic.h"

class Transformations {
public:
	Transformations();
	~Transformations();
	Vertex* do_vector_translation(Vertex* A, Vertex* input_vector);
	Vertex* do_uniform_scaling(double scalar, Vertex* A);
	Vertex* do_axis_scaling(Vertex* A, char axis, double scaling_value);
private:
	VectorArithmetic* arithmetic;
};