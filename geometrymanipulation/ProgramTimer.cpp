#include <iostream>
#include "ProgramTimer.h"

using namespace std;

ProgramTimer::ProgramTimer() {

}

ProgramTimer::~ProgramTimer() {

}

int ProgramTimer::get_start_time() {
	return start_time;
}

void ProgramTimer::set_start_time() {
	start_time = clock();
}

int ProgramTimer::get_end_time() {
	return end_time;
}

void ProgramTimer::set_end_time() {
	end_time = clock();
}

double ProgramTimer::get_execution_time() {
	return (double)(end_time - start_time)/CLOCKS_PER_SEC;
}