#ifndef __TERRAIN__
#define __TERRAIN__


#include "GL/gl.h"

#include "3dmodel.h"
#include "bitmap.h"
#include "objectdata.h"


class xTerrain : public x3DModel {
  public:

    xTerrain(char* fileName, GLfloat width, GLfloat height) {
        cout << "Loaading terrainb" << endl;
        xVector vec;
        vec.X = -width/2;
        vec.Y = -height/2;
        vec.Z = 0;
        frames.at(activeFrame)->vertices.push_back(vec);

        vec.X = width/2;
        vec.Y = -height/2;
        vec.Z = 0;
        frames.at(activeFrame)->vertices.push_back(vec);

        vec.X = -width/2;
        vec.Y = height/2;
        vec.Z = 0;
        frames.at(activeFrame)->vertices.push_back(vec);

        vec.X = width/2;
        vec.Y = -height/2;
        vec.Z = 0;
        frames.at(activeFrame)->vertices.push_back(vec);

        vec.X = width/2;
        vec.Y = height/2;
        vec.Z = 0;
        frames.at(activeFrame)->vertices.push_back(vec);

        vec.X = -width/2;
        vec.Y = height/2;
        vec.Z = 0;
        frames.at(activeFrame)->vertices.push_back(vec);


        vec.X =0; vec.Y=0;vec.Z = 1.0;
        for (int i =0; i<6;i++) frames.at(activeFrame)->normals.push_back(vec);

        frames.at(activeFrame)->hasTexture = false;





        generateBuffers();
        //loadTexture(fileName);


    }
    GLfloat getHeight(GLfloat x, GLfloat y);
};


#endif
