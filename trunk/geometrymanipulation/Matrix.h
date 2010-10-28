#ifndef MATRIX_H
#define MATRIX_H

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