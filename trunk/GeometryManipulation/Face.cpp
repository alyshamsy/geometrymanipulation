#include <iostream>
#include "Face.h"

#define min_size 4

using namespace std;

/*
Face::Face() {
	this->array_size = min_size;
	face = new int[array_size];
}

Face::Face(int size) {
	this->array_size = array_size;
	face = new int[array_size];
}

Face::Face(const Face& source): 
face(source.face) {
}

Face::~Face() {
	delete[] face;
	face = NULL;
}

void Face::set_face_values(int* face_values, int array_size) {
	for(int i = 0; i < array_size; i++) 
		face[i] = face_values[i];
}

int* Face::get_face_values() {
	return face;
}
*/

Face::Face() {
	face = new vector<int>(min_size);
}

Face::Face(int size) {
	face = new vector<int>(size);
}

Face::Face(const Face& source): 
face(source.face) {
}

Face::~Face() {
	face->clear();
	delete face;
}

void Face::set_face_values(int* face_values, int array_size) {
	for(int i = 0; i < array_size; i++) {
		if(face->size() > array_size)
			face->erase(face->begin() + i);

		face->insert((face->begin() + i), face_values[i]);
	}
	
	//print_face(face);
}

vector<int>* Face::get_face_values() {
	return face;
}

