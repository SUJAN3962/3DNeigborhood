#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>
#include<stdio.h>
#include<dos.h>
#define font_style ((void*)0x0005)

GLubyte r=0,g=0,b=0;
int slide=0;int flag=1;
int doorOpen=1,flagCori=0,flagBed1=0,flagBed2=0,flagKitchen=0,flagToil=0; float fanAngle=0.0;
void *font1;
GLfloat sun_spin=0,sun_x=0,sun_y=0;
float mouse_x,mouse_y;
float leglen=0.3,legthick=0.02;
float angle=0.0,angle1=0.0;
float lx=0.0f,lz=-1.0f,ly=0.0f;
float x=0.0f,z=5.0f;
GLfloat rotx=0,roty=0.5,rotz=3,camx=0,camy=0,camz=0/*,angle=0*/;
int curX,curY;

GLfloat ax=0,bx=0,cx=0,dx=0,str=500.0,mn=500.0;
GLfloat sr=0.0,sg=0.749,sb=1.0;
GLfloat spin = 0.0;

int nightMode=0;
void nightmode();
void daymode();

void mytimer(int n)
{
    if(flag==1)
    {
        fanAngle+=15;
        if(fanAngle>360.0)
                fanAngle=0;
        glutTimerFunc(10,mytimer,0);
    }
    glutPostRedisplay();
}
void processSpecialKeys(int key, int xx, int yy)
{

    float fraction = 0.1f;
    if(slide==2 || slide==3 || slide==4 || slide==10 ||slide==15){
        if(z>=2.35 ){
                z=2.35;
        }
        if(z<=0.8){
            z=0.8;
        }
        switch(key){
		case GLUT_KEY_UP :
			z -= 0.1;
			break;
		case GLUT_KEY_DOWN :
			z += 0.1;
			break;

        }
        glutPostRedisplay();
        return;
    }
    switch(key){
            case GLUT_KEY_LEFT :
			x -= cos(angle)*0.1;
			z -=sin(angle)*0.1;
			break;
		case GLUT_KEY_RIGHT :
			x+=cos(angle)*0.1;
			z +=sin(angle)*0.1;
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;

    }
    glutPostRedisplay();
}

void keyboard1(unsigned char c,int x,int y){

    if((c==65 ||c==97)){
        nightMode=1;

    }

    if(c == 69|| c== 101)
    {
        nightMode=0;
    }

    if((c=='F' || c=='f')&&doorOpen==1){
            slide=2;
            x=0;z=1.8;camx=0;camy=0.35;camz=0;
            lx=0.0f,lz=-1.0f,ly=0.0f;
            angle=0.0,angle1=0.0;
            gluLookAt(x,0.4f,z,x+lx,0.5f+ly,z+lz,0.0f,1.0f,0.0f);
            flagCori=1;
    }

    if(c==13){
        if(slide==0)// insert coordinates for house door knob
        {
           slide=5;
            rotx=0;roty=0.5;rotz=2;camx=0;camy=0.35;camz=0;
            glutTimerFunc(200,mytimer,0);
            glutPostRedisplay();

        }
        else if(slide==5)// insert coordinates for house door knob
        {
           slide=1;
            rotx=0;roty=0.5;rotz=2;camx=0;camy=0.35;camz=0;
            glutTimerFunc(200,mytimer,0);
            glutPostRedisplay();

        }
    }
    if(c=='r'&& flag==1){
            flag=0;
            mytimer(5);
    }
    else if(c=='r' && flag==0){
        flag=1;
        mytimer(10);
    }

    if(slide==2){
        if(c=='1'){
            slide=3;
            flagBed1=1;
        }
        else if(c=='2'){
            slide=4;
            flagBed2=1;
        }
        else if(c=='3'){
            slide=10;
            flagKitchen=1;
        }
    }
    else if(slide==3){
        if(c=='1'){
            slide=15;
            flagToil=1;
            printf("%d",slide);
            glutPostRedisplay();
        }

    }
}
void mousemain(int btn,int st,int x,int y)
{
    if(btn==GLUT_RIGHT_BUTTON&&st==GLUT_DOWN)
    {

        switch(slide)
        {
            case 3: {
            slide=2;
            x=0;z=1.8;camx=0;camy=0.35;camz=0;
            lx=0.0f,lz=-1.0f,ly=0.0f;break;
            glutPostRedisplay();

        }break;
            case 4: {
            slide=2;
            x=0;z=1.8;camx=0;camy=0.35;camz=0;
            lx=0.0f,lz=-1.0f,ly=0.0f;break;
            flagCori=0;
            glutPostRedisplay();

        }break;
            case 2: {
           slide=1;
            x=0;z=1.8;camx=0;camy=0.35;camz=0;
            lx=0.0f,lz=-1.0f,ly=0.0f;
            glutTimerFunc(200,mytimer,0);
            glutPostRedisplay();

        }break;
            case 10: {
            slide=2;
            x=0;z=1.8;camx=0;camy=0.35;camz=0;
            lx=0.0f,lz=-1.0f,ly=0.0f;break;
            glutPostRedisplay();

        }break;
        case 15: {
            slide=3;
            x=0;z=1.8;camx=0;camy=0.35;camz=0;
            lx=0.0f,lz=-1.0f,ly=0.0f;break;
            glutPostRedisplay();

        }break;

            case 1: slide=5;break;
            case 5: slide=0;break;
            case 0: exit(0);
        }
    }
}
void door(){
        glPushMatrix();
        glColor3ub(104, 40, 0);
        glTranslatef(0,0,0);
        glScalef(0.5,2,0.05);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(137, 52, 0);
        glTranslatef(0,0.5,0);
        glScalef(0.4,0.7,0.08);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(137, 52, 0);
        glTranslatef(0,-0.5,0);
        glScalef(0.4,0.7,0.08);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(255, 250, 216);
        glTranslatef(0.15,0,0);
        glutSolidSphere(0.05,32,32);
    glPopMatrix();
}
void door2(){
        glPushMatrix();
        glColor3ub(65, 92, 109);
        glTranslatef(0,0,0);
        glScalef(0.5,2,0.05);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(26, 38, 45);
        glTranslatef(0,0.5,0);
        glScalef(0.4,0.7,0.08);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(26, 38, 45);
        glTranslatef(0,-0.5,0);
        glScalef(0.4,0.7,0.08);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(26, 38, 45);
        glTranslatef(0.15,0,0);
        glutSolidSphere(0.05,32,32);
    glPopMatrix();
}
void lamp(){
    glPushMatrix();
        glScalef(0.6,1,0.6);

        /*-----------------Lamp pole-----------*/
        glPushMatrix();
            glColor3f(1,0,0);
            glTranslatef(0,0.4,0);
            glScalef(0.2,0.3,0.4);
            glutSolidSphere(1,32,32);
        glPopMatrix();

        /*-----------------Lamp shade-----------*/
        glPushMatrix();
            GLUquadricObj * qobj = gluNewQuadric();
            glTranslatef(0,1.3,0);
            glScalef(2,2,2);
            glColor3ub(253, 255, 178);
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            gluCylinder(qobj, 0.15, 0.3, 0.35, 50, 50);
            gluDeleteQuadric(qobj);
        glPopMatrix();
    glPopMatrix();
}



