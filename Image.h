#pragma once
#include <string>
#include <filesystem>
using namespace std::filesystem;

struct Image {
	Image(uint16_t InWidth, uint16_t InHeight, uint8_t InChannels, uint8_t* InData);
	~Image();

	uint16_t Width;
	uint16_t Height;
	uint8_t  Channels;
	uint8_t* Data;
};

class ImageIO {
public:
	static Image* ReadImage(path InPath);
	static void WriteImage(path InPath, Image* InImage);
};