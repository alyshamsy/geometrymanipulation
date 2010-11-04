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

/*
This method is used to trim preceding and trailing spaces from a string. Used during script handler if a user enters a trailing space after the words.

It finds the first non space characte and last non space character as its starting and ending position and it gets the substring from starting to end
*/
void TrimSpaces(string& current_line) {
	int starting_position = current_line.find_first_not_of(" \t");
	int end_position = current_line.find_last_not_of(" \t");

	if(starting_position == end_position)
		current_line = "";
	else
		current_line = current_line.substr(starting_position, end_position - starting_position+1);
}

/*
This method handles the commands passed either via the custom command terminal or the file handler. 
It loops through a vector of strings 
It will ignore any operations until it hits the word load and erases all preceding commands
It will try and load the file and if unsuccessful it will return
if successful, it generates the identity matrix as the original multiplier of size 4 and iterates through the vector till the end
it then checks if the command at the current location on the vector is print, save, normals or load
	- if yes, then it breaks out of the loop and performs the geometry manipulation if its not a load command. if its the load command it loads the new file
	- if no, then it generates the translate, scaling, free-rotate or axis-rotate matrix for the vertices to be multiplied by
once it breaks out of the inner loop it transforms the vertices to a column vector matrices and performs the operation and then transforms it back to vertices and stores them
*/
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

		//loop till end of vector
		while(j < custom_commands.size()) {
			//loop till it hits one of these 4 commands
			while(custom_commands.at(j).compare("print") != 0 && custom_commands.at(j).compare("save") != 0 && custom_commands.at(j).compare("normals") != 0 && custom_commands.at(j).compare("load") != 0) {
				if(custom_commands.at(j).compare("translate") == 0) {
					//generate the translation matrix(T) and multiply that by the multiplier matrix(M) (T*M)
					Vertex translation_vertex;

					stringstream translate_vector(stringstream::in | stringstream::out);
					translate_vector << custom_commands.at(++j);
					translate_vector >> translation_vertex.x >> translation_vertex.y >> translation_vertex.z;

					multiplier = matrix_handler.get_translation_matrix(size, translation_vertex)*multiplier;
					j++;
				} else if(custom_commands.at(j).compare("scale") == 0) {
					//generates the uniform scaling matrix(S) and multiply it by the multiplier matrix(M) (S*M)
					int scaling_value;

					stringstream scaler(stringstream::in | stringstream::out);
					scaler << custom_commands.at(++j);
					scaler >> scaling_value;

					multiplier = matrix_handler.get_uniform_scaling_matrix(size, scaling_value)*multiplier;
					j++;
				} else if(custom_commands.at(j).compare("axis-rotate") == 0) {
					//generates the axis-rotate(AR) and multiply it by the multiplier matrix(M) (AR*M)
					char axis;
					double angle;

					stringstream axis_rotate(stringstream::in | stringstream::out);
					axis_rotate << custom_commands.at(++j);
					axis_rotate >> axis >> angle;

					if(axis == 'x' || axis == 'y' || axis == 'z') {
						multiplier = matrix_handler.get_axis_rotation_matrix(size, axis, angle)*multiplier;
					} else {
						cout << "Please provide a correct axis x, y or z" << endl;
					}
					j++;
				} else if(custom_commands.at(j).compare("free-rotate") == 0) {
					//generates the free-rotate(FR) and multiply it by the multiplier matrix(M) (FR*M)
					Vertex arbitrary_axis_vertex;
					double angle;

					stringstream free_rotate(stringstream::in | stringstream::out);
					free_rotate << custom_commands.at(++j);
					free_rotate >> arbitrary_axis_vertex.x >> arbitrary_axis_vertex.y >> arbitrary_axis_vertex.z >> angle;

					multiplier = matrix_handler.get_free_rotation_matrix(size, arbitrary_axis_vertex, angle)*multiplier;
					j++;
				} else {
					cout << custom_commands.at(j) << " could not be recognized and has not been executed. The script loading has been terminated." << endl;
					j++;
				}
			}

			/*
			if the user tries to reload a new file from the script it will check if it is the same file
				- if yes, it will not reload the file but clear the multiplier matrix to the identity matrix
				- if no then it reloads the files
			*/
			if(custom_commands.at(j).compare("load") == 0) {
				string new_file = custom_commands.at(++j);
				if(input_file.compare(new_file) != 0) {
					input_file = new_file;
					load_file = file_loader->LoadNewFile(input_file);

					if(load_file == 0) {
						file_loaded = true;

						cout << input_file << " loaded successfully!" << endl;
						j++;
					} else {
						cout << input_file << " is either open or does not exist. Please take appropriate action" << endl;
						cout << "Returning to main menu" << endl;
						return;
					}
				}
				multiplier = matrix_handler.generate_identity_matrix(size);
			} else {
				/*
				if the command is not load it will carry out the multiplication and reset the multiplier matrix
				*/
				int vertices_vector_size = file_loader->vertices->size();
				for(int i = 0; i < vertices_vector_size; i++) {
					Matrix current_matrix = matrix_handler.generate_column_vector(file_loader->vertices->at(i), 4);
					current_matrix = multiplier*current_matrix;
					file_loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
				}

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
		}
	} else {
		cout << input_file << " is either open or does not exist. Please take appropriate action" << endl;
	}

	return;
}

