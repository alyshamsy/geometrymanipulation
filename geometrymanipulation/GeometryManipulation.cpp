#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include "VectorManipulations.h"
#include "MatrixManipulations.h"
#include "FileLoader.h"
#include "ProgramTimer.h"

using namespace std;

void HandleScript(string& script_file, FileLoader* file_loader, bool& file_loaded) {
	fstream script_handler;
	int bad_input = 0;

	script_handler.open(script_file, ios::in);

	if(!script_handler) {
		cout << "Script file does not exist. Please provide a valid script file" << endl;
	} else {
		string command;
		vector<string> command_set;

		while(!bad_input) {
			script_handler >> command;
			command_set.push_back(command);
		}


	}
}

void HandleCustomCommands(vector<string>& custom_commands, FileLoader* file_loader, bool& file_loaded) {

}

int main() {
	int input = 1;
	char sub_input, exit;
	bool file_loaded = false;
	FileLoader* loader = new FileLoader();
	MatrixManipulations matrix_handler;

	cout << "Welcome to Aly's world of Geometry Manipulation" << endl;

	while(input != 0) {
		cout << "\nPlease select one of the following options:" << endl;
		cout << "\t1 - To run an existing script" << endl;
		cout << "\t2 - To run custom commands" << endl;
		cout << "\t3 - To run a set of pre-determined commands" << endl;
		cout << "\t0 - To exit\n" << endl;

		cin >> input;

		switch(input) {
		case 1:
			cout << "\n\tPlease select from one of the following options:" << endl;
			cout << "\t\ta - To run an existing script file" << endl;
			cout << "\t\tb - To go back to the main menu\n" << endl;

			cin >> sub_input;

			if(sub_input == 'a') {
				//a - To run an existing script file
				string script_name;
				cout << "Please provide a file name" << endl;
				cin >> script_name;

				HandleScript(script_name, loader, file_loaded);
			} else if(sub_input == 'b') {
				//b - To go back to the main menu
				break;
			} else {
				//no valid entry was provided
				cout << "Please provide a valid entry" << endl;
			}
		case 2:
			cout << "\n\tPlease select from one of the following options:" << endl;
			cout << "\t\ta - To run custom commands" << endl;
			cout << "\t\tb - To go back to the main menu\n" << endl;

			cin >> sub_input;

			if(sub_input == 'a') {
				//a - To run custom commands
				int done = 0;
				string command;
				vector<string> command_set;

				cout << "Please type in your custom commands. Type done when finished" << endl;

				while(!done) {
					cin >> command;

					if(command.compare("done")) {
						done = 1;
					} else {
						command_set.push_back(command);
					}
				}

				HandleCustomCommands(command_set, loader, file_loaded);
			} else if(sub_input == 'b') {
				//b - To go back to the main menu
				break;
			} else {
				//no valid entry was provided
				cout << "Please provide a valid entry" << endl;
			}

		case 3:
			sub_input = 'a';

			while(sub_input != 'i') {
				cout << "\n\tPlease select from one of the following options:" << endl;
				cout << "\t\ta - Load a geometry file" << endl;
				if(file_loaded) {
					cout << "\t\tb - Print the current geometry to screen" << endl;
					cout << "\t\tc - Save the current geometry to file" << endl;
					cout << "\t\td - Translate by a specified vector" << endl;
					cout << "\t\te - Scale by a specified scalar" << endl;
					cout << "\t\tf - Rotate the vertices around the x, y or z axis" << endl;
					cout << "\t\tg - Rotate the vertices around an arbitrary axis" << endl;
					cout << "\t\th - Generate a list of unit normals and save to file" << endl;
				}
				cout << "\t\ti - To go back to the main menu\n" << endl;

				cin >> sub_input;

				if(sub_input == 'a') {
					//a - Load a geometry file
					string input_file;

					cout << "Please enter a filename" << endl;
					cin >> input_file;

					int load_file = loader->LoadNewFile(input_file);

					if(load_file == 0) {
						file_loaded = true;
						cout << input_file << " loaded successfully!" << endl;
					} else {
						cout << input_file << " is either open or does not exist. Please take appropriate action" << endl;
					}
				} else if(file_loaded && sub_input == 'b') {
					//b - Print the current geometry to screen
					char print_input = 'A';

					while(print_input != 'D') {
						cout << "\t\tPlease select of the following options" << endl;
						cout << "\t\t\tA - Print Vertices" << endl;
						cout << "\t\t\tB - Print Faces" << endl;
						cout << "\t\t\tC - Print Vertices and Faces" << endl;
						cout << "\t\t\tD - Go back to commands menu" << endl;

						cin >> print_input;

						if(print_input == 'A') {
							//A - Print Vertices
							cout << "\nvertices" << endl;
							cout << loader->vertices << endl;
						} else if(print_input == 'B') {
							//B - Print Faces
							cout << "\nfaces" << endl;
							cout << loader->faces << endl;
						} else if(print_input == 'C') {
							//C - Print Vertices and Faces
							cout << "\nvertices" << endl;
							cout << loader->vertices << endl;
							cout << "faces" << endl;
							cout << loader->faces << endl;
						} else if(print_input == 'D') {
							//D - Go back to commands menu
							break;
						} else {
							//no valid entry was provided
							cout << "Please provide a valid entry" << endl;
						}
					}
				} else if(file_loaded && sub_input == 'c') {
					//c - Save the current geometry to file
					string save_file;
					
					cout << "Please provide a filename to save to" << endl;
					cin >> save_file;

					fstream file_saver;
					file_saver.open(save_file, ios::out);

					if(file_saver.is_open()) {						
						file_saver << "vertices" << endl;
						file_saver << loader->vertices << endl;
						file_saver << "faces" << endl;
						file_saver << loader->faces << endl;
						file_saver.close();
						cout << save_file << " was saved successfully" << endl;
					} else {
						cout << save_file << " is currently open. Please close the file and retry saving" << endl;
					}
				} else if(file_loaded && sub_input == 'd') {
					//d - Translate by a specified vector
					Vertex translate_vertex;

					cout << "Please provide the vector to translate your vertices by, in the format x y z" << endl;
					cin >> translate_vertex.x >> translate_vertex.y >> translate_vertex.z;

					int vertices_vector_size = loader->vertices->size();
					for(int i = 0; i < vertices_vector_size; i++) {
						loader->vertices->at(i) = translate_vertex + loader->vertices->at(i);
					}
				} else if(file_loaded && sub_input == 'e') {
					//e - Scale by a specified scalar
					int scaling_value;

					cout << "Please provide a scalar to scale all your vertices by" << endl;
					cin >> scaling_value;

					int vertices_vector_size = loader->vertices->size();
					for(int i = 0; i < vertices_vector_size; i++) {
						Matrix current_matrix = matrix_handler.generate_column_vector(loader->vertices->at(i));
						matrix_handler.do_uniform_scaling(scaling_value, current_matrix);
						loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
					}
				} else if(file_loaded && sub_input == 'f') {
					//f - Rotate the vertices around the x, y or z axis
					char axis;
					double angle;

					cout << "Please provide an axis and an angle to rotate the image by, in the form axis angle" << endl;
					cin >> axis >> angle;

					if(axis == 'x' || axis == 'y' || axis == 'z') {
						int vertices_vector_size = loader->vertices->size();
						for(int i = 0; i < vertices_vector_size; i++) {
							Matrix current_matrix = matrix_handler.generate_column_vector(loader->vertices->at(i));
							matrix_handler.do_axis_rotation(axis, angle, current_matrix);
							loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
						}
					} else {
						cout << "Please provide a correct axis x, y or z" << endl;
					}
				} else if(file_loaded && sub_input == 'g') {
					//g - Rotate the vertices around an arbitrary axis
					Vertex arbitrary_axis_vertex;
					double angle;

					cout << "Please provide an arbitrary axis and an angle to rotate the vertices by, in the form x y z angle" << endl;
					cin >> arbitrary_axis_vertex.x >> arbitrary_axis_vertex.y >> arbitrary_axis_vertex.z >> angle;

					int vertices_vector_size = loader->vertices->size();
					for(int i = 0; i < vertices_vector_size; i++) {
						Matrix current_matrix = matrix_handler.generate_column_vector(loader->vertices->at(i));
						matrix_handler.do_free_rotation(arbitrary_axis_vertex, angle, current_matrix);
						loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
					}
				} else if(file_loaded && sub_input == 'h') {
					//h - Generate a list of unit normals and save to file
					string normals_file;

					cout << "Please provide a filename to save to" << endl;
					cin >> normals_file;

					fstream generate_normals_file(normals_file, ios::out);

					if(generate_normals_file.is_open()) {
						loader->GenerateNormals(normals_file);
					} else {
						cout << normals_file << " is currently open. Please close the file and retry saving" << endl;
					}
				} else if(sub_input == 'i') {
					//i - To go back to the main menu
					break;
				} else {
					//no valid entry was provided
					cout << "Please provide a valid entry" << endl;
				}
			}
		}
	}

	cout << "\n\nThank you for experiencing Aly's world of Geometry Manipulation" << endl;
	cout << "Bye! \n" << endl;

	loader->~FileLoader();

	cout << "Type x to exit" << endl;
	cin >> exit;

	return 0;
}