
#include <iostream>
#include "Image.h"

int main()
{
	path Cwd = current_path();
	
	path FilePath = Cwd;
	FilePath.concat("\\resources\\tree.png");

	Image* MyImage = ImageIO::ReadImage(FilePath);
	if (MyImage->Data == nullptr) {
		std::cout << "Error reading image!\n";
	}

	//algoritmo change Image ...

	path DestFilePath = Cwd;
	DestFilePath.concat("\\resources\\tree3.png");
	ImageIO::WriteImage(DestFilePath, MyImage);

	delete MyImage;

/*
	const char* fileName = "C:\\_fdf\\PaintFillerCpp\\resources\\tree.png";
	int width, height, channels;

	//RGB
	//Red = (255, 0, 0)
	// 2x2 pixel = [ 255, 0, 0,   255, 0, 0,    0, 0, 255,   0, 0, 255]
	uint8_t* bytes = stbi_load(fileName, &width, &height, &channels, 0);
	
	if (bytes == nullptr) {
		std::cout << "Error reading image!\n";
	}
	std::cout << "W: " << width << "\n";
	std::cout << "H: " << height << "\n";


	uint8_t pixel_0_R = bytes[0];
	uint8_t pixel_0_G = bytes[1];
	uint8_t pixel_0_B = bytes[2];

	printf("%d\n", pixel_0_R);

	std::cout << "R: " << (unsigned int)pixel_0_R  <<"\n";
	std::cout << "G: " << (unsigned int)pixel_0_G << "\n";
	std::cout << "B: " << (unsigned int)pixel_0_B << "\n";


	//Make first pixel RED
	bytes[0] = 255;
	bytes[1] = 0;
	bytes[2] = 0;

	const char* fileNameWrite = "C:\\_fdf\\PaintFillerCpp\\resources\\tree2.png";
	stbi_write_png(fileNameWrite, width, height, channels, bytes, 0);
*/
}
