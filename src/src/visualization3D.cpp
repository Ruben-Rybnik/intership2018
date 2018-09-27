#include "CTImageExample.h"
#include "Labels.h"

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
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkimagedata.h>
#include <vtkProperty.h>
#include <vtkTexture.h>

namespace
{
	template<class T>
	auto make_vtk()
	{
		return vtkSmartPointer<T>::New();
	}
}

class Rendering
{
	public:
		Rendering()
		{
			renderer = make_vtk<vtkRenderer>();
			renderWindowInteractor = make_vtk<vtkRenderWindowInteractor>();
			renderWindow = make_vtk<vtkRenderWindow>();

			renderWindow->AddRenderer(renderer);
			renderWindowInteractor->SetRenderWindow(renderWindow);
			renderer->SetBackground(0, 0, 255);
			
		};
	
	private:
		vtkSmartPointer<vtkRenderer>renderer;
		vtkSmartPointer<vtkRenderWindowInteractor>renderWindowInteractor;
		vtkSmartPointer<vtkRenderWindow>renderWindow;
	
	public:
		vtkRenderer* getRenderer()
		{
			return renderer;
		}
		
		vtkRenderWindowInteractor* getRenderWindowInteractor()
		{
			return renderWindowInteractor;
		}
		vtkRenderWindow* getRenderWindow()
		{
			return renderWindow;
		}
};


namespace gris
{
	/** \brief A Visualization of a sphere
	*/
	void runVisualization3D()
	{
		//   visualization window & renderer
		//auto renderer = make_vtk<vtkRenderer>();
		//auto renderWindow = make_vtk<vtkRenderWindow>();
		//renderWindow->AddRenderer(renderer);
		//auto renderWindowInteractor = make_vtk<vtkRenderWindowInteractor>();
		//renderWindowInteractor->SetRenderWindow(renderWindow);
		//renderer->SetBackground(0, 0, 255); 
		Rendering Render;
		Render.getRenderer();
		Render.getRenderWindow();
		Render.getRenderWindowInteractor();



		auto mapper = make_vtk<vtkImageSliceMapper>();
		mapper->SliceFacesCameraOn();
		mapper->SetSliceAtFocalPoint(true);
		auto actor = make_vtk<vtkImageSlice>();
		actor->SetMapper(mapper);
		//renderer->AddActor(actor);


		//---  Schaedel
		Label3D Schaedel;
		auto reader = make_vtk<vtkMetaImageReader>();
		reader->SetFileName("D:/P01_CT.mhd");
		reader->Update();

		Schaedel.setThreshold(2000, 4000);
		Schaedel.setRenderer(Render.getRenderer());
		Schaedel.setInput(reader->GetOutput());

		// Ohr
		auto reader2 = make_vtk<vtkMetaImageReader>();
		reader2->SetFileName("D:/P01_GroundTruth.mhd");
		reader2->Update();

		Label3D Labels[10];
		for (int i = 0; i < 10; ++i)
		{
			Labels[i].setThreshold(i + 1);
			Labels[i].setRenderer(Render.getRenderer());
			Labels[i].setColor(i);
			Labels[i].setInput(reader2->GetOutput());
		}

		mapper->SetInputData(reader->GetOutput());
		mapper->Update();
		actor->GetProperty()->SetColorWindow(4000);
		actor->GetProperty()->SetColorLevel(2000);
		actor->Update();
		Render.getRenderer()->ResetCamera();


		// show
		Render.getRenderWindow()->Render();
		Render.getRenderWindowInteractor()->Start();
	}
}
