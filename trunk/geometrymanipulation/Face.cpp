#include <iostream>
#include "Face.h"

#define min_size 3

using namespace std;

/*
The default constructor which sets the number of vertices to a minimum size of 3 and resizes the face vector to the minimum size
*/
Face::Face() {
	this->number_of_vertices = min_size;
	this->face.resize(min_size);
}

/*
Parameter constructor sets the number of vertices to a the size provided and resizes the face vector to the the size
*/
Face::Face(int size) {
	this->number_of_vertices = size;
	this->face.resize(size);
}

/*
The copy constructor copies the values of the source Face to the local Face by setting the number of vertices and the vector<int> to the source vector
*/
Face::Face(const Face& source): 
face(source.face),
number_of_vertices(source.number_of_vertices) {
}

/*
The default constructor
*/
Face::~Face() {
}

/*
a setter which takes in the pointer of an integer array as a parameter and copies them to the vector<int>

for efficiency, if the size of the face vector is larger than the number of vertices then it erases the trailing values from the vector
*/
void Face::set_face_values(int* face_values) {
	for(int i = 0; i < number_of_vertices; i++) {
		if(face.size() >= number_of_vertices)
			face.erase(face.begin() + i);

		face.insert((face.begin() + i), face_values[i]);
	}
	if(face.size() > number_of_vertices)
		face.erase(face.begin()+number_of_vertices, face.begin()+face.size());
}

/*
returns the face vector
*/
vector<int> Face::get_face_values() {
	return face;
}

/*
sets the number of vertices to the value provided as a parameter
*/
void Face::set_number_of_vertices(int vertices) {
	this->number_of_vertices = vertices;
}

/*
gets the number of vertices
*/
int Face::get_number_of_vertices() {
	return number_of_vertices;
}