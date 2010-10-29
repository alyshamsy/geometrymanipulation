#ifndef Face_H
#define Face_H

#include <vector>

#define min_size 4

using namespace std;

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

	ostream& operator<<(ostream& ostr, const Vertex& current_vertex);

private:
	vector<int> face;
	int number_of_vertices;
};
#endif