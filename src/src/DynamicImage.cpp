#include "DynamicImage.h"
#include "userinput.h"
#include <iostream>

namespace
{
	using namespace gris;
	using Image = int**;
	
	
	void readUserInput(int&, int&, int&);
	Image createImage(const int& NumberofColumns, const int& NumberofRows, const int Value);
	void deleteImage(Image img, const int& NumberofRows);
	void printImage(const Image& image, const int& NumberofColumns, const int& NumberofRows, const int Value);
	void thresholdFilter(CImage& img, int lowerbound, int upperbound);
}


namespace gris
{
	/** \brief This function works with memory allocation
	*/
	void runDynamicImage()
	{
		int NumberofColumns, NumberofRows, Value;
		readUserInput(NumberofColumns, NumberofRows, Value);

		auto img = CImage();
		img.createImage(NumberofRows, NumberofColumns, Value);
		img.printImage();

		thresholdFilter(img, 10, 20);
		
		
		
		img.printImage();

		//Image image;
		//image = createImage(NumberofColumns, NumberofRows, Value);
		//printImage(image, NumberofColumns, NumberofRows, Value);
		//deleteImage(image, NumberofColumns);
	}
}

namespace
{
	// filter
	void thresholdFilter(CImage& img, int lowerbound, int upperbound)
	{
		for (int i = 0; i < img.getRows(); ++i)
		{
			for (int j = 0; j < img.getCols(); ++j)
			{
				if (img.getValue(i, j) < lowerbound || img.getValue(i, j) > upperbound)
				{
					img.setValue(i, j, 0);
				}
				else
				{
					img.setValue(i, j, 1);
				}
			}
		}
	}

	void readUserInput(int& NumberofColumns, int& NumberofRows, int& Value)
	{
		NumberofRows = gris::getInteger(1, 20);
        NumberofColumns = gris::getInteger(1, 20);
		Value = gris::getInteger(0, 100);
	}
    
	
	
    Image createImage(const int& NumberofColumns, const int& NumberofRows, const int Value)
	{
		Image image = new int*[NumberofColumns];
		for (int i(0); i < NumberofColumns; ++i)
		{
			image[i] = new int[NumberofRows];
			for (int j(0); j < NumberofRows ; ++j)
			{
				image[i][j] = Value;
			}
		}
		return image;
	}

	void deleteImage(Image img, const int& NumberofColumns)
	{
		for (int i(0); i < NumberofColumns; ++i)
			delete[] img[i];
		delete img;
	}

	void printImage(const Image& image, const int& NumberofColumns, const int& NumberofRows, const int Value)
	{
		for (int i = 0; i < NumberofRows; ++i)
		{
			for (int j = 0; j < NumberofColumns; ++j)
			{
				std::cout << image[j][i] << " ";
			}
			    std::cout << std::endl;
		}
		system("pause");
	}
}