void cabinet1(){
    glPushMatrix();
        glScalef(0.6,1,0.6);
            /*----------------Cabinet Top------------------------*/
        glPushMatrix();
            glColor3ub(28, 7, 0);
            glTranslatef(0,0.1,0);
            glScalef(1,0.05,1);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0.25,0);
            /*----------------Cabinet part1 ------------------------*/
            glPushMatrix();
                glColor3ub(58, 15, 0);
                glTranslatef(0,-0.3,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet part2 ------------------------*/
            glPushMatrix();
                glColor3ub(81, 20, 0);
                glTranslatef(0,-0.6,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet part3 ------------------------*/
            glPushMatrix();
                glColor3ub(58, 15, 0);
                glTranslatef(0,-0.9,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet handle3 ------------------------*/
            glPushMatrix();
                glColor3f(1,1,0);
                glTranslatef(0,-0.9,.5);
                glScalef(0.2,0.025,0.05);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet handle1 ------------------------*/
            glPushMatrix();
                glColor3f(1,1,0);
                glTranslatef(0,-0.6,.5);
                glScalef(0.2,0.025,0.05);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet handle2 ------------------------*/
            glPushMatrix();
                glColor3f(1,1,0);
                glTranslatef(0,-0.3,.5);
                glScalef(0.2,0.025,0.05);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
void bed1(){
    glPushMatrix();
        glScalef(0.75,1,0.75);
        /*----------------Mattress------------------------*/
        glPushMatrix();//Mattress
            glColor3ub(221, 221, 221);
            glTranslatef(0,0.1,0);
            glScalef(1,0.15,1.25);
            glutSolidCube(1);
        glPopMatrix();
    /*----------------Bed Cot------------------------*/
        glPushMatrix();//Bed Cot
            glColor3ub(147, 39, 0);
            glScalef(1.1,0.2,1.35);
            glutSolidCube(1);
        glPopMatrix();
    /*----------------Bed headrest------------------------*/
        glPushMatrix();//Bed headrest
            glColor3ub(79, 21, 0);
            glTranslatef(0,-0.1,-0.65);
            glScalef(1,0.4,0.1);
            glTranslatef(0,1,-0.1);
            glRotatef(90,1,0,0);
            glScalef(1.1,0.2,1.35);
            glutSolidCube(1);
        glPopMatrix();
    /*----------------Pillow------------------------*/
        glPushMatrix();//Pillow1
            GLUquadricObj * qobj = gluNewQuadric();
            glTranslatef(0.1,0.2,-0.4);
            glScalef(0.75,0.75,0.75);
           glColor3ub(255, 255, 255);
            glRotatef(90, 0.0f, 0.0f, 1.0f);
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            gluCylinder(qobj, 0.1, 0.1, 0.35, 50, 50);
            gluDeleteQuadric(qobj);
        glPopMatrix();

        glPushMatrix();//Pillow2
            GLUquadricObj * qobj2 = gluNewQuadric();
            glTranslatef(-0.4,0.2,-0.4);
            glScalef(0.75,0.75,0.75);
            glColor3ub(255, 255, 255);
            glRotatef(90, 0.0f, 0.0f, 1.0f);
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            gluCylinder(qobj2, 0.1, 0.1, 0.35, 50, 50);
            gluDeleteQuadric(qobj2);
        glPopMatrix();
    glPopMatrix();
}
void wardrobe(){
    glPushMatrix();
        /*------------Left door----------------*/
        glPushMatrix();
            glScalef(1,1,1);
            glPushMatrix();
                    glColor3ub(209, 177, 131);
                    glTranslatef(0,0,0.025);
                    glScalef(0.3,1.5,0.25);
                    glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();

        /*------------Right door----------------*/
        glPushMatrix();
            glScalef(1,1,1);
            glPushMatrix();
                    glColor3ub(209, 177, 131);
                    glTranslatef(0.305,0,0.025);
                    glScalef(0.3,1.5,0.25);
                    glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();

        /*------------Frame----------------*/
        glPushMatrix();
            glScalef(1,1,1);
            glPushMatrix();
                    glColor3ub(237, 205, 158);
                    glTranslatef(0.15,00,0);
                    glScalef(0.70,1.6,0.26);
                    glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
        /*------------Knob1-----------------*/
        glPushMatrix();
            glScalef(0.05,0.05,0.05);
            glTranslatef(1,1,2.5);
            glColor3ub(135, 135, 135);
            glutSolidSphere(1,32,32);
        glPopMatrix();
        /*------------Knob2-----------------*/
        glPushMatrix();
            glScalef(0.05,0.05,0.05);
            glTranslatef(5,1,2.5);
            glColor3ub(135, 135, 135);
            glutSolidSphere(1,32,32);
        glPopMatrix();
    glPopMatrix();
}
void photoFrame1(){
    /*-------------Frame-------------*/
    glPushMatrix();
            glScalef(1.2,0.75,0.1);
            glPushMatrix();
                    glColor3ub(104, 69, 37);
                    glutSolidCube(1);
            glPopMatrix();
    glPopMatrix();

    /*-------------Picture-------------*/
    glPushMatrix();
            glScalef(1,0.6,0.1);
            glTranslatef(0,0,0.05);
            glPushMatrix();
                    glColor3ub(108, 196, 37);
                    glutSolidCube(1);
            glPopMatrix();
    glPopMatrix();
}
void ac(){
    /*--------------------------AC---------------------------*/
    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(0.647,0.852,0.2495);
        glRotatef(-30,0,0,1);
        glRotatef(330,0,0,1);
        glRotatef(90,0,1,0);
        glRotatef(90,1,0,0);
        glScalef(0.001,0.05,0.5);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(0.43,0.725,0);
        glRotatef(30,0,0,1);
        glScalef(0.001,0.05,0.5);
        glutSolidCube(1);
    glPopMatrix();




    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(0.45,0.8,0);
        glScalef(0.06,0.1,0.5);
        glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(0.43,0.725,0);
        glRotatef(30,0,0,1);
        glScalef(0.001,0.05,0.5);
        glutSolidCube(1);
    glPopMatrix();

   glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(0.46,0.725,0);
        glScalef(0.025,0.04,0.5);
        glutSolidCube(1);
    glPopMatrix();
/*----------------------------AC end-----------------------------*/
}
void photoFrame2(){
    /*-------------Frame-------------*/
    glPushMatrix();
            glScalef(1.2,0.75,0.1);
            glPushMatrix();
                    glColor3ub(104, 69, 37);
                    glutSolidCube(1);
            glPopMatrix();
    glPopMatrix();

    /*-------------Picture-------------*/
    glPushMatrix();
            glScalef(1,0.6,0.1);
            glTranslatef(0,0,0.05);
            glPushMatrix();
                    glColor3ub(216, 108, 207);
                    glutSolidCube(1);
            glPopMatrix();
    glPopMatrix();
}
void fridge(){
    glPushMatrix();
        glScalef(1,1,1);
        /*-----------Fridge------------*/
        glPushMatrix();
                glScalef(1,1,1);
                glPushMatrix();
                        glColor3ub(183, 183, 183);
                        glTranslatef(0,0,0.025);
                        glScalef(0.3,0.9,0.25);
                        glutSolidCube(1);
                glPopMatrix();
        glPopMatrix();

        /*-----------Freezer------------*/
        glPushMatrix();
                glScalef(1,1,1);
                glPushMatrix();
                        glColor3ub(183, 183, 183);
                        glTranslatef(0,0.6525,0.025);
                        glScalef(0.3,0.4,0.25);
                        glutSolidCube(1);
                glPopMatrix();
        glPopMatrix();
        /*-----------Freezer handle------------*/
        glPushMatrix();
                glScalef(1,1,1);
                glPushMatrix();
                        glColor3ub(119, 119, 119);
                        glTranslatef(-0.125,0.6025,0.04);
                        glScalef(0.025,0.2,0.25);
                        glutSolidCube(1);
                glPopMatrix();
        glPopMatrix();

        /*-----------Fridge handle------------*/
        glPushMatrix();
                glScalef(1,1,1);
                glPushMatrix();
                        glColor3ub(119, 119, 119);
                        glTranslatef(-0.125,0.3025,0.04);
                        glScalef(0.025,0.25,0.25);
                        glutSolidCube(1);
                glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
void gasCylinder(){
    glPushMatrix();
        glScalef(1,1,1);
            /*-------------Center cylinder-----------*/
            glPushMatrix();
                    GLUquadricObj * qobj2 = gluNewQuadric();
            //        glTranslatef(-0.4,0.2,-0.4);
                    glScalef(1,1,1);
                    glColor3ub(150, 0, 0);
               //     glRotatef(90, 0.0f, 0.0f, 1.0f);
                    glRotatef(90, 1.0f, 0.0f, 0.0f);
                    gluCylinder(qobj2, 0.1, 0.1, 0.35, 50, 50);
                    gluDeleteQuadric(qobj2);
            glPopMatrix();
            /*-------------Top bottom sphere-----------*/
            glPushMatrix();
                glColor3ub(150, 0, 0);
                glutSolidSphere(0.1,32,32);
            glPopMatrix();
            glPushMatrix();
                glColor3ub(150, 0, 0);
                glTranslatef(0,-0.35,0);
                glutSolidSphere(0.1,32,32);
            glPopMatrix();
             /*-------------Bottom cylinder-----------*/
            glPushMatrix();
                    GLUquadricObj * qobj1 = gluNewQuadric();
                    glTranslatef(0,-0.26,0);
                    glScalef(0.5,0.5,0.5);
                    glColor3ub(150, 0, 0);
               //     glRotatef(90, 0.0f, 0.0f, 1.0f);
                    glRotatef(90, 1.0f, 0.0f, 0.0f);
                    gluCylinder(qobj1, 0.15, 0.15, 0.35, 50, 50);
                    gluDeleteQuadric(qobj1);
            glPopMatrix();
            /*-------------Top cylinder-----------*/
            glPushMatrix();
                    GLUquadricObj * qobj3 = gluNewQuadric();
                    glTranslatef(0,0.2,0);
                    glScalef(0.5,0.5,0.5);
                    glColor3ub(150, 0, 0);
               //     glRotatef(90, 0.0f, 0.0f, 1.0f);
                    glRotatef(90, 1.0f, 0.0f, 0.0f);
                    gluCylinder(qobj3, 0.15, 0.15, 0.35, 50, 50);
                    gluDeleteQuadric(qobj3);
            glPopMatrix();
    glPopMatrix();
}
void sofa(){
    glPushMatrix();
    glScalef(1,1,1);
    /*--------------Sofa ----------*/
        glPushMatrix();
                glColor3ub(0, 112, 80);
                glScalef(1,0.275,0.3);
                glutSolidCube(1);
        glPopMatrix();
        /*---------Sofa legs-------------*/
        glPushMatrix();
                glColor3ub(63, 27, 0);
                glTranslatef(-0.46,-0.2,0);
                glScalef(0.025,0.25,0.28);
                glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
                glColor3ub(63, 27, 0);
                glTranslatef(0.46,-0.2,0);
                glScalef(0.025,0.25,0.28);
                glutSolidCube(1);
        glPopMatrix();
        /*---------Sofa pillows1-------------*/
        glPushMatrix();
        glColor3ub(0, 49, 175);
        glScalef(0.7,0.7,0.5);
        glTranslatef(-0.6,0.275,-2.8);
        glRotatef(90,1,0,0);
        glTranslatef(0,3,0);
            glPushMatrix();
                    GLUquadricObj * qobj2 = gluNewQuadric();
                    glScalef(1,1,1);
                    glRotatef(90, 1.0f, 0.0f, 0.0f);
                    gluCylinder(qobj2, 0.1, 0.1, 0.35, 50, 50);
                    gluDeleteQuadric(qobj2);
            glPopMatrix();
            /*-------------Top bottom sphere-----------*/
            glPushMatrix();
                glutSolidSphere(0.1,32,32);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0,-0.35,0);
                glutSolidSphere(0.1,32,32);
            glPopMatrix();
        glPopMatrix();
        /*---------Sofa pillows2-------------*/

        glPushMatrix();
        glColor3ub(0, 49, 175);
        glScalef(0.7,0.7,0.5);
        glTranslatef(0.6,0.275,-2.8);
        glRotatef(90,1,0,0);
        glTranslatef(0,3,0);
            glPushMatrix();
                    GLUquadricObj * qobj3 = gluNewQuadric();
                    glScalef(1,1,1);
                    glRotatef(90, 1.0f, 0.0f, 0.0f);
                    gluCylinder(qobj3, 0.1, 0.1, 0.35, 50, 50);
                    gluDeleteQuadric(qobj3);
            glPopMatrix();
            /*-------------Top bottom sphere-----------*/
            glPushMatrix();
                glutSolidSphere(0.1,32,32);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0,-0.35,0);
                glutSolidSphere(0.1,32,32);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
void bookshelf(){
        /*-------Book shelf--------------*/
    glPushMatrix();
                glColor3ub(170, 127, 83);
                glScalef(0.05,2,0.3);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glColor3ub(170, 127, 83);
                glTranslatef(0.97,0.5,0);
                glRotatef(90,0,0,1);
                glScalef(0.05,2,0.3);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glColor3ub(170, 127, 83);
                glTranslatef(0.97,0.0,0);
                glRotatef(90,0,0,1);
                glScalef(0.05,2,0.3);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glColor3ub(170, 127, 83);
                glTranslatef(0.97,-0.5,0);
                glRotatef(90,0,0,1);
                glScalef(0.05,2,0.3);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glColor3ub(170, 127, 83);
                glTranslatef(0.97,1,0);
                glRotatef(90,0,0,1);
                glScalef(0.05,2,0.3);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.95,0,0);
        glRotatef(180,0,0,1);
        glPushMatrix();
                glColor3ub(170, 127, 83);
                glScalef(0.05,2,0.3);
                glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
                glColor3ub(170, 127, 83);
                glTranslatef(0.97,1,0);
                glRotatef(90,0,0,1);
                glScalef(0.05,2,0.3);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    /*--------------Books----------------*/
    /*------------2nd rack----------------*/
    glPushMatrix();//Book red 2nd rack
        glTranslatef(0.3,0,0);
        glRotatef(-10,0,0,1);
        glPushMatrix();
                glColor3ub(255, 0, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.4,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book red 2nd rack
        glTranslatef(0.25,0.05,0);
        glRotatef(-10,0,0,1);
        glPushMatrix();
                glColor3ub(150, 0, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.45,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    /*-----------Books 3rd rack----------*/
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.45,-0.73,0);
        glPushMatrix();
                glColor3ub(0, 0, 50);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.4,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.39,-0.73,0);
        glPushMatrix();
                glColor3ub(0, 0, 130);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.08,0.45,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.33,-0.73,0);
        glPushMatrix();
                glColor3ub(255, 0, 50);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.42,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.28,-0.75,0);
        glPushMatrix();
                glColor3ub(255, 150, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.35,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.23,-0.75,0);
        glPushMatrix();
                glColor3ub(255, 200, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.35,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.18,-0.75,0);
        glPushMatrix();
                glColor3ub(150, 150, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.35,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.135,-0.79,0);
        glPushMatrix();
                glColor3ub(0, 144, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.015,0.3,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.150,-0.79,0);
        glPushMatrix();
                glColor3ub(200, 0, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.015,0.3,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.120,-0.79,0);
        glPushMatrix();
                glColor3ub(10, 123, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.015,0.3,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.105,-0.79,0);
        glPushMatrix();
                glColor3ub(0, 23, 56);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.015,0.3,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.090,-0.79,0);
        glPushMatrix();
                glColor3ub(0, 144, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.015,0.3,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-1.075,-0.79,0);
        glPushMatrix();
                glColor3ub(255, 144, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.015,0.3,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(-0.915,-0.975,0);
        glRotatef(10,0,0,1);
        glPushMatrix();
                glColor3ub(206, 205, 204);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.08,0.4,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glTranslatef(1.5,-1.95,0);
        glRotatef(90,0,0,1);
        glPushMatrix();
                glColor3ub(255, 0, 0);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.4,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();//Book 3rd rach
        glScalef(0.9,1,1);
        glTranslatef(1.6,-1.9,0);
        glRotatef(90,0,0,1);
        glPushMatrix();
                glColor3ub(10, 10, 10);
                glTranslatef(1.5,0.45,0.025);
                glScalef(0.05,0.4,0.2);
                glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    /*-------------Cone---------------*/
    glPushMatrix();
        glColor3ub(59, 255, 10);
        glTranslatef(1.5,0.5,0.05);
        glScalef(0.2,0.2,0.2);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.5,2,32,32);
    glPopMatrix();
    /*--------------Ball---------------*/
    glPushMatrix();
        glColor3ub(246, 255, 0);
        glTranslatef(1.1,0.6,0.05);
        glScalef(0.2,0.2,0.2);
        glutSolidSphere(0.5,32,32);
    glPopMatrix();
}
void table1(){
    /*--------------Table top------------------*/
    glPushMatrix();
                glColor3ub(15, 0, 99);
                glScalef(1.3,0.05,0.65);
                glutSolidCube(1);
    glPopMatrix();
    /*----------Table legs---------------------*/
    glPushMatrix();
        glTranslatef(0,-0.375,0);
        glPushMatrix();
                    glTranslatef(0.6,0,0.275);
                    glColor3ub(170, 127, 83);
                    glScalef(0.05,0.75,0.05);
                    glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
                    glTranslatef(0.6,0,-0.275);
                    glColor3ub(170, 127, 83);
                    glScalef(0.05,0.75,0.05);
                    glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
                    glTranslatef(-0.6,0,0.275);
                    glColor3ub(170, 127, 83);
                    glScalef(0.05,0.75,0.05);
                    glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
                    glTranslatef(-0.6,0,-0.275);
                    glColor3ub(170, 127, 83);
                    glScalef(0.05,0.75,0.05);
                    glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
}

