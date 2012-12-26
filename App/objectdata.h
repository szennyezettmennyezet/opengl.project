#ifndef __OBJECTDATA__
#define __OBJECTDATA__

#include "GL/gl.h"

struct xVector {
    GLfloat X,Y,Z;
};

struct xUVCoord {
    GLfloat u,v;
};




struct xObjectData {
    vector<xVector>* vertices;
    vector<xVector>* normals;
    vector<xVector>* uvcoords;
};


#endif
