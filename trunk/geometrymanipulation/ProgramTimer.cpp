#include <iostream>
#include "ProgramTimer.h"

using namespace std;

/*
The default empty constructor
*/
ProgramTimer::ProgramTimer() {

}

/*
The default empty destructor
*/
ProgramTimer::~ProgramTimer() {

}

/*
returns the start time
*/
int ProgramTimer::get_start_time() {
	return start_time;
}

/*
sets the start time to the current clock value
*/
void ProgramTimer::set_start_time() {
	start_time = clock();
}

/*
returns the end time
*/
int ProgramTimer::get_end_time() {
	return end_time;
}

/*
sets the end time to the current clock time
*/
void ProgramTimer::set_end_time() {
	end_time = clock();
}

/*
calculates the execution time by subtracting start time and end time and dividing by clocks per second
*/
double ProgramTimer::get_execution_time() {
	return (double)(end_time - start_time)/CLOCKS_PER_SEC;
}