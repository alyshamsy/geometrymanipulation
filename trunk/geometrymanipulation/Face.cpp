#include <iostream>
#include "Face.h"

using namespace std;

Face::Face() {
	this->number_of_vertices = min_size;
	this->face.resize(min_size);
}

Face::Face(int size) {
	this->number_of_vertices = size;
	this->face.resize(size);
}

Face::Face(const Face& source): 
face(source.face),
number_of_vertices(source.number_of_vertices) {
}

Face::~Face() {
}

void Face::set_face_values(int* face_values) {
	for(int i = 0; i < number_of_vertices; i++) {
		if(face.size() >= number_of_vertices)
			face.erase(face.begin() + i);

		face.insert((face.begin() + i), face_values[i]);
	}
	if(face.size() > number_of_vertices)
		face.erase(face.begin()+number_of_vertices, face.begin()+face.size());
}

vector<int> Face::get_face_values() {
	return face;
}

void Face::set_number_of_vertices(int vertices) {
	this->number_of_vertices = vertices;
}

int Face::get_number_of_vertices() {
	return number_of_vertices;
}