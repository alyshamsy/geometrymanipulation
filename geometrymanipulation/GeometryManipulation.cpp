#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include "VectorManipulations.h"
#include "MatrixManipulations.h"
#include "FileLoader.h"
#include "ProgramTimer.h"

using namespace std;

void HandleCommands(vector<string>& custom_commands, FileLoader* file_loader, bool& file_loaded) {
	MatrixManipulations matrix_handler;
	fstream script_handler;
	int start = 0;

	while(custom_commands.at(start).compare("load") != 0) {
		custom_commands.erase(custom_commands.begin() + start);
	}

	string input_file = custom_commands.at(++start);
	int load_file = file_loader->LoadNewFile(input_file);

	if(load_file == 0) {
		file_loaded = true;
		int size = 4;

		cout << input_file << " loaded successfully!" << endl;
		custom_commands.erase(custom_commands.begin(), custom_commands.begin()+start+1);
		Matrix multiplier = matrix_handler.generate_identity_matrix(size);
		int j = 0;

		while(j < custom_commands.size()) {
			while(custom_commands.at(j).compare("print") != 0 && custom_commands.at(j).compare("save") != 0 && custom_commands.at(j).compare("normals") != 0) {
				if(custom_commands.at(j).compare("translate") == 0) {
					Vertex translation_vertex;

					stringstream translate_vector(stringstream::in | stringstream::out);
					translate_vector << custom_commands.at(++j);
					translate_vector >> translation_vertex.x >> translation_vertex.y >> translation_vertex.z;

					multiplier = multiplier*matrix_handler.get_translation_matrix(size, translation_vertex);
					matrix_handler.print_matrix(multiplier);
					j++;
				} else if(custom_commands.at(j).compare("scale") == 0) {
					int scaling_value;

					stringstream scaler(stringstream::in | stringstream::out);
					scaler << custom_commands.at(++j);
					scaler >> scaling_value;

					multiplier = multiplier*matrix_handler.get_uniform_scaling_matrix(size, scaling_value);
					matrix_handler.print_matrix(multiplier);
					j++;
				} else if(custom_commands.at(j).compare("axis-rotate") == 0) {
					char axis;
					double angle;

					stringstream axis_rotate(stringstream::in | stringstream::out);
					axis_rotate << custom_commands.at(++j);
					axis_rotate >> axis >> angle;

					if(axis == 'x' || axis == 'y' || axis == 'z') {
						multiplier = multiplier*matrix_handler.get_axis_rotation_matrix(size, axis, angle);
						matrix_handler.print_matrix(multiplier);
					} else {
						cout << "Please provide a correct axis x, y or z" << endl;
					}
					j++;
				} else if(custom_commands.at(j).compare("free-rotate") == 0) {
					Vertex arbitrary_axis_vertex;
					double angle;

					stringstream free_rotate(stringstream::in | stringstream::out);
					free_rotate << custom_commands.at(++j);
					free_rotate >> arbitrary_axis_vertex.x >> arbitrary_axis_vertex.y >> arbitrary_axis_vertex.z >> angle;

					multiplier = multiplier*matrix_handler.get_free_rotation_matrix(size, arbitrary_axis_vertex, angle);
					matrix_handler.print_matrix(multiplier);
					j++;
				} else {
					cout << custom_commands.at(j) << " could not be recognized and has not been executed. The script loading has been terminated." << endl;
					j++;
				}
			}

			int vertices_vector_size = file_loader->vertices->size();
			for(int i = 0; i < vertices_vector_size; i++) {
				Matrix current_matrix = matrix_handler.generate_row_vector(file_loader->vertices->at(i), 4);
				current_matrix = current_matrix*multiplier;
				file_loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
			}

			matrix_handler.print_matrix(multiplier);
			multiplier = matrix_handler.generate_identity_matrix(size);

			if(custom_commands.at(j).compare("print") == 0) {
				cout << "\nvertices" << endl;
				cout << file_loader->vertices << endl;
				cout << "faces" << endl;
				cout << file_loader->faces << endl;
				j++;
			} else if(custom_commands.at(j).compare("save") == 0) {
				fstream file_saver;
				string save_file = custom_commands.at(++j);

				file_saver.open(save_file, ios::out);

				if(file_saver.is_open()) {						
					file_saver << "vertices" << endl;
					file_saver << file_loader->vertices << endl;
					file_saver << "faces" << endl;
					file_saver << file_loader->faces << endl;
					file_saver.close();
					cout << save_file << " was saved successfully" << endl;
				} else {
					cout << save_file << " is currently open. Please close the file and retry saving" << endl;
				}
				j++;
			} else if(custom_commands.at(j).compare("normals") == 0) {
				string normals_file = custom_commands.at(++j);
				fstream generate_normals_file(normals_file, ios::out);

				if(generate_normals_file.is_open()) {
					file_loader->GenerateNormals(normals_file);
				} else {
					cout << normals_file << " is currently open. Please close the file and retry saving" << endl;
				}
				j++;
			}
		}
	} else {
		cout << input_file << " is either open or does not exist. Please take appropriate action" << endl;
	}

	return;
}

