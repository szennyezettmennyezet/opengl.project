#ifndef __XOBJECT__
#define __XOBJECT__

#include "GL/gl.h"
#include <vector>







using namespace std;

class xObject {
    public:
        GLfloat posX,posY,posZ;
        GLfloat rotX,rotY,rotZ;
        GLfloat scaleX,scaleY,scaleZ;

        xObject() :posX(0), posY(0), posZ(0), rotX(0), rotY(0), rotZ(0) {}
        virtual ~xObject() {}
};



#endif
