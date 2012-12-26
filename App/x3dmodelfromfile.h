#ifndef __X3DMODELFROMFILE__
#define __X3DMODELFROMFILE__


#include <vector>

#include "3dmodel.h"

#include "objectdata.h"

#include "Bitmap.h"


typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);




class x3DModelFromFile : public x3DModel {
    protected:
        Bitmap *textureImage;
        void loadModel(string, bool hasTex);
        void loadTexture(char*);
    protected:
        x3DModelFromFile() {}
    public:
        x3DModelFromFile(char* filename);
};

#endif
