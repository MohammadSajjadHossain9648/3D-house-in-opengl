#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <gl/glut.h>

#define pi (2*acos(0.0))
#define sqrt2 (sqrt(2))

typedef struct point
{
    double x,y,z;
} Point;

float windowAngle = 0;
bool drawAxes = true;
bool drawgrid = true;
bool road = true;
bool transition = true;
bool flag;
bool ray = true;

static GLfloat spin = 0.0;
float angle = 30.0f;
float doorOpen = 0;
float doorClose= 0;
float upWindow = 0;
float upDoor = 0;
//float spin = -90.0f;
float tyreAngle = 85;
float quadAngle = 0;
float boxAngleC = 0;
float boxAngleAC = 0;
float boxScaleFactorX = 1;
float boxScaleFactorY = 1;
float boxScaleFactorZ = 1;
float tyreScaleFactor = 1;
float tinyBoxAngle = 0;
float movecar = 0;
float background = 0;
float i=0.00012;

Point pos, u, r, l;

//void gridX()
//{
//    if(drawgrid)
//    {
//        glBegin(GL_LINES);
//        {
//            glColor3f(1.0, 0, 0);
//
//            glVertex3f( 485,0,0);
//            glVertex3f(-485,0,0);
//
//        }
//        glEnd();
//    }
//}
//void gridY()
//{
//    if(drawgrid)
//    {
//        glBegin(GL_LINES);
//        {
//            glColor3f(0, 1.0, 0);
//
//            glVertex3f(0,-485,0);
//            glVertex3f(0, 485,0);
//
//        }
//        glEnd();
//    }
//}
void displayAxes()
{
    if(drawAxes)
    {
        glBegin(GL_LINES);
        {
            glColor3f(1.0, 0, 0);

            glVertex3f( 500,0,0); // a point on pos x axis
            glVertex3f(-500,0,0); // a point on neg x axis

            glColor3f(0, 1.0, 0);

            glVertex3f(0,-500,0); // a point on pos y axis
            glVertex3f(0, 500,0); // a point on neg y axis

            glColor3f(0, 0, 1.0);

            glVertex3f(0,0, 500);  // a point on pos z axis
            glVertex3f(0,0,-500);   // a point on neg z axis
        }
        glEnd();
    }
}

//void displaygrid()
//{
//    if(drawgrid)
//    {
//        glPushMatrix();
//        for(int i=0; i<=9; i++)
//        {
//            gridY();
//            glTranslatef(i+50, 0, 0);
//        }
//        glPopMatrix();
//
//        glPushMatrix();
//        for(int i=0; i<=9; i++)
//        {
//            gridY();
//            glTranslatef(-(i+50), 0, 0);
//        }
//        glPopMatrix();
//
//        glPushMatrix();
//        for(int i=0; i<=9; i++)
//        {
//            gridX();
//            glTranslatef(0, (i+50), 0);
//
//        }
//        glPopMatrix();
//
//        glPushMatrix();
//        for(int i=0; i<=9; i++)
//        {
//            gridX();
//            glTranslatef(0, -(i+50), 0);
//
//        }
//        glPopMatrix();
//
//    }
//
//}

//    float halfQuadWidth = qWidth / 2, halfQuadLength = qLength / 2;
//
//    glBegin(GL_QUADS);
//    {
//
//        /** Gradient Fill Quad **/
//
//
//        glColor3f(1, 0, 0);
//
//        glVertex3f(halfQuadWidth, 0, halfQuadLength);
//        glVertex3f(-halfQuadWidth, 0, halfQuadLength);
//
//        glColor3f(0, 1, 0);
//
//        glVertex3f(-halfQuadWidth +70, 0, -halfQuadLength +70);
//        glVertex3f(halfQuadWidth+70, 0, -halfQuadLength+70);
//
//    }
//    glEnd();
//}

