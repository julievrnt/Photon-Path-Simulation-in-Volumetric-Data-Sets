#pragma once
#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <ctime> 
#include <cstdlib> 
#include <Eigen/Dense>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <random>
#include <chrono>

using namespace std;

void toString(vector<float>& a);

float hgFunction(float teta);

float hgInverseFunction(float xi);

float rayleighFunction(float teta);

float rayleighInverseFunction(float xi);

float rayleighCoefficient(float n, float d, float lambda);

Eigen::Vector3f randomPoint(float z_max);

bool operator<=(Eigen::Vector3f a, Eigen::Vector3f b);

bool operator>=(Eigen::Vector3f a, Eigen::Vector3f b);

int getIndex(vector<float>& a, float k);

Eigen::Matrix3f rotateX(float angle);

Eigen::Matrix3f rotateY(float angle);

Eigen::Matrix3f rotateZ(float angle);

#endif