void HandleCustomCommands(vector<string>& custom_commands, FileLoader* file_loader, bool& file_loaded) {
	MatrixManipulations matrix_handler;
	int bad_input = 0;
	int start = 0;

	while(custom_commands.at(start).compare("load") != 0) {
		custom_commands.erase(custom_commands.begin() + start);
	}

	string input_file = custom_commands.at(++start);
	int load_file = file_loader->LoadNewFile(input_file);

	if(load_file == 0) {
		file_loaded = true;
		cout << input_file << " loaded successfully!" << endl;
		custom_commands.erase(custom_commands.begin(), custom_commands.begin()+start+1);

		for(int j = 0; j < custom_commands.size(); j++) {
			if(custom_commands.at(j).compare("translate") == 0) {
				Vertex translated_vertex;
				stringstream translate_vector(stringstream::in | stringstream::out);
				translate_vector << custom_commands.at(++j);
				translate_vector >> translated_vertex.x >> translated_vertex.y >> translated_vertex.z;

				int vertices_vector_size = file_loader->vertices->size();
				for(int i = 0; i < vertices_vector_size; i++) {
					file_loader->vertices->at(i) = translated_vertex + file_loader->vertices->at(i);
				}
			} else if(custom_commands.at(j).compare("scale") == 0) {
				int scaling_value;

				stringstream scaler(stringstream::in | stringstream::out);
				scaler << custom_commands.at(++j);
				scaler >> scaling_value;

				int vertices_vector_size = file_loader->vertices->size();
				for(int i = 0; i < vertices_vector_size; i++) {
					Matrix current_matrix = matrix_handler.generate_column_vector(file_loader->vertices->at(i), 3);
					matrix_handler.do_uniform_scaling(scaling_value, current_matrix);
					file_loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
				}
			} else if(custom_commands.at(j).compare("axis-rotate") == 0) {
				char axis;
				double angle;

				stringstream axis_rotate(stringstream::in | stringstream::out);
				axis_rotate << custom_commands.at(++j);
				axis_rotate >> axis >> angle;

				if(axis == 'x' || axis == 'y' || axis == 'z') {
					int vertices_vector_size = file_loader->vertices->size();
					for(int i = 0; i < vertices_vector_size; i++) {
						Matrix current_matrix = matrix_handler.generate_column_vector(file_loader->vertices->at(i), 3);
						matrix_handler.do_axis_rotation(axis, angle, current_matrix);
						file_loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
					}
				} else {
					cout << "Please provide a correct axis x, y or z" << endl;
				}
			} else if(custom_commands.at(j).compare("free-rotate") == 0) {
				Vertex arbitrary_axis_vertex;
				double angle;

				stringstream free_rotate(stringstream::in | stringstream::out);
				free_rotate << custom_commands.at(++j);
				free_rotate >> arbitrary_axis_vertex.x >> arbitrary_axis_vertex.y >> arbitrary_axis_vertex.z >> angle;

				int vertices_vector_size = file_loader->vertices->size();
				for(int i = 0; i < vertices_vector_size; i++) {
					Matrix current_matrix = matrix_handler.generate_column_vector(file_loader->vertices->at(i), 3);
					matrix_handler.do_free_rotation(arbitrary_axis_vertex, angle, current_matrix);
					file_loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
				}
			} else if(custom_commands.at(j).compare("print") == 0) {
				cout << "\nvertices" << endl;
				cout << file_loader->vertices << endl;
				cout << "faces" << endl;
				cout << file_loader->faces << endl;
			} else if(custom_commands.at(j).compare("save") == 0) {
				fstream file_saver;
				string save_file = custom_commands.at(++j);

				file_saver.open(save_file, ios::out);

				if(file_saver.is_open()) {						
					file_saver << "vertices" << endl;
					file_saver << file_loader->vertices << endl;
					file_saver << "faces" << endl;
					file_saver << file_loader->faces << endl;
					file_saver.close();
					cout << save_file << " was saved successfully" << endl;
				} else {
					cout << save_file << " is currently open. Please close the file and retry saving" << endl;
				}
			} else if(custom_commands.at(j).compare("normals") == 0) {
				string normals_file = custom_commands.at(++j);
				fstream generate_normals_file(normals_file, ios::out);

				if(generate_normals_file.is_open()) {
					file_loader->GenerateNormals(normals_file);
				} else {
					cout << normals_file << " is currently open. Please close the file and retry saving" << endl;
				}
			} else {
				cout << custom_commands.at(j) << " could not be recognized and has not been executed. The script loading has been terminated." << endl;
				return;
			}
		}
	} else {
		cout << input_file << " is either open or does not exist. Please take appropriate action" << endl;
	}

	return;
}

void HandleScript(string& script_file, FileLoader* file_loader, bool& file_loaded) {
	MatrixManipulations matrix_handler;
	fstream script_handler;
	int bad_input = 0;
	ProgramTimer script_handling;

	script_handling.set_start_time();
	script_handler.open(script_file, ios::in);

	if(!script_handler) {
		cout << "Script file does not exist. Please provide a valid script file" << endl;
		return;
	} else {
		string command;
		vector<string> command_set;

		while(!bad_input && !script_handler.eof()) {
			getline(script_handler, command);

			if(!command.empty())
				command_set.push_back(command);
		}

		script_handler.close();

		HandleCommands(command_set, file_loader, file_loaded);
		script_handling.set_end_time();
		
		cout << "Handling of the script file took " << script_handling.get_execution_time() << " seconds" << endl;
		return;
	}
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
				break;
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
				ProgramTimer custom_commands_handling;

				cout << "Please type in your custom commands. Type done when finished" << endl;

				while(!done) {
					//cin >> command;
					getline(cin, command);

					if(command.compare("done") == 0) {
						done = 1;
					} else {
						command_set.push_back(command);
					}
				}

				custom_commands_handling.set_start_time();
				HandleCustomCommands(command_set, loader, file_loaded);
				custom_commands_handling.set_end_time();

				cout << "Handling of the custom commands took " << custom_commands_handling.get_execution_time() << " seconds" << endl;
				break;
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
						Matrix current_matrix = matrix_handler.generate_column_vector(loader->vertices->at(i), 3);
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
							Matrix current_matrix = matrix_handler.generate_column_vector(loader->vertices->at(i), 3);
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
						Matrix current_matrix = matrix_handler.generate_column_vector(loader->vertices->at(i), 3);
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