void drawTyre(float tRadius, float tWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);

    {
        glVertex3f(halfTyreWidth, 0, tRadius);
        glVertex3f(halfTyreWidth, 0, -tRadius);
        glVertex3f(-halfTyreWidth, 0, -tRadius);
        glVertex3f(-halfTyreWidth, 0,tRadius);
    }
    glEnd();

    glVertex3f(halfTyreWidth, 0,tRadius);
    glVertex3f(-halfTyreWidth,0, tRadius);
    glVertex3f(-halfTyreWidth,0, -tRadius);
    glVertex3f(halfTyreWidth,0, -tRadius);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, 0, tRadius);
        glVertex3f(halfTyreWidth, 0, -tRadius);
        glVertex3f(-halfTyreWidth, 0, -tRadius);
        glVertex3f(-halfTyreWidth, 0, tRadius);
    }
    glEnd();


    for(int i=0; i<tyreSlices; i++)
    {
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tRadius, 0);

        glBegin(GL_QUADS);
        {
            if(i%2==0)  ///for two color use
            {
                glColor3f(1, 1, 0);
                glVertex3f(halfTyreWidth, 0, halfSliceWidth);
                glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
                glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
                glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }
            else
            {
                glColor3f(0, 0, 1);
                glVertex3f(halfTyreWidth, 0, halfSliceWidth);
                glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
                glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
                glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }
        }
        glEnd();
        glPopMatrix();
    }
}



void floorBox(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;


    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 1);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);


        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);


        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}


void bodyBox(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl /2, halfbw = bw /2, halfbh = bh / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.698, 0.133, 0.133);
        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);

        glColor3f(0.698, 0.133, 0.133);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);  ///Gradiant color

        glColor3f(0.698, 0.133, 0.133);
        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);


        glColor3f(0.698, 0.133, 0.133);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glColor3f(0.698, 0.133, 0.133);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);

        glColor3f(0.698, 0.133, 0.133);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glColor3f(0.698, 0.133, 0.133);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}
void roofBox(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;


    glBegin(GL_QUADS);
    {
        glColor3f(0.196, 0.804, 0.196);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);


        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);


        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);


        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}


void rooftopBox(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;


    glBegin(GL_QUADS);
    {
        glColor3f(0.855, 0.647, 0.125);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);


        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);




        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);


        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}

void sideBox1(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;


    glBegin(GL_QUADS);
    {
        glColor3f(0.502, 0.502, 0.502);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);


        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);




        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);


        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);


        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}


void sideBox2(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;


    glBegin(GL_QUADS);
    {
        glColor3f(0.275, 0.510, 0.706);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);

        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);


        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}

void sideBox3(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0.855, 0.647, 0.125);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);


        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);


        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);

        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}

void frontDoorLeft(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(	0.000, 0.749, 1.000);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);

        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);




        glVertex3f(halfbl, halfbw, bw);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}
void frontDoorRight(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.000, 0.749, 1.000);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);

        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);




        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);


        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}

void backDoorLeft(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.000, 0.749, 1.000);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);

        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);



        glVertex3f(halfbl, halfbw, bw);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);


        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}
void backDoorRight(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.000, 0.749, 1.000);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);

        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);




        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);



        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}


void rotatingWindowBox(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1.000, 1.000, 0.000);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);

        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);


        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}
void slidingWindowBox(float bl, float bw, float bh) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfbl = bl / 2, halfbw = bw / 2, halfbh = bh / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1.000, 1.000, 0.000);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);

        glVertex3f(halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);


        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, halfbw, halfbh);
        glVertex3f(-halfbl, -halfbw, halfbh);
        glVertex3f(halfbl, -halfbw, halfbh);

        glVertex3f(halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, halfbw, -halfbh);
        glVertex3f(-halfbl, -halfbw, -halfbh);
        glVertex3f(halfbl, -halfbw, -halfbh);
    }
    glEnd();
}





