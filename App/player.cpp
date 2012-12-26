#include "stdafx.h"

#include "player.h"

//#include "math.h"
#include <iostream>


using namespace std;

void Player::towards(GLfloat x, GLfloat y) {
    GLfloat diffX = x;
    GLfloat diffY = -y;

    if  ((diffX > 0) && (diffY > 0)) {
        rotZ = atan(diffX/diffY) * 180 / 3.14;
    } else if ((diffX < 0) && (diffY < 0)) {
        rotZ = atan(diffX/diffY) * 180 / 3.14 + 180;
    } else if ((diffX > 0) && (diffY < 0)) {
        rotZ = atan(diffX/diffY) * 180 / 3.14 + 180;
    } else {
        rotZ = atan(diffX/diffY) * 180 / 3.14;
    }

}

void Player::forward(float n) {
    posY += cos (rotZ /180 *3.14) *n;
    posX -= sin (rotZ /180 *3.14) *n;
}

void Player::move(GLfloat x, GLfloat y) {
    //cout << x << " " << y << endl;
    posY += sin (rotZ /180 *3.14) *x;
    posX += cos (rotZ /180 *3.14) *x;
}


void Player::backward(float n) {
    forward(-n);
}

void Player::drawData(unsigned int mode) {
    model->drawData(mode);
}
