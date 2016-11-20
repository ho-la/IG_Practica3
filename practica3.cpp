/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   practica1.cpp
 * Author: chen
 *
 * Created on 10 de octubre de 2016, 11:02
 */
//-lopengl32 -lglu32 -lglew32 -lfreeglut
//https://github.com/ho-la/IG_Practica3.git

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
//Funciones de opengl
void initFunc();
void funReshape(int w, int h);
void funDisplay();
void funKeyboard(int key, int x, int y);
void destroyFunc();
//Funciones de creacion de objetos
void drawTriangulo(char color);
void glDrawSphere(char color,float radio);
void drawCube();
void drawRoom();
void drawLights();
void drawObject(GLfloat s, GLint c);

//Practica 3
void P3Tarea1();
void P3Tarea2();
void P3Tarea3();
// Variables globales
int w = 800;
int h = 500;
GLfloat desZ = -5.0f;
GLfloat rotY =  0.0f;
GLfloat rotX = 0.0f;
GLfloat PL0[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat PL1[] = {-2.0f, 1.0f,-4.0f, 1.0f };
//Si gira de 4h en 4h
GLfloat anio = (360.0/365.0)/6; //365*24 horas
GLfloat dia = (360.0/6.0); //24 horas
GLfloat mes= anio*12;  // Luna gira 12 veces sobre la Tierra en un año

GLfloat RAnio = 0.0f;
GLfloat RDia = 0.0f;
GLfloat RMes=0.0f;

GLfloat T4Girar=0.0f;
GLfloat T4Dezplazar=0.0f;
GLboolean esTarea4=true;

int main(int argc, char** argv) {
    
 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("QiaoLang Chen y Alexey Sorokin");
    
 // Inicializamos GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    printf("This system supports OpenGL Version: %s\n", oglVersion);
    
 // Inicializaciones específicas
    initFunc();
    
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutSpecialFunc(funKeyboard);
      
 // Bucle principal
    glutMainLoop();
    
 // Destrucción de objetos
    destroyFunc();
    
    return(0);
}

void initFunc() {
    
 // Configuracion de etapas del cauce
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    
    GLfloat IA[]  = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, IA);
    
    // Parámetros de la Luz 0 (direccional=sol)
     GLfloat Ia0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
     GLfloat Id0[] = { 0.9f, 0.9f, 0.9f, 1.0f };
     GLfloat Is0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
     glLightfv(GL_LIGHT0, GL_AMBIENT , Ia0);
     glLightfv(GL_LIGHT0, GL_DIFFUSE , Id0);
     glLightfv(GL_LIGHT0, GL_SPECULAR, Is0);
     glEnable(GL_LIGHT0);
     
  // Parámetros de la Luz 1 (posicional=bombilla)
     GLfloat Ia1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
     GLfloat Id1[] = { 0.8f, 0.8f, 0.8f, 1.0f };
     GLfloat Is1[] = { 0.7f, 0.7f, 0.7f, 1.0f };
     glLightfv(GL_LIGHT1, GL_AMBIENT , Ia1);
     glLightfv(GL_LIGHT1, GL_DIFFUSE , Id1);
     glLightfv(GL_LIGHT1, GL_SPECULAR, Is1);
     glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION , 0.90f);
     glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION   , 0.05f);
     glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01f);
     glEnable(GL_LIGHT1);
     
  // Modelo de Sombreado
     glShadeModel(GL_SMOOTH);
    
}

void destroyFunc() {
    
}

void funReshape(int wnew, int hnew) {
    
 // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    
    w = wnew;
    h = hnew;
}

void funDisplay() {
    
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 // Para configurar la matriz matriz P
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    // Proyeccion Ortogonal: 
    //GLfloat left=-4.0, right=4.0, bottom=-4.0, top=4.0, nplane=1.0, fplane=10.0;
    //glOrtho(left, right, bottom, top, nplane, fplane);
  
    //Proyeccion en Frustum
    //GLfloat left=-2.0, right=2.0, bottom=-2.0, top=2.0, nplane=3.0, fplane=10.0;
    //glFrustum(left, right, bottom, top, nplane, fplane);
  

    //En perspectiva
    /**/
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;    
    GLfloat fovy = 50.0f, nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    /**/ 
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V
    
 // Dibujamos los objetos (M)
    //glTranslatef(0.0f, 0.0f, desZ);
    
    GLfloat eye[3]    = {0.0f,  2.0f,  0.0f};
    GLfloat center[3] = {0.0f,  2.0f, -5.0f};
    GLfloat up[3]     = {0.0f,  1.0f,  0.0f};
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                up[0],     up[1],     up[2]);
    //P1tarea1();
    //P1tarea2();
    //P1tarea3();
    //P2Tarea1();
    //glTranslatef(0.0f, 0.0f, -5.0f);
    //glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    drawLights();
    drawRoom();
    drawObject(1.0f,100);
 // Intercambiamos los buffers
    glutSwapBuffers();
}

