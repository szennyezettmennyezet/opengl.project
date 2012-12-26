#include "stdafx.h"

#include "material.h"

xMaterial::xMaterial() {

}


xMaterial::xMaterial(const GLfloat* specular, const GLfloat* shininess) {
    this->specular = new GLfloat[4];
    this->shininess = new GLfloat[4];

    for (int i=0; i<4; i++) {
        this->specular[i] = specular[i];
        this->shininess[i] = shininess[i];
    }
}

void xMaterial::set() {
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
