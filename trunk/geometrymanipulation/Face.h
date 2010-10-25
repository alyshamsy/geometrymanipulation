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
	void set_face_values(int* face_values, int array_size);
	vector<int> get_face_values();
private:
	vector<int> face;
};
#endif