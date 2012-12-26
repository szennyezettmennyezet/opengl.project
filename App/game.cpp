#include "stdafx.h"

#include "game.h"


#include <iostream>
#include <iomanip>

using namespace std;

void xGame::keyDown(unsigned int keyCode) {
    if (!keys[keyCode]) {
        keyDownNow(keyCode);
    }
    keys[keyCode] = true;
}

void xGame::keyUp(unsigned int keyCode) {
    keys[keyCode] = false;
}

void xGame::keyDownNow(unsigned int keyCode) {
    //cout << keyCode << endl;

    if (keyCode == KEYCODE_ESCAPE) {
        showMenu = !showMenu;
    }

    if (keyCode == KEYCODE_F1) {
        draw_mode = (draw_mode +1)%3;

    }

    if (keyCode == KEYCODE_F2) {
        fog = !fog;

        if (fog) {
            glEnable(GL_FOG);
        } else {
            glDisable(GL_FOG);
        }
    }


    if (showMenu){
        if (keyCode == KEYCODE_ENTER) {
            switch(menuPosition) {
                 case 0: showMenu = false;break;
                 case 1: endGame = true;break;
            }

        }


        if (keyCode == KEYCODE_UP) {
            menuPosition = (menuPosition-1+2)%2;
            //player->move(0,timeDiff );
        }

        if (keyCode == KEYCODE_DOWN) {
            menuPosition = (menuPosition+1)%2;
        }
    }

}
void xGame::keyUpNow(unsigned int keyCode) {
    keys[keyCode] = false;
}








bool xGame::checkContinue() {
    return !endGame;
}


void xGame::mouseLeftButtonDown() {
    mouse[0] =true;
}

void xGame::mouseLeftButtonUp() {
    mouse[0] = false;
}




