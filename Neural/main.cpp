#include <iostream>
#include "matrix.h"

int main() {
	Matrix matrix_one(3, 3);
	Matrix matrix_two(3, 3);
	Matrix matrix_three(3, 3);

	for (int i = 0; i < matrix_one.colSize(); i++) {
		for (int j = 0; j < matrix_one.rowSize(); j++) {
			matrix_one.toApplyElement(i, j, i + j);
		}
	}

	for (int i = 0; i < matrix_two.colSize(); i++) {
		for (int j = 0; j < matrix_two.rowSize(); j++) {
			matrix_two.toApplyElement(i, j, i + j);
		}
	}


	matrix_one.show();
	std::cout << "====================" << std::endl;

	matrix_two.show();
	std::cout << "====================" << std::endl;

	matrix_three = matrix_one * 5;
	matrix_three.show();
	return 0;
}