/*
This method handles the script by putting all the contents of the file on a vector<string> after trimming the trailing and preceding spaces
once loaded on the vector, it will call the HandleCommands method
*/
int HandleScript(string& script_file, FileLoader* file_loader, bool& file_loaded) {
	MatrixManipulations matrix_handler;
	fstream script_handler;
	int bad_input = 0;
	ProgramTimer script_handling;

	script_handler.open(script_file, ios::in);

	while(!script_handler) {
		script_handler.close();
		cin.clear();
		cin.ignore(1024, '\n');

		cout << "Script file does not exist. Please provide a valid script file name" << endl;
		cin >> script_file;

		script_handler.open(script_file, ios::in);
	} 

	script_handling.set_start_time();

	string command;
	vector<string> command_set;

	while(!bad_input && !script_handler.eof()) {
		getline(script_handler, command);
		TrimSpaces(command);

		if(!command.empty())
			command_set.push_back(command);
	}

	script_handler.close();

	HandleCommands(command_set, file_loader, file_loaded);
	script_handling.set_end_time();
		
	cout << "Handling of the script file took " << script_handling.get_execution_time() << " seconds" << endl;
	return 0;	
}

/*
The main method displays the menu to run the program. There are 2 levels of menus.
	- the first level asks the user to input if they want to run an existing script or create their own script or run a set of predetermined commands
	- under each of the high level menus there are commands to run the commands
*/
int main() {
	int input = 4;
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
		/*
		This case allows the user to provide an existing script
		*/
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
				input = 4;
				break;
			} else if(sub_input == 'b') {
				//b - To go back to the main menu
				input = 4;
				break;
			} else {
				//no valid entry was provided
				cout << "Please provide a valid entry" << endl;
			}
		/*
		This case allows the user to create their own script
		*/
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
					TrimSpaces(command);

					if(command.compare("done") == 0) {
						done = 1;
					} else {
						command_set.push_back(command);
					}
				}

				custom_commands_handling.set_start_time();
				HandleCommands(command_set, loader, file_loaded);
				custom_commands_handling.set_end_time();

				cout << "Handling of the custom commands took " << custom_commands_handling.get_execution_time() << " seconds" << endl;
				input = 4;
				break;
			} else if(sub_input == 'b') {
				//b - To go back to the main menu
				input = 4;
				break;
			} else {
				//no valid entry was provided
				cout << "Please provide a valid entry" << endl;
			}
		/*
		This case allows the user to run a set of predetermined commands. A file must be loaded before any of the transformations or printing, saving and calculating normals can happen
		In each of the transformation selection, the transformation matrix is generated and the vertices are multiplied by a column vector format vertex
		*/
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
					double angle = NULL;

					cout << "Please provide an arbitrary axis and an angle to rotate the vertices by, in the form x y z angle" << endl;
					cin >> arbitrary_axis_vertex.x >> arbitrary_axis_vertex.y >> arbitrary_axis_vertex.z >> angle;

					if(angle == NULL) {
						cout << "Correct values were not provided to free-rotate the vertices" << endl;
						cin.clear();
						cin.ignore(1024, '\n');
					} else {
						int vertices_vector_size = loader->vertices->size();
						for(int i = 0; i < vertices_vector_size; i++) {
							Matrix current_matrix = matrix_handler.generate_column_vector(loader->vertices->at(i), 3);
							matrix_handler.do_free_rotation(arbitrary_axis_vertex, angle, current_matrix);
							loader->vertices->at(i) = matrix_handler.generate_vertex_from_matrix(current_matrix);
						}
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
					input = 4;
					break;
				} else {
					//no valid entry was provided
					cout << "Please provide a valid entry" << endl;
				}
				input = 4;
			}

		default:
			cout << "Please provide a valid entry" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			break;
		}
	}

	cout << "\n\nThank you for experiencing Aly's world of Geometry Manipulation" << endl;
	cout << "Bye! \n" << endl;

	loader->~FileLoader();

	cout << "Type x to exit" << endl;
	cin >> exit;

	return 0;
}