#include "userinput.h"
#include <iostream>

namespace gris
{
	int getInteger(int lowerBound, int upperBound)
	{
		std::cout << "Bitte geben Sie eine Zahl von " << lowerBound << " bis " << upperBound << " ein. \n";
		int badInput = true;
		int integer;
		while (badInput)
		{
			std::cin >> integer;
			if (integer >= lowerBound && integer <= upperBound)
			{
				badInput = false;
				break;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		};
		return integer;
	}

	
	
	// create image
	void CImage::createImage(int rows, int cols, int value)
	{
		nRows = rows;
		nCols = cols;
		nValue = value;
		image = new int*[rows];
		for (int i(0); i < rows; ++i)
		{
			image[i] = new int[cols];
			for (int j(0); j < cols; ++j)
			{
				image[i][j] = value;
			}
		}
	}
	
	// print image
	void CImage::printImage()
	{
		for (int i = 0; i < nRows; ++i)
		{
			for (int j = 0; j < nCols; ++j)
			{
				std::cout << image[i][j] << " ";
			}
			std::cout << std::endl;
		}
		system("pause");
	}

	CImage::CImage() 
	{

	}

	CImage::~CImage() 
	{
		for (int i(0); i < nRows; ++i)
			delete[] image[i];
		delete image;
		std::cout << "DTor" << std::endl;
	}

	// get value
	int CImage::getValue(int i, int j)
	{
		return image[i][j];
	}
	
	// set value
	void CImage::setValue(int i, int j, int value)
	{
		image[i][j] = value;
	}
}