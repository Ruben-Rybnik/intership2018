#include "Labels.h"
#include <vtkNIFTIImageReader.h>
#include "CTImageExample.h"
#include <vtkMetaImageReader.h>
#include <vtkImageProperty.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkExtractVOI.h>
#include <vtkImageExtractComponents.h>

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
	void runSpine()
	{
		// visualization window & renderer
		auto renderer = make_vtk<vtkRenderer>();
		auto renderWindow = make_vtk<vtkRenderWindow>();
		renderWindow->AddRenderer(renderer);
		auto renderWindowInteractor = make_vtk<vtkRenderWindowInteractor>();
		/*auto style = make_vtk<vtkInteractorStyleImage>();
		style->SetInteractionModeToImageSlicing();
		renderWindowInteractor->SetInteractorStyle(style);*/
		renderWindowInteractor->SetRenderWindow(renderWindow);
		renderer->SetBackground(0.0, 0.0, 1.0); // Background color black

												// functionality to show something in above window
		auto mapper = make_vtk<vtkImageSliceMapper>();
		mapper->SliceFacesCameraOn();
		mapper->SetSliceAtFocalPoint(true);
		auto actor = make_vtk<vtkImageSlice>();
		actor->SetMapper(mapper);
		renderer->AddActor(actor);

		// the data
		///auto reader = make_vtk<vtkNIFTIImageReader>();
		auto reader = make_vtk<vtkMetaImageReader>();
		reader->SetFileName("D:/Thorax/GALLAS_HARTMUT_HU.mhd");
		///reader->SetFileName("D:/01_inn.nii");
		reader->Update();

		///auto* readerExt = reader->GetOutput()->GetExtent();
		///for (int i(0); i < 6; ++i)
		///	std::cout << readerExt[i] << " ";
		///std::cout << std::endl;
	
		auto Size = make_vtk<vtkExtractVOI>();
		Size->SetVOI(0, 511, 0, 435, 0, 623);
		Size->SetInputData(reader->GetOutput());
		///Size->SetSampleRate(1, 1, 1);
		Size->Update();

		///auto* img = Size->GetOutput()->GetExtent();
		///for (int i(0); i < 6; ++i)
		///	std::cout << img[i] << " ";
		///std::cout << std::endl;

		//ExtractComponents Components;
		auto extract = make_vtk<vtkImageExtractComponents>();
		extract->SetInputConnection(Size->GetOutputPort());
		extract->SetComponents(200,1500);
		extract->Update();
		
		Label3D Object;
		Object.setColor(4);
		Object.setRenderer(renderer);
		Object.setThreshold(200, 1500);
		Object.setInput(Size->GetOutput());
	
		mapper->SetInputData(reader->GetOutput());
		mapper->Update();
		actor->GetProperty()->SetColorWindow(2);
		actor->GetProperty()->SetColorLevel(1);
		actor->Update();
		renderer->ResetCamera();

		// show
		renderWindow->Render();
		renderWindowInteractor->Start();
	}
}
