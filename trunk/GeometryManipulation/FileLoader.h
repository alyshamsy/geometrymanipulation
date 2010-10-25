#include "Vertex.h"
#include "Face.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class FileLoader {
public:
	FileLoader();
	FileLoader(string& file_name);
	~FileLoader();
	void get_vertices_vector();
	void get_faces_vector();
private:
	string current_file;
	fstream read_file;
	int array_size;
	vector<Vertex>* vertices;
	//Face** faces;
	vector<Face>* faces;
	void ParseFile(string& file_name);
	void TrimSpaces(string& current_line);
	void ExtractVertices(Vertex* current_vertex, string& current_line, string& delimeter);
	void ExtractFaces(Face* current_face, string& current_line, string& delimeter, const int array_size);
};