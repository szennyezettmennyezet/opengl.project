#define GL_GLEXT_PROTOTYPES

#include "stdafx.h"

#include "3dmodel.h"

#include <windows.h>
#include "glext.h"
#include "glut.h"
#include <exception>
#include <stdexcept>

#include <iostream>

using namespace std;

GLfloat normalize(GLfloat x, GLfloat y,GLfloat z) {
    GLfloat l = x*x + y*y+z*z;
    return l;
}

void x3DModel::generateBuffers() {
    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");

    if (glGenBuffersARB == NULL) {
        //cout << "Error: glGenBuffersARB" << endl;
    }

    glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
    glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
    glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");

    glGenBuffersARB(1, &(frames.at(activeFrame)->vertexArray));
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->vertexArray );
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->vertices.size()*sizeof(xVector),&(frames.at(activeFrame)->vertices.at(0)), GL_STATIC_DRAW);

    glGenBuffersARB(1, &(frames.at(activeFrame)->normalArray));
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->normalArray );
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->normals.size()*sizeof(xVector),&frames.at(activeFrame)->normals.at(0), GL_STATIC_DRAW);


    if (frames.at(activeFrame)->hasTexture) {
        glGenBuffersARB(1, &frames.at(activeFrame)->textureCoordArray);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->textureCoordArray );
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->texturecoords.size()*sizeof(xUVCoord),&frames.at(activeFrame)->texturecoords.at(0), GL_STATIC_DRAW);
    }
}




void x3DModel::drawData(unsigned int mode) {
    cout << "draw " << activeFrame<<endl;

    glScalef(scaleX, scaleY, scaleZ);
    switch(mode) {
        case 0: drawDataVBO();break;
        case 1: drawDataImmediate();break;
        case 2: drawDataDisplayList();break;
    }


    activeFrame = (activeFrame+1)% frames.size();




    //cout << "bibi" << endl;

}

void x3DModel::drawDataImmediate() {
    glEnable(GL_TEXTURE_2D);

    if (frames.at(activeFrame)->hasTexture) {
        glBindTexture(GL_TEXTURE_2D, frames.at(activeFrame)->texture);
    }



    glBegin(GL_TRIANGLES);

    for (unsigned int i =0; i<frames.at(activeFrame)->vertices.size(); i++) {
        if (frames.at(activeFrame)->hasTexture) {
            glTexCoord2f(frames.at(activeFrame)->texturecoords.at(i).u, frames.at(activeFrame)->texturecoords.at(i).v);
        }
        glNormal3f(frames.at(activeFrame)->normals.at(i).X, frames.at(activeFrame)->normals.at(i).Y, frames.at(activeFrame)->normals.at(i).Z);
        glVertex3f(frames.at(activeFrame)->vertices.at(i).X, frames.at(activeFrame)->vertices.at(i).Y, frames.at(activeFrame)->vertices.at(i).Z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void x3DModel::drawDataDisplayList() {
    if (!frames.at(activeFrame)->displayList) {
        frames.at(activeFrame)->displayList = glGenLists (1);
        glNewList(frames.at(activeFrame)->displayList, GL_COMPILE);
        drawDataImmediate();
        glEndList();
    }

    glCallList(frames.at(activeFrame)->displayList);


}

void x3DModel::drawDataVBO() {

    //glScaled(0.05,0.05,0.05);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState( GL_NORMAL_ARRAY );

    if (frames.at(activeFrame)->hasTexture) {
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    }

    glEnableClientState( GL_VERTEX_ARRAY );

    if (frames.at(activeFrame)->hasTexture) {
        glBindTexture(GL_TEXTURE_2D, frames.at(activeFrame)->texture);
    }

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->normalArray );
	glNormalPointer( GL_FLOAT, 0, (char *) NULL );		// Set The TexCoord Pointer To The TexCoord Buffer


    if (frames.at(activeFrame)->hasTexture) {
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->textureCoordArray );
        glTexCoordPointer( 2, GL_FLOAT, 0, (char*) 0);
    }



    glBindBufferARB( GL_ARRAY_BUFFER_ARB, frames.at(activeFrame)->vertexArray );
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer


    glDrawArrays( GL_TRIANGLES, 0, frames.at(activeFrame)->vertices.size() );		// Draw All Of The Triangles


    glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisable(GL_TEXTURE_2D);


}
