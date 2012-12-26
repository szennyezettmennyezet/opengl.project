#include "stdafx.h"

#include "light.h"

#include <iostream>


using namespace std;

xLight::xLight(GLenum number) {

    position = new GLfloat[4];
    this->number = number;
}

void xLight::enable() {
    glEnable(number);
}

void xLight::disable() {
    glDisable(number);
}

void xLight::setPosition(GLfloat X, GLfloat Y, GLfloat Z, GLfloat W ) {
    position[0] = X;
    position[1] = Y;
    position[2] = Z;
    position[3] = W;

    glLightfv(number, GL_POSITION, position );

    //cout << "position "<< X << " " << Y << " " << Z << " " << W <<endl;
}

void xLight::setDiffuse( GLfloat* color ) {
    glLightfv(number, GL_DIFFUSE, color);
}

void xLight::setSpecular( GLfloat* color ) {
    glLightfv(number, GL_SPECULAR, color);
}