void displayScene()
{
    //Primitive Object dimensions
    float quadLength = 100, quadWidth = 60;
    float floorBoxLength = 300, floorBoxWidth = 130, floorBoxHeight = 40;
    float bodyBoxLength = 280, bodyBoxWidth = 110, bodyBoxHeight = 250;
    float roofBoxLength = 300, roofBoxWidth = 130, roofBoxHeight = 12;
    float rooftopLength = 150, rooftopWidth = 20, rooftopHeight = 100;
    float tyreRadius = 40, tyreWidth = 20;
    float sideBox1Length = 150, sideBox1Width = 150, sideBox1Height = 12;
    float sideBox2Length = 130, sideBox2Width = 120, sideBox2Height = 12;
    float sideBox3Length = 110, sideBox3Width = 100, sideBox3Height = 12;
    float doorBoxLength = 55, doorBoxWidth = 0, doorBoxHeight = 200;
    float windowBoxLength = 2, windowBoxWidth = 60, windowBoxHeight = 80;

    /**** Principal Axes ****/
    displayAxes();

    /*** Scaling house ***/
    glScalef(boxScaleFactorX,1.0, 1.0);
    glScalef(1.0, boxScaleFactorY, 1.0);
    glScalef(1.0, 1.0, boxScaleFactorZ);
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);

    glRotatef(boxAngleC, 0, 0, 1);
    glRotatef(boxAngleAC, 0, 0, 1);
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);


    /**** HOUSE BODY ****/
    glPushMatrix();
    glTranslatef(0, 0, 15);
    //glTranslatef(0, 0, (BodyBoxHeight/2));
    floorBox(floorBoxLength, floorBoxWidth, floorBoxHeight);
    glTranslatef(0, 0, (bodyBoxHeight/2) + (floorBoxHeight/2));
    bodyBox(bodyBoxLength, bodyBoxWidth, bodyBoxHeight);
    glTranslatef(0, 0, (bodyBoxHeight/2.5) + (floorBoxHeight/2.5) + (roofBoxHeight/3));
    roofBox(roofBoxLength, roofBoxWidth, roofBoxHeight);
    glTranslatef(0, 0, (bodyBoxHeight/5.5) + (floorBoxHeight/5.5) + (roofBoxHeight/5) + (rooftopHeight/5));
    rooftopBox(rooftopLength, rooftopWidth, rooftopHeight);
    glTranslatef(0,50, 0);
    glRotatef(0, 90, 0, 00);
    drawTyre(tyreRadius, tyreWidth);
    glPopMatrix();

    ///* SIDE STAIR */
    glPushMatrix();
    glTranslatef(0,(floorBoxWidth/2), 0);
    sideBox1(sideBox1Length, sideBox1Width, sideBox1Height);
    glTranslatef(0,0, ((sideBox1Height/2)+(sideBox2Height/2)));
    sideBox2(sideBox2Length, sideBox2Width, sideBox2Height);
    glTranslatef(0,0, ((sideBox1Height/3)+(sideBox2Height/3)+(sideBox3Height/3)));
    sideBox3(sideBox3Length, sideBox3Width, sideBox3Height);
    glPopMatrix();

    //front door left
    glPushMatrix();
    glTranslatef(25+ doorOpen, 60 , 100 );
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    frontDoorLeft(doorBoxLength, doorBoxWidth, doorBoxHeight); // large box
    glPopMatrix();

    //front door right
    glPushMatrix();
    glTranslatef( -25 - doorOpen + doorClose, 60 , 100 );
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    frontDoorRight(doorBoxLength, doorBoxWidth, doorBoxHeight); // large box
    glPopMatrix();

    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 1);

        glVertex3f(-55, 60 , 200 );
        glVertex3f(55, 60 , 200 );
        glVertex3f(55, 60 , 210);
        glVertex3f(-55, 60 , 210);
    }
    glEnd();

    //back door left
    glPushMatrix();
    glTranslatef(25, -60 , 100 );
    glRotatef(upDoor, 0, 0, 1);
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    backDoorLeft(doorBoxLength, doorBoxWidth, doorBoxHeight); // large box
    glPopMatrix();

    //back door right
    glPushMatrix();
    glTranslatef( -25, -60 , 100 );
    glRotatef(-upDoor, 0, 0, 1);
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    backDoorRight(doorBoxLength, doorBoxWidth, doorBoxHeight); // large box
    glPopMatrix();

    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 1);
        //glTranslatef( -25, 60 , 200 );
        glVertex3f(-55, -60 , 200 );
        glVertex3f(55, -60 , 200 );
        glVertex3f(55, -60 , 210);
        glVertex3f(-55, -60 , 210);
    }
    glEnd();


    //sliding window
    glPushMatrix();
    glTranslatef(-140 , 0 , 150 + upWindow );
    slidingWindowBox(windowBoxLength, windowBoxWidth,windowBoxHeight ); // large box
    glPopMatrix();

    //rotating window
    glPushMatrix();
    glTranslatef(140 , 0 , 150);
    glRotatef(-windowAngle, 0, 1, 0);
    rotatingWindowBox(windowBoxLength, windowBoxWidth,windowBoxHeight ); // large box
    glPopMatrix();

    //tyre
    glPushMatrix();
    //glTranslatef(0, 30, 350); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 0, 0, 1); // check what happens to the tyre after exchanging the order of translation and roation
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    drawTyre(tyreRadius, tyreWidth);
    glPopMatrix();



    /*** Auto Transition ***/
