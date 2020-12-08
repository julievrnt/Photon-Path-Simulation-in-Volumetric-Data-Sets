#include "Light.h"

void Light::updatePosition() {
	position += scalar * direction;
}

bool Light::isInCloud() {
	return Eigen::Vector3f::Zero() <= position && position <= Eigen::Vector3f(0.9f, 1.0f, 1.0f);
}

Eigen::Vector3f Light::getCell(Eigen::Vector3f& v) {
	int x = getIndex(*cloud->getXCoord(), v.x());
	int y = getIndex(*cloud->getYCoord(), v.y());
	int z = getIndex(*cloud->getZCoord(), v.z());
	return Eigen::Vector3f(x, y, z);
}

bool notScattered(float nccloud, float nccloud_max) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<float> ud(0, 1);
	float u = ud(generator);
	if (cbrt(nccloud / nccloud_max) < u)
		return true;
	return false;
}

bool mieS(float nccloud, float mieScatCoeff, float l) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<float> ud(0, 1);
	float u = ud(generator);
	float realMieScatCoef = (nccloud * mieScatCoeff) / (pow(10.0f, 18.0f));
	float t = exp(-realMieScatCoef * l);
	if (1 - t >= u)
		return true;
	return false;
}

bool rayleighS(float nccloud, float sigma_s, float l) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<float> ud(0, 1);
	float u = ud(generator);
	float scatCoef = nccloud * sigma_s;
	float t = exp(-scatCoef * l);
	cout << 1 - t << endl;
	system("pause");
	if (1 - t >= u)
		return true;
	return false;
}

void Light::updateDirection() {
	Eigen::Vector3f cell = getCell(position);
	float nccloud = cloud->getDatenNumberAt(cell.x() * cloud->getNumberY() + cell.y() + cell.z() * cloud->getNumberX() * cloud->getNumberY());

	if (nccloud == 0)
		return;
	//if (rayleighS(nccloud, cloud->getRCoef(), cloud->getPathLength())) {
	if (mieS(nccloud, cloud->getMieScatCoef(), cloud->getPathLength())) {
	//if (!notScattered(nccloud, cloud->getNCCLOUDMAX())) {
		Eigen::Matrix3f rotationMatrix = rotateX(cloud->getProbLastNumber()) * rotateY(cloud->getProbLastNumber()) * rotateZ(cloud->getProbLastNumber());
		direction = rotationMatrix * direction;
		direction.normalized();
	}
	nccloud_values.push_back(nccloud);
	updatePath();
}

void Light::updatePath() {
	path.push_back(position);
}

int Light::savePath(int r, int n) {
	fstream fout;
	fout.open("path.txt", std::ios_base::app);
	Eigen::Vector3f cell;
	float nccloud, nccloud_max = cloud->getNCCLOUDMAX();

	for (int i = 0; i < path.size(); i++) {
		fout << "v " << path[i].x() << " " << path[i].y() << " " << path[i].z() << " \n";
		nccloud = nccloud_values[i];
		fout << "vt " << cbrt(nccloud / nccloud_max) << "\n"; //Wert auf Farbe --> A changer : NCCLOUD / time / HG / cos(teta) ...
	}
	fout << "g line" << r << "\n" << "l ";
	for (int j = 0; j < path.size(); j++) {
		fout << n << " ";
		n++;
	}
	fout << "\n";

	fout.close();
	return n;
}