void drawTriangulo(char color) {  
    switch(color) {
        case 'r':
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 'g':
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 'b':
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        default:
            glColor3f(1.0f, 1.0f, 1.0f);            
    }
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5f, -0.5f, 0.0f); // v1
        glVertex3f( 0.5f, -0.5f, 0.0f); // v2
        glVertex3f( 0.0f,  0.5f, 0.0f); // v3
    glEnd();
    
}

void funKeyboard(int key, int x, int y) {
    if(esTarea4){
        switch(key){
        case GLUT_KEY_UP:
            T4Girar += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            T4Girar  -= 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            T4Dezplazar += 0.1f;
            break;
        case GLUT_KEY_LEFT:
            T4Dezplazar -= 0.1f;
            break;
        default:
            T4Girar = 0.0f;
            T4Dezplazar = 0.0f;
        }
    }
    else{
    switch(key) {
        case GLUT_KEY_UP:
            desZ -= 0.1f;
            break;
        case GLUT_KEY_DOWN:
            desZ += 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            //rotY -= 5.0f;
            RAnio -= anio;
            RDia -= dia;
            RMes -=mes;
            break;
        case GLUT_KEY_LEFT:
            //rotY += 5.0f;
            RAnio += anio;
            RDia += dia;
            RMes +=mes;
            break;
        default:
            desZ = -5.0f;  
            rotY =  0.0f;
    }
    }
    glutPostRedisplay();
    
}

void glDrawSphere(char color,float radio){
    switch(color) {
        //White
        case 'w':
            glColor3f(1.0f, 1.0f, 1.0f);
            break;
        //Yellow    
        case 'y':
            glColor3f(1.0f, 1.0f, 0.0f);
            break;
        //Red
        case 'r':
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        //Green
        case 'g':
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        //Blue
        case 'b':
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        //White
        default:
            glColor3f(1.0f, 1.0f, 1.0f);            
    }
    glutWireSphere(radio,20,20); 
    //(GLdouble radius,GLint slices, GLint stacks); (number of lines)
}

void P3Tarea1() {
    
}
void P3Tarea2() {
     glPushMatrix();
        //Dibujar sol
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('y',2.0f);
        glPopMatrix();
        //Dibujar tierra
        glRotatef(RAnio,0.0f,1.0f,0.0f);
        
        glTranslatef(4.0f,0.0f,0.0f);
        glRotatef(RDia,0.0f,1.0f,0.0f);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('b',0.5f);
        glPopMatrix();
        glRotatef(-RDia,0.0f,1.0f,0.0f);
        //Dibujar luna
        glRotatef(RMes,0.0f,1.0f,0.0f);
        glTranslatef(1.5,0.0,0.0);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('w',0.1f);
        glPopMatrix();
        //incrementar variables
    glPopMatrix();
}
void P3Tarea3() {
    
}

void drawCube() {
     
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 0.8f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
         
  // Definimos el cubo
     glBegin(GL_QUADS);
      // CARA DERECHA (x = 1)
         glVertex3f( 1.0f, -1.0f,  1.0f); 
         glVertex3f( 1.0f, -1.0f, -1.0f);   
         glVertex3f( 1.0f,  1.0f, -1.0f);    
         glVertex3f( 1.0f,  1.0f,  1.0f);   
      // CARA IZQUIERDA (x = -1)
         glVertex3f(-1.0f, -1.0f,  1.0f);
         glVertex3f(-1.0f,  1.0f,  1.0f);
         glVertex3f(-1.0f,  1.0f, -1.0f);
         glVertex3f(-1.0f, -1.0f, -1.0f);
      // CARA SUPERIOR (y = 1)
         glVertex3f( 1.0f,  1.0f,  1.0f);
         glVertex3f( 1.0f,  1.0f, -1.0f);
         glVertex3f(-1.0f,  1.0f, -1.0f); 
         glVertex3f(-1.0f,  1.0f,  1.0f);
      // CARA INFERIOR (y = -1)
         glVertex3f( 1.0f, -1.0f,  1.0f);    
         glVertex3f(-1.0f, -1.0f,  1.0f);
         glVertex3f(-1.0f, -1.0f, -1.0f);    
         glVertex3f( 1.0f, -1.0f, -1.0f);
      // CARA DELANTERA (z = 1)
         glVertex3f(-1.0f, -1.0f,  1.0f);
         glVertex3f( 1.0f, -1.0f,  1.0f);
         glVertex3f( 1.0f,  1.0f,  1.0f);
         glVertex3f(-1.0f,  1.0f,  1.0f);
      // CARA TRASERA (z = -1)
         glVertex3f(-1.0f, -1.0f, -1.0f);
         glVertex3f(-1.0f,  1.0f, -1.0f);
         glVertex3f( 1.0f,  1.0f, -1.0f);  
         glVertex3f( 1.0f, -1.0f, -1.0f);
     glEnd();
     
 }

