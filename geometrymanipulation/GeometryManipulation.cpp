#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include "VectorManipulations.h"
#include "MatrixManipulations.h"
#include "FileLoader.h"
#include "ProgramTimer.h"

using namespace std;

void HandleScript(string& script_file) {

}

void HandleCustomCommands(vector<string>& custom_commands) {

}

int main() {
	int input;
	char sub_input, exit;

	cout << "Welcome to Aly's world of Geometry Manipulation \n" << endl;

	while(input != 0) {
		cout << "Please select one of the following options:" << endl;
		cout << "	1 - To run an existing script" << endl;
		cout << "	2 - To run a set of pre-determined commands" << endl;
		cout << "	3 - To run custom commands" << endl;
		cout << "	0 - To exit" << endl;

		cin >> input;

		switch(input) {
		case 1:
			cout << "Please select from one of the following options:" << endl;
			cout << "a - To run an existing script file" << endl;
			cout << "b - To go back to the main menu" << endl;

			cin >> sub_input;

			if(sub_input == 'a') {
				string script_name;
				cout << "Please provide a file name" << endl;
				cin >> script_name;

				HandleScript(script_name);
			} else if(sub_input == 'b') {
				break;
			} else {
				cout << "Please provide a valid entry" << endl;
			}
		case 2:
			cout << "Please select from one of the following options:" << endl;
			cout << "a - To run custom commands" << endl;
			cout << "b - To go back to the main menu" << endl;

			cin >> sub_input;

			if(sub_input == 'a') {
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

				HandleCustomCommands(command_set);
			} else if(sub_input == 'b') {
				break;
			} else {
				cout << "Please provide a valid entry" << endl;
			}

		case 3:
			bool file_loaded = false;
			FileLoader* loader = new FileLoader();

			while(sub_input != 'i') {
				cout << "Please select from one of the following options:" << endl;
				cout << "a - Load a geometry file" << endl;
				if(!file_loaded) {
					cout << "b - Print the current geometry to screen" << endl;
					cout << "c - Save the current geometry to file" << endl;
					cout << "d - Translate by a specified vector" << endl;
					cout << "e - Scale by a specified scalar" << endl;
					cout << "f - Rotate the vertices around the x, y or z axis" << endl;
					cout << "g - Rotate the vertices around an arbitrary axis" << endl;
					cout << "h - Generate a list of unit normals and save to file" << endl;
				}
				cout << "i - To go back to the main menu" << endl;

				cin >> sub_input;

				if(sub_input == 'a') {
					string input_file;

					cout << "Please enter a filename" << endl;
					cin >> input_file;

					int file_loaded = loader->LoadNewFile(input_file);

					if(file_loaded == 0) {
						file_loaded = true;
						cout << input_file << " loaded successfully!" << endl;
					} else {
						cout << input_file << " is either open or does not exist. Please take appropriate action" << endl;
					}
				} else if(file_loaded && sub_input == 'b') {
					cout << loader->vertices << endl;
				} else if(file_loaded && sub_input == 'c') {
					string save_file;
					
					cout << "Please provide a filename to save to" << endl;
					cin >> save_file;

					fstream vertices_file;

					if(vertices_file.is_open()) {
						vertices_file.open(save_file, ios::out);
						vertices_file << loader->vertices << endl;
						vertices_file.close();
					} else {
						cout << save_file << " is currently open. Please close the file and retry saving" << endl;
					}
				} else if(file_loaded && sub_input == 'd') {
					
				} else if(file_loaded && sub_input == 'e') {
					
				} else if(file_loaded && sub_input == 'f') {
					
				} else if(file_loaded && sub_input == 'g') {
					
				} else if(file_loaded && sub_input == 'h') {
					
				} else if(sub_input == 'i') {
					break;
				} else {
					cout << "Please provide a valid entry" << endl;
				}
			}

			loader->~FileLoader();
		}
	}

	cout << "Thank you for experiencing Aly's world of Geometry Manipulation" << endl;
	cout << "Bye! \n" << endl;

	cout << "Type x to exit" << endl;
	cin >> exit;

	return 0;
}

/*
int main() {
	int exit;

	ProgramTimer pt;	
	pt.set_start_time();

	string input_file = "default.txt";
	string normal_file = "normals.txt";
	FileLoader* loader = new FileLoader();

	loader->LoadNewFile(input_file);
	loader->GenerateNormals(normal_file);

	pt.set_end_time();

	cout << "Program execution took " << pt.get_execution_time() << " seconds" << endl;
	
	cout << "Type a number to exit" << endl;
	cin >> exit;
	return 0;
}
*/