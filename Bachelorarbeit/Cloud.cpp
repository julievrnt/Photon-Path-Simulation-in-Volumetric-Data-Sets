#include "Cloud.h"

void Cloud::readData(string dataName, std::string xName, std::string yName, std::string zName)
{
	fstream fin;
	fin.open(dataName, ios::in);
	float nccloud, coord;
	while (fin >> nccloud) {
		if (nccloud > nccloud_max)
			nccloud_max = nccloud;
		daten.push_back(nccloud);
	}
	fin.close();

	fin.open(xName, ios::in);
	while (fin >> coord) {
		numberX++;
		xCoord.push_back(coord);
		if (coord > coord_max)
			coord_max = coord -xCoord[0];
	}
	fin.close();

	fin.open(yName, ios::in);
	while (fin >> coord) {
		numberY++;
		yCoord.push_back(coord);
		if (coord > coord_max) 
			coord_max = coord - yCoord[0];
	}
	fin.close();

	fin.open(zName, ios::in);
	while (fin >> coord)
		zCoord.push_back(coord);
	fin.close();
}

void reduce(vector<float>& a, float& coord_max) {
	float min = a[0];
	if (coord_max <= 1) return;
	for (int i = 0; i < a.size(); i++) {
		a[i] = (a[i] - min) / coord_max;
	}
}

void Cloud::reduceBox() {
	reduce(xCoord, coord_max);
	reduce(yCoord, coord_max);
	float zMax = zCoord.back() - zCoord.front();
	reduce(zCoord, zMax);
}

void metropolisHastings(vector<float>& s) {
	float x_i, x_j;

	//initialisation
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	normal_distribution<float> nd(0, 90);
	uniform_real_distribution<float> ud(0, 1);
	x_i = nd(generator);

	float accept = 0, reject = 0;
	for (int i = 0; i < 100000; i++) {
		nd = normal_distribution<float>(x_i, 90);
		x_j = nd(generator);
		float hg_x_i = rayleighFunction(x_i), hg_x_j = rayleighFunction(x_j);
		float alpha = hg_x_j / hg_x_i;
		float u = ud(generator);
		if (alpha > u) {
			x_i = x_j;
			if (i % 100 == 0)
				s.push_back(x_i);
		}
		else
			i--;
	}
}

float getAngle(vector<float>& x, vector<float>& s) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<float> ud(0, 1);
	float u, lambda, x_final;
	int index;
	do {
		u = ud(generator);
		index = getIndex(s, u);
	} while (index >= s.size() - 1);

	lambda = (u - s[(double)index + 1]) / (s[index] - s[(double)index + 1]);
	x_final = lambda * x[index] + (1 - lambda) * x[(double)index + 1];

	return x_final;
}

void cdfHG(vector<float>& prob) {
	vector<float> x, cdf;

	for (int i = 0; i <= 6282; i++)
		x.push_back(-3.141f + i * 0.001f);

	cdf.push_back(0);
	for (int i = 0; i < x.size(); i++)
		//cdf.push_back(rayleighFunction(x[i]) + hg[i]);
		cdf.push_back(hgFunction(x[i]) + cdf[i]);
	cdf.erase(cdf.begin());

	for (int i = 0; i < cdf.size(); i++)
		cdf[i] /= cdf.back();

	for (int i = 0; i < 1000; i++)
		prob.push_back(getAngle(x, cdf));
}

void inverseCDF(vector<float>& prob) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<float> ud(0, 1);
	float xi;

	for (int i = 0; i < 1000; i++) {
		xi = ud(generator);
		//prob.push_back(acos(rayleighInverseFunction(xi)));
		prob.push_back(acos(hgInverseFunction(xi)));
	}
}

void Cloud::createSampling() {
	inverseCDF(prob);
	//cdfHG(prob);
	//metropolisHastings(prob);
}