#include "BitmapHandler.h"

BMP		BitmapHandler::getBMPFromFile(std::string &filename)
{
	BMP	image;

	image.ReadFromFile(filename.c_str());

	return image;
}

void	BitmapHandler::generateImage(std::string &filename, BMP &image, std::deque<Coord> &pntCoords)
{
	BMP	newImage;
	int x,y,i;

	newImage.SetSize(image.TellWidth(), image.TellHeight());
	newImage.SetBitDepth(32);

	for (y = 0; y < newImage.TellHeight(); ++y)
	{
		for (x = 0; x < newImage.TellWidth(); ++x)
		{
			RGBApixel	p;
			p.Red = 0;
			p.Green = 0;
			p.Blue = 0;
			newImage.SetPixel(x, y, p);
		}
	}

	for (i = 0; i < pntCoords.size(); ++i)
	{
		newImage.SetPixel(pntCoords[i].x, pntCoords[i].y, image.GetPixel(pntCoords[i].x, pntCoords[i].y));
	}

	newImage.WriteToFile(filename.c_str());
}