bool xGame::init() {
    sec = new Sector*[100];

    for (unsigned int y = 0; y < 10; y++) {
        for (unsigned int x = 0; x < 10; x++) {
            cout << (10*y + x) << endl;
            sec[10*y + x] = new Sector(8*x-40, 8*y-40, 0, 0.02);
            sec[10*y + x]->createSnow();
        }
    }

    cout << "Runnning init" << endl;


    showMenu = true;
    rotMenu = 0.0f;
    menuPosition = 0;

    camRotX = 0.0f;

    text = new x3DText();


    for (int i=0; i<256; i++) {
        keys[i] = false;
    }

    light = new xLight(GL_LIGHT0);

    camRotX = 0.0;
    camRotY = 0.0;
    camRotZ = 0.0;

    camPosX = 0.0;
    camPosY = 0.0;
    camPosZ = 0.0;

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat black_light[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    xMaterial* mat = new xMaterial(mat_specular, mat_shininess);
    mat->set();



    glEnable(GL_COLOR);

    glColor4f(0.5,0.0,0.0,1.0);

    light->setPosition(2.0, 1.0, 1.0, 0.0);
    light->setDiffuse(white_light);


    light->setSpecular(black_light);


    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    //glDepthRange(0.0, 1.0);




    glEnable(GL_LIGHTING);

    light->enable();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);



    player = new Player("soldier");


    for (float i =0.0; i < 1; i++) {
        Player *p = new Player("monster");
        p->posX = 10 - 5*i;

        zombies.push_back(p);
        //drawed_objects.push_back(p);
    }

    cout << "Loading terrain" << endl;

    //terrain = new xTerrain("terrain",40.0,40.0);
    terrain = new Player("terrain");

    cout << "Terrain loaded" << endl;

    skyBox = new x3DModelFromFile("skybox");


    house = new Player("malom");    house->posX = 5.0f;     //drawed_objects.push_back(house);
    house = new Player("house");    house->posX = 8.0f;     //drawed_objects.push_back(house);



    mlyn = new Player("lapat");    mlyn->posX = 6.0f;mlyn->posZ = 8.0f;     //drawed_objects.push_back(mlyn);


    cout << "Init complete" << endl;


    drawed_objects.push_back(player);
    drawed_objects.push_back(terrain);



    explosions.push_back(new Explosion(0.0,2.0,0.5));


    Player* h = 0;
    h = new Player("hedge");    h->posX = -20.0f;   h->posY = 30.0f;    hedges.push_back(h);
    h = new Player("hedge");    h->posX = -10.0f;   h->posY = 30.0f;    hedges.push_back(h);
    h = new Player("hedge");    h->posX =   0.0f;   h->posY = 30.0f;    hedges.push_back(h);
    h = new Player("hedge");    h->posX =  10.0f;   h->posY = 30.0f;    hedges.push_back(h);
    h = new Player("hedge");    h->posX =  20.0f;   h->posY = 30.0f;    hedges.push_back(h);

    h = new Player("hedge");    h->posX = -20.0f;   h->posY = -30.0f;    hedges.push_back(h);
    h = new Player("hedge");    h->posX = -10.0f;   h->posY = -30.0f;    hedges.push_back(h);
    h = new Player("hedge");    h->posX =   0.0f;   h->posY = -30.0f;    hedges.push_back(h);
    h = new Player("hedge");    h->posX =  10.0f;   h->posY = -30.0f;    hedges.push_back(h);
    h = new Player("hedge");    h->posX =  20.0f;   h->posY = -30.0f;    hedges.push_back(h);

    h = new Player("hedge");    h->posY = -20.0f;   h->posX = -30.0f;    hedges.push_back(h); h->rotZ = 90.0f;
    h = new Player("hedge");    h->posY = -10.0f;   h->posX = -30.0f;    hedges.push_back(h);h->rotZ = 90.0f;
    h = new Player("hedge");    h->posY =   0.0f;   h->posX = -30.0f;    hedges.push_back(h);h->rotZ = 90.0f;
    h = new Player("hedge");    h->posY =  10.0f;   h->posX = -30.0f;    hedges.push_back(h);h->rotZ = 90.0f;
    h = new Player("hedge");    h->posY =  20.0f;   h->posX = -30.0f;    hedges.push_back(h);h->rotZ = 90.0f;

    h = new Player("hedge");    h->posY = -20.0f;   h->posX = 30.0f;    hedges.push_back(h); h->rotZ = -90.0f;
    h = new Player("hedge");    h->posY = -10.0f;   h->posX = 30.0f;    hedges.push_back(h);h->rotZ = -90.0f;
    h = new Player("hedge");    h->posY =   0.0f;   h->posX = 30.0f;    hedges.push_back(h);h->rotZ = -90.0f;
    h = new Player("hedge");    h->posY =  10.0f;   h->posX = 30.0f;    hedges.push_back(h);h->rotZ = -90.0f;
    h = new Player("hedge");    h->posY =  20.0f;   h->posX = 30.0f;    hedges.push_back(h);h->rotZ = -90.0f;


    h = new Player("chapel");   h->posY =  25.0f;   h->posX = 41.0f; h->posZ = 0.5f;    hedges.push_back(h);h->rotZ = -90.0f;

    for (vector<Player*>::iterator i = hedges.begin(); i!=hedges.end(); i++) {
        drawed_objects.push_back(*i);

    }

fog = true;



    glMatrixMode(GL_PROJECTION_MATRIX);

    glEnable(GL_FOG);
    {
        GLfloat fogColor[4] = {0.4, 0.4, 0.4, 0.1};
        static GLint fogMode = GL_EXP;


        glFogi (GL_FOG_MODE, fogMode);

        glFogfv (GL_FOG_COLOR, fogColor);
        glFogf (GL_FOG_DENSITY, 0.03);
        glHint (GL_FOG_HINT, GL_DONT_CARE);
        glFogf (GL_FOG_START, 10.0);
        glFogf (GL_FOG_END, 60.0);
    }
    glClearColor(0.4, 0.4, 0.4, 0.5);  /* fog color */


    //glClearColor(0.0, 0.0, 0.4, 1.0);  /* fog color */



   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
   //glShadeModel(GL_FLAT);

    glPixelTransferf(GL_RED_SCALE, 1.0);
    glPixelTransferf(GL_GREEN_SCALE, 1.0);
    glPixelTransferf(GL_BLUE_SCALE, 1.0);
    glPixelTransferf(GL_RED_BIAS, 0.0);
    glPixelTransferf(GL_GREEN_BIAS, 0.0);
    glPixelTransferf(GL_BLUE_BIAS, -0.5);




    return true;

}

