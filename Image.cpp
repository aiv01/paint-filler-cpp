#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(uint16_t InWidth, uint16_t InHeight, uint8_t InChannels, uint8_t* InData)
{
	Width = InWidth;
	Height = InHeight;
	Channels = InChannels;
	Data = InData;
}

Image::~Image() {
	stbi_image_free(Data);
}

Image* ImageIO::ReadImage(path InPath)
{
	int width, height, channels;

	std::string PathToStr = InPath.string();

	uint8_t* bytes = stbi_load(PathToStr.c_str(), &width, &height, &channels, 0);

	if (bytes == nullptr) {
		std::cout << "Error reading image!\n";
		return nullptr;
	}

	Image* Result = new Image(width, height, channels, bytes);
	return Result;
}

void ImageIO::WriteImage(path InPath, Image* InImage)
{
	std::string PathToStr = InPath.string();
	stbi_write_png(PathToStr.c_str(), InImage->Width, InImage->Height, InImage->Channels, InImage->Data, 0);
}