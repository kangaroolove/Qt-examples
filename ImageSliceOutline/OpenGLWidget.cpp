#include "OpenGLWidget.h"
#include <vtkNrrdReader.h>
#include <vtkPNGReader.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkBox.h>
#include <vtkImplicitBoolean.h>
#include <vtkClipPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkLookupTable.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageReader2.h>
#include <vtkEventQtSlotConnect.h>
#include <QDebug>
#include <vtkCamera.h>
#include <vtkMath.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkInformation.h>
#include <vtkClipVolume.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataToImageStencil.h>
#include <vtkNew.h>
#include <vtkImageStencilSource.h>
#include <vtkImageReslice.h>
#include <vtkMatrix4x4.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageData.h>
#include <vtkImageLogic.h>
#include <vtkTransform.h>
#include <vtkImageClip.h>
#include <vtkProbeFilter.h>
#include <vtkPlaneSource.h>
#include <vtkLinearTransform.h>
#include <vtkExtractVOI.h>
#include <vtkBoundingBox.h>
#include <vtkImageDataToPointSet.h>
#include <vtkOutlineFilter.h>
#include <vtkBoxClipDataSet.h>
#include <vtkGenericClip.h>
#include <vtkPlane.h>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QVTKOpenGLWidget(parent)
{
}


OpenGLWidget::~OpenGLWidget()
{
}
