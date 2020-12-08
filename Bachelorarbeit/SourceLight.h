#pragma once
#ifndef SOURCELIGHT_H
#define SOURCELIGHT_H

#include "Light.h"

class SourceLight
{
private:
	Cloud* cloud;
	vector<Light> rays;
	Eigen::Vector3f spos = Eigen::Vector3f(-0.001, 0.36, 0.721);

public:
	SourceLight(Cloud* c) {
		cloud = c;
	}
	void generateLight(int nrays);
	void addRay(Light ray) {
		rays.push_back(ray);
	}
	void update();
	void updatePath();
	void savePath();
	void eraseNS();
};

#endif