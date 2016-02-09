#pragma once
#include	<deque>
#include	"EasyBMP.h"

struct Coord
{
	int	x;
	int y;
};

class BitmapHandler
{
public:
	BitmapHandler(){};
	~BitmapHandler(){};

	BMP		getBMPFromFile(std::string &);
	void	generateImage(std::string &, BMP &, std::deque<Coord> &);
};