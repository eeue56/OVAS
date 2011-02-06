/* 
 * File:   Volume4D.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 17:45
 */

#ifndef VOLUME4D_H
#define	VOLUME4D_H
#include "StepToParamConverter.h"
#include "vtkEssentials.h"

class Volume4D {
public:
    Volume4D(){};
    Volume4D(int xdim, int ydim, int zdim,int numSteps);
    Volume4D(const Volume4D& orig);
    virtual ~Volume4D();
    virtual void setToStep(int Step);
    void setStepConverter(StepToParamConverter* sc);
    virtual float getVoxelValue(int x,int y,int z,int step){ return 0;}
    void updateActor();
    vtkSmartPointer<vtkActor> getVolActor(){
        return volActor;
        //vtkSmartPointer<vtkActor> ac= vtkSmartPointer<vtkActor>::New();
        //return ac;
    }
   
protected:
    vtkSmartPointer<vtkActor> volActor;
    StepToParamConverter* stepConverter;
    vtkSmartPointer<vtkImageData> vtkVol;
    vtkSmartPointer<vtkContourFilter> contourer;
    float* isoVal;
    int xDim,yDim,zDim;
   
};

#endif	/* VOLUME4D_H */

