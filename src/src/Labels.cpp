#include "Labels.h"

namespace
{
	template<class T>
	auto make_vtk()
	{
		return vtkSmartPointer<T>::New();
	}
}

namespace gris
{
	double Label3D::ColorLut[11][3] =
	{
		{ 1,0,0 },
		{ 0,1,0 },
		{ 0,0,1 },
		{ 1,1,0 },
		{ 1,0,1 },
		{ 0,1,1 },
		{ 1,1,1 },
		{ 1,2,0 },
		{ 1,0,2 },
		{ 2,0,1 },
	};
}