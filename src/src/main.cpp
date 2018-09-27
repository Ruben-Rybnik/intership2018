#include "LoopsAndConditions.h"
#include "PointerAndReferences.h"
//#include "SphereSourceExample.h"
#include <DynamicImage.h>
#include "SphereSourceExample.h"
#include "CTImageExample.h"
#include "visualization3D.h"
#include "Spine.h"
#include <exception>
#include <vector>
#include <iostream>

class tBruch
{
public:
	tBruch() { zaehler = 0; nenner = 1; }
		long GetNenner() { return nenner; }
		long GetZaehler() { return zaehler; }
		void SetNenner(long p) { if (p != 0) nenner = p; }
		void SetZaehler(long p) {zaehler = p; }
		void Show();

private:
	long zaehler;
	long nenner;
};

void tBruch::Show()
	{
		std::cout << zaehler << "/" << nenner << std::endl;
	}



int main(int argc, char** argv)
{
	for (int i(0); i<argc; ++i)
		std::cout << argv[i] << std::endl;

	//gris::runSphereSourceExample();
	//gris::runCTImageExample();
	//gris::runVisualization3D();
	gris::runSpine();
	/*tBruch bruch;
	long inNenner, inZaehler;
	std::cout << "Zaehler Leerzeichen Nenner eingeben!" << std::endl;
	std::cin >> inZaehler >> inNenner;
	bruch.SetNenner(inNenner);
	bruch.SetZaehler(inZaehler);
	bruch.Show();*/
	
		//gris::runSphereSourceExample();
  //gris::runLoopsAndConditions();
  //try
  //{
	 // //std::vector<double> vec(std::numeric_limits<size_t>::max());

	 // double  d  = 5.0;
	 // double* pd = &d;

	 // std::cout << "value:   " << d << std::endl;
	 // std::cout << "address: " << pd << std::endl;
	 // std::cout << "value:   " << *pd << std::endl;
  //}
  //catch (std::exception& e)
  //{
	 // std::cout << e.what() << std::endl;
  //}
  //gris::runDynamicImage();
  return 0;
}