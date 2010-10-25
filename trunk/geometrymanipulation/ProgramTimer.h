#include <time.h>

class ProgramTimer {
public:
	ProgramTimer();
	~ProgramTimer();
	int get_start_time();
	void set_start_time();
	int get_end_time();
	void set_end_time();
	double get_execution_time();
private:
	int start_time;
	int end_time;
};