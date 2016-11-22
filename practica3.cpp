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
void funIdle();

void myObject();
void vboObject();
void raton (int button, int state, int x, int y);
void destroyFunc();
void moveMouse(int x,int y);
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
//Tarea2
GLfloat T2PL0[] = { -20.0f, 1.0f, 1.0f, 0.0f };
GLfloat T2PL1[] = {-2.0f, 1.0f,-4.0f, 1.0f };
GLfloat T2PL2[] = { 1.0f, 1.0f, 1.0f, 0.0f };
//Si gira de 4h en 4h
GLfloat anio = (360.0/365.0)/6; //365*24 horas
GLfloat dia = (360.0/6.0); //24 horas
GLfloat mes= anio*12;  // Luna gira 12 veces sobre la Tierra en un año

GLfloat RAnio = 0.0f;
GLfloat RDia = 0.0f;
GLfloat RMes=0.0f;

GLfloat T4Girar=0.0f;
GLfloat T4Dezplazar=0.0f;
GLboolean esTarea1;
GLfloat giroVertical=0.0f;
GLboolean anima=true;
GLboolean hacerZoom=true;
GLfloat zoom = -10.0f;
int iniX;
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
    glutMouseFunc(raton);
    glutMotionFunc(moveMouse);
    glutIdleFunc(funIdle); 
      
 // Bucle principal
    glutMainLoop();
    
 // Destrucción de objetos
    destroyFunc();
    
    return(0);
}

void initFunc() {
    
 // Configuracion de etapas del cauce
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
        //Luz ambientar inicial
        //GLfloat IA[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat IA[]  = { 0.9f, 0.9f, 0.9f, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, IA);
    if(esTarea1){
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
         glShadeModel(GL_SMOOTH);
    }
    else{
        
        GLfloat T2Ia0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat T2Id0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat T2Is0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        glLightfv(GL_LIGHT2,GL_AMBIENT,T2Ia0);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,T2Id0);
        glLightfv(GL_LIGHT2,GL_SPECULAR,T2Is0);
        glEnable(GL_LIGHT2);
        
        glEnable(GL_CULL_FACE);
        glShadeModel(GL_FLAT);
    }
  // Modelo de Sombreado
     
     
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

    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;    
    GLfloat fovy = 50.0f, nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);

 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V
    
 // Dibujamos los objetos (M)
    //glTranslatef(0.0f, 0.0f, desZ);
    if(esTarea1){
        GLfloat eye[3]    = {0.0f,  2.0f,  0.0f};
        GLfloat center[3] = {0.0f,  2.0f, -5.0f};
        GLfloat up[3]     = {0.0f,  1.0f,  0.0f};
        gluLookAt(    eye[0],    eye[1],    eye[2],
                   center[0], center[1], center[2],
                    up[0],     up[1],     up[2]);
    }
    else{
        glTranslatef(0.0f,0.0f, zoom);
        glRotatef(giroVertical,1.0f,0.0f,0.0f);
    }
    //P3Tarea1();
    P3Tarea2();
    //P3Tarea3();
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
    if(esTarea1){
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
        if(anima==true)
         switch(key) {
             case GLUT_KEY_F1:
                 anima = false;
                 break;
        }    
        else{
            switch(key){
                case GLUT_KEY_F1:
                    anima = true;
                    break;
                case GLUT_KEY_RIGHT:
                    //rotY -= 5.0f;
                    RAnio--;
                    RDia -= 365;
                    RMes -= 12;
                    break;
                case GLUT_KEY_LEFT:
                    //rotY += 5.0f;
                    RAnio++;
                    RDia += 365;
                    RMes +=12;
                    break;
            }
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
            glColor3f(1.0f, 1.0f, 0.0f);            
    }
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    glutSolidSphere(radio,20,20);
    //glutWireSphere(radio,20,20); 
    //(GLdouble radius,GLint slices, GLint stacks); (number of lines)
}

void funIdle() {
    if(anima){
        RAnio += anio;
        RDia += dia;
        RMes += mes;
    }   
    Sleep(10);   
    glutPostRedisplay();  
}

void raton (int button, int state, int x, int y){
    if(!esTarea1){
        switch(button){
            case GLUT_LEFT_BUTTON:
                //gluLookAt(0,0,1,0,0,-5,0,1,0);
                if(state == GLUT_DOWN)
                    iniX=y;
                /*if(state == GLUT_UP)
                    giroVertical += (x-iniX)*10;
                */  
                    break;
            //Rueba arriba
            case 3:
                if (zoom<-7)
                    zoom+=1;
                break;
            //Rueda abajo    
            case 4:
                if (zoom>-17)
                    zoom-=1;
                break;
        }        
    }
    glutPostRedisplay();
}
void moveMouse(int x,int y){
    if(!esTarea1){
        giroVertical = (GLfloat)(y - iniX);
    }
    //angulo =(GLfloat)  -(y-300)/10;
    glutPostRedisplay();
}

void P3Tarea1() {
    drawLights();
    drawRoom();
    drawObject(1.0f,100);
    esTarea1=true;
}
void P3Tarea2() {
        /*
        1. Colocar una tenue luz ambiental para iluminar la imagen globalmente (esta luz ambiental se puede
            aumentar con la tecla + y disminuir con la tecla -).
        2. Colocar una fuente de luz intensa en el sol.
        3. Añadir un tono amarillo al Sol, azul a la Tierra y blanco a la Luna.
        4. Transformar la luna en una nueva estrella haciendo que se encienda y apague con la tecla E.
        */
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
    esTarea1=false;
}
void P3Tarea3() {
    /*añadir las texturas del Sol, Tierra y Luna*/
    esTarea1=false;
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
    if(esTarea1){
 // Luz 0: Direccional
    glLightfv(GL_LIGHT0, GL_POSITION, PL0);
 // Luz 1: Posicional
    glLightfv(GL_LIGHT1, GL_POSITION, PL1);
    }
    else{
        glLightfv(GL_LIGHT2, GL_POSITION, T2PL0);
        //glLightfv(GL_LIGHT3, GL_POSITION, T2PL1);
    }
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