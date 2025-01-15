
#include <iostream>
#include "Image.h"
#include <vector>

struct Color3
{
	uint8_t R;  // 0
	uint8_t G;  // 1
	uint8_t B;  // 2

	bool operator==(const Color3& InOther) {
		if (R != InOther.R) return false;
		if (G != InOther.G) return false;
		if (B != InOther.B) return false;
		return true;
	}

	bool operator!=(const Color3& InOther) {
		return !(*this == InOther);
	}
};

bool IsVisitable(std::vector<bool>& InCache, int InX, int InY, Image* InImage) {
	if (InImage->Height < InY || InY < 0)
		return false;
	if (InImage->Width < InX || InX < 0)
		return false;

	int Index = (InY * InImage->Width + InX);
	if (InCache[Index]) return false;
	return true;
}

void RecurseFillerInternal(Image* InImage, int InX, int InY, Color3 InColor, Color3 InSample, std::vector<bool>& InCache)
{
	int Index = (InY * InImage->Width + InX);
	int Position = Index * 3;

	uint8_t* PointerToCurrentPixel = &InImage->Data[Position];
	Color3* PointerToCurrentColor = (Color3*)PointerToCurrentPixel;

	InCache[Index] = true;

	/*
	Color3 CurrentColor;
	CurrentColor.R = InImage->Data[Position + 0];
	CurrentColor.G = InImage->Data[Position + 1];
	CurrentColor.B = InImage->Data[Position + 2];
	*/


	//if (CurrentColor != InSample)
	if (*PointerToCurrentColor != InSample)
	{
		return;
	}

	/*
	InImage->Data[Position + 0] = InColor.R;
	InImage->Data[Position + 1] = InColor.G;
	InImage->Data[Position + 2] = InColor.B;
	*/

	PointerToCurrentColor->R = InColor.R;
	PointerToCurrentColor->G = InColor.G;
	PointerToCurrentColor->B = InColor.B;

	//Right Neighb
	if (IsVisitable(InCache, InX + 1, InY, InImage)) {
		RecurseFillerInternal(InImage, InX + 1, InY, InColor, InSample, InCache);
	}
	
	//Left Neighb
	if (IsVisitable(InCache, InX - 1, InY, InImage)) {
		RecurseFillerInternal(InImage, InX - 1, InY, InColor, InSample, InCache);
	}

	//Bott Neighb
	if (IsVisitable(InCache, InX, InY + 1, InImage)) {
		RecurseFillerInternal(InImage, InX, InY + 1, InColor, InSample, InCache);
	}

	//Top Neighb
	if (IsVisitable(InCache, InX, InY - 1, InImage)) {
		RecurseFillerInternal(InImage, InX, InY - 1, InColor, InSample, InCache);
	}
}

void RecursiveFiller(Image* InImage, int InX, int InY, Color3 InColor)
{
	auto Size = InImage->Width * InImage->Height;

	std::vector<bool> Cache(Size, false);

	int Position = (InY * InImage->Width + InX) * 3;

	Color3 Sample;
	Sample.R = InImage->Data[Position + 0];
	Sample.G = InImage->Data[Position + 1];
	Sample.B = InImage->Data[Position + 2];

	RecurseFillerInternal(InImage, InX, InY, InColor, Sample, Cache);
}

int main()
{
	path Cwd = current_path();

	path FilePath = Cwd;
	FilePath.concat("\\resources\\white_32x32_24bit.png");

	Image* MyImage = ImageIO::ReadImage(FilePath);
	if (MyImage->Data == nullptr)
	{
		std::cout << "Error reading image!\n";
	}

	Color3 Red{ 255,0,0 };

	RecursiveFiller(MyImage,0,0,Red);

	path DestFilePath = Cwd;
	DestFilePath.concat("\\x64\\copy.png");
	ImageIO::WriteImage(DestFilePath, MyImage);

	delete MyImage;



	//char = 1byte  vs char* = 8 byte
	//sizeof(char) < sizeof(char*)
}
