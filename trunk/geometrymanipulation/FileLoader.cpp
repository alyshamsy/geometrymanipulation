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
	int i = 0, j = 0, bad_input = 0, array_size;
	Vertex current_vertex;
	Face current_face;

	read_file.open(file_name, ios::in);

	read_file >> current_line;
	//getline(read_file, current_line);
	
	if(current_line.find("vertices") == 0) {
		while(!bad_input) {
			read_file >> current_vertex.x >> current_vertex.y >> current_vertex.z; 
					
			if(!read_file) {
				bad_input = 1;
				read_file.clear();
				read_file >> current_line;
			} else {
				vertices->push_back(current_vertex);
			}
		}
	}

	if(current_line.find("faces") == 0) {
		while(!read_file.eof()) {
			//handle faces here

			read_file >> array_size;
			int* face_values = new int[array_size];
			
			for(int i = 0; i < array_size; i++) {
				read_file >> face_values[i];
			}

			current_face.set_number_of_vertices(array_size);
			current_face.set_face_values(face_values);
			delete[] face_values;
			face_values = NULL;

			faces->push_back(current_face);
		}
	}
	read_file.close();
}