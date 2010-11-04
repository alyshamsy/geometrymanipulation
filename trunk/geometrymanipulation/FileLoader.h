#ifndef File_Loader_H
#define File_Loader_H

#include "Vertex.h"
#include "Face.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
This class is used to load and save files along with generating normals and printing the vertices and faces of the object
There are 2 vectors, one of type Vertex and one of type Face which stores the vertices and the faces
*/

class FileLoader {
public:
	FileLoader();
	~FileLoader();

	int LoadNewFile(string& file_name);
	int GenerateNormals(string& file_name);

	friend ostream& operator<<(ostream& ostr, vector<Vertex>* current_vertices);
	friend ostream& operator<<(ostream& ostr, vector<Face>* current_faces);

	static vector<Vertex>* vertices;
	static vector<Face>* faces;
private:
	string current_file;
	fstream read_file;
	int array_size;
	int ParseFile(string& file_name);
};
#endif