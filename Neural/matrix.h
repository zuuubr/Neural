#pragma once
#include <vector>
#include <iostream>

#define STEP_MASSIVE_SIZE 10

class Matrix {
private:
	float** matrix;
	int size_x, size_y;
public:
	Matrix(int, int);
	float getElement(int, int);
	void toApplyElement(int, int, float);
	int size();
	int rowSize();
	int colSize();
	void show();
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