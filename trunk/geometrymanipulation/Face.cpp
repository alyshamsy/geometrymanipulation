#include <iostream>
#include "Face.h"

using namespace std;

Face::Face() {
	this->face.resize(min_size);
}

Face::Face(int size) {
	this->face.resize(size);
}

Face::Face(const Face& source): 
face(source.face) {
}

Face::~Face() {
}

void Face::set_face_values(int* face_values, int array_size) {
	for(int i = 0; i < array_size; i++) {
		if(face.size() >= array_size)
			face.erase(face.begin() + i);

		face.insert((face.begin() + i), face_values[i]);
	}
	if(face.size() > array_size)
		face.erase(face.begin()+array_size, face.begin()+face.size());
}

vector<int> Face::get_face_values() {
	return face;
}