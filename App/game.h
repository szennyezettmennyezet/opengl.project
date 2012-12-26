#ifndef __XGAME__
#define __XGAME__


#include "GL/gl.h"
#include "glut.h"

#include "light.h"
#include "material.h"

#include "object.h"
#include "drawable.h"
#include "primitives.h"
#include "3dmodel.h"
#include "terrain.h"

#include "explosion.h"

#include "particle.h"


#include "player.h"
#include "bullet.h"
#include "text.h"

//#include "modelloader/modelloader.h"


#include <list>


#include "hrtimer.h"

#define KEYCODE_ENTER  13

#define KEYCODE_ESCAPE  27

#define KEYCODE_SPACE   32
#define KEYCODE_LEFT    37
#define KEYCODE_UP      38
#define KEYCODE_RIGHT   39
#define KEYCODE_DOWN    40

#define KEYCODE_F1      0x70
#define KEYCODE_F2      0x71


#define KEYCODE_COMMA   188
#define KEYCODE_PERIOD  190


#define KEYCODE_PG_UP 33
#define KEYCODE_PG_DOWN 34





using namespace std;

class Sector {
    public:
        int X,Y,Z;
        float size;
        vector<xParticle*> snow;

        Sector(int x, int y, int z, float s): X(x),Y(y),Z(z),size(s) { cout << x << " " << y <<endl;}


        void createSnow() {
            float* color1 = new float[3];
            float* color2 = new float[3];
            float* color3 = new float[3];
            float* color4 = new float[3];

            color1[0] = 1.00; color1[1] = 0.76; color1[2] = 0.05; color1[3] = 0.05;
            color2[0] = 1.00; color2[1] = 0.50; color2[2] = 0.00; color2[3] = 0.05;
            color3[0] = 1.00; color3[1] = 0.50; color3[2] = 0.00; color3[3] = 0.05;
            color4[0] = 1.93; color4[1] = 0.11; color4[2] = 0.14; color4[3] = 0.05;


            for(unsigned int i = 0; i<100;i++) {
                float sx = ((float)(rand()%100))/12.5f + X;
                float sy = ((float)(rand()%100))/12.5f + Y;
                float sz = ((float)(rand()%10000))/1250;
                float particle_size = size;//0.1f;

                xParticle *p = new xParticle();
                p->X = sx;
                p->Y = sy;
                p->Z = sz;
                p->particle_size = particle_size;
                p->dZ = -0.4;

                p->color1 = color1;
                p->color2 = color2;
                p->color3 = color3;
                p->color4 = color4;

                snow.push_back(p);
            }

            //delete[] color1;
            //delete[] color2;
            //delete[] color3;
            //delete[] color4;

        }


        void drawSnow(float rot) {
            glPushMatrix();

            glEnable(GL_COLOR);
            glEnable(GL_COLOR_MATERIAL);
            for(unsigned int i = 0; i<snow.size();i++) {
                snow.at(i)->draw(rot);
            }
            glColor3f(1.0f,1.0f,1.0f);
            glDisable(GL_COLOR_MATERIAL);

            glPopMatrix();
        }

        void tick(double time) {
            for(unsigned int i = 0; i<snow.size();i++) {


                snow.at(i)->tick(time);

                if (snow.at(i)->Z < 0) {
                    snow.at(i)->Z = 4.0f;
                }
            }
        }


};



class xGame {
    protected:
        bool endGame;

        bool	keys[256];								// Array Used For The Keyboard Routine
        bool    mouse[3];


        unsigned int scrW, scrH;

        /*************************************
        *   TIMING
        *************************************/

        static const int NUM_FPS_SAMPLES = 64;
        float fpsSamples[NUM_FPS_SAMPLES];
        int currentSample;
        int actualTime;

        unsigned int lastShot;
        HRTimer timer;
        double fps;





        /*************************************
        *   DRAWING
        *************************************/

        Player *mlyn;

        bool fog;
        unsigned int draw_mode;
        vector<xDrawable*> drawed_objects;
        GLfloat angle;
        GLfloat camPosX, camPosY, camPosZ, camRotX, camRotY, camRotZ;

        vector<xParticle*> rain;


        Sector **sec;
        int sectorX;
        int sectorY;
        int sectorIndex;

        vector<Explosion*> explosions;


        /*************************************
        *   MENU
        *************************************/
        bool showMenu;
        float rotMenu;
        unsigned int menuPosition;





        unsigned int mouseX, mouseY;


        /*************************************
        *   OBJECTS
        *************************************/
        xLight* light;

        Player* player;
        list<Player*> zombies;
        list<Bullet*> bullets;
        x3DText *text;
        Player *house;
        Player*  terrain;

        x3DModelFromFile *skyBox;


        vector<Player*> hedges;

        void display();
        void displayMenu();



        bool firstFrame;


    public:
        xGame();
        ~xGame();


        bool init();

        void tick();

        float calcFPS(int dt);


        void reshape(int w, int h);


        void keyUp(unsigned int keyCode);
        void keyDown(unsigned int keyCode);

        void keyDownNow(unsigned int keyCode);
        void keyUpNow(unsigned int keyCode);


        bool checkContinue();

        void mouseMove(int X, int Y);

        void mouseLeftButtonDown();
        void mouseLeftButtonUp();

};



#endif