void table2(){
    /*--------------Table top------------------*/
    glPushMatrix();
                glColor3ub(0, 61, 53);
                glScalef(1.3,0.05,0.65);
                glutSolidCube(1);
    glPopMatrix();
    /*----------Table legs---------------------*/
    glPushMatrix();
        glTranslatef(0,-0.375,0);
        glPushMatrix();
                    glTranslatef(0.6,0,0.275);
                    glColor3ub(151, 255, 147);
                    glScalef(0.05,0.75,0.05);
                    glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
                    glTranslatef(0.6,0,-0.275);
                    glColor3ub(151, 255, 147);
                    glScalef(0.05,0.75,0.05);
                    glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
                    glTranslatef(-0.6,0,0.275);
                    glColor3ub(151, 255, 147);
                    glScalef(0.05,0.75,0.05);
                    glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
                    glTranslatef(-0.6,0,-0.275);
                    glColor3ub(151, 255, 147);
                    glScalef(0.05,0.75,0.05);
                    glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
}


void bunkerBed(){
    /*----------Bunker sides----------*/
    glPushMatrix();
        glTranslatef(0,0,0);
        glScalef(0.5,1.05,0.025);
        glColor3ub(118, 0, 155);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0,1);
        glScalef(0.5,1.05,0.025);
        glColor3ub(82, 0, 150);
        glutSolidCube(1);
    glPopMatrix();
    /*---------Bunker bottom support--------*/
    glPushMatrix();
        glTranslatef(0,2.13,0);
        glScalef(1,8.5,0.75);
        glTranslatef(0,-0.3,0.675);
        glScalef(1,1,0.75);
        glRotatef(90,1,0,0);
        glScalef(0.5,1.75,0.025);
        glColor3ub(9, 0, 117);
        glutSolidCube(1);
    glPopMatrix();
    /*---------Bunker top support--------*/
    glPushMatrix();
        glScalef(1,1,0.75);
        glTranslatef(0,0.25,0.675);
        glScalef(1,1,0.75);
        glRotatef(90,1,0,0);
        glScalef(0.5,1.75,0.025);
        glColor3ub(0, 105, 117);
        glutSolidCube(1);
    glPopMatrix();
    /*---------Bunker top mattress--------*/
    glPushMatrix();
        glScalef(0.9,2.25,0.7);
        glTranslatef(0,0.12,0.7);
        glScalef(1,1,0.75);
        glRotatef(90,1,0,0);
        glScalef(0.5,1.75,0.025);
        glColor3ub(252, 227, 83);
        glutSolidCube(1);
    glPopMatrix();

    /*---------Bunker bottom mattress--------*/
    glPushMatrix();
        glScalef(0.9,2.25,0.7);
        glTranslatef(0,-0.1275,0.7);
        glScalef(1,1,0.75);
        glRotatef(90,1,0,0);
        glScalef(0.5,1.75,0.025);
        glColor3ub(255, 132, 56);
        glutSolidCube(1);
    glPopMatrix();
    /*----------Ladder-----------------------*/
    glPushMatrix();
                glTranslatef(-0.26,-0.025,0.7);
                glColor3ub(9, 0, 117);
                glScalef(0.025,0.55,0.025);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glTranslatef(-0.26,-0.025,0.9);
                glColor3ub(9, 0, 117);
                glScalef(0.025,0.55,0.025);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();//Ladder steps
                glTranslatef(-0.26,-0.025,0.8);
                glColor3ub(9, 0, 117);
                glRotatef(90,1,0,0);
                glScalef(0.025,0.2,0.025);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glTranslatef(-0.26,-0.125,0.8);
                glColor3ub(9, 0, 117);
                glRotatef(90,1,0,0);
                glScalef(0.025,0.2,0.025);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glTranslatef(-0.26,-0.225,0.8);
                glColor3ub(9, 0, 117);
                glRotatef(90,1,0,0);
                glScalef(0.025,0.2,0.025);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glTranslatef(-0.26,0.075,0.8);
                glColor3ub(9, 0, 117);
                glRotatef(90,1,0,0);
                glScalef(0.025,0.2,0.025);
                glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glTranslatef(-0.26,0.175,0.8);
                glColor3ub(9, 0, 117);
                glRotatef(90,1,0,0);
                glScalef(0.025,0.2,0.025);
                glutSolidCube(1);
    glPopMatrix();
}
void ceilingLamp(){
    glPushMatrix();
        glPushMatrix();//Wire
                GLUquadricObj * qobj2 = gluNewQuadric();
                glColor3ub(35, 35, 35);
                glTranslatef(0,1.0,0);
                glScalef(1,1,1);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                gluCylinder(qobj2, 0.02, 0.02, 0.5, 50, 50);
                gluDeleteQuadric(qobj2);
        glPopMatrix();
        glTranslatef(0,0,0);
        glPushMatrix();//Shade
        glColor3ub(35, 35, 35);
                GLUquadricObj * qobj3 = gluNewQuadric();
                glTranslatef(0,0.5,0);
                glScalef(1,1,1);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                gluCylinder(qobj3, 0.1, 0.4, 0.35, 50, 50);
                gluDeleteQuadric(qobj3);
        glPopMatrix();
        glPushMatrix();//Bulb
        glColor3ub(255,0,0);
        glTranslatef(0,0.25,0);
        glScalef(0.5,2,0.5);
            glutSolidSphere(0.1,32,32);
        glPopMatrix();
    glPopMatrix();
}
void shower(){
    glPushMatrix();
        glPushMatrix();//Wire
                GLUquadricObj * qobj2 = gluNewQuadric();
                glColor3ub(145, 145, 145);
                glTranslatef(0,1.0,0);
                glScalef(1,1,1);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                gluCylinder(qobj2, 0.05, 0.05, 0.5, 50, 50);
                gluDeleteQuadric(qobj2);
        glPopMatrix();
        glTranslatef(0,0,0);
        glPushMatrix();//Shade
        glColor3ub(145, 145, 145);
                GLUquadricObj * qobj3 = gluNewQuadric();
                glTranslatef(0,0.5,0);
                glScalef(1,1,1);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                gluCylinder(qobj3, 0.1, 0.4, 0.35, 50, 50);
                gluDeleteQuadric(qobj3);
        glPopMatrix();
    glPopMatrix();
}
void setfont1(void *font)
 {
    font1=font;
 }
void letter1(float x,float y,float z,char *str)
 {
 int i,len;
 len=strlen(str);
 glRasterPos3f(x,y,z);
 for(i=0;i<len;i++)
    glutBitmapCharacter(font1,(int)str[i]);
 }
