#include "SourceLight.h"

using namespace std;

void run(SourceLight& source, Cloud& cloud) {
	int k = 0;
	while (k < 50000) {
		source.update();
		k++;
	}
	source.savePath();
}

void generateLight(int nrays, Cloud &cloud) {
	SourceLight source(&cloud);
	source.generateLight(nrays);
	run(source, cloud);
}

int main()
{
	string dataName = "cloud_nccloud.csv";
	string xName = "rlat_cloud.txt", yName = "rlon_cloud.txt", zName = "altitude_cloud.txt";
	Cloud mycloud(dataName, xName, yName, zName);
	
	generateLight(100000, mycloud);
	std::cout << "done" << std::endl;
	std::system("pause");
	return 0;
}