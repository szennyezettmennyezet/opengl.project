#define GL_GLEXT_PROTOTYPES

#include "stdafx.h"

#include "3dmodel.h"

#include "math.h"

#include <iostream>
#include <fstream>
#include <vector>

#include <windows.h>

#include "glext.h"

using namespace std;

GLfloat normalize(GLfloat x, GLfloat y,GLfloat z) {
    GLfloat l = x*x + y*y+z*z;
    return l;
}



x3DModel::x3DModel() {




    vertices = new xVector[10000];
    normals = new xVector[10000];




    cout << "model";

    for (unsigned int x = 0; x < 100; x++) {
        for (int z = 0; z < 100; z++) {
            xVector vertex;
            vertex.X = x;
            vertex.Y = sin ( (float)x/10 );
            vertex.Z = z;

            vertices.push_back(vertex);




            GLfloat ratio = normalize(cos((float)x/10),1,1);

            vertex.X = -cos((float)x/10)/ratio;
            vertex

            normals[z*100 + x].X = -cos((float)x/10)/ratio;
            normals[z*100 + x].Y = 1.0/ratio;
            normals[z*100 + x].Z = 0.0;


            //cout << x << " " << vertices[z*100 + x].nX << " " << vertices[z*100 + x].nY << " " << vertices[z*100 + x].nZ << endl;
        }

    }


    /*displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);



    for (int i=0; i<99; i++) {
        for (int j =0; j<99; j++) {
            glColor3f(0.0,0.0,1.0);
            glBegin(GL_TRIANGLES);
                glNormal3f(normals[100*i + j].nX, normals[100*i + j].nY, normals[100*i + j].nZ);
                glVertex3f(vertices[100*i + j].X, vertices[100*i + j].Y, vertices[100*i + j].Z);

                glNormal3f(normals[100*i + j + 1].nX, normals[100*i + j + 1].nY, normals[100*i + j + 1].nZ);
                glVertex3f(vertices[100*i + j + 1].X,  vertices[100*i + j + 1].Y,  vertices[100*i + j + 1].Z);

                glNormal3f(normals[100*(i+1) + j].nX, normals[100*(i+1) + j].nY, normals[100*(i+1) + j].nZ);
                glVertex3f(vertices[100*(i+1) + j].X, vertices[100*(i+1) + j].Y, vertices[100*(i+1) + j].Z);


                glNormal3f(normals[100*i + j + 1].nX, normals[100*i + j + 1].nY, normals[100*i + j + 1].nZ);
                glVertex3f(vertices[100*i + j + 1].X, vertices[100*i + j + 1].Y, vertices[100*i + j + 1].Z);

                glNormal3f(normals[100*(i+1) + j].nX, normals[100*(i+1) + j].nY, normals[100*(i+1) + j].nZ);
                glVertex3f(vertices[100*(i+1) + j].X, vertices[100*(i+1) + j].Y, vertices[100*(i+1) + j].Z);

                glNormal3f(normals[100*(i+1) + j+1].nX, normals[100*(i+1) + j+1].nY, normals[100*(i+1) + j+1].nZ);
                glVertex3f(vertices[100*(i+1) + j+1].X, vertices[100*(i+1) + j+1].Y, vertices[100*(i+1) + j+1].Z);
            glEnd();

        glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINES);



            glVertex3f(vertices[100*i + j].X+normals[100*i + j].nX, vertices[100*i + j].Y+normals[100*i + j].nY, vertices[100*i + j].Z+normals[100*i + j].nZ);
            glVertex3f(vertices[100*i + j].X, vertices[100*i + j].Y, vertices[100*i + j].Z);

            glVertex3f(vertices[100*i + j + 1].X+normals[100*i + j + 1].nX, vertices[100*i + j + 1].Y+normals[100*i + j + 1].nY, vertices[100*i + j + 1].Z+normals[100*i + j + 1].nZ);
            glVertex3f(vertices[100*i + j + 1].X,  vertices[100*i + j + 1].Y,  vertices[100*i + j + 1].Z);

            glVertex3f(vertices[100*(i+1) + j].X+normals[100*(i+1) + j].nX, vertices[100*(i+1) + j].Y+vertices[100*(i+1) + j].nY, vertices[100*(i+1) + j].Z+vertices[100*(i+1) + j].nZ);
            glVertex3f(vertices[100*(i+1) + j].X, vertices[100*(i+1) + j].Y, vertices[100*(i+1) + j].Z);


            glVertex3f(vertices[100*i + j + 1].X+vertices[100*i + j + 1].nX, vertices[100*i + j + 1].Y+vertices[100*i + j + 1].nY, vertices[100*i + j + 1].Z+vertices[100*i + j + 1].nZ);
            glVertex3f(vertices[100*i + j + 1].X, vertices[100*i + j + 1].Y, vertices[100*i + j + 1].Z);

            glVertex3f(vertices[100*(i+1) + j].X+vertices[100*(i+1) + j].nX, vertices[100*(i+1) + j].Y+vertices[100*(i+1) + j].nY, vertices[100*(i+1) + j].Z+vertices[100*(i+1) + j].nZ);
            glVertex3f(vertices[100*(i+1) + j].X, vertices[100*(i+1) + j].Y, vertices[100*(i+1) + j].Z);

            glVertex3f(vertices[100*(i+1) + j+1].X+vertices[100*(i+1) + j+1].nX, vertices[100*(i+1) + j+1].Y+vertices[100*(i+1) + j+1].nY, vertices[100*(i+1) + j+1].Z+vertices[100*(i+1) + j+1].nZ);
            glVertex3f(vertices[100*(i+1) + j+1].X, vertices[100*(i+1) + j+1].Y, vertices[100*(i+1) + j+1].Z);

    glEnd();


        }

    }


    glEndList();*/



    vertexIndices = new GLuint[99*99*6];

    vert = new xVector[99*99*6];
    norms = new xVector[99*99*6];


    for (int i=0; i<99; i++) {
        for (int j =0; j<99; j++) {
            vert [(i*99+j)*6+0] =    vertices[100*i + j];
            norms[(i*99+j)*6+0] =    normals [100*i + j];

            vert [(i*99+j)*6+1] =    vertices[100*(i+1) + j];
            norms[(i*99+j)*6+1] =    normals [100*(i+1) + j];

            vert [(i*99+j)*6+2] =    vertices[100*i + j + 1];
            norms[(i*99+j)*6+2] =    normals [100*i + j + 1];

            vert [(i*99+j)*6+3] =    vertices[100*i + j + 1];
            norms[(i*99+j)*6+3] =    normals [100*i + j + 1];

            vert [(i*99+j)*6+4] =    vertices[100*(i+1) + j];
            norms[(i*99+j)*6+4] =    normals [100*(i+1) + j];

            vert [(i*99+j)*6+5] =    vertices[100*(i+1) + j+1];
            norms[(i*99+j)*6+5] =    normals [100*(i+1) + j+1];






        }

    }







    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");


    glGenBuffersARB(1, &buffer);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffer );
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, 99*99*6*sizeof(xVector),vert, GL_STATIC_DRAW);




    glGenBuffersARB(1, &normalArray);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, normalArray );
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, 99*99*6*sizeof(xVector),norms, GL_STATIC_DRAW);


    for(int i=0; i < 99*99*6; i++) {
        //cout << norms[i].X << " " << norms[i].Y << " "<<norms[i].Z << endl;
    }


}




