#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include "VectorArithmetic.h"
#include "FileLoader.h"

using namespace std;


int main() {
	int exit;
	string input_file = "teapot.txt";
	FileLoader* loader = new FileLoader();
	loader->get_vertices_vector();
	//loader->get_faces_vector();
	
	cout << "Type a number to exit" << endl;
	cin >> exit;
	return 0;
}

/*
int main()
{
	int exit;
  vector<vector<int>> items;
  int k = 0;

  for ( int i = 0; i < 5; i++ ) {
    items.push_back ( vector<int>() );

    for ( int j = 0; j < 5; j++ )
      items[i].push_back ( k++ );
  }

  for ( int i = 0; i < 5; i++ ) {
    for ( int j = 0; j < 5; j++ )
      cout<< items[i][j] <<' ';
    cout<<'\n';
  }

  cout << "Type a number to exit" << endl;
	cin >> exit;
}
*/


/*
void print_vertex(Vertex* vertex) {
	cout << vector->x << "\t" << vector->y << "\t" << vector->z << endl;
}

int main() {
	VectorArithmetic* vector_calculation = new VectorArithmetic();
	int exit;
	double vector_magnitude, dot_product, angle;

	Vertex* A = new Vertex();
	Vertex* B = new Vertex();
	Vertex* C = new Vertex();
	Vertex* negative_vector = new Vertex();
	Vertex* added_vector = new Vertex(); 
	Vertex* subtracted_vector = new Vertex();
	Vertex* scalar_multiple = new Vertex();
	Vertex* unit_vector = new Vertex();
	Vertex* cross_product = new Vertex();
	Vertex* normal_vector_1 = new Vertex();
	Vertex* normal_vector_2 = new Vertex();

	A->set_vertex(2.0, 3.0, 4.0);
	B->set_vertex(3.0, 4.0, 7.0);
	C->set_vertex(4.0, 6.0, 9.0);

	negative_vector = vector_calculation->get_vector_negation(A);
	vector_magnitude = vector_calculation->get_vector_magnitude(negative_vector);
	added_vector = vector_calculation->do_vector_addition(A, B);
	subtracted_vector = vector_calculation->do_vector_subtraction(C, B);
	scalar_multiple = vector_calculation->do_scalar_multiplication(4, C);
	unit_vector = vector_calculation->get_unit_vector(A);
	dot_product = vector_calculation->get_dot_product(A, B);
	angle = vector_calculation->get_angle_between_vectors(A, B);
	cross_product = vector_calculation->get_cross_product(A, B);
	normal_vector_1 = vector_calculation->get_normal_vector(A, B);
	normal_vector_2 = vector_calculation->get_normal_vector(A, B, C);

	
	cout << "vector A: ";
		print_vector(A);
	cout << "vector B: ";
		print_vector(B);
	cout << "vector C: ";
		print_vector(C);

	cout << "The negation of vector A is ";
		print_vector(negative_vector);	
	cout << "The magnitude of the negative vector of A is " 
		<< vector_magnitude << endl;
	cout << "The addition of vector A and vector B is ";
		print_vector(added_vector);
	cout << "The subtraction of vector B and vector C is ";
		print_vector(subtracted_vector);
	cout << "After scalar multiplication of 4, vector C is at position ";
		print_vector(scalar_multiple);
	cout << "The unit vector of vector A is ";
		print_vector(unit_vector);
	cout << "The dot product of vector A and B is " 
		<< dot_product << endl;
	cout << "The angle between vector A and B is " 
		<< angle << endl;
	cout << "The cross product of vector A and B is ";
		print_vector(cross_product);
	cout << "The normal vector of vector A and B is ";
		print_vector(normal_vector_1);
	cout << "The normal vector from three position vectors A, B and C is ";
		print_vector(normal_vector_2);


	delete A;
	delete B;
	delete C;
	delete negative_vector;
	delete added_vector;
	delete subtracted_vector;
	delete scalar_multiple;
	delete unit_vector;
	delete cross_product;
	delete normal_vector_1;
	delete normal_vector_2;

	A = NULL;
	B = NULL;
	C = NULL;
	negative_vector = NULL;
	added_vector = NULL;
	subtracted_vector = NULL;
	scalar_multiple = NULL;
	unit_vector = NULL;
	cross_product = NULL;
	normal_vector_1 = NULL;
	normal_vector_2 = NULL;

	cout << "Type a number to exit" << endl;
	cin >> exit;

	return 0;
}
*/