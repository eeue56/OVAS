/* 
 * File:   Analyser4D.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 17:51
 */

#ifndef ANALYSER4D_H
#define	ANALYSER4D_H
#include "Volume4D.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "GeoSphere.h"
#include "MetaballsVol4D.h"
using namespace std;
class Analyser4D {
public:
    Analyser4D();
    Analyser4D(const Analyser4D& orig);
    virtual ~Analyser4D();
    void initFeatures();
    void initAnalyser3D(int step);
    void evalEach3D();
    void setVolume(Volume4D* vol);
    void setAreaWeight(float weight);
    void setTopologyWeight(float weight);
    void setTemporalChangeWeight(float weight);
    void setCurvatureWeight(float weight);
    void loadConfig(string filename);
private:
    int step;
    Volume4D* vol4D;
    float areaWeight,topologyWeight,temporalChangeWeight,curvatureWeight;
    StepToParamConverter* stepConverter;
    GeoSphere* geoSphere;
    int dims,numSteps;
};

#endif	/* ANALYSER4D_H */

