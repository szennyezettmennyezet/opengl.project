#ifndef __PARTICLE__
#define __PARTICLE__

#include "GL/gl.h"


class xParticle {
    public:
        bool repeat;

        float X,Y,Z;

        float dX,dY,dZ;
        float gX,gY,gZ;

        float *color1;
        float *color2;
        float *color3;
        float *color4;

        float particle_size;
        GLuint list;

        void tick(float timeDiff) {
            dX += gX*timeDiff;
            dY += gY*timeDiff;
            dZ += gZ*timeDiff;

            X += dX*timeDiff;
            Y += dY*timeDiff;
            Z += dZ*timeDiff;


        }


        xParticle(): X(0.0f),Y(0.0f),Z(0.0f),dX(0.0),dY(0.0f),dZ(0.0f),gX(0.0),gY(0.0),gZ(0.0),particle_size(0.01),repeat(false) {
            color1 = new float[4];
            color2 = new float[4];
            color3 = new float[4];
            color4 = new float[4];

            color1[0] = 1.00; color1[1] = 0.76; color1[2] = 0.05; color1[3] = 0.8f;
            color2[0] = 1.00; color2[1] = 0.50; color2[2] = 0.00; color2[3] = 0.8f;
            color3[0] = 1.00; color3[1] = 0.50; color3[2] = 0.00; color3[3] = 0.8f;
            color4[0] = 1.93; color4[1] = 0.11; color4[2] = 0.14; color4[3] = 0.8f;



            list = 0;
        }

        void draw(float rot) {

            glEnable(GL_BLEND);		// Turn Blending On
            glEnable(GL_COLOR_MATERIAL);

            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// Blending Function For Translucency Based On Source Alpha Value ( NEW )


            if (list == 0) {
                list = glGenLists(1);
                glNewList(list, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    /*glColor4f(1.0 ,0.76,0.05,1.0);glVertex3f( 0.0f,             0.0f, particle_size);
                    glColor4f(1.0 ,0.5 ,0.0 ,1.0);glVertex3f(-particle_size,    0.0f, 0.0f);
                    glColor4f(1.0 ,0.5 ,0.0 ,1.0);glVertex3f( particle_size,    0.0f, 0.0f);
                    glColor4f(1.0 ,0.5 ,0.0 ,1.0);glVertex3f(-particle_size,    0.0f, 0.0f);
                    glColor4f(0.93,0.11,0.14,1.0);glVertex3f( 0.0f,             0.0f, -particle_size);
                    glColor4f(1.0 ,0.5 ,0.0 ,1.0);glVertex3f( particle_size,    0.0f, 0.0f);*/

                    glColor4fv(color1);glVertex3f( 0.0f,             0.0f, particle_size);
                    glColor4fv(color2);glVertex3f(-particle_size,    0.0f, 0.0f);
                    glColor4fv(color3);glVertex3f( particle_size,    0.0f, 0.0f);


                    glColor4fv(color2);glVertex3f(-particle_size,    0.0f, 0.0f);
                    glColor4fv(color4);glVertex3f( 0.0f,             0.0f, -particle_size);
                    glColor4fv(color3);glVertex3f( particle_size,    0.0f, 0.0f);
                glEnd();

                glEndList();
            }

            glPushMatrix();

            glTranslatef(-X,Y,Z);
            glRotatef(rot, 0.0f, 0.0f, -1.0f);
            glDisable(GL_TEXTURE_2D);
            glCallList(list);
            glPopMatrix();


            glDisable(GL_BLEND);		// Turn Blending On

        }
};


#endif