void drawObject(GLfloat s, GLint c) {
     
  // Definimos el material del objeto
     GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
     GLfloat Kd[] = { 0.7f, 0.7f, 0.3f, 1.0f };
     GLfloat Ks[] = { 0.5f, 0.5f, 0.5f, 1.0f };
     glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
     glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
     glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
     glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
     
  // Definimos el objeto
     glPushMatrix();
         glTranslatef(0.0f, 2.0f, -5.0f);
         glRotatef(rotX, 1.0f, 0.0f, 0.0f);
         glRotatef(rotY, 0.0f, 1.0f, 0.0f);
         glutSolidTeapot(s);
     glPopMatrix();
 
 }

void drawLights() {
    
 // Luz 0: Direccional
    glLightfv(GL_LIGHT0, GL_POSITION, PL0);
    
 // Luz 1: Posicional
    glLightfv(GL_LIGHT1, GL_POSITION, PL1);
    
}

void drawRoom() {
    
 // Definimos el material de la habitación
     GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
     GLfloat Kd[] = { 0.7f, 0.7f, 0.7f, 1.0f };
     GLfloat Ks[] = { 0.8f, 0.8f, 0.8f, 1.0f };
     glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
     glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
     glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
     glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
     
  // Definimos la habitación
     glPushMatrix();
         glTranslatef(0.0f,2.5f,-10.f);
         glScalef(5.0f,2.5f,10.0f);
         
     // SUELO (y = -1)
        glBegin(GL_QUADS);
            glNormal3f( 0.0f,  1.0f,  0.0f);
            glVertex3f(-1.0f, -1.0f,  1.0f);
            glVertex3f( 1.0f, -1.0f,  1.0f);
            glVertex3f( 1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
        glEnd();
 
     // PARED IZQUIERDA (x = -1)
        glBegin(GL_QUADS);
            glNormal3f( 1.0f,  0.0f,  0.0f);
            glVertex3f(-1.0f, -1.0f,  1.0f); 
            glVertex3f(-1.0f, -1.0f, -1.0f);   
            glVertex3f(-1.0f,  1.0f, -1.0f);    
            glVertex3f(-1.0f,  1.0f,  1.0f); 
        glEnd();
 
     // PARED DEL FONDO (z = -1)
        glBegin(GL_QUADS);
            glNormal3f( 0.0f,  0.0f,  1.0f);
            glVertex3f(-1.0f, -1.0f, -0.8f);
            glVertex3f( 1.0f, -1.0f, -0.8f);
            glVertex3f( 1.0f,  1.0f, -0.8f);
            glVertex3f(-1.0f,  1.0f, -0.8f);
        glEnd();
 
     // PARED DERECHA (x = 1)
        glBegin(GL_QUADS);
            glNormal3f(-1.0f,  0.0f,  0.0f);
            glVertex3f( 1.0f, -1.0f, -1.0f);
            glVertex3f( 1.0f, -1.0f,  1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);
            glVertex3f( 1.0f,  1.0f, -1.0f);
        glEnd();
 
     // TECHO (y = 1)
        glBegin(GL_QUADS);
            glNormal3f( 0.0f, -1.0f,  0.0f);
            glVertex3f(-1.0f,  1.0f, -1.0f);  
            glVertex3f( 1.0f,  1.0f, -1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);    
            glVertex3f(-1.0f,  1.0f,  1.0f);
        glEnd();
     
     glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}