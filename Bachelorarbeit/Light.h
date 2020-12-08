#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "Cloud.h"

class Light
{
private:
	Cloud *cloud;
	Eigen::Vector3f position;
	Eigen::Vector3f direction;
	float scalar = 0.001;
	vector<Eigen::Vector3f> path;
	vector<float> nccloud_values;

	Eigen::Vector3f getCell(Eigen::Vector3f& v);

public:
	Light(Eigen::Vector3f p, Eigen::Vector3f d, Cloud *c) {
		position = p;
		direction = d.normalized();
		cloud = c;
	}
	bool isInCloud();
	size_t getSize() {
		return path.size();
	}
	void updatePosition();
	void updateDirection();
	Eigen::Vector3f getPosition() {
		return position;
	}
	void updatePath();
	int savePath(int i, int n);
};

#endif