#include <fstream>
#include <iostream>
#include <string>
#include "ppm.h"
using namespace std;
using namespace imaging;

float* ReadPPM(const char * filename, int * w, int * h) {

	ifstream file(filename, ios::binary);

	if (!file) {
		cerr << "File could not be opened." << endl;
		return 0;
	}

	string format;
	int maxVal;
	char space;

	file >> format >> *w >> *h >> maxVal >> space;

	if (format != "P6") {
		cerr << "Cannot support the " << format << " format." << endl;
		return nullptr;
	}

	if (maxVal <= 0 || maxVal > 255) {
		cerr << "Cannot support this pixel's value." << endl;
		return nullptr;
	}

	if (*w == 0 || *h == 0) {
		cerr << "Ivalid width and height." << endl;
		return nullptr;
	}

	int size = 3 * *w * *h;
	float* buffer = new float[size];
	unsigned char* buffer2 = new unsigned char[size];

	file.read((char*)buffer2, size);

	for (int y = 0; y < size; y++) {

		buffer[y] = (float)buffer2[y] / 255.0f;
	}

	if (file.fail()) {
		cerr << "Could not read data." << endl;
		file.close();
		return nullptr;
	}

	file.close();
	return buffer;
}

bool WritePPM(const float * data, int w, int h, const char * filename) {


	if (data == nullptr) {
		return false;
	}

	ofstream file(filename, ios::binary);

	if (!file) {
		cerr << "File could not be opened." << endl;
		return false;
	}

	int size = 3 * w * h;
	char* bufferw = new char[size];

	file << "P6" << endl << w << endl << h << endl << "255\n" << endl;

	for (int i = 0; i < size; i++) {
		bufferw[i] = data[i] * 255;
	}

	file.write((char *)bufferw, size);

	if (file.fail()) {
		cerr << "Could not write data." << endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}
