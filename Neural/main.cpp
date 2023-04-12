#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

class Neural {
private:
	int inputNodes, hiddenNodes, outputNodes;
	float speedLearning;
	Matrix weightInputToHidden, weightHiddenToOutput;
public:
	Neural(int, int, int, float = 0.3);
	inline float sigma(float num) { return (1 / (1 + exp(-num))); }
	const Matrix query(Matrix&);
};

Neural::Neural(int _inputNodes, int _hiddenNodes, int _outputNodes, float _speedLearning) {
	srand(time(NULL));
	float randomValue;

	inputNodes = _inputNodes;
	hiddenNodes = _hiddenNodes;
	outputNodes = _outputNodes;
	speedLearning = _speedLearning;

	// Создадим 2 матрицы весовых коэффициентов
	// от входного слоя до скрытого
	// от скрытого слоя до выходного

	Matrix bufWeightInputToHidden(hiddenNodes, inputNodes), bufWeightHiddenToOutput(outputNodes, hiddenNodes);
	for (int i = 0; i < bufWeightInputToHidden.colSize(); i++) {
		for (int j = 0; j < bufWeightInputToHidden.rowSize(); j++) {
			randomValue = rand() % (int)pow(10, 2);
			randomValue = -1 + (randomValue / pow(10, 2)) * 2;
			bufWeightInputToHidden.toApplyElement(i, j, randomValue);
		}
	}

	for (int i = 0; i < bufWeightHiddenToOutput.colSize(); i++) {
		for (int j = 0; j < bufWeightHiddenToOutput.rowSize(); j++) {
			randomValue = rand() % (int)pow(10, 2);
			randomValue = -1 + (randomValue / pow(10, 2)) * 2;
			bufWeightHiddenToOutput.toApplyElement(i, j, randomValue);
		}
	}

	weightInputToHidden = bufWeightInputToHidden;
	weightHiddenToOutput = bufWeightHiddenToOutput;
}

const Matrix Neural::query(Matrix& inputs) {
	Matrix hiddenInputs, hiddenOutputs, finalInputs, finalOutputs;
	inputs = inputs.transponse();

	hiddenInputs = weightInputToHidden * inputs;
	for (int i = 0; i < hiddenInputs.colSize(); i++) {
		for (int j = 0; j < hiddenInputs.rowSize(); j++) {
			hiddenOutputs.toApplyElement(i, j, sigma(hiddenInputs.getElement(i, j)));
		}
	}

	finalInputs = weightHiddenToOutput * hiddenOutputs;
	for (int i = 0; i < finalInputs.colSize(); i++) {
		for (int j = 0; j < finalInputs.rowSize(); j++) {
			finalOutputs.toApplyElement(i, j, sigma(finalInputs.getElement(i, j)));
		}
	}

	return finalInputs;
}

int main() {
	Neural network(3, 2, 3);
	return 0;
}