void letter2(float x,float y,float z,char *str)
{
    int i,len;
    len=strlen(str);
    glRasterPos3f(x,y,z);
    for(i=0;i<len;i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
}

void road()
{
    glPushMatrix();
    glScalef(20,0.01,0.7);
    glColor3ub(252, 199, 75);
	glutSolidCube(1);
    glPopMatrix();
}
void controls()
{
    glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluPerspective(40,1,0.25,4);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0.5,3, 0,0.35,0, 0,1,0);

    glColor3f(0.529, 0.808, 0.922);

	 glPushMatrix();
    glTranslatef(-0.15,1.3,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"TUTORIAL");
    glPopMatrix();

	  glPushMatrix();
    glTranslatef(-0.68,1.1,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"Explore the 3D ");
    glPopMatrix();

     glPushMatrix();
    glTranslatef(-0.16,0.9,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"CONTROLS");
    glPopMatrix();

     glPushMatrix();
    glTranslatef(-0.85,0.6,0);
    letter1(0,0,0,"MOVE CAMERA: UP DOWN LEFT RIGHT");
     glPopMatrix();

     glPushMatrix();
    glTranslatef(-0.85,0.4,0);
    letter1(0,0,0,"F - Enter Drawing Room");
     glPopMatrix();

       glPushMatrix();
    glTranslatef(-0.85,0.3,0);
    letter1(0,0,0,"1 - Enter the first door");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.85,0.2,0);
    letter1(0,0,0,"2 - Second door");
     glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.85,0.1,0);
    letter1(0,0,0,"3 - Third Door");
     glPopMatrix();


     glPushMatrix();
    glTranslatef(0.35,0.6,0);
    letter1(0,0,0,"Drag MOUSE to Look at");
     glPopMatrix();
     glPushMatrix();
    glTranslatef(0.2,0,0);
    letter1(0,0,0,"Right Click - PREVIOUS ROOM");
     glPopMatrix();

    glColor3f(0,0,1);
     glPushMatrix();
    setfont1(GLUT_BITMAP_TIMES_ROMAN_24);
    glTranslatef(-0.15,-0.4,0);
    letter1(0,0,0,"READY");
    glPopMatrix();
    glFlush();
}


