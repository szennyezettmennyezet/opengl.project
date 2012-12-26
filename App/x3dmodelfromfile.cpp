#define GL_GLEXT_PROTOTYPES

#include "stdafx.h"

#include "x3dmodelfromfile.h"
//#include "math.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "glext.h"
#include "glut.h"
#include <exception>
#include <stdexcept>

#include <cmath>
using namespace std;


void IntToString(int i, string & s) {
    s = "";
    if (i == 0) {
        s = "0";
        return;
    }
    if (i < 0) {
        s += '-';
        i = -i;
    }
    int count = log10(i);
    while (count >= 0) {
        s += ('0' + i/pow(10.0, count));
        i -= static_cast<int>(i/pow(10.0,count)) * static_cast<int>(pow(10.0,count));
        count--;
    }
}



void x3DModelFromFile::loadModel(string fileName, bool hasTex) {


    if (hasTex) frames.at(activeFrame)->hasTexture = true;
    else frames.at(activeFrame)->hasTexture = false;

    ifstream modelFile(fileName.c_str(), ios_base::binary);
    int i = 0;
    char c;

    cout << "Error opening file: " << fileName << endl;

    std::vector<xVector> vert;
    std::vector<xVector> norm;
    std::vector<xUVCoord> text;

    std::vector<unsigned int> ind;

    if (modelFile.fail()) {
            cout << "Error opening file: " << fileName << endl;
    }


    unsigned int numOfFaces = 0;



    modelFile.read(&c,1);

    while (!modelFile.eof()) {


        switch (c) {
            case 'V': {
                //cout << "v";
                xVector v;
                modelFile.read((char*)&v.X, sizeof(GLfloat));
                modelFile.read((char*)&v.Y, sizeof(GLfloat));
                modelFile.read((char*)&v.Z, sizeof(GLfloat));

                //cout << v.X << " " << v.Y << " " << v.Z << endl;

                vert.push_back(v);
                } break;
            case 'N': {
                //cout << "n";
                xVector v;
                modelFile.read((char*)&v.X, sizeof(GLfloat));
                modelFile.read((char*)&v.Y, sizeof(GLfloat));
                modelFile.read((char*)&v.Z, sizeof(GLfloat));
                norm.push_back(v);
                } break;
            case 'T': {
                //cout << "t";
                xUVCoord tex;
                modelFile.read((char*)&tex.u, sizeof(GLfloat));
                modelFile.read((char*)&tex.v, sizeof(GLfloat));
                text.push_back(tex);
                } break;
            case 'F': {


                /*cout << "Vertex count: " << vert.size() << endl;
                cout << "Normal count: " << norm.size() << endl;*/

                //cout << "face ";

                numOfFaces++;

                for (int k=0; k<3; k++) {

                    modelFile.read((char*)&i, sizeof(GLuint));

                    //cout << (i-1) << " ";
                    ind.push_back(i-1);

                    try {
                        frames.at(activeFrame)->vertices.push_back(  vert.at(i-1)      );
                    } catch (std::out_of_range outOfRange) {
                        cout << "Err: vertex.  Index: " << (i-1) << ", num of vertices: " << vert.size() << endl;
                    }

                    modelFile.read((char*)&i, sizeof(GLuint));

                    if (frames.at(activeFrame)->hasTexture) {
                        try {
                            frames.at(activeFrame)->texturecoords.push_back(  text.at(i-1 )      );
                        } catch (std::out_of_range outOfRange) {
                            cout << "Err: texture. Index: " << i << ", num of textures: " << text.size()  << endl;
                            //return;
                        }
                    }


                    modelFile.read((char*)&i, sizeof(GLuint));

                    try {
                        frames.at(activeFrame)->normals.push_back(  norm.at(i-1)      );
                    } catch (std::out_of_range outOfRange) {
                        cout << "Err: normal.  Index: " << (i-1) << ", num of normals: " << norm.size()  << endl;
                        //return;
                    }
                }

                //cout << endl;



            } break;

            default: {
                //cout << "u";
            }
        }

        modelFile.read(&c,1);
        //cout << "      - OK" << endl;
    }



    if (modelFile.eof()) {
       // cout << endl << "VEGE" <<endl;
    }

    cout << "Loaded " << frames.at(activeFrame)->vertices.size() << " vertices"<<endl;
    cout << "Loaded " << frames.at(activeFrame)->normals.size() << " vertices"<<endl;
    cout << "Loaded " << numOfFaces << " faces"<<endl;


    modelFile.close();


}

void x3DModelFromFile::loadTexture(char* fileName) {
    string fn = fileName;
    string dirName = "objects/"+fn + "/";
    string textureFilename = dirName + fileName + ".bmp";
    textureImage = new Bitmap(textureFilename.c_str());
    glGenTextures(1, &frames.at(activeFrame)->texture);
    glBindTexture(GL_TEXTURE_2D, frames.at(activeFrame)->texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage->width, textureImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage->data);
}


x3DModelFromFile::x3DModelFromFile(char* fileName) {
    cout << "Loading "<< fileName << endl;



    string fn = fileName;
    string dirName = "objects/"+fn + "/";

    string descriptionFilename = dirName + fileName + ".txt";
    string objectFilename = dirName + fileName + ".bin";
    string textureFilename = dirName + fileName + ".bmp";

    ifstream infoFile(descriptionFilename.c_str());
    infoFile >> scaleX;
    infoFile >> scaleY;
    infoFile >> scaleZ;
    unsigned char hasTex;
    infoFile >> hasTex;

    unsigned char animated;
    infoFile >> animated;



    if (animated!='0') {
        activeFrame = 0;
        unsigned int frameCount;
        infoFile >> frameCount;

        for (activeFrame =0; activeFrame < frameCount; activeFrame++) {
            frames.push_back(new VBOData());
            string fn = fileName;

            string fileNum;
            IntToString(activeFrame+1,fileNum);


            string fname = "objects/"+fn + "/anim/frame"+fileNum+".bin";
            cout << fname << endl;
            loadModel(fname, hasTex);
            generateBuffers();
                if (frames.at(activeFrame)->hasTexture) {
        loadTexture(fileName);
    }

        }

        activeFrame = 0;

    } else {
        activeFrame = 0;
        frames.push_back(new VBOData());

        string fn = fileName;
        string dirName = "objects/"+fn + "/";
        string filename = dirName + fileName + ".bin";

        loadModel(filename, hasTex);
        generateBuffers();
            if (frames.at(activeFrame)->hasTexture) {
        loadTexture(fileName);
    }
    }













    cout << "Finished model" << endl << "------------------------------------" << endl;
}