//    if(transitioncount >= 1)
//    {
//        if(transition)
//        {
//            if(background <= 0)
//            {
//                flag = true;
//            }
//            else if(background >= 1)
//            {
//                flag =  false;
//            }
//            if(flag == true)
//            {
//                background += i;
//            }
//            else if(flag == false)
//            {
//                background -= i;
//            }
//        }
//    }
}


void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background, background, background,0);	//sets background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

    glutSwapBuffers();
}


Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}



void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {
    case '1':
    {
        Point l1 = func(l, r, -1);
        r = func(r, l, 1);
        l = l1;
        break;
    }
    case '2':
    {
        Point l1 = func(l, r, 1);
        r = func(r, l, -1);
        l = l1;
        break;
    }

    case '3':
    {
        Point u1 = func(u, l, -1);
        l = func(l, u, 1);
        u = u1;
        break;
    }
    case '4':
    {
        Point u1 = func(u, l, 1);
        l = func(l, u, -1);
        u = u1;
        break;
    }
    case '5':
    {
        Point r1 = func(r, u, -1);
        u = func(u, r, 1);
        r = r1;
        break;
    }
    case '6':
    {
        Point r1 = func(r, u, 1);
        u = func(u, r, -1);
        r = r1;
        break;
    }
    case '7':
    {
        tyreScaleFactor += 0.2;
        break;
    }
    case '8':
    {
        tyreScaleFactor -= 0.2;
        break;
    }
    case '9':
    {
        if(windowAngle == 45)
        {
            break;

        }
        else
        {
            windowAngle +=5;
        }
        break;

    }
    case '0':
    {
        if(windowAngle == 0)
        {
            break;
        }
        else
        {
            windowAngle -= 5;
        }
        break;

    }

    case 'l':
    {
        boxAngleC -= 5;
        break;
    }

    case 'L':
    {
        boxAngleC -= 5;
        break;
    }

    case 'r':
    {
        boxAngleC += 5;
        break;
    }

    case 'R':
    {
        boxAngleC += 5;
        break;
    }

    case 'U':
    {
        if(boxScaleFactorX<= 1.120000 && boxScaleFactorY<= 1.120000 && boxScaleFactorZ<= 1.120000)
        {
            boxScaleFactorX +=0.015;
            boxScaleFactorY +=0.015;
            boxScaleFactorZ +=0.015;
        }
        break;
    }
    case 'u':
    {
        if(boxScaleFactorX<= 1.120000 && boxScaleFactorY<= 1.120000 && boxScaleFactorZ<= 1.120000)
        {
            boxScaleFactorX +=0.015;
            boxScaleFactorY +=0.015;
            boxScaleFactorZ +=0.015;
        }
        break;
    }
    case 'D':
    {
        if(boxScaleFactorX>= 0.010001 && boxScaleFactorY>= 0.010001 && boxScaleFactorZ>= 0.010001)
        {
            boxScaleFactorX -=0.015;
            boxScaleFactorY -=0.015;
            boxScaleFactorZ -=0.015;
        }
        break;
    }
    case 'd':
    {
        if(boxScaleFactorX>= 0.010001 && boxScaleFactorY>= 0.010001 && boxScaleFactorZ>= 0.010001)
        {
            boxScaleFactorX -=0.015;
            boxScaleFactorY -=0.015;
            boxScaleFactorZ -=0.015;
        }
        break;
    }

    case 'q':
    {
        if(upWindow == 30)
        {
            break;

        }
        else
        {
            upWindow +=30;
        }
        break;

    }
    case 'w':
    {
        if(upWindow == 0)
        {
            break;
        }
        else
        {
            upWindow -= 30;
        }
        break;

    }

    case 'o':
    {
        if(upDoor == 140)
        {
            break;

        }
        else
        {
            upDoor += 140;
        }
        break;

    }
    case 'p':
    {
        if(upDoor == 0)
        {
            break;
        }
        else
        {
            upDoor -= 140;
        }
        break;

    }

    default:
        break;
    }
}

