#include <iostream>
#include <string>
#include "Color.h"
#include "Image.h"
#include "ppm/ppm.h"
using namespace std;
using namespace imaging;

Color* Image::getRawDataPtr() {
	return buffer;
}

Color Image::getPixel(unsigned int x, unsigned int y) const {

	if (x > width || y > height )
		return Color();

	return buffer[x + y*width];
}

void Image::setPixel(unsigned int x, unsigned int y, Color & value) {

	if (x > width || y > height)
		return;

	buffer[x + y * width] = value;
}

void Image::setData(const Color * & data_ptr) {

	if (width == 0 || height == 0 || buffer == nullptr) {
		return;
	}

	for (int i = 0; i < width*height; i++) {
		buffer[i] = data_ptr[i];
	}
}

Image::Image() {

	width = 0;
	height = 0;
	buffer = nullptr;
}

Image::Image(unsigned int width, unsigned int height) {

	this->width = width;
	this->height = height;
	buffer = new Color[width * height];
}

Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) {

	this->width = width;
	this->height = height;
	setData(data_ptr);
}

Image::Image(const Image &src) {

	width = src.width;
	height = src.height;
	buffer = src.buffer;
}

Image::~Image() {
	delete[] buffer;
}

Image & Image::operator = (const Image & right) {

	int size = width * height;
	int nSize = right.width * right.height;

	if (size != nSize) {
		delete[] buffer;
		buffer = new Color[nSize];
	}

	width = right.width;
	height = right.height;

	for (int i = 0; i < width * height; i++) {
		buffer[i] = right.buffer[i];
	}

	return *this;
}

bool Image::load(const std::string & filename, const std::string & format) {
	
	string extension = filename.substr(filename.length() - 3);

	if (extension != format) {
		cout << "Can't support this format." << endl;
		return false;
	}

	int w = 0, h = 0; 
	buffer = nullptr;
	float *temp = ReadPPM(filename.c_str(), &w, &h);
	width = w;
	height = h;

	if (temp == nullptr)
		return false;
	
	delete[] buffer;
	buffer = new Color[width*height];

	for (int i = 0, j = 0; i < 3 * width * height; i += 3, j++) {
		buffer[j] = Color(temp[i], temp[i + 1], temp[i+2]);
	}
	return true;
}

bool Image::save(const std::string & filename, const std::string & format) {

	string extension = filename.substr(filename.length() - 3);

	if (extension != format) {
		cout << "Can't support this format." << endl;
		return false;
	}

	float *temp = new float[3 * width * height];

	for (int i = 0, j = 0; i < width * height; i++, j += 3) {
		temp[j] = buffer[i][0];
		temp[j + 1] = buffer[i][1];
		temp[j + 2] = buffer[i][2];
	}

	if (!WritePPM(temp, width, height, filename.c_str()))
		return false;

	return true;
 }