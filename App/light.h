#include "GL/gl.h"


class xLight {
    GLenum number;



    GLfloat* position;



    GLfloat* diffuse;
    //GLfloat*



    public:
        xLight(GLenum number);
        void enable();
        void disable();

        void setPosition(GLfloat X, GLfloat Y, GLfloat Z, GLfloat W );

        void setDiffuse( GLfloat* color );
        void setSpecular( GLfloat* color );

};
