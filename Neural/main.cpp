#include <iostream>
#include "matrix.h"

int main() {
	Matrix matrix_one(3, 3);
	Matrix matrix_two(1, 3);
	Matrix matrix_three(1, 3);

	for (int i = 0; i < matrix_one.colSize(); i++) {
		for (int j = 0; j < matrix_one.rowSize(); j++) {
			matrix_one.toApplyElement(i, j, i + j);
		}
	}

	for (int i = 0; i < matrix_one.colSize(); i++) {
		for (int j = 0; j < matrix_one.rowSize(); j++) {
			std::cout << matrix_one.getElement(i, j) << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "====================" << std::endl;

	for (int i = 0; i < matrix_two.colSize(); i++) {
		for (int j = 0; j < matrix_two.rowSize(); j++) {
			matrix_two.toApplyElement(i, j, i + j);
		}
	}

	for (int i = 0; i < matrix_two.colSize(); i++) {
		for (int j = 0; j < matrix_two.rowSize(); j++) {
			std::cout << matrix_two.getElement(i, j) << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "====================" << std::endl;

	matrix_three = matrix_one * matrix_two;
	for (int i = 0; i < matrix_three.colSize(); i++) {
		for (int j = 0; j < matrix_three.rowSize(); j++) {
			std::cout << matrix_three.getElement(i, j) << "\t";
		}
		std::cout << std::endl;
	}
	return 0;
}