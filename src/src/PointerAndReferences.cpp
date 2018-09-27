#include "PointerAndReferences.h"
#include "userinput.h"

#include <string>
#include <iostream>
#include <algorithm>

namespace
{
	using namespace gris;

  // these are the types and functions used by this file. Again implemented in the anonymous namespace.
  // some types
  typedef int ImageT[10][10];
  // from the c++11-standard on you can do it like this, too. That's "modern c++":
  using Image    = int[10][10];  /// our image is a fixed size matrix of 10*10 int values
  

  enum EnValueTypes
  {
	  enInt = 0,
	  enDouble,
  };

  static std::string ImageTypeNames[3] = 
  {
    "chess",
    "stripes",
    "black"
  };

  // Some functions, declared here but implemented at the end of the file.
  void        readUserInput(EnImageTypes& imageType, int& indentation);
  Image*      createImage(const EnImageTypes& imageType);
  void        printImage(const Image& image, int indentation);
}

namespace gris
{
  /** This little program reads in user input, creates an image from it and prints it out. 

    We do not work with real images here.
    Instead we use an array of arrays to symbolize a 2 dimensional image with entries "0" (black) and "1" (white).
    An enumerator "EnImageTypes" is used to describe the different images that can be created.

    The program subdivides itself in three functions:
      - one to ask the user which image should be created and displayed.
      - one to create the image
      - one to display it.
  */
  void runPointerAndReferences()
  {
    EnImageTypes imageType;
    int          indentation;
    readUserInput(imageType, indentation);

    Image* pImage   = createImage(imageType);
    printImage(*pImage, indentation);
	
	
	
		
		//row
		std::cout << "Reihe, in der Sie den Wert aendern moechten. ";
		int r = getInteger(0, 9);
	
		// column
		std::cout << "Spalte, in der Sie den Wert aendern moechten. ";
		int s = getInteger(0, 9);
		
		// value
		int wert;
		std::cout << "Wert, den Sie aendern moechten. ";
		std::cin >> wert;
	
		Image* nImage = pImage;
		(*nImage)[r][s] = wert;
		nImage[0][r][s] = wert;

		Image& rIm = *nImage;
		const Image& rcIm = rIm;
		//const Image& image, int indentation
		printImage(rcIm, indentation);

		
		int sum = 0;
		for (r=0 ; r<10 ; ++r)
		{
			for (s=0 ; s<10 ; ++s)
			{
				sum += rcIm[r][s];
			}
		}
		std::cout << sum;
  }
}

namespace
{
  /** \brief A function that reads in several inputs from the console.

    Note that a function can only have one return parameter.
    If you want more return parameters you have several choices:
      - create a new function for every return parameter
      - use modifiable parameters (pointers or references) as input to the function and let the function modify those. This is done here.
      - return a class that has the return parameters as member variables. We will learn about classes in the next section (A5).

    \param[in, out] imageType : describes the type of image, the user wants to have created
    \param[in, out] indentation : the indentation the user wants to have, when the image is printed out.
    
    \return void
  */
  void readUserInput(EnImageTypes& imageType, int& indentation)
  {
    // read in first input (image type)
    std::cout << "Es gibt drei Bilder zur Auswahl: \n" << std::endl;
    for (int i(0); i<3; ++i)
    {
      std::cout << "   " << i << ":" << ImageTypeNames[i] << "\n" <<std::endl;
    }
    
	  int integer = gris::getInteger(0,2);
	  imageType = static_cast<EnImageTypes>(integer);
    

   
	// read in second input (indentation)
    std::cout << "\nNun koennen Sie die Einrueckung eingeben." << std::endl;
	indentation = gris::getInteger(1,10);
  }

  /** \brief Creates an iamge based on the input parameter

     The proper way would be to dynamically allocate memory for an image af arbitrary size.
     However, we do not know how memory is allocated dynamically, yet.
     For now, we use a static image that is defined within this function instead.

     \param[in] imageType: the type of image we want to have created
     \return A Pointer to the created image

     Notes on parameter choice:
      - If you pass a parameter by reference and it is not changed by the function, ALWAYS add "const" to the parameter. It makes your code much easier to understand.
      - If a parameter is passed by reference without the "const" qualifier, people usually expect the function to change that value.
      - If a function returns a pointer to a variable, you always have to expect this pointer to be null.
      - This function is a bad example. The pointer will never be null. What would be a better choice?
  */
  Image* createImage(const EnImageTypes& imageType)
  {
    static int TheImage[10][10]; // this is our memory for the static image
    // already create our return value p.
    Image* p = &TheImage;
    // create the image based on #imageType
    switch(imageType)
    {
      case enChess:
      {
        for (int i(0); i < 10; ++i)
        {
          // The code 
          //    "expression ? A : B;" 
          // is a short syntax for an if-else-clause
          //    "if (expression) { return A; } else { return B; }"
          // i % 2 is the modulo operator and computes the remainder of a division
          // In the following line "expression" is "i % 2 == 0", "A" is "0" and "B" is "1"
          // => This line defines a variable "pixel" and assigns it the value 0 or 1, depending if "i devided by 2" has remainder 0.
          int pixel = i % 2 == 0 ? 0 : 1; // even rows start with a black pixel
          for (int j(0); j < 10; ++j)
          {
            (*p)[i][j] = pixel; // if we write *p[i][j], the program crashes. Do you know why? (Hint: check e.g. https://stackoverflow.com/questions/19782111/does-the-bracket-operator-only-have-a-single-use)
            pixel = pixel == 0 ? 1 : 0; // switch between 1 and 0
          }
        }
        break;
      }
      case enStripes:
      {
        int pixel(0);
        for (int i(0); i < 10; ++i)
        {
          for (int j(0); j < 10; ++j)
          {
            (*p)[i][j] = pixel;
          }
          pixel = pixel == 0 ? 1 : 0; // switch between 0 and 1
        }
        break;
      }
      case enBlack:
      {
        for (int i(0); i < 10; ++i)
          for (int j(0); j < 10; ++j)
            (*p)[i][j] = 0;
        break;
      }
    };
    return p;
  }

  /** \brief Writes the entries if the image to the console

    \param[in] image : the image to be printed out.
    \param[in] indentation: the indentation used.
  */
  void printImage(const Image& image, int indentation)
  {
    std::cout << "\nIhr Bild sieht so aus:\n " << std::endl;
    for (int i(0); i<10; ++i)
    {
      for (int k(0); k < indentation; ++k)
        std::cout << " ";
      for (int j(0); j < 10; ++j)
      {
        std::cout << image[i][j] << " ";
      }
      std::cout << std::endl;
	 }
	system("pause");
  }
}