void xGame::tick(){
    actualTime = clock();
    //cout << "Running tick" << endl;

    if (firstFrame) {
        timer.startTimer();
        firstFrame = false;
    }

    double timeDiff = timer.stopTimer();
    timer.startTimer();
    fps = 1.0/timeDiff;







    if (!showMenu) {
        player->rotZ += (float(mouseX)-100)/10;
        camRotX += (float(mouseY)-100)/10;


        if (keys[KEYCODE_LEFT]) {
            player->move(timeDiff*5,0);
        }

        if (keys[KEYCODE_RIGHT]) {
            player->move(-timeDiff*5,0);
        }


        if (keys[KEYCODE_UP]) {
            player->forward(timeDiff*5);
            //player->move(0,timeDiff );
        }

        if (keys[KEYCODE_DOWN]) {
            player->forward(-timeDiff*5);
            //player->move(0.0,-timeDiff);
        }



        if (keys[KEYCODE_COMMA]) {
            camRotY -= 0.1;
            cout << camRotY << endl;
        }

        if (keys[KEYCODE_PERIOD]) {
            camRotY += 0.1;
        }


        if (keys[KEYCODE_PG_UP]) {
            camPosY += 0.01;
        }


        if (keys[KEYCODE_PG_DOWN]) {
            camPosY -= 0.01;
        }

        //player->posZ = terrain->getHeight(player->posX, player->posY)/200;


        if (keys[KEYCODE_SPACE] || mouse[0]) {
                //cout << "FPS: " << (1.0 / timeDiff) << endl;
            if ((actualTime - lastShot) > 200) {
                Bullet *b = new Bullet(player->posX, player->posY, player->rotZ);
                b->setSpeed(0.01);
                bullets.push_back(b);

                lastShot = actualTime;
            }
        }

        list<Bullet*>::iterator bullet;

        int ik=0;

        for (list<Player*>::iterator zombie = zombies.begin() ; zombie != zombies.end(); zombie++ ) {
            if ((-player->posX + (*zombie)->posX!=0) && (-player->posY + (*zombie)->posY!=0)) {
                (*zombie)->towards(-player->posX + (*zombie)->posX   , -player->posY + (*zombie)->posY);
                (*zombie)->forward(timeDiff);
            }
            ik++;
        }




        for (bullet = bullets.begin(); bullet != bullets.end();) {
            (*bullet)->tick(1.0);
            bool deleted = false;

            for (list<Player*>::iterator zombie = zombies.begin() ; zombie != zombies.end();) {

                GLfloat diffX = (*bullet)->getPosX() - (*zombie)->getPosX();
                GLfloat diffY = (*bullet)->getPosY() - (*zombie)->getPosY();

                GLfloat dist = diffX*diffX + diffY*diffY;


                if ( dist < 0.001) {

                    explosions.push_back(new Explosion((*zombie)->posX,(*zombie)->posY,(*zombie)->posZ));


                    vector<xDrawable*>::iterator i = drawed_objects.begin();

                    while (i!= drawed_objects.end()) {
                        if ((*i) == (*zombie)) {
                            drawed_objects.erase(i);
                            break;
                        } else {
                            i++;
                        }
                    }

                    delete (*zombie);

                    zombie = zombies.erase(zombie);




                    bullet = bullets.erase(bullet);
                    deleted = true;
                    zombie = zombies.end();
                    cout << "bum" << endl;
                } else {
                    zombie++;
                }



            }


            if (!deleted) {
                bullet++;
            }


        }

        //cout << "Collision ok" << endl;



        angle += 0.1;


        if (player->posX < -28) player->posX = -28;
        if (player->posX >  28) player->posX =  28;

        if (player->posY < -28) player->posY = -28;
        if (player->posY >  28) player->posY =  28;



        sectorX = (int)((player->posX + 40.0) / 8);
        sectorY = (int)((player->posY + 40.0) / 8);
        sectorIndex = sectorY*10+sectorX;



        for (int secY = sectorY - 1; secY <= sectorY+1; secY++) {
            for (int secX = sectorX - 1; secX <= sectorX+1; secX++) {
                if ((secY>=0) && (secY<=9) && (secX>=0) && (secX<=9)) sec[10*secY + secX]->tick(timeDiff);
            }
        }

        vector<Explosion*>::iterator i = explosions.begin();
        while(i!=explosions.end()) {
            (*i)->tick(timeDiff);
            i++;
        }

        mlyn->rotY += 30.0f*timeDiff;


    } else {

    }

    display();

}


void xGame::displayMenu() {
    glLoadIdentity();

    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0,1.0,1.0);

    glTranslatef(0.0,0.5,-1.5);
    glPushMatrix();
    glScalef(0.2f,0.2f,0.2f);
    if (menuPosition == 0) glRotatef(rotMenu, 1.0,0.0,0.0);
    glTranslatef(0.0,-0.25,0.1);
    text->glPrint("START GAME/RESUME");
    glPopMatrix();

    glTranslatef(0.0,-0.2,0.0);
    glPushMatrix();
    glScalef(0.2f,0.2f,0.2f);
    if (menuPosition == 1) glRotatef(rotMenu, 1.0,0.0,0.0);
    glTranslatef(0.0,-0.25,0.1);
    text->glPrint("QUIT");
    glPopMatrix();

    //glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');

    rotMenu += 0.1;
    glDisable(GL_COLOR_MATERIAL);
}

