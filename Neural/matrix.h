#pragma once

class Matrix {
private:
	float** array;
	int row, col;
public:
	Matrix();
	Matrix(int, int, float = 0.0);

	float getElement(int, int) const;
	void toApplyElement(int, int, float);
	int size() const;
	int rowSize() const;
	int colSize() const;
	Matrix max() const;
	Matrix min() const;
	void show() const;
	Matrix transponse() const;

	Matrix operator+(const Matrix&) const;
	Matrix& operator+=(const Matrix&);
	Matrix operator-(const Matrix&) const;
	Matrix& operator-=(const Matrix&);
	Matrix operator*(const Matrix&) const;
	Matrix operator*(float) const;
	Matrix operator/(float) const;
	Matrix& operator=(const Matrix&);

	friend Matrix operator*(float, const Matrix&);
	friend Matrix multiplication(const Matrix&, const Matrix&);
	~Matrix();
};
