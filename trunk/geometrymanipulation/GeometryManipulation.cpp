#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include "VectorManipulations.h"
#include "FileLoader.h"
#include "ProgramTimer.h"

using namespace std;


int main() {
	int exit;

	ProgramTimer pt;	
	pt.set_start_time();

	string input_file = "teapot.txt";
	//FileLoader* loader = new FileLoader();
	FileLoader* loader = new FileLoader(input_file);
	//loader->get_vertices_vector();
	//loader->get_faces_vector();

	pt.set_end_time();

	cout << "Program execution took " << pt.get_execution_time() << " seconds" << endl;
	
	cout << "Type a number to exit" << endl;
	cin >> exit;
	return 0;
}