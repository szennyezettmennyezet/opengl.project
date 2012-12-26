#ifndef __BULLET__
#define __BULLET__

#include <math.h>


class Bullet : public xDrawable {
    double speed;

    public:
        void setSpeed(double s) {
            speed = s;
        }

        void drawData(unsigned int mode) {
            glColor3f(0.0,0.0,0.0);
            glScaled(0.1,0.5,0.1);
            glutSolidCube(0.1);
        }

        void tick(double time) {
            posY += cos (rotZ /180 *3.14) *time*speed;
            posX -= sin (rotZ /180 *3.14) *time*speed;
        }

        Bullet(double x, double y, double rot) {
            this->posX = x;
            this->posY = y;
            this->rotZ = rot;
        }

        ~Bullet() { }

};


#endif
