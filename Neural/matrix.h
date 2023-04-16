#pragma once
#include <iostream>


class Matrix {
private:
	float** matrix;
	int size_x, size_y;
public:
	Matrix(int, int, float = 0);
	Matrix();
	float getElement(int, int);
	void toApplyElement(int, int, float);
	int size();
	int rowSize();
	int colSize();
	void show();
	Matrix transponse();
	friend Matrix multiplication(const Matrix, const Matrix);
	Matrix operator+(const Matrix&);
	Matrix operator+=(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator-=(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix operator*(float);
	Matrix operator/(float);
	Matrix& operator=(const Matrix&);
	friend Matrix operator*(float, const Matrix&);
	~Matrix();
};