#ifndef __XPRIMITIVES__
#define __XPRIMITIVES__

#include "drawable.h"
#include "glut.h"

class xSphereObject : public xDrawable {
    public:
        void drawData();
        ~xSphereObject() {};

};

class xCubeObject : public xDrawable {
    protected:
        float X;
        float Y;
        float Z;


    public:
        void drawData();
};

#endif
