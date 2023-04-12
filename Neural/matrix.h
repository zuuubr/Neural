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
	const Matrix transponse();
	const Matrix operator+(const Matrix&);
	const Matrix operator+=(const Matrix&);
	const Matrix operator-(const Matrix&);
	const Matrix operator-=(const Matrix&);
	const Matrix operator*(const Matrix&);
	const Matrix operator*(float);
	const Matrix operator/(float);
	const Matrix& operator=(const Matrix&);
	friend const Matrix operator*(float, const Matrix&);
	~Matrix();
};