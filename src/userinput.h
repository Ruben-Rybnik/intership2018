#pragma once

namespace gris
{
	enum EnImageTypes
	{
		enChess,
		enStripes,
		enBlack
	};
	
	
	// neue Klasse
	class CImage
	{
		private:
			using nImage = int**;

		private:
			int nRows;
			int nCols;
			int nValue;
			nImage image;
		
		public:

			CImage();
			~CImage();

	public:
			// create image
			void createImage(int nRows, int nCols, int nValue);
		 
            // print image
			void printImage();
	
			int  getValue(int i, int j);
			void setValue(int i, int j, int Value);

			int getRows() { return nRows; }
			int getCols() { return nCols; }
						
	};

	
	
	
	int getInteger(int lowerBond, int upperBound);
	
	int getIndentation(int upperBound, int lowerBound);
}