void initLight()
{
    GLfloat white[]={1,1,1};
	GLfloat ambient_light[]={.5,.5,.5,.5};
    GLfloat diffuse_light[]={1,1,1,1};
    GLfloat lightpos[]={2,0,-1,1};
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_light);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_light);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);
}
void wallbed()
{
	glPushMatrix();
	glScalef(1.6,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
}



void wall()
{
	glPushMatrix();
	glScalef(1,0.05,1);
	glutSolidCube(1);
	glPopMatrix();
}

void fan()
{

     glPushMatrix();
     glRotatef(fanAngle, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
                glScalef(0.5,0.05,0.5);
                glColor3ub(20, 20, 20);

                glutSolidSphere(1,32,32);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,1.3);
                glScalef(0.5,0.05,3);
                glColor3ub(20, 20, 20);

                glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(01.3,0,1.7);

                glColor3ub(20, 20, 20);
                glRotatef(40,0,1,0);
                glScalef(0.5,0.05,3);
                glTranslatef(0,0,-1.3);
                glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-01.3,0,1.7);

                glColor3ub(20, 20, 20);
                glRotatef(-40,0,1,0);
                glScalef(0.5,0.05,3);
                glTranslatef(0,0,-1.3);
                glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();//Wire
                GLUquadricObj * qobj2 = gluNewQuadric();
                glColor3ub(20, 20, 20);
                glTranslatef(0,2.0,0);
                glScalef(1,1,1);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                gluCylinder(qobj2, 0.05, 0.05, 2, 50, 50);
                gluDeleteQuadric(qobj2);
    glPopMatrix();
    glPopMatrix();
}
void Ceiling(){
    /*------------0 ceiling----------------*/
    glPushMatrix();
        glColor3ub(137, 0, 0);
        glTranslatef(0,01.0,0.15);
        glScalef(1,0.01,0.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(137, 0, 0);
        glTranslatef(0.3,0.0,0.55);
        glRotatef(90,0,1,0);
        glTranslatef(0,01.0,0.15);
        glScalef(1,0.01,0.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(137, 0, 0);
        glTranslatef(-0.3,0.0,0.55);
        glRotatef(90,0,1,0);
        glTranslatef(0,01.0,-0.15);
        glScalef(1,0.01,0.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glScalef(1.1,1,1);
        glTranslatef(0,0,1.0);
        glColor3ub(137, 0, 0);
        glTranslatef(0,01.0,0.15);
        glScalef(1,0.01,0.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0,0.25);
        glColor3ub(191, 40, 40);
        glTranslatef(0,01.0,0.15);
        glScalef(0.175,0.01,0.175);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0,0.75);
        glColor3ub(191, 40, 40);
        glTranslatef(0,01.0,0.15);
        glScalef(0.175,0.01,0.175);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.25,0,0.5);
        glColor3ub(191, 40, 40);
        glTranslatef(0,01.0,0.15);
        glScalef(0.175,0.01,0.175);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.25,0,0.5);
        glColor3ub(191, 40, 40);
        glTranslatef(0,01.0,0.15);
        glScalef(0.175,0.01,0.175);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0.05,-0.17);
        glScalef(2.5,1,2.0);
        glTranslatef(0,-0.1,0.3);
        glColor3ub(219, 116, 116);
        glTranslatef(0,01.0,0.15);
        glScalef(0.175,0.01,0.175);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,1.0,0.4);
        glColor3ub(251, 255, 153);
        glScalef(0.025,0.025,0.025);
        glutSolidSphere(1,32,32);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(251, 255, 153);
        glTranslatef(0,1.0,0.9);
        glScalef(0.025,0.025,0.025);
        glutSolidSphere(1,32,32);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(251, 255, 153);
        glTranslatef(-0.2775,1.0,0.65);
        glScalef(0.025,0.025,0.025);
        glutSolidSphere(1,32,32);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.2775,1.0,0.65);
        glColor3ub(251, 255, 153);
        glScalef(0.025,0.025,0.025);
        glutSolidSphere(1,32,32);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0.04,0.3);
        glScalef(1,1,1);
        glTranslatef(0,-0.1,0.3);
        glColor3ub(253, 255, 196);
        glTranslatef(0,01.0,0.15);
        glScalef(0.175,0.01,0.175);
        glutSolidCube(1);
    glPopMatrix();
}
void bedroom1()
{
    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(40,1,0.25,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(flagBed1){
        x=0;z=2.25;camx=0;camy=0.35;camz=0;
                lx=0.0f,lz=-1.0f,ly=0.0f;
                angle=0;angle1=0;
            flagBed1=0;
	}
	gluLookAt(x,0.4f,z,x+lx,0.5f+ly,z+lz,0.0f,1.0f,0.0f);

    glColor3ub(247, 242, 180); //brown
    glPushMatrix();
    glScalef(1,1,4);
	wallbed();
    glPopMatrix();
//roof
	glPushMatrix();
	glScalef(1,1,4);
	glTranslatef(0,1.2,0);
	glColor3ub(200, 200, 200);
	wallbed();
	glPopMatrix();
//left
	glPushMatrix();
	glColor3ub(255, 97, 0);
	glScalef(1,1,4);
	glTranslatef(-0.78,0.7,0);
	glRotatef(90,0,0,1);
	glPushMatrix();
	glScalef(1,1,4);
	glScalef(1.5,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	//back
	glColor3ub(255, 136, 0);
	glPushMatrix();
	glTranslatef(0,0.7,-0.85);
	glRotatef(-90,1,0,0);
	wallbed();
	glPopMatrix();
//right
	glPushMatrix();
	glScalef(1,1,4);
    glColor3ub(255, 97, 0);
	glTranslatef(0.78,0.7,0);
	glRotatef(90,0,0,1);
	glPushMatrix();
	glScalef(1.5,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
        glScalef(0.75,1,1);
        glTranslatef(0,0.1,0);
        bed1();
    glPopMatrix();
    glPushMatrix();//carpet
        glScalef(0.8,0.05,1.4);
        glTranslatef(0,0.2,0);
        glColor3ub(0, 0, 61);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glScalef(0.5,0.25,0.5);
        glTranslatef(1,1,-1);
        cabinet1();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.7,-0.08,0);
        glRotatef(-90,0,1,0);
        glScalef(0.5,0.5,0.5);
        glTranslatef(1,1,0);
        wardrobe();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.5,0.25,-0.45);
        glScalef(0.15,0.15,0.15);
        lamp();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.5,0.3,-0.6);
        glScalef(0.25,0.25,0.25);
        door2();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.75,0.6,0.0);
        glRotatef(90,0,1,0);
        glScalef(0.25,0.25,0.25);
        photoFrame1();
    glPopMatrix();
    Ceiling();

    glPushMatrix();
        glTranslatef(0,0.2,-0.3);
        glScalef(1,1,1);
        glRotatef(90,0,1,0);
        ac();
    glPopMatrix();
    glFlush();

}
void chair(){
        glPushMatrix();
        glScalef(0.4,1,1);
        table1();
    glPopMatrix();
    glPushMatrix();
                    glRotatef(-10,0,0,1);
                    glTranslatef(0.2,0.2,0.275);
                    glColor3ub(170, 127, 83);
                    glScalef(0.05,0.4,0.05);
                    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                    glRotatef(-10,0,0,1);
                    glTranslatef(0.2,0.2,-0.275);
                    glColor3ub(170, 127, 83);
                    glScalef(0.05,0.4,0.05);
                    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
                glTranslatef(0.275,0.4,0);
                glRotatef(80,0,0,1);
                glScalef(0.2,1.1,1);
                glColor3ub(0, 20, 155);
                glScalef(1.3,0.05,0.65);
                glutSolidCube(1);
    glPopMatrix();
}
void bedroom2()
{
    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(40,1,0.25,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(flagBed2){
        x=0;z=2.35;camx=0;camy=0.35;camz=0;
                lx=0.0f,lz=-1.0f,ly=0.0f;
                angle=0;angle1=0;
            flagBed2=0;
	}
	gluLookAt(x,0.4f,z,x+lx,0.5f+ly,z+lz,0.0f,1.0f,0.0f);

    glColor3ub(244, 188, 75); //brown
    glPushMatrix();
    glScalef(1,1,4);
	wallbed();
    glPopMatrix();
//roof
	glPushMatrix();
	glScalef(1,1,4);
	glTranslatef(0,1.2,0);
	glColor3ub(255, 255, 255);
	wallbed();
	glPopMatrix();
//left
	glPushMatrix();
	glColor3ub(201, 210, 255);
	glScalef(1,1,4);
	glTranslatef(-0.78,0.7,0);
	glRotatef(90,0,0,1);
	glPushMatrix();
	glScalef(1,1,4);
	glScalef(1.5,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	//back
	glColor3ub(54, 0, 130);
	glPushMatrix();
	glTranslatef(0,0.7,-0.85);
	glRotatef(-90,1,0,0);
	wallbed();
	glPopMatrix();
//right
	glPushMatrix();
	glScalef(1,1,4);
    glColor3ub(201, 210, 255);
	glTranslatef(0.78,0.7,0);
	glRotatef(90,0,0,1);
	glPushMatrix();
	glScalef(1.5,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.72,0.4,-0.7);
    glScalef(0.35,0.35,0.35);
    bookshelf();
    glPopMatrix();

    glPushMatrix();//0 ceiling
        glTranslatef(0,1.15,0.5);
        glScalef(1,0.01,2);
        glColor3ub(134, 116, 219);
        glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(0.3,0.55,-0.7);
        glScalef(0.65,0.65,2.2);
        wardrobe();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.6,0.4,0.0);
        glScalef(0.7,0.7,0.7);
        bunkerBed();
    glPopMatrix();

    glPushMatrix();//carpet
        glTranslatef(0,0.0,0.4);
        glScalef(0.8,0.05,1.4);
        glTranslatef(0,0.2,0);
        glColor3ub(244, 242, 255);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.6,0.2,0.5);
        glRotatef(90,0,1,0);
        glScalef(0.5,0.5,0.5);
        glTranslatef(0,0.2,0);
        glColor3ub(244, 242, 255);
        table1();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.4,0,0.6);
  //      glRotatef(90,0,1,0);
        glScalef(0.4,0.4,0.4);
        glTranslatef(0,0.5,0);
        chair();
    glPopMatrix();
     glPushMatrix();
        glTranslatef(-0.77,0.4,0.2);
        glScalef(0.8,0.8,0.8);
        glRotatef(90,0,1,0);
        glScalef(1,0.8,0.8);
        glTranslatef(0,0.5,0);
        photoFrame2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,1.0,0.8);
        glScalef(0.1,0.1,0.1);
        fan();
    glPopMatrix();


    glFlush();

}
void kitchenCeilingCabinet(){
        /*----------------Cabinet part1 ------------------------*/
            glPushMatrix();
                glColor3ub(148, 255, 0);
                glTranslatef(0,-0.3,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet part2 ------------------------*/
            glPushMatrix();
                glColor3ub(148, 255, 0);
                glTranslatef(0,-0.6,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();
            /*----------------Cabinet part3 ------------------------*/
            glPushMatrix();
                glColor3ub(148, 255, 0);
                glTranslatef(0,-0.6,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();
            /*----------------Cabinet handle1 ------------------------*/
            glPushMatrix();
                glColor3f(255, 255, 255);
                glTranslatef(0,-0.65,.5);
                glScalef(0.2,0.025,0.05);
                glutSolidCube(1);
            glPopMatrix();
}
void kitchenCeilingCabinet2(){
        glPushMatrix();
        glScalef(0.6,1,0.6);
        glPushMatrix();
            glTranslatef(0,0.25,0);
            /*----------------Cabinet part1 ------------------------*/
            glPushMatrix();
                glColor3ub(148, 255, 0);
                glTranslatef(0,-0.3,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet part2 ------------------------*/
            glPushMatrix();
                glColor3ub(148, 255, 0);
                glTranslatef(0,-0.6,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet handle ------------------------*/
            glPushMatrix();
                glColor3ub(255, 255, 255);
                glTranslatef(0,-0.3,.5);
                glScalef(0.2,0.025,0.05);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
void kitchOven(){
        glPushMatrix();
        glScalef(0.6,1,0.6);
        glPushMatrix();
            glTranslatef(0,0.25,0);
            /*----------------Cabinet part1 ------------------------*/
            glPushMatrix();
                glColor3ub(130, 130, 130);
                glTranslatef(0,-0.3,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();

            /*----------------Cabinet part2 ------------------------*/
            glPushMatrix();
                glColor3ub(130, 130, 130);
                glTranslatef(0,-0.6,0);
                glScalef(0.8,0.3,0.8);
                glutSolidCube(1);
            glPopMatrix();

            glPushMatrix();//Black
                glColor3ub(0, 0, 0);
                glTranslatef(0,-0.4,0.175);
                glScalef(0.6,0.25,0.5);
                glutSolidCube(1);
            glPopMatrix();

            glPushMatrix();
                glColor3ub(60, 60, 60);
                glTranslatef(0,-0.4,0.2);
                glScalef(0.5,0.2,0.5);
                glutSolidCube(1);
            glPopMatrix();

            glPushMatrix();
                glColor3ub(200, 200, 200);
                glTranslatef(0,-0.2,0.3);
                glScalef(0.5,0.025,0.5);
                glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
                glColor3ub(0, 0, 0);
                glTranslatef(0,-0.6,0.16);
                glScalef(0.8,0.01,0.5);
                glutSolidCube(1);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
}
void kitchen()
{
    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(40,1,0.25,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(flagBed1){
        x=0;z=2.25;camx=0;camy=0.35;camz=0;
                lx=0.0f,lz=-1.0f,ly=0.0f;
                angle=0;angle1=0;
            flagBed1=0;
	}
	gluLookAt(x,0.4f,z,x+lx,0.5f+ly,z+lz,0.0f,1.0f,0.0f);

    glColor3ub(237, 237, 237); //brown
    glPushMatrix();
    glScalef(1,1,4);
	wallbed();
    glPopMatrix();
//roof
	glPushMatrix();
	glScalef(1,1,4);
	glTranslatef(0,1.2,0);
	glColor3ub(200, 200, 200);
	wallbed();
	glPopMatrix();
//left
	glPushMatrix();
	glColor3ub(0, 109, 74);
	glScalef(1,1,4);
	glTranslatef(-0.78,0.7,0);
	glRotatef(90,0,0,1);
	glPushMatrix();
	glScalef(1,1,4);
	glScalef(1.5,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	//back
	glColor3ub(255, 255, 255);
	glPushMatrix();
	glTranslatef(0,0.7,-0.85);
	glRotatef(-90,1,0,0);
	wallbed();
	glPopMatrix();
//right
	glPushMatrix();
	glScalef(1,1,4);
    glColor3ub(0, 109, 74);
	glTranslatef(0.78,0.7,0);
	glRotatef(90,0,0,1);
	glPushMatrix();
	glScalef(1.5,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
    /*---------Top kitchen Cabin--------*/
	glPushMatrix();
	glTranslatef(0,1.2,-0.7);
	glScalef(0.25,0.5,0.4);
    kitchenCeilingCabinet();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.205,1.2,-0.7);
	glScalef(0.25,0.5,0.4);
    kitchenCeilingCabinet();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(0.41,1.2,-0.7);
	glScalef(0.25,0.5,0.4);
    kitchenCeilingCabinet();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(0.615,1.2,-0.7);
	glScalef(0.25,0.5,0.4);
    kitchenCeilingCabinet();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,1.2,-0.7);
	glScalef(0.25,0.5,0.4);
    kitchenCeilingCabinet();
	glPopMatrix();
	/*----*/
	glPushMatrix();
	glTranslatef(-0.205,1.2,-0.7);
	glScalef(0.25,0.5,0.4);
    kitchenCeilingCabinet();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(-0.41,1.575,-0.7);
	glScalef(0.25,3,0.4);
    kitchenCeilingCabinet();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(-0.615,1.575,-0.7);
	glScalef(0.25,3,0.4);
    kitchenCeilingCabinet();
	glPopMatrix();

	glPushMatrix();
        glTranslatef(-0.7,0,0.3);
        glRotatef(90,0,1,0);
        glTranslatef(0,0.1,0);
        glScalef(0.8,0.8,0.8);
        fridge();
	glPopMatrix();
    /*----------Slabs-----------------*/
    glPushMatrix();
        glColor3f(0,0,0);
        glTranslatef(0.45,0.35,-0.9);
        glScalef(1.5,0.01,0.8);
        glutSolidCube(1);
	glPopMatrix();
	/*---------------Bottom cabin---------*/
	glPushMatrix();
	glTranslatef(-0.18,0.29,-0.65);
	glScalef(0.5,0.6,0.5);
    kitchenCeilingCabinet2();
    glPopMatrix();
    glPushMatrix();
	glTranslatef(0.0675,0.29,-0.65);
	glScalef(0.5,0.6,0.5);
    kitchenCeilingCabinet2();
    glPopMatrix();
    glPushMatrix();
	glTranslatef(0.315,0.29,-0.65);
	glScalef(0.5,0.6,0.5);
    kitchOven();
    glPopMatrix();
    glPushMatrix();
	glTranslatef(0.5625,0.29,-0.65);
	glScalef(0.5,0.6,0.5);
    kitchenCeilingCabinet2();
    glPopMatrix();
    glPushMatrix();
	glTranslatef(0.81,0.29,-0.65);
	glScalef(0.5,0.6,0.5);
    kitchenCeilingCabinet2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.2,0.6,-0.75);
        glScalef(0.5,0.25,0.01);
        glColor3ub(48, 162, 255);
        glutSolidCube(1);
    glPopMatrix();
        glPushMatrix();
        glTranslatef(0.2,0.6,-0.8);
        glScalef(0.6,0.325,0.01);
        glColor3ub(0, 107, 24);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.6,0.2,0.5);
        glRotatef(90,0,1,0);
        glScalef(0.5,0.5,0.5);
        glTranslatef(0,0.2,0);
        glColor3ub(244, 242, 255);
        table2();
    glPopMatrix();

    glPushMatrix();//Stove
        glTranslatef(0.2,0.37,-0.6);
        glScalef(0.3,0.03,0.1);
        glColor3ub(80,80,80);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.6,0.36,0.4);
        glScalef(0.07,0.07,0.07);
        glColor3ub(173, 0, 0);
        glutSolidTeapot(1);
    glPopMatrix();

    glPushMatrix();//Stove
        glTranslatef(0.6,0.35,-0.65);
        glScalef(0.2,0.03,0.2);
        glColor3ub(191, 191, 191);
        glutSolidCube(1);
    glPopMatrix();

        glPushMatrix();//Tap
        glTranslatef(0.6,0.4,-1.0);
        glScalef(0.01,0.01,0.4);
        glColor3ub(191, 191, 191);
        glutSolidSphere(1,32,32);
    glPopMatrix();

    glFlush();

}
void bucket1(){
    glPushMatrix();//Shade
        glColor3ub(76, 192, 255);
                GLUquadricObj * qobj3 = gluNewQuadric();
                glTranslatef(0,0.5,0);
                glScalef(1,1,1);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                gluCylinder(qobj3, 0.3, 0.2, 0.9, 50, 50);
                gluDeleteQuadric(qobj3);
    glPopMatrix();
}
void bucket2(){
    glPushMatrix();//Shade
        glColor3ub(209, 29, 29);
                GLUquadricObj * qobj3 = gluNewQuadric();
                glTranslatef(0,0.5,0);
                glScalef(1,1,1);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                gluCylinder(qobj3, 0.3, 0.2, 0.9, 50, 50);
                gluDeleteQuadric(qobj3);
    glPopMatrix();
}
void tap(){
    glPushMatrix();//Shade
        glColor3ub(122, 122, 122);
                GLUquadricObj * qobj3 = gluNewQuadric();
                glRotatef(90, 0.0f, 0.0f, 1.0f);
                glTranslatef(0,0.5,0);
                glScalef(1,1,1);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                gluCylinder(qobj3, 0.2, 0.2, 1.3, 50, 50);
                gluDeleteQuadric(qobj3);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.5,0.0,0);
        glColor3ub(122, 122, 122);
        glScalef(0.3,0.3,0.3);
        glutSolidSphere(1,32,32);
    glPopMatrix();
}
void toilet()
{
    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(40,1,0.25,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(flagToil){
        x=0;z=2.25;camx=0;camy=0.35;camz=0;
                lx=0.0f,lz=-1.0f,ly=0.0f;
                angle=0;angle1=0;
            flagToil=0;
	}
	gluLookAt(x,0.4f,z,x+lx,0.5f+ly,z+lz,0.0f,1.0f,0.0f);

    glColor3ub(114, 34, 106); //brown
    glPushMatrix();
    glScalef(1,1,4);
	wallbed();
    glPopMatrix();
//roof
	glPushMatrix();
	glScalef(1,1,4);
	glTranslatef(0,1.2,0);
	glColor3ub(255, 224, 252);
	wallbed();
	glPopMatrix();
//left
	glPushMatrix();
	glTranslatef(0.4,0,0);
	glColor3ub(255, 193, 248);
	glScalef(1,1,4);
	glTranslatef(-0.78,0.7,0);
	glRotatef(90,0,0,1);
	glPushMatrix();
	glScalef(1,1,4);
	glScalef(1.5,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	//back
	glColor3ub(255, 53, 232);
	glPushMatrix();
	glTranslatef(0,0.7,-0.85);
	glRotatef(-90,1,0,0);
	wallbed();
	glPopMatrix();
//right
	glPushMatrix();
	glTranslatef(-0.4,0,0);
	glScalef(1,1,4);
    glColor3ub(255, 193, 248);
	glTranslatef(0.78,0.7,0);
	glRotatef(90,0,0,1);
	glPushMatrix();
	glScalef(1.5,0.05,1.6);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,1.0-0.0,0);
	glScalef(0.3,0.3,0.3);
        ceilingLamp();
	glPopMatrix();

   glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslatef(0,0.6,-0.9);
	glScalef(0.4,0.2,0.25);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslatef(0,0.25,-0.7);
	glScalef(0.15,0.1,0.5);
	glutSolidCube(1);
	glPopMatrix();

		glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslatef(0,0.18,-0.7);
	glScalef(0.1,0.1,0.5);
	glutSolidCube(1);
	glPopMatrix();

    glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslatef(0,0.3,-0.7);
	glScalef(0.11,0.009,0.14);
	glutSolidSphere(1,32,32);
	glPopMatrix();

    glPushMatrix();
    glColor3ub(100, 100, 100);
    glTranslatef(0.15,0.6,-0.7);
	glScalef(0.02,0.02,0.02);
	glutSolidSphere(1,32,32);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.1,0.4,0);
	glRotatef(-45,0,0,1);
	glTranslatef(0,0.5,0);
	glScalef(0.15,0.15,0.15);
        shower();
	glPopMatrix();

    glPushMatrix();
	glTranslatef(0.2,0.05,0.5);
	glScalef(0.25,0.4,0.25);
        bucket1();
	glPopMatrix();

    glPushMatrix();
	glTranslatef(0.2,0.05,0.9);
	glScalef(0.25,0.2,0.25);
        bucket2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.35,0.35,0.4);
	glScalef(0.1,0.1,0.1);
        tap();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.35,0.35,0.7);
	glScalef(0.1,0.1,0.1);
        tap();
	glPopMatrix();

    glPushMatrix();
	glTranslatef(0.42,0.45,00);
	glScalef(0.1,0.1,0.1);
        tap();
	glPopMatrix();


    glFlush();

}
void corridor()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(40,1,0.25,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(flagCori){
        x=0;z=2.25;camx=0;camy=0.35;camz=0;
                lx=0.0f,lz=-1.0f,ly=0.0f;
                angle=0;angle1=0;
            flagCori=0;
	}

    gluLookAt(x,0.4f,z,x+lx,0.5f+ly,z+lz,0.0f,1.0f,0.0f);
	glColor3ub(224,145,0);
    glPushMatrix();
        glScalef(1,1,4);
        wall();
    glPopMatrix();

	glPushMatrix();
	glTranslatef(0,1,0);
	glScalef(1,1,4);
	glColor3ub(130,175,255);
	wall();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0,165,255);
	glTranslatef(-0.5,0.5,0);
	glScalef(1,1,4);
	glRotatef(90,0,0,1);
	wall();
	glPopMatrix();

	//back
	glColor3ub(0,144,255);
	glPushMatrix();
	glTranslatef(0,0.5,-0.5);
	glRotatef(-90,1,0,0);
	wall();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0,165,255);
	glTranslatef(0.5,0.5,0);
	glScalef(1,1,4);
	glRotatef(90,0,0,1);
	wall();
	glPopMatrix();

    glPushMatrix();
        glScalef(1,1,2);
        glTranslatef(-0.42,-0.2,0.1);
        glRotatef(90,0,1,0);
        glTranslatef(0,0.5,0);
        glScalef(0.25,0.25,0.25);
        door();
    glPopMatrix();
    glPushMatrix();
        glScalef(1,1,2);
        glTranslatef(0.42,-0.2,0.3);
        glRotatef(90,0,1,0);
        glTranslatef(0,0.5,0);
        glScalef(0.25,0.25,0.25);
        door();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.85,0,1.0);
        glRotatef(180,0,1,0);
        glScalef(1,1,2);
        glTranslatef(0.42,-0.2,0.4);
        glRotatef(90,0,1,0);
        glTranslatef(0,0.5,0);
        glScalef(0.25,0.25,0.25);
        door();
    glPopMatrix();
	//frame
	glPushMatrix();
	glTranslatef(-.02,0.4,-.4);
	glScalef(0.1,0.1,0.1);
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        glVertex3f(-2,-1.5,0);
        glVertex3f(3,-1.5,0);
        glVertex3f(3,2.5,0);
        glVertex3f(-2,2.5,0);
 	glEnd();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-.02,0.4,-.4);
	glScalef(0.1,0.1,0.1);
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_QUADS);
        glVertex3f(-2.1,-1.8,-0.05);
        glVertex3f(3.1,-1.8,-0.05);
        glVertex3f(3.1,2.6,-0.05);
        glVertex3f(-2.1,2.6,-0.05);
 	glEnd();

     glBegin(GL_QUADS);
        glVertex3f(-3,-1.5,-0.05);
        glVertex3f(-2.7,-1.5,-0.05);
        glVertex3f(-2.7,2.3,-0.05);
        glVertex3f(-3,2.3,-0.05);
 	glEnd();

 	glTranslatef(6.6,0,0);
 	glColor3f(0,0,0);
 	glPushMatrix();
         glBegin(GL_QUADS);
        glVertex3f(-3,-1.5,-0.05);
        glVertex3f(-2.7,-1.5,-0.05);
        glVertex3f(-2.7,2.3,-0.05);
        glVertex3f(-3,2.3,-0.05);
 	glEnd();
 	glPopMatrix();

    glPopMatrix();
    ac();
    glPushMatrix();
        glTranslatef(0.03,0.14,0.8);
        glScalef(0.5,0.3,0.5);
        sofa();
        glutPostRedisplay();
    glPopMatrix();

	glFlush();
}

