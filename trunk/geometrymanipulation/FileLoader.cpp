#include "FileLoader.h"
#include "ProgramTimer.h"
#include "VectorManipulations.h"
#include <iostream>

using namespace std;

vector<Vertex>* FileLoader::vertices;
vector<Face>* FileLoader::faces;

FileLoader::FileLoader() {
	vertices = new vector<Vertex>();
	faces = new vector<Face>();
}

FileLoader::~FileLoader() {
	vertices->clear();
	faces->clear();
	delete vertices;
	delete faces;
}

int FileLoader::LoadNewFile(string& file_name) {
	vertices->clear();
	faces->clear();
	current_file = file_name;
	int success = ParseFile(current_file);

	return success;
}

int FileLoader::GenerateNormals(string& file_name) {
	//read the faces vector and get the corresponding vertices from the vertiices vector
	//generate normals by calling the get_normal_vector(Vertex& A, Vertex& B, Vertex& C) method from VectorArithmetic class
	//store the normal vertices to the normals vector<Vertex>
	//print the normals vector to file
	fstream normals_file;
	normals_file.open(file_name, ios::out);

	vector<Vertex>* normals = new vector<Vertex>();
	Vertex A, B, C, current_normal;
	VectorManipulations vector_manipulations;

	for (vector<Face>::iterator i = faces->begin(); i != faces->end(); ++i) {
		A = vertices->at(i->get_face_values()[0]);
		B = vertices->at(i->get_face_values()[1]);
		C = vertices->at(i->get_face_values()[2]);

		current_normal = vector_manipulations.get_normal_vector(A, B, C);
		normals->push_back(current_normal);
	}

	normals_file << normals << endl;

	normals->clear();
	delete normals;

	normals_file.close();

	return 0;
}

ostream& operator<<(ostream& ostr, vector<Vertex>* current_vertices) {
	//print the contents of the vertices vector
	for(vector<Vertex>::iterator current_vertex = current_vertices->begin(); current_vertex != current_vertices->end(); ++current_vertex) {
		ostr << current_vertex->x << "\t" << current_vertex->y << "\t" << current_vertex->z << endl;
	}

	return ostr;
}

ostream& operator<<(ostream& ostr, vector<Face>* current_faces) {
	//print the contents of the faces vector
	vector<int> items;
	for (vector<Face>::iterator i = current_faces->begin(); i != current_faces->end(); ++i) {
		items = i->get_face_values();
		for (int j = 0; j < items.size(); j++)
			ostr << items[j] << "\t";
		ostr << '\n';
	}

	return ostr;
}

int FileLoader::ParseFile(string& file_name) {
	ProgramTimer pt_1;	
	ProgramTimer pt_2;

	string current_line, delimeter = " ";
	int i = 0, j = 0, bad_input = 0, array_size;
	Vertex current_vertex;
	Face current_face;

	if(!read_file.is_open()) {
		return 1;
	}

	read_file.open(file_name, ios::in);
	
	if(!read_file) {
		return 1;
	}

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
		bad_input = 0;
	}
	pt_1.set_end_time();

	cout << "execution of vertices extraction took " << pt_1.get_execution_time() << " seconds" << endl;

	pt_2.set_start_time();

	if(current_line.find("faces") == 0) {
		while(!bad_input) {
			//handle faces here

			read_file >> array_size;

			if(!read_file) {
				bad_input = 1;
				read_file.clear();
			} else {
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
	}

	pt_2.set_end_time();

	cout << "execution of faces extraction took " << pt_2.get_execution_time() << " seconds" << endl;

	read_file.close();

	return 0;
}