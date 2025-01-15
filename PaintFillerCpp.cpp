
#include <iostream>
#include "Image.h"

struct Color3
{
	uint8_t R;
	uint8_t G;
	uint8_t B;

};


void RecurseFillerInternal(Image* InImage, int InX, int InY, Color3 InColor, Color3 InSample)
{
	if (InImage->Height < InY || InY < 0)
		return;
	if (InImage->Width < InX || InX < 0)
		return;

	int Position = (InY * InImage->Width + InX) * 3;


	uint8_t Red = InImage->Data[Position + 0];
	uint8_t Green = InImage->Data[Position + 1];
	uint8_t Blue = InImage->Data[Position + 2];

	Color3 CurrentColor{ Red,Green,Blue };

	bool SameColor = CurrentColor.R == InSample.R && CurrentColor.G == InSample.G && CurrentColor.B == InSample.B;

	if (!SameColor)
	{
		return;
	}

	InImage->Data[Position + 0] = InColor.R;
	InImage->Data[Position + 1] = InColor.G;
	InImage->Data[Position + 2] = InColor.B;


	RecurseFillerInternal(InImage, InX + 1, InY, InColor, InSample);
	RecurseFillerInternal(InImage, InX - 1, InY, InColor, InSample);
	RecurseFillerInternal(InImage, InX, InY + 1, InColor, InSample);
	RecurseFillerInternal(InImage, InX, InY - 1, InColor, InSample);

}

void RecursiveFiller(Image* InImage, int InX, int InY, Color3 InColor)
{
	int Position = (InY * InImage->Width + InX) * 3;

	uint8_t Red = InImage->Data[Position + 0];
	uint8_t Green = InImage->Data[Position + 1];
	uint8_t Blue = InImage->Data[Position + 2];

	Color3 Sample{ Red,Green,Blue };

	RecurseFillerInternal(InImage, InX, InY, InColor, Sample);

}





int main()
{
	path Cwd = current_path();

	path FilePath = Cwd;
	FilePath.concat("\\resources\\white_48x48_24bit.png");

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


}
