#include "FileLoader.h"
#include <iostream>

using namespace std;

vector<Vertex>* FileLoader::vertices;
vector<Face>* FileLoader::faces;

FileLoader::FileLoader() {
	vertices = new vector<Vertex>();
	faces = new vector<Face>();
	current_file = "default.txt";
	ParseFile(current_file);
}

FileLoader::FileLoader(string& file_name) {
	vertices = new vector<Vertex>();
	faces = new vector<Face>();
	current_file = file_name;
	ParseFile(current_file);
}

FileLoader::~FileLoader() {
	vertices->clear();
	faces->clear();
	delete vertices;
	delete faces;
}

void FileLoader::get_vertices_vector() {
	//print the contents of the vertices vector
	for(vector<Vertex>::iterator i = vertices->begin(); i != vertices->end(); ++i) {
		cout << i->x << "\t" << i->y << "\t" << i->z << endl;
	}
}

void FileLoader::get_faces_vector() {
	//print the contents of the faces vector
	vector<int> items;
	for (vector<Face>::iterator i = faces->begin(); i != faces->end(); ++i) {
		items = i->get_face_values();
		for ( int j = 0; j < items.size(); j++ )
			cout << items[j] << "\t";
		cout << '\n';
	}
}

void FileLoader::ParseFile(string& file_name) {
	string current_line, delimeter = " ";
	int i = 0, j = 0;
	Vertex current_vertex;
	Face current_face;

	read_file.open(file_name, ios::in);

	read_file >> current_line;
	//getline(read_file, current_line);
	
	if(current_line.find("vertices") == 0) {
		while(!read_file.eof() /* getline(read_file, current_line) && current_line.find("faces")*/) {
			read_file >> current_vertex.x >> current_vertex.y >> current_vertex.z; 
			//handle vertices here
			//TrimSpaces(current_line);
			//ExtractVertices(&current_vertex, current_line, delimeter);
			vertices->push_back(current_vertex);
		}
	}

	read_file >> current_line;

	if(current_line.find("faces") == 0) {
		while(getline(read_file, current_line)) {
			//handle faces here
			TrimSpaces(current_line);
			ExtractFaces(&current_face, current_line, delimeter);
			faces->push_back(current_face);
		}
	}
	read_file.close();
}

string FileLoader::TrimSpaces(string& current_line) {
	int starting_position = current_line.find_first_not_of(" \t");
	int end_position = current_line.find_last_not_of(" \t");

	if(starting_position == end_position)
		current_line = "";
	else 
		current_line = current_line.substr(starting_position, end_position - starting_position+1);

	return current_line;
}

void FileLoader::ExtractVertices(Vertex* current_vertex, string& current_line, string& delimeter) {
	double x, y, z;
	string modified_string;
	int current_pos = 0, previous_pos = 0;

	current_pos = current_line.find(delimeter, current_pos);
	modified_string = current_line.substr(previous_pos, current_pos - previous_pos+1);
	current_pos += delimeter.size();
	previous_pos = current_pos;
	x = atof(modified_string.c_str());

	current_pos = current_line.find(delimeter, current_pos);
	modified_string = current_line.substr(previous_pos, current_pos - previous_pos+1);
	current_pos += delimeter.size();
	previous_pos = current_pos;
	y = atof(modified_string.c_str());

	current_pos = current_line.find(delimeter, current_pos);
	modified_string = current_line.substr(previous_pos, current_pos - previous_pos+1);
	z = atof(modified_string.c_str());

	current_vertex->set_vertex(x, y, z);
}

void FileLoader::ExtractFaces(Face* current_face, string& current_line, string& delimeter) {
	string modified_string;
	int current_pos = current_line.find_first_of(delimeter) + delimeter.size();
	int previous_pos = current_pos;

	array_size = atoi(current_line.substr(0, current_line.find_first_of(delimeter)).c_str());
	int* face_values = new int[array_size];

	for(int i = 0; i < array_size; i++) {
		current_pos = current_line.find(delimeter, current_pos);
		modified_string = current_line.substr(previous_pos, current_pos - previous_pos+1);
		face_values[i] = atoi(modified_string.c_str());
		current_pos += delimeter.size();
		previous_pos = current_pos;
	}

	current_face->set_number_of_vertices(array_size);
	current_face->set_face_values(face_values);
	delete[] face_values;
	face_values = NULL;
}