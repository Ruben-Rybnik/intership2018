#include "CTImageExample.h"
#include <vtkNIFTIImageReader.h>

#include <vtkMetaImageReader.h>
#include <vtkImageProperty.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

#include <vtkImageThreshold.h>
#include <vtkMarchingCubes.h>
#include <vtkimagedata.h>

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
  */
  void runCTImageExample()
  {
	// visualization window & renderer
	auto renderer = make_vtk<vtkRenderer>();
	auto renderWindow = make_vtk<vtkRenderWindow>();
	renderWindow->AddRenderer(renderer);
	auto renderWindowInteractor = make_vtk<vtkRenderWindowInteractor>();
	auto style = make_vtk<vtkInteractorStyleImage>();
	style->SetInteractionModeToImageSlicing();
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderer->SetBackground(0.0, 0.0, 0.0); // Background color black

	// functionality to show something in above window
	auto mapper = make_vtk<vtkImageSliceMapper>();
	mapper->SliceFacesCameraOn();
	mapper->SetSliceAtFocalPoint(true);
	auto actor = make_vtk<vtkImageSlice>();
	actor->SetMapper(mapper);
	renderer->AddActor(actor);

	// the data
	auto reader = make_vtk<vtkMetaImageReader>();
	reader->SetFileName("D:/P01_CT.mhd");
	reader->Update();

	//
	auto thresh = make_vtk<vtkImageThreshold>();
	thresh->SetInputData(reader->GetOutput());
	thresh->SetInValue(1.0);
	thresh->SetOutValue(0);
	thresh->ThresholdBetween(2000, 4000);
	thresh->Update();

	auto img = reader->GetOutput();

	mapper->SetInputData(reader->GetOutput());
	mapper->Update();
	actor->GetProperty()->SetColorWindow(4000);
	actor->GetProperty()->SetColorLevel(2000);
	actor->Update();
	renderer->ResetCamera();

	// show
	renderWindow->Render();
	renderWindowInteractor->Start();
  }
}
