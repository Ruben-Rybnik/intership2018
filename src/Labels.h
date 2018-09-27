#pragma once

#include <vtkImageProperty.h>
#include <vtkImageSlice.h>
#include <vtkImageData.h>
#include <vtkPolyDataMapper.h>
#include <vtkImageSliceMapper.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkExtractVOI.h>
#include <vtkImageConnectivityFilter.h>



#include <vtkImageThreshold.h>
#include <vtkMarchingCubes.h>

namespace gris
{
	template<class T>
	auto make_vtk()
	{
		return vtkSmartPointer<T>::New();
	}

	class ExtractComponents
	{
	public:
		ExtractComponents()
		{
			mThresh = make_vtk<vtkImageThreshold>();
			mThresh->SetInValue(1);
			mThresh->SetOutValue(0);

			extract = make_vtk<vtkImageConnectivityFilter>();
			extract->SetComponents(300);
			
			mMarchingCubes = make_vtk<vtkMarchingCubes>();
			mMarchingCubes->SetInputData(mThresh->GetOutput());
			mMarchingCubes->SetNumberOfContours(1);
			mMarchingCubes->SetValue(0, 0.5);

			mMapper = make_vtk<vtkPolyDataMapper>();
			mMapper->SetInputData(mMarchingCubes->GetOutput());
			mMapper->SetScalarVisibility(0);

			mActor = make_vtk<vtkActor>();
			mActor->SetMapper(mMapper);
			mActor->GetProperty()->SetLighting(true);	
			
		};
	
	public:
		void setThreshold(int d)
		{
			mThresh->ThresholdBetween(d, d);
		}

		void setThreshold(int d, int a)
		{
			mThresh->ThresholdBetween(d, a);
		}

		void setRenderer(vtkRenderer* ren)
		{
			ren->AddActor(mActor);
		}

		void setColor(int i)
		{
			//double step = i*1.0 / 10;
			mActor->GetProperty()->SetColor(ColorLut[i]);
		}

		void setInput(vtkImageData* img)
		{
			mThresh->SetInputData(img);
			mThresh->Update();
			mMarchingCubes->Update();
			std::cout << mMarchingCubes->GetOutput()->GetNumberOfPoints() << std::endl;
			mActor->Modified();
		}
	
	private:
		vtkSmartPointer<vtkImageConnectivityFilter>extract;
		vtkSmartPointer<vtkImageThreshold>mThresh;
		vtkSmartPointer<vtkActor>mActor;
		vtkSmartPointer<vtkPolyDataMapper>mMapper;
		vtkSmartPointer<vtkMarchingCubes>mMarchingCubes;

	};
	
	
	class Label3D
	{
	public:
		static double ColorLut[11][3];

	public:
		Label3D()
		{
			mThresh = make_vtk<vtkImageThreshold>();
			mThresh->SetInValue(1);
			mThresh->SetOutValue(0);

			mMarchingCubes = make_vtk<vtkMarchingCubes>();
			mMarchingCubes->SetInputData(mThresh->GetOutput()); 
			mMarchingCubes->SetNumberOfContours(1);
			mMarchingCubes->SetValue(0, 0.5);

			mMapper = make_vtk<vtkPolyDataMapper>();
			mMapper->SetInputData(mMarchingCubes->GetOutput());
			mMapper->SetScalarVisibility(0);

			mActor = make_vtk<vtkActor>();
			mActor->SetMapper(mMapper);
			mActor->GetProperty()->SetLighting(true);
		};

	public:
		void setThreshold(int d)
		{
			mThresh->ThresholdBetween(d, d);
		}

		void setThreshold(int d, int a)
		{
			mThresh->ThresholdBetween(d, a);
		}

		void setRenderer(vtkRenderer* ren)
		{
			ren->AddActor(mActor);
		}

		void setColor(int i)
		{
			//double step = i*1.0 / 10;
			mActor->GetProperty()->SetColor(ColorLut[i]);
		}

		void setInput(vtkImageData* img)
		{
			mThresh->SetInputData(img);
			mThresh->Update();
			mMarchingCubes->Update();
			std::cout << mMarchingCubes->GetOutput()->GetNumberOfPoints() << std::endl;
			mActor->Modified();
		}
			
	private:
		vtkSmartPointer<vtkImageThreshold>mThresh;
		vtkSmartPointer<vtkActor>mActor;
		vtkSmartPointer<vtkPolyDataMapper>mMapper;
		vtkSmartPointer<vtkMarchingCubes>mMarchingCubes;


	};
}