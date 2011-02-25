/* 
 * File:   FlyingSaucersVol4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 February 2011, 20:04
 */

#include "FlyingSaucersVol4D.h"

FlyingSaucersVol4D::FlyingSaucersVol4D(OVASControl* oc) : ImplicitVolume4D(oc) {
}

FlyingSaucersVol4D::FlyingSaucersVol4D(const FlyingSaucersVol4D& orig) {
}

FlyingSaucersVol4D::~FlyingSaucersVol4D() {
}

float FlyingSaucersVol4D::getVoxelValue(int x, int y, int z, int step) {

    float time = oc->stepToParamConverter->getParamForStep(step);
    float tFraction = oc->stepToParamConverter->getParamFractionForStep(step);
    int noCenters = 1;
    float spread = 0.3;

    vector<float> centres(3 * noCenters);

    float fieldVal = 0;
    float cx, cy, cz;
    float weight = 5;
    for (size_t i = 0; i < noCenters; i++) {
//        cx = 0.5 + spread * sin(time + sin(0.1 * time) * i);
//        cy = 0.5 + spread * cos(0.9 * time + sin(0.1 * time) * i);
//        cz = 0.5 + spread * cos(0.7 * time + sin(0.01 * time) * i);
        cx=cy=cz=0.5;
        float sx, sy, sz;
        float sinVal=sin(tFraction*(2*3.14152));
        sx = 700;
        sy = 2;
        sz = 2;

        float xv = (float) x / oc->xDim;
        float yv = (float) y / oc->yDim;
        float zv = (float) z / oc->zDim;
        fieldVal += (exp(-1 * (pow(xv - cx, 2) * sx + pow(yv - cy, 2) * sy + pow(zv - cz, 2) * sz))) * weight;
        //cout<<" for "<<x<<" "<<y<<" "<<z<<" "<<(exp(-1 * (pow(xv - cx, 2))*sx))<<endl;
    }
    //cout<<" for "<<x<<" "<<y<<" "<<z<<" "<<fieldVal<<endl;
    return fieldVal;

}

