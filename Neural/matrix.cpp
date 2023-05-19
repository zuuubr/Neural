#include "matrix.h"
#include <iostream>

Matrix::Matrix() : row(0), col(0), array(nullptr) { }

Matrix::Matrix(int _row, int _col, float value) : row(_row), col(_col), array(nullptr) {
	array = new float* [row];
	for (int i = 0; i < row; i++) {
		array[i] = new float[col];
		for (int j = 0; j < col; j++) array[i][j] = value;
	}
}

float Matrix::getElement(int _row, int _col) const {
	if (_row > row || _row < 0 || _col > col || _col < 0) {
		std::cout << "ERROR: accessing a nonexistent variable." << std::endl;
		exit(1);
	}

	return array[_row][_col];
}

void Matrix::toApplyElement(int _row, int _col, float value) {
	array[_row][_col] = value;
}

int Matrix::size() const {
	return col * row;
}

int Matrix::rowSize() const {
	return row;
}

int Matrix::colSize() const {
	return col;
}

void Matrix::show() const {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			std::cout << array[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix Matrix::transponse() const {
	Matrix result(col, row);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.array[j][i] = array[i][j];
		}
	}

	return result;
}

Matrix Matrix::max() const {
	float max = array[0][0];
	int index_x, index_y;
	Matrix result(1, 2);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (array[i][j] > max) {
				max = array[i][j];
				result.array[0][0] = i;
				result.array[0][1] = j;
			}
		}
	}

	return result;
}

Matrix Matrix::min() const {
	float min = array[0][0];
	int index_x, index_y;
	Matrix result(1, 2);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (array[i][j] < min) {
				min = array[i][j];
				result.array[0][0] = i;
				result.array[0][1] = j;
			}
		}
	}

	return result;
}

Matrix Matrix::operator+(const Matrix& right) const {
	if (row != right.row || col != right.col)
	{
		std::cout << "ERROR: arrays of different sizes." << std::endl;
		exit(1);
	}

	Matrix result(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.array[i][j] = array[i][j] + right.array[i][j];
		}
	}

	return result;
}

Matrix& Matrix::operator+=(const Matrix& right) {
	if (row != right.row || col != right.col)
	{
		std::cout << "ERROR: arrays of different sizes." << std::endl;
		exit(1);
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			array[i][j] = array[i][j] + right.array[i][j];
		}
	}

	return *this;
}

Matrix Matrix::operator-(const Matrix& right) const {
	if (row != right.row || col != right.col)
	{
		std::cout << "ERROR: arrays of different sizes." << std::endl;
		exit(1);
	}

	Matrix result(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.array[i][j] = array[i][j] - right.array[i][j];
		}
	}

	return result;
}

Matrix& Matrix::operator-=(const Matrix& right) {
	if (row != right.row || col != right.col)
	{
		std::cout << "ERROR: arrays of different sizes." << std::endl;
		exit(1);
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			array[i][j] = array[i][j] - right.array[i][j];
		}
	}

	return *this;
}

Matrix Matrix::operator*(const Matrix& right) const {
	if (col != right.row) {
		std::cout << "matrices are incompatible." << std::endl;
		exit(1);
	}

	Matrix result(row, right.col);
	for (int i = 0; i < result.row; i++) {
		for (int j = 0; j < result.col; j++) {
			result.array[i][j] = 0;
			for (int k = 0; k < right.row; k++) {
				result.array[i][j] = result.array[i][j] + array[i][k] * right.array[k][j];
			}
		}
	}

	return result;
}

Matrix Matrix::operator*(float value) const {
	Matrix result(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
		{
			result.array[i][j] = array[i][j] * value;
		}
	}

	return result;
}

Matrix Matrix::operator/(float value) const {
	if (!value) {
		std::cout << "division by zero." << std::endl;
		exit(1);
	}

	Matrix result(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
		{
			result.array[i][j] = array[i][j] / value;
		}
	}

	return result;
}

Matrix& Matrix::operator=(const Matrix& right) {

	if (row != right.row || col != right.col)
	{
		for (int i = 0; i < row; i++) {
			delete[] array[i];
		}
		delete[] array;

		row = right.row;
		col = right.col;

		array = new float* [row];
		for (int i = 0; i < row; i++) {
			array[i] = new float[col];
			for (int j = 0; j < col; j++) {
				array[i][j] = right.array[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				array[i][j] = right.array[i][j];
			}
		}
	}

	return *this;
}

Matrix operator*(float value, const Matrix& right) {
	Matrix result(right.row, right.col);
	for (int i = 0; i < right.row; i++) {
		for (int j = 0; j < right.col; j++) {
			result.array[i][j] = value * right.array[i][j];
		}
	}

	return result;
}

Matrix multiplication(const Matrix& left, const Matrix& right) {
	if (left.row != right.row || left.col != right.col)
	{
		std::cout << "ERROR: arrays of different sizes!" << std::endl;
		exit(1);
	}

	Matrix result(left.row, left.col);
	for (int i = 0; i < left.row; i++) {
		for (int j = 0; j < left.col; j++) {
			result.array[i][j] = left.array[i][j] * right.array[i][j];
		}
	}

	return result;
}

Matrix::~Matrix() {
	for (int i = 0; i < row; i++) delete[] array[i];
	delete array;
}
