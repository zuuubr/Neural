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
	Neural() { };
	Neural(int, int, int, float = 0.3);
	inline float sigma(float num) { return (1 / (1 + exp(-num))); }
	Matrix query(Matrix&);
	Matrix train(Matrix&, Matrix&);
	bool saveWeights(Matrix, Matrix, std::string = "neuralWeights.txt");
	bool loadWeights(std::string = "neuralWeights.txt");
	//~Neural();
};

Neural::Neural(int _inputNodes, int _hiddenNodes, int _outputNodes, float _speedLearning): inputNodes(_inputNodes), hiddenNodes(_hiddenNodes), outputNodes(_outputNodes), speedLearning(_speedLearning) {
	srand(time(NULL));
	float randomValue;

	// Создадим 2 матрицы весовых коэффициентов
	// от входного слоя до скрытого
	// от скрытого слоя до выходного

	Matrix bufWeightInputToHidden(hiddenNodes, inputNodes), bufWeightHiddenToOutput(outputNodes, hiddenNodes);
	for (int i = 0; i < bufWeightInputToHidden.rowSize(); i++) {
		for (int j = 0; j < bufWeightInputToHidden.colSize(); j++) {
			randomValue = rand() % (int)pow(10, 2);
			randomValue = -1 + (randomValue / pow(10, 2)) * 2;
			bufWeightInputToHidden.toApplyElement(i, j, randomValue);
		}
	}

	for (int i = 0; i < bufWeightHiddenToOutput.rowSize(); i++) {
		for (int j = 0; j < bufWeightHiddenToOutput.colSize(); j++) {
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
	for (int i = 0; i < hiddenInputs.rowSize(); i++) {
		for (int j = 0; j < hiddenInputs.colSize(); j++) {
			hiddenOutputs.toApplyElement(i, j, sigma(hiddenInputs.getElement(i, j)));
		}
	}

	finalInputs = weightHiddenToOutput * hiddenOutputs;
	finalOutputs = finalInputs;
	for (int i = 0; i < finalInputs.rowSize(); i++) {
		for (int j = 0; j < finalInputs.colSize(); j++) {
			finalOutputs.toApplyElement(i, j, sigma(finalInputs.getElement(i, j)));
		}
	}

	return finalOutputs;
}

Matrix Neural::train(Matrix& inputs, Matrix& targets) {

	Matrix hiddenInputs, hiddenOutputs, finalInputs, finalOutputs;
	Matrix outputError, hiddenError;
	Matrix bufFinalOutputs;
	Matrix sigmaFinalOutputs, sigmaHiddenOutputs;

	hiddenInputs = weightInputToHidden * inputs;
	hiddenOutputs = hiddenInputs;
	for (int i = 0; i < hiddenInputs.rowSize(); i++) {
		for (int j = 0; j < hiddenInputs.colSize(); j++) {
			hiddenOutputs.toApplyElement(i, j, sigma(hiddenInputs.getElement(i, j)));
		}
	}

	finalInputs = weightHiddenToOutput * hiddenOutputs;
	finalOutputs = finalInputs;
	for (int i = 0; i < finalInputs.rowSize(); i++) {
		for (int j = 0; j < finalInputs.colSize(); j++) {
			finalOutputs.toApplyElement(i, j, sigma(finalInputs.getElement(i, j)));
		}
	}


	hiddenInputs = weightInputToHidden * inputs;
	hiddenOutputs = hiddenInputs;
	for (int i = 0; i < hiddenInputs.rowSize(); i++) {
		for (int j = 0; j < hiddenInputs.colSize(); j++) {
			hiddenOutputs.toApplyElement(i, j, sigma(hiddenInputs.getElement(i, j)));
		}
	}

	finalInputs = weightHiddenToOutput * hiddenOutputs;
	finalOutputs = finalInputs;
	for (int i = 0; i < finalInputs.rowSize(); i++) {
		for (int j = 0; j < finalInputs.colSize(); j++) {
			finalOutputs.toApplyElement(i, j, sigma(finalInputs.getElement(i, j)));
		}
	}


	bufFinalOutputs = finalOutputs;
	outputError = targets - bufFinalOutputs;	// столбец row = 10 col = 1
	hiddenError = weightHiddenToOutput.transponse() * outputError; // weightHiddenToOutput row = 10 col = 100

	sigmaFinalOutputs = finalOutputs;
	sigmaHiddenOutputs = hiddenOutputs;

	for (int i = 0; i < sigmaFinalOutputs.rowSize(); i++) {
		for (int j = 0; j < sigmaFinalOutputs.colSize(); j++) {
			sigmaFinalOutputs.toApplyElement(i, j, sigma(finalOutputs.getElement(i, j)));
			sigmaHiddenOutputs.toApplyElement(i, j, sigma(hiddenOutputs.getElement(i, j)));
		}
	}

	Matrix deltaSigma = sigmaFinalOutputs - (multiplication(sigmaFinalOutputs, sigmaFinalOutputs));
	weightHiddenToOutput += speedLearning * ((multiplication(outputError, deltaSigma)) * hiddenOutputs.transponse());

	deltaSigma = sigmaHiddenOutputs - (multiplication(sigmaHiddenOutputs, sigmaHiddenOutputs));
	weightInputToHidden += speedLearning * ((multiplication(hiddenError, deltaSigma)) * inputs.transponse());

	return outputError;
}

Matrix getTarget(int size, int targetCount) {
	if (size <= 0 || targetCount >= size || targetCount < 0) {
		std::cout << "ERROR: not right argument for target diaposone!" << std::endl;
		exit(1);
	}

	Matrix result(size, 1, 0.01);
	result.toApplyElement(targetCount, 0, 0.99);

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
	Matrix inputs(784, 1);
	Neural network(784, 100, 10);
	Matrix target, result;

	std::vector<std::string> arguments;

	std::string stringInput;
	std::ifstream fin_train("mnist_train.csv");
	std::ifstream fin_test("mnist_test.csv");



	int i = 0;
	while (i < 10000) {
		std::getline(fin_train, stringInput);
		arguments = getArguments(stringInput);
		target = getTarget(10, std::stoi(arguments[0]));


		for (int j = 0; j < arguments.size() - 1; j++) {
			inputs.toApplyElement(j, 0, std::stoi(arguments[j + 1]));
		}

		result = network.train(inputs, target);
		result.show();

		std::cout << "=====" << i + 2 << "=======" << std::endl;
		i++;
	}

	Matrix answer;
	i = 0;
	while (i < 10000) {
		std::getline(fin_test, stringInput);
		arguments = getArguments(stringInput);
		target = getTarget(10, std::stoi(arguments[0]));


		for (int j = 0; j < arguments.size() - 1; j++) {
			inputs.toApplyElement(j, 0, std::stoi(arguments[j + 1]));
		}

		result = network.query(inputs);
		//result.show();
		answer = result.max();
		std::cout << "======" << i + 2 << " - " << answer.getElement(0, 0) << " >>======" << std::endl;
		i++; 
	}

	fin_train.close();
	fin_test.close();
	return 0;

}