void xGame::display() {
    glMatrixMode(GL_PROJECTION);                        // Budeme menit projekcnu maticu (transformaciu)
	glLoadIdentity();                                   // Vynulovanie
    gluPerspective(65, 1.333, 0.5, 200.0); // Chceme perspektivu
	glMatrixMode(GL_MODELVIEW);                         // Vratime sa spat k modelview matici
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_COLOR_MATERIAL);
    glLoadIdentity();


    glRotatef(camRotX, 1.0,0.0,0.0);

    glTranslatef(0.0,0.0,-2.5);


    glRotatef(-65, 1.0,0.0,0.0);


    glRotatef(player->rotZ, 0.0,0.0,1.0);

    glPushMatrix();
    skyBox->drawData(draw_mode);
    glPopMatrix();

    glTranslatef( player->posX, -player->posY, 0.0);




    glPushMatrix();
      light->setPosition(1.0, 1.0, 1.0, 0.0);
    glPopMatrix();





    glColor3f(0.0,0.5,0.0);





    for (list<Bullet*>::iterator bullet = bullets.begin(); bullet != bullets.end(); bullet++ ) {
       (*bullet)->draw(draw_mode);
    }


    for (vector<xDrawable*>::iterator object = drawed_objects.begin(); object!=drawed_objects.end(); object++) {
        //(*object)->draw(draw_mode);
    }


    (*zombies.begin())->draw(draw_mode);



    int radius = 1;

    for (int secY = sectorY - radius; secY <= sectorY+radius; secY++) {
        for (int secX = sectorX - radius; secX <= sectorX+radius; secX++) {
            int index = 10*secY + secX;
            if ((index>=0) && (index<100)) {
                sec[index]->drawSnow(player->rotZ);
                //cout << index << endl;
            }
        }
    }

    vector<Explosion*>::iterator i = explosions.begin();
    while(i!=explosions.end()) {
        (*i)->draw(player->rotZ);
        i++;
    }




    //sec[sectorIndex]->drawSnow(player->rotZ);


    glLoadIdentity();
    glTranslatef(-1.2,1.2,-2.0);


    if (showMenu) {
        glClear(GL_DEPTH_BUFFER_BIT);
        displayMenu();
    }


    glDisable(GL_LIGHTING);


    glColor3f(1.0,1.0,1.0);
    text->printRasterString("TEXT", 8, 8);

    switch(draw_mode) {
        case 0: text->printRasterString("DRAW MODE (F1): vertex buffer", 8, 22);break;
        case 1: text->printRasterString("DRAW MODE (F1): immediate mode", 8, 22);break;
        case 2: text->printRasterString("DRAW MODE (F1): display list", 8, 22);break;
    }

    char s[20];
    sprintf_s(s,"%f",fps);
    string fpsstring = "FPS: ";
    fpsstring = fpsstring + s;
    text->printRasterString(fpsstring, 8, 40);

    if (fog) {
        text->printRasterString("Fog: ON", 8, 52);
    } else {
        text->printRasterString("Fog: OFF", 8, 52);
    }


    sprintf_s(s,"Position %u %u Index: %u",sectorX,sectorY,sectorIndex);

    string c = "Pos";
    c = c + s;

    text->printRasterString(c, 8, 64);

    glEnable(GL_LIGHTING);





    glFlush();
}



void xGame::reshape(int w, int h) {
    glViewport(0,0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    scrW = w;
    scrH = h;

    /*
    if (w<=h) {
        glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)h/(GLfloat)w, - 10.0, 10.0);
    } else {
        glOrtho(-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    }*/

    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.0,1.0,1.5,50.0);



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}


void xGame::mouseMove(int X, int Y) {

    //double paramX = ((double(X)) / (double(scrW)) - 0.5);
    //double paramY = ((double(Y)) / (double(scrH)) - 0.5);


    //player->towards(paramX, paramY);

    mouseX = X;
    mouseY = Y;

}



xGame::xGame(): firstFrame(true), draw_mode(0)  {
    endGame = false;

    fog = false;

    light;
    angle = 0.0;

}

xGame::~xGame() {
//    delete t;
}



float xGame::calcFPS(int dt)
{
    fpsSamples[currentSample % NUM_FPS_SAMPLES] = 1.0f / dt;
    float fps = 0;
    for (int i = 0; i < NUM_FPS_SAMPLES; i++)
        fps += fpsSamples[i];
    fps /= NUM_FPS_SAMPLES;
    return fps;
}



