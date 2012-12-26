#ifndef __EXPLOSION__
#define __EXPLOSION__

#include "particle.h"
#include <list>

using namespace std;


class Explosion {
    public:
        float X,Y,Z;

        list<xParticle*> particles;

        Explosion(float x,float y, float z): X(x),Y(y),Z(z) {
            for(unsigned int i = 0; i<1000;i++) {
                float particle_size = 0.03f;

                xParticle *p = new xParticle();
                p->X = X;p->Y = Y;p->Z = Z;


                p->dZ = 1.0;
                p->gZ = -0.5;

                p->dX = ((float)(rand()%100))/100.0f - 0.5f;
                p->dY = ((float)(rand()%100))/100.0f - 0.5f;

                p->dZ = ((float)(rand()%100))/70.0f;






                p->particle_size = particle_size;

                particles.push_back(p);
            }
        }

        void draw(float rot) {
            glPushMatrix();

            glEnable(GL_COLOR);
            glEnable(GL_COLOR_MATERIAL);


            for(list<xParticle*>::iterator i = particles.begin(); i!=particles.end();i++) {
                (*i)->draw(rot);
            }
            glColor3f(1.0f,1.0f,1.0f);
            glDisable(GL_COLOR_MATERIAL);

            glPopMatrix();
        }

        void tick(double time) {
            for(list<xParticle*>::iterator i = particles.begin(); i!=particles.end();) {
                (*i)->tick(time);

                if ((*i)->Z <0) {
                    //cout << "del"<<endl;
                    delete (*i);
                    //cout << "erase"<<endl;
                    i = particles.erase(i);
                    //cout << "ok"<<endl;

                } else {
                    i++;
                }




            }
        }



};


#endif
