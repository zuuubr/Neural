#include "matrix.h"

Matrix::Matrix() {
	size_x = 1;
	size_y = 1;

	matrix = new float*[1];
	matrix[0] = new float[1];
	matrix[0][0] = 0.0;
}

Matrix::Matrix(int _size_y, int _size_x, float num) {
	size_x = _size_x;
	size_y = _size_y;

	matrix = new float*[size_x];
	for (int i = 0; i < size_x; i++) {
		matrix[i] = new float[size_y];
	}

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			matrix[i][j] = num;
		}
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

void Matrix::show() {
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			std::cout << getElement(i, j) << "\t";
		}
		std::cout << std::endl;
	}
}

Matrix Matrix::transponse() {
	Matrix result(size_x, size_y);
	for (int i = 0; i < result.size_x; i++) {
		for (int j = 0; j < result.size_y; j++) {
			result.matrix[i][j] = this->matrix[j][i];
		}
	}

	return result;
}

Matrix multiplication(const Matrix left, const Matrix right) {
	if (left.size_x != right.size_x || left.size_y != right.size_y)
	{
		std::cout << "ERROR: arrays of different sizes!" << std::endl;
		exit(1);
	}

	Matrix result(left.size_x, left.size_y);
	for (int i = 0; i < left.size_x; i++) {
		for (int j = 0; j < left.size_y; j++) {
			result.toApplyElement(i, j, left.matrix[i][j] * right.matrix[i][j]);
		}
	}

	return result;
}

Matrix Matrix::operator+(const Matrix& right) {
	if (size_x != right.size_x || size_y != right.size_y)
	{
		std::cout << "ERROR: arrays of different sizes!" << std::endl;
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
		std::cout << "ERROR: arrays of different sizes!" << std::endl;
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
	if (size_x != right.size_y) {
		std::cout << "ERROR: arrays of different sizes!" << std::endl;
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
		std::cout << "ERROR: arrays of different sizes!" << std::endl;
		exit(1);
	}

	Matrix result(size_y, size_x);
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
		std::cout << "ERROR: arrays of different sizes!" << std::endl;
		exit(1);
	}

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			toApplyElement(i, j, matrix[i][j] - right.matrix[i][j]);
		}
	}

	return *this;
}

Matrix& Matrix::operator=(const Matrix& right) {
	if (&right != this) // чтобы не выполнялось самоприсваивание
	{
		if (this->size_x != right.size_x || this->size_y != right.size_y)
		{
			for (int i = 0; i < this->size_x; i++) {
				delete[] this->matrix[i];
			}
			delete[] this->matrix;

			this->size_x = right.size_x; // установить нужный размер матрицы
			this->size_y = right.size_y;

			this->matrix = new float* [this->size_x];
			for (int i = 0; i < this->size_x; i++) {
				this->matrix[i] = new float[this->size_y];
			}
		}

		for (int i = 0; i < this->size_x; i++)
			for (int j = 0; j < this->size_y; j++)
				this->matrix[i][j] = right.matrix[i][j]; // скопировать массив
	}

	return *this;
}

Matrix Matrix::operator*(float num) {

	Matrix result(this->size_y, this->size_x);
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < this->size_y; j++) {
			result.matrix[i][j] = this->matrix[i][j] * num;
		}
	}

	return result;
}

Matrix operator*(float num, const Matrix& right)
{
	Matrix result(right.size_y, right.size_x);
	for (int i = 0; i < right.size_x; i++) {
		for (int j = 0; j < right.size_y; j++) {
			result.matrix[i][j] = right.matrix[i][j] * num;
		}
	}

	return result;
}

Matrix Matrix::operator/(float num) {
	if (!num) {
		std::cout << "ERROR: division by zero" << std::endl;
		exit(1);
	}

	Matrix result(this->size_y, this->size_x);
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < this->size_y; j++) {
			result.matrix[i][j] = this->matrix[i][j] / num;
		}
	}

	return result;
}

Matrix::~Matrix() {
	for (int i = 0; i < size_x; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
 