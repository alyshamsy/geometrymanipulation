#ifndef Matrix_H
#define Matrix_H

/*
This class defines the structure of the Matrix which is made up of rows and columns and has an initial value

It has a constructor which takes in 3 parameters and sets the initial value to 0 and number of rows and columns to 3. 
There is also a copy constructor and a destructor along with getters for number of rows and columns
There are methods for getting and setting the matrix element and an assignment operator overload
*/

class Matrix {
public:
	Matrix(double init_value = 0, int rows = default_rows, int columns = default_columns);
	~Matrix();
	Matrix(const Matrix& src);

	int get_rows() { return rows; }
	int get_columns() { return columns; }
	void set_matrix_element(int row, int column, double value);
	double get_matrix_element(int row, int column);

	Matrix& operator=(const Matrix& rhs);

	static const int default_rows = 3;
	static const int default_columns = 3;
private:
	double** matrix;
	double init_value;
	int rows;
	int columns;
};
#endif