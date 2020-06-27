#include <iostream>
#include <string>
#include "Image.h"
#include "Color.h"
using namespace std;
using namespace imaging;

int main(int argc, char* argv[]) {

	if (argc == 1) {
		cout << "Enter the file's name." << endl;
		cout << "> ";
		cin >> *argv;
	}

	string filename(*argv);
	Image image;

	if (!(image.load(filename, "ppm"))) {
		cerr << "Load error." << endl;
		system("PAUSE");
		return 0;
	}

	cout << "Image dimensions are: " << image.getWidth() << " x " << image.getHeight() << endl;

	string filenameneg = filename.substr(0, filename.length() - 4);
	filenameneg += "_neg.ppm";

	for (int x = 0; x < image.getWidth(); x++) {
		for (int y = 0; y < image.getHeight(); y++) {

			Color cur = image.getPixel(x, y);
			Color neg = Color(1, 1, 1) - cur;
			image.setPixel(x, y, neg);
		}
	}
	
	if (!(image.save(filenameneg, "ppm"))) {
		cerr << "Save error." << endl;
		system("PAUSE");
		return 0;
	}

	system("PAUSE");
	return 0;
}