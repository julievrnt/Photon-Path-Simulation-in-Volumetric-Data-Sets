#include "SourceLight.h"

void SourceLight::generateLight(int nrays) {
	Eigen::Vector3f ldir;
	srand(time(0));

	for (int i = 0; i < nrays; i++) {
		ldir = randomPoint(1.0f)-spos;
		Light ray(spos, ldir, cloud);
		addRay(ray);
	}
}

void SourceLight::update() {
	for (int i = 0; i < rays.size(); i++) {
		if (rays[i].isInCloud())
			rays[i].updateDirection();
		rays[i].updatePosition();
	}
}

void SourceLight::updatePath() {
	for (int i = 0; i < rays.size(); i++)
		rays[i].updatePath();
}

void SourceLight::eraseNS() {
	for (int i = 0; i < rays.size(); i++) {
		if (rays[i].getSize() == 0) {
			rays.erase(rays.begin() + i);
			i--;
		}
	}
}

void SourceLight::savePath() {
	eraseNS();
	int n = 1;
	for (int i = 0; i < rays.size(); i++) {
		if (i % 1000 == 0)
			cout << i << endl;
		n = rays[i].savePath(i, n);
	}
}