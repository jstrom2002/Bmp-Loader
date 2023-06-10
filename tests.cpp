#include <cstdlib>
#include <fstream>
#include <iostream>
#include "bmp.h"

#define NUM_ARGS 5
int main(int argc, char** argv)
{
	// Test load from file
	Bmp::Bmp bmp("cat.bmp");
	
	// Test save to file
	bmp.saveBmp("cat_saved1.bmp");

	// Dump pixels to simple bin file to reload
	auto ofile = std::ofstream("dump.bin", std::ios::out | std::ios::binary);
	for (auto& i : bmp.pixels)
		for (auto& j : i)
			ofile << j;
	ofile.close();

	// Load pixel data from disk
	std::vector<std::vector<unsigned char>> pixelData;
	auto ifile = std::ifstream("dump.bin", std::ios::in | std::ios::binary);
	unsigned int c;
	for (unsigned int i = 0; i < bmp.pixels.size(); ++i)
	{
		std::vector<unsigned char> temp;
		for (unsigned int j = 0; j < bmp.pixels[i].size(); ++j)
		{
			temp.push_back(ifile.get());
		}
		pixelData.push_back(temp);
	}
	Bmp::Bmp bmp2(pixelData,bmp.wdt,bmp.hgt);

	// Save loaded pixel data to disk for comparison
	bmp2.saveBmp("cat_saved2.bmp");

	return EXIT_SUCCESS;
}
