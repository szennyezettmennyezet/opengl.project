#ifndef __PLAYER__
#define __PLAYER__

#include "x3dmodelfromfile.h"
#include <math.h>

class Player:public xDrawable {
    unsigned int life;
    GLfloat speed;




    x3DModelFromFile *model;

    public:
        void towards(GLfloat x, GLfloat y);
        void forward(float n);
        void backward(float n);

        void move(GLfloat x, GLfloat y);
        void drawData(unsigned int mode);
        Player(char* fileName) {
            model = new x3DModelFromFile(fileName);
        }

};







#endif
