#ifndef __XDRAWABLE__
#define __XDRAWABLE__

#include "object.h"



class xDrawable : public xObject {
    protected:
        vector<xDrawable*> children;



    public:
        void draw(unsigned int mode) {
            glPushMatrix();
            glTranslated(-posX,posY,posZ);

            glRotated(-rotX, 1.0,0.0,0.0);
            glRotated(-rotY, 0.0,1.0,0.0);
            glRotated(-rotZ, 0.0,0.0,1.0);

            drawData(mode);

            glPopMatrix();
        }

        virtual void drawData(unsigned int mode) = 0;


        GLfloat getPosX() { return posX; }
        GLfloat getPosY() { return posY; }
        GLfloat getPosZ() { return posZ; }

        GLfloat getRotX() { return rotX; }
        GLfloat getRotY() { return rotY; }
        GLfloat getRotZ() { return rotZ; }

        void setPos(float x, float y, float z) {
            posX = x;
            posY = y;
            posZ = z;

            rotZ = 0.0;
            rotX = 0.0;
            rotY = 0.0;
            //cout << posX << " " << posY << " " << posZ << endl;
        }
};


#endif
