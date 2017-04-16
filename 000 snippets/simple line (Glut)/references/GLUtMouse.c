
/* Illustration de l'utilisation          */
/* de la souris avec GLUt                 */
/* (detection des clics                   */
/*  et determination de leurs positions)  */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>

static int c = 0 ;

void mouse(int bouton,int etat,int x,int y) {
  if ( etat == GLUT_DOWN )
    switch ( bouton ) {
      case GLUT_LEFT_BUTTON  : c = (c+1)%7;
                               printf("%4d %4d\n",x,y); 
                               glutPostRedisplay();
                               break ;
      case GLUT_RIGHT_BUTTON : exit(0);
                               break; }
}

void display(void) {
  glClearColor(0.0F,0.0F,0.0F,0.0F) ;
  glClear(GL_COLOR_BUFFER_BIT) ;
  glOrtho(-1.0,1.0,-1.0,1.0,
          -1.0,1.0);
  switch(c) {
    case 0 : glColor3f(1.0F,1.0F,1.0F) ;
             break ;
    case 1 : glColor3f(1.0F,1.0F,0.0F) ;
             break ;
    case 2 : glColor3f(1.0F,0.0F,1.0F) ;
             break ;
    case 3 : glColor3f(0.0F,1.0F,1.0F) ;
             break ;
    case 4 : glColor3f(0.0F,1.0F,0.0F) ;
             break ;
    case 5 : glColor3f(0.0F,0.0F,1.0F) ;
             break ;
    case 6 : glColor3f(1.0F,0.0F,0.0F) ;
             break ; }
  glBegin(GL_POLYGON) ;
  glVertex2f(-0.5F,-0.5F) ;
  glVertex2f(-0.5F,0.5F) ;
  glVertex2f(0.5F,0.5F) ;
  glVertex2f(0.5F,-0.5F) ;
  glEnd() ;
  glFlush() ;
}

int main(int argc,char **argv) {
  glutInit(&argc,argv);
  glutInitWindowSize(200,200);
  glutInitWindowPosition(100,100);
  glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
  glutCreateWindow("Clics de souris") ;
  glutDisplayFunc(display) ;
  glutMouseFunc(mouse) ;
  glutMainLoop() ;
  return(0);
}

