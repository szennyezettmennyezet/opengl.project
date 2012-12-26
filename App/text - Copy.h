#ifndef __TEXT__
#define __TEXT__


#include <windows.h>
#include <gl/gl.h>
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <iostream>
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\glu.h>			// Header File For The GLu32 Library


class x3DText {
        GLYPHMETRICSFLOAT gmf[256];	// Storage For Information About Our Outline Font Characters
        GLuint	base;				// Base Display List For The Font Set
        HDC hDC;
        HFONT	font;

        GLubyte letters[26][13];
        GLuint fontOffset;
        GLubyte space[13];
    public:
        x3DText() {
GLubyte spac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        for (int i = 0; i < 13; i++) {
            space[i] = spac[i];
        }


        GLubyte let[26][13] =  {
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
    {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
    {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
    {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff},
    };

for (int j =0; j<26; j++) {
    for (int i = 0; i < 13; i++) {
            letters[j][i] = let[j][i];
    }
}




   makeRasterFont();



            hDC = wglGetCurrentDC();

            										// Windows Font ID
            base = glGenLists(256);								// Storage For 256 Characters
            font = CreateFont(	-12,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Arial");				// Font Name

            SelectObject(hDC, font);							// Selects The Font We Created
                        wglUseFontOutlines(	hDC,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						base,							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						gmf);	// Address Of Buffer To Recieve Data
        }

        GLvoid KillFont(GLvoid) {
            glDeleteLists(base, 256);								// Delete All 256 Characters
        }

        GLvoid glPrint(const char *fmt, ...) {
            float		length=0;								// Used To Find The Length Of The Text
            char		text[256];								// Holds Our String
            va_list		ap;										// Pointer To List Of Arguments

            if (fmt == NULL)									// If There's No Text
                return;											// Do Nothing

            va_start(ap, fmt);									// Parses The String For Variables
            vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
            va_end(ap);											// Results Are Stored In Text

            for (unsigned int loop=0;loop<(strlen(text));loop++) {
                length+=gmf[text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width
            }

            glTranslatef(-length/2,0.0f,0.0f);					// Center Our Text On The Screen

glPushAttrib(GL_POLYGON_BIT);
            glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
                glListBase(base);									// Sets The Base Character to 0
                glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
            glPopAttrib();
            glPopAttrib();									// Pops The Display List Bits




        }







    void makeRasterFont(void) {
        GLuint i, j;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        fontOffset = glGenLists (128);
        for (i = 0,j = 'A'; i < 26; i++,j++) {
            glNewList(fontOffset + j, GL_COMPILE);
            glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
            glEndList();
        }
        glNewList(fontOffset + ' ', GL_COMPILE);
        glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
        glEndList();
    }

    void printRasterString(char *s) {
        glPushAttrib (GL_LIST_BIT);
        glListBase(fontOffset);
        glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
        glPopAttrib ();
    }

    void printRasterGLUTString(void* ft, const char* string) {

        char* p = (char*) string;
        while (*p != '\0')
            glutBitmapCharacter(ft, *p++);
    }

    void display(void) {
        glLoadIdentity();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glRasterPos2i(20, 70);
   //printString("PRIKLAD OPENGL");
   //printGLUTString(GLUT_BITMAP_TIMES_ROMAN_24, "Tento vykresleny text ma");


        printRasterGLUTString(GLUT_BITMAP_TIMES_ROMAN_10, "Tento vykresleny text ma");


        glColor3f(1.0, 0.0, 1.0);
        glRasterPos2i(20, 30);
   //printString("BITMAPOVE FONTY");
        char dlzka[100];


        sprintf(dlzka, "%i pixelov", glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char*) "Tento vykresleny text ma"));
   //printGLUTString(GLUT_BITMAP_TIMES_ROMAN_24, dlzka);


        printRasterGLUTString(GLUT_BITMAP_TIMES_ROMAN_10, dlzka);

    }




};


#endif
