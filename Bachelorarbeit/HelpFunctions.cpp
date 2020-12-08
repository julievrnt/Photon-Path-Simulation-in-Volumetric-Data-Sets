#include "HelpFunctions.h"

void toString(vector<float>& a) {
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << endl;
	}
	cout << endl;
}

float g = 0.857f; //-0.8 -0-5 0.857f

float hgFunction(float theta) {
	float num, denum;
	num = 1.0f - pow(g, 2.0f);
	denum = 1.0f + pow(g, 2.0f) - 2.0f * g * cos(theta);
	denum = 2.0f * pow(denum, 1.5f);
	return num / denum;
}

float hgInverseFunction(float xi) {
	float a, b, c;
	a = 1.0f / (2.0f * g);
	b = 1.0f + pow(g, 2.0f);
	c = (1.0f - pow(g, 2.0f)) / (1.0f - g + 2.0f * g * xi);
	return a * (b - pow(c, 2.0f));
}

float pi = 3.14159265358979323846;

float rayleighFunction(float theta) {
	float a, b;
	a = 3.0f / (16.0f * pi);
	b = 1 + pow(cos(theta), 2.0f);
	return a * b;
}

float rayleighInverseFunction(float xi) {
	float a, b, c, z;
	z = 2.0f * (2.0f * xi - 1);
	c = pow(pow(z, 2.0f) + 1.0f, 0.5f);
	a = pow(z + c, 1.0f / 3.0f);
	b = -pow(fabs(z - c), 1.0f / 3.0f);
	return a + b;
}


float rayleighCoefficient(float n, float d, float lambda) {
	float a, b, c;
	a = (2.0f * pow(pi, 5.0f)) / 3.0f;
	b = pow(d, 6.0f) / pow(lambda, 4.0f);
	c = (pow(n, 2.0f) - 1) / (pow(n, 2.0f) + 2);
	return a * b * pow(c, 2.0f);
}


Eigen::Vector3f randomPoint(float z_max) {
	float rx = (float)rand() / float(RAND_MAX), ry = (float)rand() / float(RAND_MAX), rz = ((float)rand() / float(RAND_MAX)) * z_max;
	return  Eigen::Vector3f(rx, ry, rz);
}

bool operator<=(Eigen::Vector3f a, Eigen::Vector3f b) {
	return a.x() <= b.x() && a.y() <= b.y() && a.z() <= b.z();
}

bool operator>=(Eigen::Vector3f a, Eigen::Vector3f b) {
	return b <= a;
}

int getIndex(vector<float>& a, float x) {

	int k = 0;
	int k1 = a.size() - 1;

	while (abs(k1 - k) > 1)
	{
		int kMid = (k + k1) / 2;
		float pMid = a[kMid];
		if (x >= pMid)
			k = kMid;
		else
			k1 = kMid;
	}
	if (abs(a[k] - x) > abs(a[k1] - x))
		return k1;
	return k;
}

Eigen::Matrix3f rotateX(float angle) {
	Eigen::Matrix3f r;
	r << 1, 0, 0,
		0, cos(angle), -sin(angle),
		0, sin(angle), cos(angle);
	return r;
}

Eigen::Matrix3f rotateY(float angle) {
	Eigen::Matrix3f r;
	r << cos(angle), 0, -sin(angle),
		0, 1, 0,
		sin(angle), 0, cos(angle);
	return r;
}

Eigen::Matrix3f rotateZ(float angle) {
	Eigen::Matrix3f r;
	r << cos(angle), -sin(angle), 0,
		sin(angle), cos(angle), 0,
		0, 0, 1;
	return r;
}