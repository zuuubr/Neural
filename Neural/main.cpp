#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

class Neural {
private:
	int inputNodes, hiddenNodes, outputNodes;
	float speedLearning;
	Matrix weightInputToHidden, weightHiddenToOutput;
public:
	Neural() {};
	Neural(int, int, int, float = 0.3);
	inline float sigma(float num) { return (1 / (1 + exp(-num))); }
	Matrix query(Matrix&);
	Matrix train(Matrix, Matrix);
	bool saveWeights(Matrix&, Matrix&, std::string = "neuralWeights.txt");
	bool loadWeights(std::string = "neuralWeights.txt");
	//~Neural();
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

Matrix Neural::query(Matrix& inputs) {
	Matrix hiddenInputs, hiddenOutputs, finalInputs, finalOutputs;

	hiddenInputs = weightInputToHidden * inputs;
	hiddenOutputs = hiddenInputs;
	for (int i = 0; i < hiddenInputs.colSize(); i++) {
		for (int j = 0; j < hiddenInputs.rowSize(); j++) {
			hiddenOutputs.toApplyElement(i, j, sigma(hiddenInputs.getElement(i, j)));
		}
	}

	finalInputs = weightHiddenToOutput * hiddenOutputs;
	finalOutputs = finalInputs;
	for (int i = 0; i < finalInputs.colSize(); i++) {
		for (int j = 0; j < finalInputs.rowSize(); j++) {
			finalOutputs.toApplyElement(i, j, sigma(finalInputs.getElement(i, j)));
		}
	}

	return finalInputs;
}

Matrix Neural::train(Matrix inputs, Matrix targets) {
	Matrix hiddenInputs, hiddenOutputs, finalInputs, finalOutputs;
	Matrix outputError, hiddenError;

	hiddenInputs = weightInputToHidden * inputs.transponse();
	hiddenOutputs = hiddenInputs;
	for (int i = 0; i < hiddenInputs.colSize(); i++) {
		for (int j = 0; j < hiddenInputs.rowSize(); j++) {
			hiddenOutputs.toApplyElement(i, j, sigma(hiddenInputs.getElement(i, j)));
		}
	}

	finalInputs = weightHiddenToOutput * hiddenOutputs;
	finalOutputs = finalInputs;
	for (int i = 0; i < finalInputs.colSize(); i++) {
		for (int j = 0; j < finalInputs.rowSize(); j++) {
			finalOutputs.toApplyElement(i, j, sigma(finalInputs.getElement(i, j)));
		}
	}

	Matrix buferHiddenOutputs = hiddenOutputs.transponse();
	outputError = targets - finalOutputs;
	hiddenError = buferHiddenOutputs * outputError;

	Matrix sigmaFinalOutputs = finalOutputs, sigmaHiddenOutputs = hiddenOutputs;
	for (int i = 0; i < sigmaFinalOutputs.colSize(); i++) {
		for (int j = 0; j < sigmaFinalOutputs.rowSize(); j++) {
			sigmaFinalOutputs.toApplyElement(i, j, sigma(finalOutputs.getElement(i, j)));
			sigmaHiddenOutputs.toApplyElement(i, j, sigma(hiddenOutputs.getElement(i, j)));
		}
	}

	Matrix deltaSigma = sigmaFinalOutputs - (sigmaFinalOutputs * sigmaFinalOutputs);
	weightHiddenToOutput += speedLearning * ((multiplication(outputError, deltaSigma)) * hiddenOutputs.transponse());

	deltaSigma = sigmaHiddenOutputs - (sigmaHiddenOutputs * sigmaHiddenOutputs);
	weightInputToHidden += speedLearning * ((multiplication(hiddenError, deltaSigma)) * inputs.transponse());

	return outputError;
}

Matrix getTarget(int size, int targetCount) {
	if (size <= 0 || targetCount >= size || targetCount < 0) {
		std::cout << "ERROR: not right argument for target diaposone!" << std::endl;
		exit(1);
	}

	Matrix result(size, 1, 0.01);
	result.toApplyElement(0, targetCount, 0.99);

	return result;
}

std::vector<std::string> getArguments(std::string str, char delimiter = ',') {
	std::string bufer;
	std::vector<std::string> result;
	result.reserve(10);

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == delimiter || str[i] == delimiter) {
			result.push_back(bufer);
			bufer.clear();
		}
		else {
			bufer += str[i];
		}
	}

	return result;
}

int main() {
	Matrix inputs(1, 3);
	Neural network(3, 3, 3);
	Matrix target, result;

	std::vector<std::string> arguments;

	std::string stringInput;
	std::ifstream fin("mnist_train.csv");

	std::getline(fin, stringInput);
	arguments = getArguments(stringInput);
	target = getTarget(10, std::stoi(arguments[0]));


	//for (int j = 1; j < arguments.size(); j++) {
	//	inputs.toApplyElement(0, j, std::stoi(arguments[j]));
	//}
	for (int i = 0; i < inputs.colSize(); i++) {
		for (int j = 0; j < inputs.rowSize(); j++) {
			inputs.toApplyElement(i, j, i + j);
		}
	}

	while (1) {
		result = network.train(inputs, target);
		result.show();
		std::cout << "=============" << std::endl;
	}


		
	return 0;
}
