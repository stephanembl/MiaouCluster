#include "MiaouCluster.h"

MiaouCluster::MiaouCluster(std::string &filename, 
						 int clusters, 
						 int mode)
{
	this->_filename = filename;
	this->_clusters = clusters;
	this->_mode = mode - 1;
	this->selectClusteringMode[0] = &MiaouCluster::clusterLuma;
	this->selectClusteringMode[1] = &MiaouCluster::clusterColors;
	this->selectClusteringMode[2] = &MiaouCluster::clusterLumaColors;
	this->selectClusteringMode[3] = &MiaouCluster::clusterAll;
}

MiaouCluster::~MiaouCluster()
{
}

int	MiaouCluster::run()
{
	BMP	bmp;
	int	ret;

	if (bmp.ReadFromFile(this->_filename.c_str()))
	{
		ret = (this->*selectClusteringMode[this->_mode])(bmp);
		return ret;
	}

	return (-1);
}

int													MiaouCluster::clusterLuma(BMP &bmp) const
{
	BitmapHandler									bitmapHandler;
	typedef dlib::matrix<double,1,1>				sample_type;
    typedef dlib::radial_basis_kernel<sample_type>	kernel_type;
	sample_type										m;
    std::vector<sample_type>						samples;
    std::vector<sample_type>						initial_centers;
	int												luma;
	Coord											tmp;
	
	std::cout << "Miaou Clustering using Luminance..." << std::endl;

	for (int i = 0; i < bmp.TellHeight() * bmp.TellWidth()  ; ++i)
	{
		RGBApixel px = bmp.GetPixel(i % bmp.TellWidth(), i / bmp.TellWidth());
		luma = (px.Red * 76 + px.Green * 150 + px.Blue * 29) >> 8;
		m(0) = luma;
		samples.push_back(m);
	}

	pick_initial_centers(this->_clusters, initial_centers, samples, kernel_type(0.1));

    std::vector<unsigned long> assignments(samples.size(), samples.size()); 
	find_clusters_using_kmeans(samples, initial_centers, assignments);

	for (int layer = 0; layer < this->_clusters; ++layer)
	{
		std::deque<Coord> ptList;
		for (unsigned int i = 0; i < assignments.size() ; ++i)
		{
			if (assignments[i] == layer)
			{
				tmp.x = i % bmp.TellWidth();
				tmp.y = i / bmp.TellWidth();
				ptList.push_back(tmp);
			}
		}
		std::stringstream ss;
		ss << "luminance_" << layer << ".bmp";
		bitmapHandler.generateImage(ss.str(), bmp, ptList);
	}

	return (0);
}

int													MiaouCluster::clusterColors(BMP &bmp) const
{
	BitmapHandler									bitmapHandler;
	typedef dlib::matrix<double,3,1>				sample_type;
    typedef dlib::radial_basis_kernel<sample_type>	kernel_type;
	sample_type										m;
    std::vector<sample_type>						samples;
    std::vector<sample_type>						initial_centers;
	Coord											tmp;
	
	std::cout << "Miaou Clustering using Colors..." << std::endl;

	for (int i = 0; i < bmp.TellHeight() * bmp.TellWidth()  ; ++i)
	{
		RGBApixel px = bmp.GetPixel(i % bmp.TellWidth(), i / bmp.TellWidth());
		m(0) = px.Red;
		m(1) = px.Green;
		m(2) = px.Blue;
		samples.push_back(m);
	}

	pick_initial_centers(this->_clusters, initial_centers, samples, kernel_type(0.1));

    std::vector<unsigned long> assignments(samples.size(), samples.size()); 
	find_clusters_using_kmeans(samples, initial_centers, assignments);

	for (int layer = 0; layer < this->_clusters; ++layer)
	{
		std::deque<Coord> ptList;
		for (unsigned int i = 0; i < assignments.size() ; ++i)
		{
			if (assignments[i] == layer)
			{
				tmp.x = i % bmp.TellWidth();
				tmp.y = i / bmp.TellWidth();
				ptList.push_back(tmp);
			}
		}
		std::stringstream ss;
		ss << "colors_" << layer << ".bmp";
		bitmapHandler.generateImage(ss.str(), bmp, ptList);
	}

	return (0);
}

int													MiaouCluster::clusterLumaColors(BMP &bmp) const
{
	BitmapHandler									bitmapHandler;
	typedef dlib::matrix<double,4,1>				sample_type;
    typedef dlib::radial_basis_kernel<sample_type>	kernel_type;
	sample_type										m;
    std::vector<sample_type>						samples;
    std::vector<sample_type>						initial_centers;
	int												luma;
	Coord											tmp;
	
	std::cout << "Miaou Clustering using Luminance AND Colors..." << std::endl;

	for (int i = 0; i < bmp.TellHeight() * bmp.TellWidth()  ; ++i)
	{
		RGBApixel px = bmp.GetPixel(i % bmp.TellWidth(), i / bmp.TellWidth());
		luma = (px.Red * 76 + px.Green * 150 + px.Blue * 29) >> 8;
		m(0) = luma;
		m(1) = px.Red;
		m(2) = px.Green;
		m(3) = px.Blue;
		samples.push_back(m);
	}

	pick_initial_centers(this->_clusters, initial_centers, samples, kernel_type(0.1));

    std::vector<unsigned long> assignments(samples.size(), samples.size()); 
	find_clusters_using_kmeans(samples, initial_centers, assignments);

	for (int layer = 0; layer < this->_clusters; ++layer)
	{
		std::deque<Coord> ptList;
		for (unsigned int i = 0; i < assignments.size() ; ++i)
		{
			if (assignments[i] == layer)
			{
				tmp.x = i % bmp.TellWidth();
				tmp.y = i / bmp.TellWidth();
				ptList.push_back(tmp);
			}
		}
		std::stringstream ss;
		ss << "color-luminance_" << layer << ".bmp";
		bitmapHandler.generateImage(ss.str(), bmp, ptList);
	}

	return (0);
}

int													MiaouCluster::clusterAll(BMP &bmp) const
{
	this->clusterLuma(bmp);
	this->clusterColors(bmp);
	this->clusterLumaColors(bmp);

	return (0);
}
