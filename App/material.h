#ifndef __XMATERIAL__
#define __XMATERIAL__

#include "GL/gl.h"

class xMaterial {
    protected:
        GLfloat* specular;
        GLfloat* shininess;

    public:
        xMaterial();
        xMaterial(const GLfloat* specular, const GLfloat* shininess);

        void set();
};


#endif
