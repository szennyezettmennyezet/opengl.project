#ifndef __X3DMODEL__
#define __X3DMODEL__


#include <vector>
#include "drawable.h"
#include "objectdata.h"

typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);


struct xVertexBuffer {
    GLuint buffer;
    GLenum mode;
};


struct VBOData {
    bool hasTexture;
    GLuint vertexArray;
    GLuint normalArray;
    GLuint textureCoordArray ;

    GLuint indexArray;

    std::vector<xVector> vertices;
    std::vector<xVector> normals;
    std::vector<xUVCoord> texturecoords;

    std::vector<unsigned int> indices;


    GLuint texture;

    GLuint displayList;

};


class x3DModel {
    protected:
        float scaleX,scaleY,scaleZ;

        PFNGLGENBUFFERSARBPROC glGenBuffersARB;					// VBO Name Generation Procedure
        PFNGLBINDBUFFERARBPROC glBindBufferARB;					// VBO Bind Procedure
        PFNGLBUFFERDATAARBPROC glBufferDataARB;					// VBO Data Loading Procedure
        PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;				// VBO Deletion Procedure

        unsigned int activeFrame;
        vector<VBOData*> frames;

        void generateBuffers();
        void drawDataVBO();
        void drawDataImmediate();
        void drawDataDisplayList();
    protected:
        x3DModel() {}
    public:
        void drawData(unsigned int mode);
};



#endif
