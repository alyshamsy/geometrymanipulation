#include "FileLoader.h"
#include "ProgramTimer.h"
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

//need to move it into the vertex class
void FileLoader::get_vertices_vector() {
	//print the contents of the vertices vector
	for(vector<Vertex>::iterator i = vertices->begin(); i != vertices->end(); ++i) {
		cout << i->x << "\t" << i->y << "\t" << i->z << endl;
	}
}

//need to move it into the face class
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
	ProgramTimer pt_1;	
	ProgramTimer pt_2;

	string current_line, delimeter = " ";
	int i = 0, j = 0, bad_input = 0, array_size;
	Vertex current_vertex;
	Face current_face;

	read_file.open(file_name, ios::in);

	pt_1.set_start_time();

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
	pt_1.set_end_time();

	cout << "execution of vertices extraction took " << pt_1.get_execution_time() << " seconds" << endl;

	pt_2.set_start_time();

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

	pt_2.set_end_time();

	cout << "execution of faces extraction took " << pt_2.get_execution_time() << " seconds" << endl;

	read_file.close();
}