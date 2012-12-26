#ifndef __X3DMODEL__
#define __X3DMODEL__


#include <vector>
#include "drawable.h"

        typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
        typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
        typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
        typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);



struct xVector {
    GLfloat X,Y,Z;
};




struct xVertexBuffer {
    GLuint buffer;
    GLenum mode;
};




class x3DModel : public xDrawable {
    protected:

// VBO Extension Function Pointers
        PFNGLGENBUFFERSARBPROC glGenBuffersARB;					// VBO Name Generation Procedure
        PFNGLBINDBUFFERARBPROC glBindBufferARB;					// VBO Bind Procedure
        PFNGLBUFFERDATAARBPROC glBufferDataARB;					// VBO Data Loading Procedure
        PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;				// VBO Deletion Procedure


        xVector* norms;
        xVector* vert;





        GLuint displayList;

        GLuint buffer;
        GLuint normalArray;



        xVector* vertices;
        GLuint* vertexIndices;






        std::vector<xVector> vertices;
        std::vector<xVector> normals;
        std::vector<xVector> indices;




        unsigned int triangles;


    public:
        x3DModel();
        x3DModel(char* filename);
        void draw();
};



#endif
