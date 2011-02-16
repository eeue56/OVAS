/* 
 * File:   Feature.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 18:28
 */

#include <limits>

#include "Feature.h"
#include "testVol4D.h"



Feature::Feature(){
   
}
Feature::Feature(float weight,OVASControl* o) : weight(weight),oc(o) {
   
    scoreData=ArrayTools::allocate2DArray<float>(oc->numSteps,oc->geoSphere->getNumVs());
    for(int i=0;i<oc->numSteps;i++){
        for(int j=0;j<oc->geoSphere->getNumVs();j++){
            scoreData[i][j]=0;
        }
    }
    cout<<" scd "<<oc->numSteps<<" "<<oc->geoSphere->getNumVs()<<" "<<scoreData<<endl;
    colourB=1;
    colourG=0;
    colourR=0;
 //   Feature();
}

Feature::Feature(const Feature& orig) {
}

Feature::~Feature() {
}

void Feature::readyRenderer(vtkSmartPointer<vtkRenderer> _renderer) {

    renderer = _renderer;
    renderWindow = renderer->GetRenderWindow();
    camera = renderer->GetActiveCamera();
    std::vector< vtkSmartPointer<vtkActor> >::iterator it;
    for (it = actors.begin(); it != actors.end(); it++) {
        renderer->AddActor((*it));
    }
    framebuffer = new FrameBuffer(renderer->GetRenderWindow());
}

void Feature::climbDown() {

    std::vector< vtkSmartPointer<vtkActor> >::const_iterator it;
    for (it = actors.begin(); it != actors.end(); it++) {
        renderer->RemoveActor((*it));
    }
    delete framebuffer;
}

void Feature::scoreFeature(GeoPoint* view) {
    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange * view->getz());
    renderWindow->Render();
    //int* size = renderWindow->GetSize();
    scoreData[oc->currentStep][oc->currentView]=countColour(framebuffer);
    cout<<" scpre "<<oc->currentStep<<" "<<oc->currentView<<" "<<scoreData[oc->currentStep][oc->currentView]<<endl;
}

int Feature::countColour(float r, float g, float b, FrameBuffer* fb) {
    fb->grabData();

    int count = 0;
    int len = fb->getLen();
    float* data = fb->getData();
    for (int i = 0; i < len; i++) {
        int j = i * 4;
        if (data[j] == r && data[j + 1] == g && data[j + 2] == b) {
            count++;
        }
    }
    fb->delData();

    return count;

}

float* Feature::getEvaluatedStepData(int step){
    float* data=new float[oc->geoSphere->getNumVs()];
    for(int i=0;i<oc->geoSphere->getNumVs();i++){
        
        data[i]=scoreData[step][i]*weight;
        //cout<<" the data this "<<scoreData[step][i]<<" w here "<<weight<<endl;
    }
    return data;
}