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
	static vector<Vertex>* vertices;
	static vector<Face>* faces;
	void ParseFile(string& file_name);
	string TrimSpaces(string& current_line);
	void ExtractVertices(Vertex* current_vertex, string& current_line, string& delimeter);
	void ExtractFaces(Face* current_face, string& current_line, string& delimeter);
};