x3DModel::x3DModel(char* fileName) {
    fstream modelFile(fileName, ios_base::in);

    vector<xVector*> vert1;
    vector<xVector*> normals1;
    vector<unsigned int> vindices1;
    vector<unsigned int> nindices1;

    int i;

    while ( modelFile >> i ) {
        switch(i) {
            case 1:
                xVector* v = new xVector();
                modelFile << v->X;
                modelFile << v->Y;
                modelFile << v->Z;
                vert1.push_back(v);
                break;
            case 2:
                xVector* n = new xVector();
                modelFile << n->X;
                modelFile << n->Y;
                modelFile << n->Z;
                normals1.push_back(n);
                break;
            case 3:
                unsigned int ni,vi;

                for (int i=0; i<3; i++) {
                    modelFile << vi;
                    modelFile << ni;
                    vindices1.push_back(vi);
                    nindices1.push_back(ni);
                }



                break;
        }
    }


cout << "ok";
    modelFile.close();
}




















void x3DModel::draw() {


    //glCallList(displayList);

    glEnableClientState( GL_NORMAL_ARRAY );
    //glNormalPointer( GL_FLOAT, 0, norms);

    glEnableClientState( GL_VERTEX_ARRAY );



    glBindBufferARB( GL_ARRAY_BUFFER_ARB, normalArray );
	glNormalPointer( GL_FLOAT, 0, (char *) NULL );		// Set The TexCoord Pointer To The TexCoord Buffer

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer );
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer






	//glVertexPointer( 3, GL_FLOAT, 0, vert );		// Set The Vertex Pointer To The Vertex Buffer


    glDrawArrays( GL_TRIANGLES, 0, 99*99*6 );


    glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );

/*
	glBegin(GL_TRIANGLES);

	for (int i =0; i< 99*99*6; i++) {
	    glNormal3f( norms[i].X, norms[i].Y, norms[i].Z );
        glVertex3f( vert[i].X, vert[i].Y, vert[i].Z);

	}
    glEnd();
*/











}
