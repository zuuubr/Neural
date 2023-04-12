#include "matrix.h"

Matrix::Matrix(int _size_y, int _size_x) {
	size_x = _size_x;
	size_y = _size_y;

	matrix = new float*[size_x];
	for (int i = 0; i < size_x; i++) {
		matrix[i] = new float[size_y];
	}
}

float Matrix::getElement(int i, int j) {
	return matrix[i][j];
}

void Matrix::toApplyElement(int i, int j, float value) {
	matrix[i][j] = value;
}

int Matrix::size() {
	return size_x * size_y;
}

int Matrix::rowSize() {
	return size_y;
}

int Matrix::colSize() {
	return size_x;
}

Matrix Matrix::operator+(const Matrix& right) {
	if (size_x != right.size_x || size_y != right.size_y)
	{
		std::cout << "Arrays of different sizes!" << std::endl;
		exit(1);
	}

	Matrix result(size_x, size_y);
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			result.toApplyElement(i, j, matrix[i][j] + right.matrix[i][j]);
		}
	}

	return result;
}

Matrix Matrix::operator+=(const Matrix& right) {
	if (size_x != right.size_x || size_y != right.size_y)
	{
		std::cout << "Arrays of different sizes!" << std::endl;
		exit(1);
	}

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			toApplyElement(i, j, matrix[i][j] + right.matrix[i][j]);
		}
	}

	return *this;
}

Matrix Matrix::operator*(const Matrix& right) {
	if (size_y != right.size_x) {
		std::cout << "Arrays of different sizes!" << std::endl;
		exit(1);
	}

	Matrix result(right.size_y, right.size_x);
	for (int i = 0; i < result.size_x; i++) {
		for (int j = 0; j < result.size_y; j++) {
			result.toApplyElement(i, j, 0);
			for (int k = 0; k < right.size_x; k++) {
				result.toApplyElement(i, j, result.getElement(i, j) + matrix[i][k] * right.matrix[k][j]);
			}
		}
	}

	return result;
}

Matrix Matrix::operator-(const Matrix& right) {
	if (size_x != right.size_x || size_y != right.size_y)
	{
		std::cout << "Arrays of different sizes!" << std::endl;
		exit(1);
	}

	Matrix result(size_x, size_y);
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			result.toApplyElement(i, j, matrix[i][j] - right.matrix[i][j]);
		}
	}

	return result;
}

Matrix Matrix::operator-=(const Matrix& right) {
	if (size_x != right.size_x || size_y != right.size_y)
	{
		std::cout << "Arrays of different sizes!" << std::endl;
		exit(1);
	}

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			toApplyElement(i, j, matrix[i][j] - right.matrix[i][j]);
		}
	}

	return *this;
}

Matrix::~Matrix() {
	for (int i = 0; i < size_x; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}