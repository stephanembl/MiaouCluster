#include "MiaouCluster.h"

int				launch()
{
	MiaouCluster	miaou;
	std::string	filename = "test.bmp";
	int			clusters = 0;
	int			mode = 0;
	int			ret;
	char		ex = '0';

	std::cout << "Path to the image to clusterize: ";
	std::getline(std::cin, filename);
	while (clusters < 1 || clusters > 50)
	{
		std::cout << "Number of clusters (1-50): ";
		std::cin >> clusters;
		if (clusters < 1 || clusters > 50)
			std::cerr << "Must be between 1 and 50." << std::endl;
	}

	while (mode < 1 || mode > 4)
	{
		std::cout << "Please choose a clustering mode:" << std::endl;
		std::cout << "Luminance only: (1)" << std::endl;
		std::cout << "Colors only: (2)" << std::endl;
		std::cout << "Luminance AND Colors: (3)" << std::endl;
		std::cout << "All of the above: (4)" << std::endl;
		std::cin >> mode;
		if (mode < 1 || mode > 4)
			std::cerr << "Unknown Clustering Mode." << std::endl;
	}

	miaou = MiaouCluster(filename, clusters, mode);

	ret = miaou.run();
	
	if (ret == 0)
		std::cout << "Image clusterized." << std::endl;
	else
		std::cerr << "Something went wrong... Sorry." << std::endl << std::endl;
	
	std::cout << "Type Q (or any key) + Enter to exit the program." << std::endl;
	std::cin >> ex;

	return ret;
}

int				main(int argc, char *argv[])
{
	int			ret;
	(void)argc;
	(void)argv;
	
	ret = launch();

	return ret;
}