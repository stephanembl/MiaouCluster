#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <dlib/clustering.h>
#include <dlib/rand.h>
#include <deque>
#include "BitmapHandler.h"

class MiaouCluster
{
private:
	std::string			_filename;
	int					_clusters;
	int					_mode;

	typedef int			(MiaouCluster::*selectMode)(BMP &) const;
	selectMode			selectClusteringMode[4];

public:
	MiaouCluster(){};
	MiaouCluster(std::string &, int, int);
	int					run();
	int					clusterLuma(BMP &) const;
	int					clusterColors(BMP &) const;
	int					clusterLumaColors(BMP &) const;
	int					clusterAll(BMP &) const;
	bool				allGood();
	~MiaouCluster(void);
};