void test(){
    glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(40,1,0.25,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(x,0.4f,z,x+lx,0.5f+ly,z+lz,0.0f,1.0f,0.0f);
	glFlush();
}

void intro()
{
    glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluPerspective(40,1,0.25,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0.5,3, 0,0.35,0, 0,1,0);

    glColor3f(1,1,0);

	glPushMatrix();
    glTranslatef(-0.6,1.3,0);
    setfont1(font_style);
    letter1(0,0,0,"COMPUTER GRAPHICS AND VISUALISATION PROJECT");
    glPopMatrix();

    glColor3f(1,1,1);
	glPushMatrix();
    glTranslatef(-0.4,1.2,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"TITLE : 3D Neighbourhood Simulator");
    glPopMatrix();

    glColor3f(0,1,0.4);
    glPushMatrix();
    glTranslatef(-0.9,1.0,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"We hope you like our project which was developed by me and my teammate.In this project we have introduced interactive keys that have been guided to you");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9,0.9,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"in the tutorial page.This project implements the view of a 3D House both inside and outside of the house.There are 5 components that are placed inside they");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9,0.8,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"are fan, sofa, tv, a table and a teapot placed on the table. The outside of the house has trees.The API’s that are used in implementing these of the components");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9,0.7,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"are glutSolidCube(), glutSolidTeapot(), glutSoildCone()… etc. An animation has been implemented which shows the rotation of the fan inside the house. Lighting ");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9,0.6,0);
    setfont1(GLUT_BITMAP_HELVETICA_18);
    letter1(0,0,0,"has been implemented by the inbuilt OPENGL lighting functions.");
    glPopMatrix();


    glColor3f(0.529, 0.808, 0.922);
    glPushMatrix();
    setfont1(GLUT_BITMAP_TIMES_ROMAN_10);
    glTranslatef(-0.7,-0.01,0);
    letter1(0,0,0,"DESIGNED BY~");
    glPopMatrix();

    glPushMatrix();
    setfont1(GLUT_BITMAP_TIMES_ROMAN_24);
    glTranslatef(-0.7,-0.1,0);
    letter1(0,0,0,"Rahul H Raj      4VP20CS069");
    glPopMatrix();

    glPushMatrix();
    setfont1(GLUT_BITMAP_TIMES_ROMAN_24);
    glTranslatef(-0.7,-0.2,0);
    letter1(0,0,0,"Sujan S              4VP20CS094");
    glPopMatrix();

    glColor3f(1,0,0.5);
    glPushMatrix();
    setfont1(GLUT_BITMAP_TIMES_ROMAN_24);
    glTranslatef(-0.7,-0.5,0);
    letter1(0,0,0,"BEGIN YOUR JOURNEY BY CLICKING ENTER key");
    glPopMatrix();


    glFlush();
}

