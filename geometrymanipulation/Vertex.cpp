#include <iostream>
#include "Vertex.h"

using namespace std;

Vertex::Vertex() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

Vertex::Vertex(double a, double b, double c) {
	this->x = a;
	this->y = b;
	this->z = c;
}

Vertex::Vertex(const Vertex& source):
x(source.x),
y(source.y),
z(source.z) {
}

Vertex::~Vertex() {
}

void Vertex::set_vertex(double a, double b, double c) {
	this->x = a;
	this->y = b;
	this->z = c;
}

Vertex& Vertex::operator=(const Vertex& rhs) {
	if(this == &rhs)
		return (*this);

	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;

	return (*this);
}

bool Vertex::operator==(const Vertex& rhs) {
	if(this->x == rhs.x && this->y == rhs.y && this->z == rhs.z) {
		return true;
	} else {
		return false;
	}
}

/*
ostream& operator<<(ostream& ostr, const Vertex& current_vertex) {
	//print the contents of the vertices vector
	cout << current_vertex.x << "\t" << current_vertex.y << "\t" << current_vertex.z << endl;

	return ostr;
}
*/