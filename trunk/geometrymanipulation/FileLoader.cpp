#include "FileLoader.h"
#include "ProgramTimer.h"
#include "VectorManipulations.h"
#include <iostream>

using namespace std;

/*
This specifies the static vectors of faces and vertices
*/
vector<Vertex>* FileLoader::vertices;
vector<Face>* FileLoader::faces;

/*
The constructor which allocates memory on the heap for the vertex and the face vectors. Because no values have been provided, it initially creates a vector of size 1
*/
FileLoader::FileLoader() {
	vertices = new vector<Vertex>();
	faces = new vector<Face>();
}

/*
The destructor which clears the vectors and the deletes them from the heap
*/
FileLoader::~FileLoader() {
	vertices->clear();
	faces->clear();
	delete vertices;
	delete faces;
}

/*
The file loader method which clears the current vectors of faces and vertices and loads them with new values provided in the file 

It then calls the ParseFile method to carry out the load
*/
int FileLoader::LoadNewFile(string& file_name) {
	vertices->clear();
	faces->clear();
	current_file = file_name;
	int success = ParseFile(current_file);

	return success;
}

/*
reads the face vector and gets the corresponding vertex from the vertices vector
generates normals by calling the get_normal_vector(Vertex& A, Vertex& B, Vertex& C) method from VectorArithmetic class
stores the normal vertices to the normals vector<Vertex>
prints the normals vector to file

It assumes the first 3 values of the vertices as obtained from the vector<Face> will be sufficient to generate the normals
*/
int FileLoader::GenerateNormals(string& file_name) {
	ProgramTimer normals_calculation;
	ProgramTimer normals_file_saver;

	normals_calculation.set_start_time();

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
	
	normals_calculation.set_end_time();

	normals_file_saver.set_start_time();

	normals_file << "normals" << endl;
	normals_file << normals << endl;

	normals_file_saver.set_end_time();

	cout << "Normals are calculated in " << normals_calculation.get_execution_time() << " seconds" << endl;
	cout << "Normals are saved to file in " << normals_file_saver.get_execution_time() << " seconds" << endl;

	normals->clear();
	delete normals;

	normals_file.close();

	return 0;
}

/*
The output operation prints the contents of the vertices vector to the ostr provided as the parameter
*/
ostream& operator<<(ostream& ostr, vector<Vertex>* current_vertices) {
	for(vector<Vertex>::iterator current_vertex = current_vertices->begin(); current_vertex != current_vertices->end(); ++current_vertex) {
		ostr << current_vertex->x << "\t" << current_vertex->y << "\t" << current_vertex->z << endl;
	}

	return ostr;
}

/*
The output operation prints the contents of the faces vector to the ostr provided as the parameter
*/
ostream& operator<<(ostream& ostr, vector<Face>* current_faces) {
	vector<int> items;
	for (vector<Face>::iterator i = current_faces->begin(); i != current_faces->end(); ++i) {
		items = i->get_face_values();
		ostr << i->get_number_of_vertices() << "\t";
		for (int j = 0; j < items.size(); j++)
			ostr << items[j] << "\t";
		ostr << '\n';
	}

	return ostr;
}

/*
This method takes the file_name and loads it into the corresponding vertices and faces vectors.

It opens the file and reads the first line. If the first line says vertices it starts to load the vector<Vertex> until it hits a bad input.
At that point, if the line reads faces it starts to store the values into the vector<Face>.

The assumption is no preceding new line characters before the word vertices.
Also assumes vertices and faces are spelt with lower cases
*/
int FileLoader::ParseFile(string& file_name) {
	ProgramTimer vertices_loader;	
	ProgramTimer faces_loader;

	string current_line;
	int i = 0, j = 0, bad_input = 0, array_size;
	Vertex current_vertex;
	Face current_face;

	read_file.open(file_name, ios::in);
	
	if(!read_file) {
		return 1;
	}

	vertices_loader.set_start_time();

	read_file >> current_line;
	
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
	vertices_loader.set_end_time();

	cout << "loading of " << vertices->size() << " vertices took " << vertices_loader.get_execution_time() << " seconds" << endl;

	faces_loader.set_start_time();

	if(current_line.find("faces") == 0) {
		while(!bad_input) {
			//handle faces here

			//read the first value in the line which is the number of vertices per face
			read_file >> array_size;

			//if it is a bad input i.e. no integer, it exits. else it stores the corresponding integers on the line into an array of integers and passes that to the set_face_values function
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

	faces_loader.set_end_time();

	cout << "loading of " << faces->size() << " faces took " << faces_loader.get_execution_time() << " seconds" << endl;

	read_file.close();

	return 0;
}