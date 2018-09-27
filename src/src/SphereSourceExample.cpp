#include "SphereSourceExample.h"

#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyle.h>

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
  /** \brief A Visualization of a sphere

    This code was copied from
    https://www.vtk.org/Wiki/VTK/Examples/Cxx/GeometricObjects/Sphere

    Check out the default interaction of the "vtkInteractorStyle" such as keys 's' and 'w'
    https://www.vtk.org/doc/nightly/html/classvtkInteractorStyle.html#details
  */
  void runSphereSourceExample()
  {
    // Create a sphere. Its output is a vtkPolyData: in this case the polydata containts a list of points and triangles.
    auto sphereSource = make_vtk<vtkSphereSource>();
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(5.0);

	auto d = double(5);
	
    auto mapper = make_vtk<vtkPolyDataMapper>();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    auto actor = make_vtk<vtkActor>();
    actor->SetMapper(mapper);

    auto renderer = make_vtk<vtkRenderer>();
    auto renderWindow = make_vtk<vtkRenderWindow>();
    renderWindow->AddRenderer(renderer);
    auto renderWindowInteractor = make_vtk<vtkRenderWindowInteractor>();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->AddActor(actor);
    renderer->SetBackground(.3, .6, .3); // Background color green

    renderWindow->Render();
    renderWindowInteractor->Start();
  }
}