void tree0(float x,float z,float rot){
    glTranslatef(x,0,z);
    glPushMatrix();
        glRotatef(rot,0,1,0);
        glColor3ub(0,180,0);
        glPushMatrix();
            glTranslatef(0,0.8,0);
            glutSolidSphere(0.3,100,100);
        glPopMatrix();

        glColor3ub(153,100,0);
        glPushMatrix();
            glTranslatef(0,0.1,0);
            glScalef(1.2,17,1.2);
            glutSolidCube(0.05);
        glPopMatrix();

    //row 1
        glColor3f(1,0,0);
        glPushMatrix();
            glTranslatef(0,0.8,+0.3);
            glutSolidSphere(0.035,100,100);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0.8,-0.3);
            glutSolidSphere(0.035,100,100);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0-0.3,0.8,0);
            glutSolidSphere(0.035,100,100);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0+0.3,0.8,0);
            glutSolidSphere(0.035,100,100);
        glPopMatrix();
 //row 2
         glPushMatrix();
                glRotatef(30,0,1,0);
                glColor3f(1,0,0);
                glPushMatrix();
                    glTranslatef(0,0.8+0.1,0.28);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,0.8+0.1,-0.28);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0-0.28,0.8+0.1,0);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0+0.28,0.8+0.1,0);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();
            glPopMatrix();

    //row 3
         glPushMatrix();
                glRotatef(45,0,1,0);
                glColor3f(1,0,0);
                glPushMatrix();
                    glTranslatef(0,0.8-0.11,0.28);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,0.8-0.11,-0.28);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0-0.28,0.8-0.11,0);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0+0.28,0.8-0.11,0);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();
            glPopMatrix();

        //row 4
         glPushMatrix();
                glRotatef(78,0,1,0);
                glColor3f(1,0,0);
                glPushMatrix();
                    glTranslatef(0,0.8-0.2,0.2);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,0.8-0.2,0.2);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0-0.2,0.8-0.2,0);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

            glPopMatrix();

                //row 5
           glPushMatrix();
                glRotatef(20,0,1,0);
                glColor3f(1,0,0);
                glPushMatrix();
                    glTranslatef(0,0.8+0.2,0.2);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,0.8+0.2,-0.2);
                    glutSolidSphere(0.035,100,100);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0-0.2,0.8+0.2,0);
                    glutSolidSphere(0.035,100,100);
            glPopMatrix();
    glPopMatrix();
}
void tree(float x,float z,float rot){
    glTranslatef(x,0,z);
    glPushMatrix();
        glRotatef(rot,0,1,0);
        glColor3ub(0,204,0);
        glPushMatrix();
            glTranslatef(0,0.5,0);
            glutSolidSphere(0.2,100,100);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0.5+0.15,0);
            glutSolidSphere(0.15,100,100);
        glPopMatrix();

        glColor3ub(153,76,0);
 glPushMatrix();
            glTranslatef(0,0.1,0);
            glScalef(1,10,1);
            glutSolidCube(0.05);
        glPopMatrix();
    glPopMatrix();
}
void tree2(float x,float z,float rot){
    glTranslatef(x,0,z);
    glPushMatrix();
        glRotatef(rot,0,1,0);
        glScalef(0.9,1.1,0.9);
        glColor3ub(0,225,0);
        glPushMatrix();
            glTranslatef(0,0.5,0);
            glutSolidSphere(0.2,100,100);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0.5+0.2,0);
            glutSolidSphere(0.15,100,100);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0-0.15,0.5,0);
            glutSolidSphere(0.15,100,100);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0+0.15,0.5,0);
            glutSolidSphere(0.15,100,100);
        glPopMatrix();

        glColor3ub(102,0,0);
        glPushMatrix();
            glTranslatef(0,0.1,0);
            glScalef(1,10,1);
            glutSolidCube(0.05);
        glPopMatrix();
    glPopMatrix();
}
void tree3(float x,float z,float rot){
    glTranslatef(x,0,z);
    glPushMatrix();
        glColor3ub(255,135,51);
        glPushMatrix();
            glTranslatef(0,0.1,0);
            glScalef(1,10,1);
            glutSolidCube(0.05);
        glPopMatrix();

        glRotatef(rot,0,1,0);
        glScalef(0.9,0.9,0.9);
        glTranslatef(0,0.2,0);
        glColor3ub(0,153,76);
        glRotatef(270,1,0,0);
        glPushMatrix();
            glutSolidCone(0.2,0.6,100,100);
        glPopMatrix();
    glPopMatrix();
}
void tree4(float x,float z,float rot){
    glTranslatef(x,0,z);
    glPushMatrix();
        glColor3ub(51,25,0);
        glPushMatrix();
            glTranslatef(0,0.1,0);
            glScalef(1,10,1);
            glutSolidCube(0.05);
        glPopMatrix();

        glRotatef(rot,0,1,0);
        glTranslatef(0,0.2,0);
        glColor3ub(76,153,0);
        glRotatef(270,1,0,0);
        glPushMatrix();
            glTranslatef(0,0,0.2);
            glutSolidCone(0.2,0.6,100,100);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0,0.1);
            glutSolidCone(0.2,0.6,100,100);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0,0);
            glutSolidCone(0.2,0.6,100,100);
        glPopMatrix();
    glPopMatrix();
}
void tree5(float x,float z,float rot){
    glTranslatef(x,0,z);
    glRotatef(rot,0,1,0);
    glPushMatrix();
        glColor3ub(51,25,0);
        glPushMatrix();
            glTranslatef(0,0.1,0);
            glScalef(1,10,1);
            glutSolidCube(0.05);
        glPopMatrix();

        glColor3ub(0,51,0);
        glPushMatrix();
            glTranslatef(0,0.35,0);
            glScalef(10,2,10);
            glutSolidCube(0.05);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0.42,0);
            glScalef(8,1.5,8);
            glutSolidCube(0.05);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0.48,0);
            glScalef(6,1.2,6);
            glutSolidCube(0.05);
        glPopMatrix();
                glPushMatrix();
            glTranslatef(0,0.52,0);
            glScalef(3,1,3);
            glutSolidCube(0.05);
        glPopMatrix();


    glPopMatrix();
}
void forest(){
        glPushMatrix();
            tree0(2.4,1.5,0);
        glPopMatrix();

        glPushMatrix();
            tree(-2,-2,15);
        glPopMatrix();

        glPushMatrix();
            tree2(-2.2,-1.5,55);
        glPopMatrix();

        glPushMatrix();
            tree0(1.5,1,87);
        glPopMatrix();

        glPushMatrix();
            tree(1,1.4,34);
        glPopMatrix();

        glPushMatrix();
            tree3(1.5,1.5,34);
        glPopMatrix();

        glPushMatrix();
            tree3(-1.1,-1.4,34);
        glPopMatrix();

        glPushMatrix();
            tree2(4,-2.5,55);
        glPopMatrix();

        glPushMatrix();
            tree2(2.4,-1.5,55);
        glPopMatrix();

        glPushMatrix();
            tree0(-0.68,1,45);
        glPopMatrix();

        glPushMatrix();
            tree(2,1.4,34);
        glPopMatrix();

        glPushMatrix();
            tree4(1,-2,45);
        glPopMatrix();

        glPushMatrix();
            tree4(-1.7,1.3,45);
        glPopMatrix();

        glPushMatrix();
            tree4(-2.7,-1.5,45);
        glPopMatrix();

        glPushMatrix();
            tree4(-3,1,45);
        glPopMatrix();

        glPushMatrix();
            tree5(-3.2,1.5,80);
        glPopMatrix();


        glPushMatrix();
            tree5(-1.0,2,80);
        glPopMatrix();

        glPushMatrix();
            tree5(1.4,-1,45);
        glPopMatrix();

        glPushMatrix();
            tree5(1.8,-1.2,67);
        glPopMatrix();

        glutPostRedisplay();
        glutSwapBuffers();
}
void house(){
// The ground floor
    //drawsun();
    if(nightMode==1)
    {
        r=255,g=255;
    }
    else{
        r=0;g=0;
    }
    glPushMatrix();
        glTranslatef(0,0,-2);
        glColor3ub(153,204,255);
        glScalef(1,0.5,1);
        glutSolidCube(1);
    glPopMatrix();

//Ceiling of ground floor
    glPushMatrix();
        glTranslatef(0,0.25,-2);
        glColor3ub(0,0,204);
        glScalef(1.1,0.05,1.1);
        glutSolidCube(1);
    glPopMatrix();

// The first floor

        glPushMatrix();
            glScalef(1,0.6,1);
            glTranslatef(-0.3,0.3,0);
            glPushMatrix();
                glTranslatef(0,0.3,-2);
                glColor3ub(153,204,255);
                glScalef(0.4,0.3,1);
                glutSolidCube(1);
            glPopMatrix();

            glPushMatrix();
                glColor3ub(0,51,102);
                glScalef(0.4,0.3,1);
                glTranslatef(0,1.5,-1.5);
                glBegin(GL_TRIANGLES);
                    glVertex3f(0,1,0);
                    glVertex3f(0.5,0,0);
                    glVertex3f(-0.5,0,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glColor3ub(0,51,102);
                glScalef(0.4,0.3,1);
                glTranslatef(0,1.5,-2.5);
                glBegin(GL_TRIANGLES);
                    glVertex3f(0,1,0);
                    glVertex3f(0.5,0,0);
                    glVertex3f(-0.5,0,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glColor3ub(0,51,102);
                glScalef(0.4,0.3,1);
                glTranslatef(0,1.5,-2.5);
                glBegin(GL_QUADS);
                    glVertex3f(0.5,0,0);
                    glVertex3f(0.5,0,1);
                    glVertex3f(0,1,1);
                    glVertex3f(0,1,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glColor3ub(0,51,102);
                glScalef(0.4,0.3,1);
                glTranslatef(0,1.5,-2.5);
                glBegin(GL_QUADS);
                    glVertex3f(-0.5,0,0);
                    glVertex3f(-0.5,0,1);
                    glVertex3f(0,1,1);
                    glVertex3f(0,1,0);
                glEnd();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glColor3ub(153,204,255);
            glTranslatef(0.182,0.3,-1.51);
            glScalef(0.65,0.08,0.005);
            glutSolidCube(1);
        glPopMatrix();

         glPushMatrix();
            glColor3ub(153,204,255);
            glTranslatef(0.182,0.3,-2.505);
            glScalef(0.65,0.08,0.005);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glColor3ub(153,204,255);
            glTranslatef(0.505,0.3,-2.015);
            glRotatef(90,0,1,0);
            glScalef(1,0.08,0.005);
            glutSolidCube(1);
        glPopMatrix();

        //Door
        glPushMatrix();
            glColor3ub(102,51,0);
            glTranslatef(-0.35,0,-1.5);
            glScalef(0.1,0.35,0.01);
            glutSolidCube(1);
        glPopMatrix();
        //Door 1 Knob
        glPushMatrix();
            glColor3f(1,1,0);
            glTranslatef(-0.33,0.1,-1.5);
            glutSolidSphere(0.01,100,100);
        glPopMatrix();
        //Above door
        glPushMatrix();
            glColor3ub(102,51,0);

            glTranslatef(-0.10,0.3,-2);
            glRotatef(90,0,1,0);
            glScalef(0.1,0.25,0.01);
            glutSolidCube(1);
        glPopMatrix();
        //Door 2 Knob
        glPushMatrix();
            glColor3f(1,1,0);
            glTranslatef(-0.10,0.35,-2.025);
            glRotatef(90,0,1,0);
            glutSolidSphere(0.01,100,100);
        glPopMatrix();
        //Window
        glPushMatrix();
            glColor3ub(r,g,b);
            glTranslatef(0.2,0.13,-1.5);
            glScalef(0.2,0.1,0.01);
            glutSolidCube(1);
        glPopMatrix();

}

void house2(){
// The ground floor
    glPushMatrix();
        glTranslatef(0,0,-2);
        glColor3ub(255,153,255);
        glScalef(1,0.5,1);
        glutSolidCube(1);
    glPopMatrix();

//Ceiling of ground floor
    glPushMatrix();
        glTranslatef(0,0.25,-2);
        glColor3ub(102,0,51);
        glScalef(1.1,0.05,1.1);
        glutSolidCube(1);
    glPopMatrix();

// The first floor

    glPushMatrix();
        glTranslatef(0,0.4,-2);
        glColor3ub(255,153,255);
        glScalef(1,0.25,1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0.55,-2);
        glColor3ub(102,0,51);
        glScalef(1.1,0.05,1.1);
        glutSolidCube(1);
    glPopMatrix();
        //Door
        glPushMatrix();
            glColor3ub(102,51,0);
            glTranslatef(-0.35+0.35,0,-1.5);
            glScalef(0.1,0.35,0.01);
            glutSolidCube(1);
        glPopMatrix();
        //Door 1 Knob
        glPushMatrix();
            glColor3f(1,1,0);
            glTranslatef(-0.33+0.35,0.1,-1.5);
            glutSolidSphere(0.01,100,100);
        glPopMatrix();

        //Window
        glPushMatrix();
            glColor3ub(0,0,0);
            glTranslatef(0.2+0.15,0.13,-1.5);
            glScalef(0.2,0.1,0.01);
            glutSolidCube(1);
        glPopMatrix();
         //Window2
        glPushMatrix();
            glColor3ub(0,0,0);
            glTranslatef(-(0.2+0.15),0.13,-1.5);
            glScalef(0.2,0.1,0.01);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();//window of other floor
                 //Window
                 glTranslatef(0,0.31,0);
                glPushMatrix();
                    glColor3ub(0,0,0);
                    glTranslatef(0.2+0.15,0.13,-1.5);
                    glScalef(0.2,0.1,0.01);
                    glutSolidCube(1);
                glPopMatrix();
                 //Window2
                glPushMatrix();
                    glColor3ub(0,0,0);
                    glTranslatef(-(0.2+0.15),0.13,-1.5);
                    glScalef(0.2,0.1,0.01);
                    glutSolidCube(1);
                glPopMatrix();
        glPopMatrix();

}

void house3(){
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(0,0.1,0);
        glScalef(0.2,0.2,0.2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glScalef(0.2,0.2,0.2);
        glColor3f(1,0,0);
        glTranslatef(0,0.5,0);
        //left
        glBegin(GL_POLYGON);
            glVertex3f(-.5,0.5,-.5);
            glVertex3f(-.5,0.5,.5);
            glVertex3f(0,1.1,0);
        glEnd();
        //front
        glBegin(GL_POLYGON);
            glVertex3f(-.5,0.5,.5);
            glVertex3f(.5,0.5,.5);
            glVertex3f(0,1.1,0);
        glEnd();
        //back
        glBegin(GL_POLYGON);
            glVertex3f(0,1.1,0);
            glVertex3f(-.5,0.5,-.5);
            glVertex3f(.5,0.5,-.5);
        glEnd();
        //right
        glBegin(GL_POLYGON);
            glVertex3f(0,1.1,0);
            glVertex3f(.5,0.5,-.5);
            glVertex3f(.5,0.5,.5);
        glEnd();
    glPopMatrix();

    //Window
        glPushMatrix();
            glColor3ub(0,0,0);
            glTranslatef(0,0.125,0.1);
            glScalef(0.05,0.05,0.01);
            glutSolidCube(1);
        glPopMatrix();

            //Door
    glPushMatrix();
        glTranslatef(0,0,-0.2);
        glPushMatrix();
            glColor3ub(102,51,0);
            glTranslatef(0,-0.05,0.1);
            glScalef(0.1,0.35,0.01);
            glutSolidCube(1);
        glPopMatrix();
        //Door 1 Knob
        glPushMatrix();
            glColor3f(1,1,0);
            glTranslatef(0.03,0.05,0.1);
            glutSolidSphere(0.01,100,100);
        glPopMatrix();
    glPopMatrix();

}
void house4(){
    glPushMatrix();
        glColor3ub(192,192,192);
        glTranslatef(0,0.1,0);
        glScalef(0.2,0.2,0.2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glScalef(0.2,0.2,0.2);
        glColor3ub(51,51,0);
        glTranslatef(0,0.5,0);
        //left
        glBegin(GL_POLYGON);
            glVertex3f(-.5,0.5,-.5);
            glVertex3f(-.5,0.5,.5);
            glVertex3f(0,1.1,0);
        glEnd();
        //front
        glBegin(GL_POLYGON);
            glVertex3f(-.5,0.5,.5);
            glVertex3f(.5,0.5,.5);
            glVertex3f(0,1.1,0);
        glEnd();
        //back
        glBegin(GL_POLYGON);
            glVertex3f(0,1.1,0);
            glVertex3f(-.5,0.5,-.5);
            glVertex3f(.5,0.5,-.5);
        glEnd();
        //right
        glBegin(GL_POLYGON);
            glVertex3f(0,1.1,0);
            glVertex3f(.5,0.5,-.5);
            glVertex3f(.5,0.5,.5);
        glEnd();
    glPopMatrix();

    //Window
        glPushMatrix();
            glColor3ub(0,0,0);
            glTranslatef(0,0.125,0.1);
            glScalef(0.05,0.05,0.01);
            glutSolidCube(1);
        glPopMatrix();

            //Door
    glPushMatrix();
        glTranslatef(0,0,-0.2);
        glPushMatrix();
            glColor3ub(102,51,0);
            glTranslatef(0,-0.05,0.1);
            glScalef(0.1,0.35,0.01);
            glutSolidCube(1);
        glPopMatrix();
        //Door 1 Knob
        glPushMatrix();
            glColor3f(1,1,0);
            glTranslatef(0.03,0.05,0.1);
            glutSolidSphere(0.01,100,100);
        glPopMatrix();
    glPopMatrix();

}

void house5(){
    glPushMatrix();
        glColor3ub(192,192,192);
        glTranslatef(0,0.1,0);
        glScalef(0.2,0.2,0.2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glScalef(0.2,0.2,0.2);
        glColor3ub(51,51,0);
        glTranslatef(0,0.5,0);
        //left
        glBegin(GL_POLYGON);
            glVertex3f(-.5,0.5,-.5);
            glVertex3f(-.5,0.5,.5);
            glVertex3f(0,1.1,0);
        glEnd();
        //front
        glBegin(GL_POLYGON);
            glVertex3f(-.5,0.5,.5);
            glVertex3f(.5,0.5,.5);
            glVertex3f(0,1.1,0);
        glEnd();
        //back
        glBegin(GL_POLYGON);
            glVertex3f(0,1.1,0);
            glVertex3f(-.5,0.5,-.5);
            glVertex3f(.5,0.5,-.5);
        glEnd();
        //right
        glBegin(GL_POLYGON);
            glVertex3f(0,1.1,0);
            glVertex3f(.5,0.5,-.5);
            glVertex3f(.5,0.5,.5);
        glEnd();
    glPopMatrix();

    //Window
        glPushMatrix();
            glColor3ub(0,0,0);
            glTranslatef(0,0.125,0.1);
            glScalef(0.05,0.05,0.01);
            glutSolidCube(1);
        glPopMatrix();

            //Door
    glPushMatrix();
        glTranslatef(0,0,-0.2);
        glPushMatrix();
            glColor3ub(102,51,0);
            glTranslatef(0,-0.05,0.1);
            glScalef(0.1,0.35,0.01);
            glutSolidCube(1);
        glPopMatrix();
        //Door 1 Knob
        glPushMatrix();
            glColor3f(1,1,0);
            glTranslatef(0.03,0.05,0.1);
            glutSolidSphere(0.01,100,100);
        glPopMatrix();
    glPopMatrix();

}


void outside()
{
    static GLclampf r=0.0,g= 0.0,b= 1.0,a=1;
    glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluPerspective(45,1,0.25,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(	x, 0.5f, z,
			x+lx, 0.5f+ly,  z+lz,
			0.0f, 1.0f,  0.0f);
	glColor3f(0,0.859,0.2);
	glPushMatrix();
	glTranslatef(0,-0.025,0);
	glScalef(20,0.05,50);
	glutSolidCube(1);
	glPopMatrix();
    glColor3f(0,0,0);

    house();
    glPushMatrix();
        glTranslatef(-0.8,0,-2.5);
        house5();
    glPopMatrix();
    //modified extra house
    glPushMatrix();
        glTranslatef(3,0,0);
        house2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.5,0,1);
        house3();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.25,0,-1.5);
        glRotatef(180,0,1,0);
        house4();
    glPopMatrix();

    road();
    forest();

    if(nightMode==1){
        r=0.0;g=0.0;b=0.0;a=1.0;
    }
    else{
        r=0.0;g=0.698;b=1.0;a=0.0;
    }
    glFlush();
}
void mouseMove(int mx, int my) {
    if(mx!=curX){
        if(mx>curX){
            angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
        }
        else{
            angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
        }
    }
    if(my!=curY){
        if(my>curY){
            angle1 -= 0.006f;
			ly = sin(angle1);
        }
        else{
            angle1 += 0.006f;
			ly = sin(angle1);
        }
    }
    curX=mx;
    curY=my;
    glutPostRedisplay();
}

void display()
{

    if(slide==0) intro();
    if(slide==1) {outside();;//drawcloud();
    }
    if(slide==2) corridor();
    if(slide==3) bedroom1();
    if(slide==4) bedroom2();
    if(slide==5) controls();
    if(slide==10) kitchen();
    if(slide==15) toilet();


}

int main(int argc,char *argv[])
{
    static GLenum dark=0x4000;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutCreateWindow("House");
	glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	glEnable(GL_NORMALIZE);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

    glutMouseFunc(mousemain);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyboard1);

    glutSpecialFunc(processSpecialKeys);
    glutTimerFunc(200,mytimer,0);
	initLight();

	glutMainLoop();
	return 0;
}
