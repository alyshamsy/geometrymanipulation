#ifndef Face_H
#define Face_H

#include <vector>

using namespace std;

/*
This class defines the structure of the Face which is a vector of integers which stores all the face values. The number_of_vertices variable stores the number
of vertices that make up the face

It has a default constructor, a constructor with one parameter and a copy constructor along with a destructor
It has a pair of getters and setters for the vector of integers and number_of_vertices
*/

class Face {
public:
	Face();
	Face(int size);
	Face(const Face& source);
	~Face();
	void set_face_values(int* face_values);
	vector<int> get_face_values();
	void set_number_of_vertices(int vertices);
	int get_number_of_vertices();

private:
	vector<int> face;
	int number_of_vertices;
};
#endif