Point cameraView(Point vect, Point perp, int dir)
{
    double s = dir * 3.0;

    Point point;
    point.x =  vect.x + s * perp.x;  /// pos->x + (-1/1) * (l/r/u)->x
    point.y =  vect.y + s * perp.y; /// pos->y + (-1/1) * (l/r/u)->y
    point.z =  vect.z + s * perp.z; /// pos->y + (-1/1) * (l/r/u)->z
    return point;
}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN: // down arrow
    {
        point pos1 = cameraView(pos, l, -1);
        pos = pos1;
        break;
    }

    case GLUT_KEY_UP:   // up arrow
    {
        point pos1 = cameraView(pos, l, 1);
        pos = pos1;
        break;
    }

    case GLUT_KEY_RIGHT:    // right arrow
    {
        point pos1 = cameraView(pos, r, 1);
        pos = pos1;
        break;
    }

    case GLUT_KEY_LEFT:     // left arrow
    {
        point pos1 = cameraView(pos, r, -1);
        pos = pos1;
        break;
    }

    case GLUT_KEY_PAGE_UP:
    {
        point pos1 = cameraView(pos, u, 1);
        pos = pos1;
        break;
        break;
    }

    case GLUT_KEY_PAGE_DOWN:
    {
        point pos1 = cameraView(pos, u, -1);
        pos = pos1;
        break;
        break;
    }

    case GLUT_KEY_HOME:
    {
        if(doorOpen == 25)
        {
            break;

        }
        else
        {
            doorOpen +=5;
            doorClose -= 5;
        }
        break;

    }

    case GLUT_KEY_END:
    {
        if(doorClose == 0)
        {
            break;
        }
        else
        {
            doorClose +=5;
            doorOpen -= 5;
        }
        break;
    }

    default:
        break;
    }
}

void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
        {
            printf("Mouse Left Button Clicked\n");
        }
        else if(state == GLUT_UP)
        {
            printf("Mouse Left Button Released\n");
        }
        break;
    default:
        break;
    }
}


void animate()
{
    tinyBoxAngle += 0.05;
    glutPostRedisplay();
}

void init()
{
    glClearColor(background, background, background,0); 	//sets background color

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

    // to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    pos = {300, 300, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}


//void slideMenu(int id)
//{
//    if(id == 1)
//    {
//        background = 1;
//    }
//    else if(id == 2)
//    {
//        background = 0;
//    }
//}
//void rotateMenu(int id)
//{
//    if(id == 3)
//    {
//
//    }
//    else if(id == 4)
//    {
//        background = 0;
//    }
//}
//void fanMenu(int id)
//{
//    if(id == 5)
//    {
//        background = 1;
//    }
//    else if(id == 6)
//    {
//        background = 0;
//    }
//    else if(id == 7)
//    {
//        background = 0;
//    }
//}
//
//void mainMenu(int id)
//{
//    if(id == 8)
//    {
//        if( boxScaleFactorX < 1 || boxScaleFactorX > 1 || boxScaleFactorY < 1 || boxScaleFactorY > 1 || boxScaleFactorZ < 1 || boxScaleFactorZ > 1)
//        {
//            boxScaleFactorX = 1;
//            boxScaleFactorY = 1;
//            boxScaleFactorZ = 1;
//        }
//    }
//}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("3D House OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);


//    int slidingWindow = glutCreateMenu(slideMenu);
//    glutAddMenuEntry("Sliding Up", 1);
//    glutAddMenuEntry("Sliding Down", 2);
//    int rotatingDoor = glutCreateMenu(rotateMenu);
//    glutAddMenuEntry("Open", 3);
//    glutAddMenuEntry("Close", 4);
//    int exhaustFan = glutCreateMenu(fanMenu);
//    glutAddMenuEntry("Clockwise", 5);
//    glutAddMenuEntry("Anti-clockwise", 6);
//    glutAddMenuEntry("Off", 7);
//
//
//    glutCreateMenu(mainMenu);
//    glutAddSubMenu("Sliding Window", slidingWindow);
//    glutAddSubMenu("Rotating Door", rotatingDoor);
//    glutAddSubMenu("Exhausting Fan", exhaustFan);
//    glutAddMenuEntry("Return Orginal SIze", 8);
//
//    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();		//The main loop of OpenGL, this function never returns

    return 0;
}
