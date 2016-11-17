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

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void drawTriangulo(char color);
void funKeyboard(int key, int x, int y);
void destroyFunc();

void drawOurNumber();
void glDrawSphere(char color,float radio);
//Práctica1
void P1tarea1();
void P1tarea2();
void P1tarea3();
void P1drawPieza();
//Práctica2
void P2Tarea1();
void P2Tarea2();
void P2Tarea3();
void P2Tarea4();
// Variables globales
int w = 800;
int h = 500;
GLfloat desZ = -5.0f;
GLfloat rotY =  0.0f;

//Si gira de 1h en 1h
GLfloat anio = (360.0/365.0)/24; //365*24 horas
GLfloat dia = (360.0/24.0); //24 horas
GLfloat mes= anio*12;  // Luna gira 12 veces sobre a Tierra en un año

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
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    
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
    glTranslatef(0.0f, 0.0f, desZ);
    glTranslatef(0.0f, 0.0f, -5.0f);
    //P1tarea1();
    //P1tarea2();
    //P1tarea3();
    P2Tarea1();
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
/****************************************************************************************************/
//Our number is 9
void drawOurNumber() { 
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 3.0f, 0.0f); // v1
        glVertex3f( 3.0f, 3.0f, 0.0f); // v2
        glVertex3f(3.0f, -2.0f, 0.0f); // v12
        glVertex3f(0.0f, -2.0f, 0.0f); // v11
        glVertex3f(0.0f, -1.0f, 0.0f); // v9
        glVertex3f(2.0f, -1.0f, 0.0f); // v10
        glVertex3f(2.0f, 0.0f, 0.0f); // v8
        glVertex3f(0.0f, 0.0f, 0.0f); // v7   
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f,  2.0f, 0.0f); // v3
        glVertex3f(2.0f, 2.0f, 0.0f); // v4
        glVertex3f(2.0f, 1.0f, 0.0f); // v6
        glVertex3f(1.0f, 1.0f, 0.0f); // v5
    glEnd();
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
void P1tarea1(){
    //Dibuja nuestro número
    glPushMatrix(); 
        //Grosor de las rayas
        glLineWidth(5.0);
        //Ajuste
        glScalef(0.3f, 0.3f, 0.3f);
        glTranslatef( -1.5f, -0.5f, 0.0f);
        drawOurNumber();
    glPopMatrix();
    //Dibuja esfera amarilla
    glPushMatrix();
        glLineWidth(1.0);
        glRotatef(50,0.0f,1.0f,0.0f);
        glDrawSphere('y',2.0f);
    glPopMatrix();
    
    glRotatef(RAnio,0.0f,1.0f,0.0f);
}
void P1tarea2(){
    //Dbujamos el sol y el número
    P1tarea1();
    glPushMatrix(); 
        glLineWidth(1.0);
        glTranslatef(4.0f, 0.0f, 0.0f);
        //glRotatef(rotY,0.0f,1.0f,0.0f);
        glRotatef(RMes,0.0f,1.0f,0.0f);
        //Dibujamos la Tierra
        glPushMatrix();    
            glRotatef(RDia,0.0f,1.0f,0.0f);
            glDrawSphere('b',0.5f);
        glPopMatrix(); 
            glLineWidth(1.0);
            glTranslatef(1.5f, 0.0f, 0.0f);
        glPushMatrix();    
            //Dibujamos la luna
            glDrawSphere('w',0.1f);
        glPopMatrix();
    glPopMatrix();
}
void P1tarea3(){
    glPushMatrix();
        P1drawPieza();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.5f, 3.5f, 0.0f);
        glRotatef(-90,0.0f,0.0f,1.0f);
        P1drawPieza();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.0f, 1.5f, 0.0f);
        glRotatef(-90,0.0f,0.0f,1.0f);
        P1drawPieza();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(3.0f, 0.0f, 0.0f);
        P1drawPieza();
    glPopMatrix();
}
void P1drawPieza(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f( 0.0, 0.0, 0.0);
        glVertex3f( 1.0, 0.0, 0.0);        
        glVertex3f( 1.0, 3.0, 0.0);
        glVertex3f( 0.0, 3.0, 0.0);
    glEnd();
}
void P2Tarea1(){
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
void P2Tarea2(){
    glPushMatrix();
        //Dibujar sol
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('y',2.0f);
        glPopMatrix();
        //Dibujar tierra
        glRotatef(-30,0.0f,0.0f,1.0f);
        glRotatef(RAnio,0.0f,1.0f,0.0f);
        glTranslatef(4.0f,0.0f,0.0f);
        glRotatef(RDia,0.0f,1.0f,0.0f);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('b',0.5f);
        glPopMatrix();
        glRotatef(-RDia,0.0f,1.0f,0.0f);
        //Dibujar luna
        glRotatef(45,0.0f,0.0f,1.0f);
        glRotatef(RMes,0.0f,1.0f,0.0f);
        glTranslatef(1.5,0.0,0.0);
        glPushMatrix();
            glRotatef(90,1.0f,0.0f,0.0f);
            glDrawSphere('w',0.1f);
        glPopMatrix();
    glPopMatrix();
}
void P2Tarea3(){
    
}
void P2Tarea4(){
    glPushMatrix();
        glTranslatef(2.5f,0.0f,0.0f);
        glRotatef(T4Girar,0.0f,0.0f,1.0f);
        glRotatef(-90,0.0f,0.0f,1.0f);
        glPushMatrix();
            glTranslatef(-0.5f,-0.5f,0.0f);
            glColor3f(1.0f, 0.0f, 1.0f);
            P1drawPieza();
        glPopMatrix();
        glPushMatrix();
            glRotatef(90,0.0f,0.0f,1.0f);
            glTranslatef(T4Dezplazar,0.0f,0.0f);
            glTranslatef(2.5f,0.25f,0.0f);
            glScalef(0.5f,0.5f,1.0f);
            glRotatef(-90,0.0f,0.0f,1.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            P1drawPieza();
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.5f,0.5f,0.0f);
        glRotatef(-90,0.0f,0.0f,1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        P1drawPieza();
    glPopMatrix();
    esTarea4=true;
}