
/* Illustration de l'utilisation  */
/* de la souris avec GLUt         */
/* (detection des deplacements)   */


#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

void mouseMotion(int x,int y) {
  printf("Avec bouton : %4d %4d\n",x,y);
}

void mousePassiveMotion(int x,int y) {
  printf("Sans bouton : %4d %4d\n",x,y);
}

void display(void) {
  glClearColor(0.0F,0.0F,0.0F,0.0F) ;
  glClear(GL_COLOR_BUFFER_BIT) ;
  glOrtho(-1.0,1.0,-1.0,1.0,
          -1.0,1.0);
  glColor3f(1.0F,1.0F,1.0F) ;
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
  glutCreateWindow("Deplacements souris") ;
  glutDisplayFunc(display) ;
  glutMotionFunc(mouseMotion) ;
  glutPassiveMotionFunc(mousePassiveMotion) ;
  glutMainLoop() ;
  return(0);
}

