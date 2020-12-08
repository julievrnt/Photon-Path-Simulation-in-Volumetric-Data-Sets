#pragma once
#ifndef	CLOUD_H
#define CLOUD_H

#include "HelpFunctions.h"

#include <fstream>

class Cloud {
private:
	vector<float> daten, prob;
	vector<float> xCoord, yCoord, zCoord;
	float nccloud_max = 0, coord_max = 0;
	float mieScatCoef = 625930.0f, pathLength = 10000, rCoef = rayleighCoefficient(1.333, 20 * pow(10.0f, -6.0f), pow(10.0f, -4.0f)); //r = 10microns, n=1.333, lambda = 650nm, density 1#/micron, L = 10 000 MIE / 1000 RAYLEIGH
	int numberY = 0, numberX = 0;
	void readData(string dataName, std::string xName, std::string yName, std::string zName);
	void reduceBox();
	void createSampling();
	
public:
	Cloud(std::string dataName, std::string xName, std::string yName, std::string zName) {
		readData(dataName, xName, yName, zName);
		reduceBox();
		createSampling();
	}
	
	float getDatenNumberAt(int pos) {
		return daten[pos];
	}

	vector<float>* getXCoord() {
		return &xCoord;
	}

	vector<float>* getYCoord() {
		return &yCoord;
	}

	vector<float>* getZCoord() {
		return &zCoord;
	}

	int getProbSize(){
		return prob.size();
	}

	float getProbNumberAt(int index) {
		return prob[index];
	}

	float getProbLastNumber() {
		if (prob.empty())
			createSampling();
		float ln = prob.back();
		prob.pop_back();
		return ln;
	}

	float getNCCLOUDMAX() {
		return nccloud_max;
	}

	size_t getSize() {
		return daten.size();
	}

	int getNumberX() {
		return numberX;
	}

	int getNumberY() {
		return numberY;
	}

	float getMieScatCoef() {
		return mieScatCoef;
	}

	float getRCoef() {
		return rCoef;
	}

	float getPathLength() {
		return pathLength;
	}
};

#endif