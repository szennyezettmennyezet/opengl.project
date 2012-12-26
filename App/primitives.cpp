#include "stdafx.h"

#include "primitives.h"


void xSphereObject::drawData() {


    glutSolidSphere(1.0, 50, 50);
}

void xCubeObject::drawData() {

    glTranslatef(-X,-Y,Z);

    glutSolidCube(1.0);
}
