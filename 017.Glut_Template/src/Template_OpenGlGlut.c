 /***********************************************************
 * A Template for building OpenGL applications using GLUT
 *
 * Author: Perspective @ cprogramming.com
 * Date  : Jan, 2005
 *
 * Description: 
 *   This code initializes an OpenGL ready window
 * using GLUT.  Some of the most common callbacks
 * are registered to empty or minimal functions.
 *
 * This code is intended to be a quick starting point
 * when building GLUT applications.
 *
 ***********************************************************/

//#include <windows.h>
#include <iostream>
#include <GL/glut.h>


/* process menu option 'op' */
void menu(int op) {

  switch(op) {
  case 'Q':
  case 'q':
    exit(0);
  }
}

/* executed when a regular key is pressed */
void keyboardDown(unsigned char key, int x, int y) {

  switch(key) {
  case 'Q':
  case 'q':
  case  27:   // ESC
    exit(0);
  }
}

/* executed when a regular key is released */
void keyboardUp(unsigned char key, int x, int y) {

}

/* executed when a special key is pressed */
void keyboardSpecialDown(int k, int x, int y) {

}

/* executed when a special key is released */
void keyboardSpecialUp(int k, int x, int y) {

}

/* reshaped window */
void reshape(int width, int height) {

  GLfloat fieldOfView = 90.0f;
  glViewport (0, 0, (GLsizei) width, (GLsizei) height);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fieldOfView, (GLfloat) width/(GLfloat) height, 0.1, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* executed when button 'button' is put into state 'state' at screen position ('x', 'y') */
void mouseClick(int button, int state, int x, int y) {

}

/* executed when the mouse moves to position ('x', 'y') */
void mouseMotion(int x, int y) {

}

/* render the scene */
void draw() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* render the scene here */

  glFlush();
  glutSwapBuffers();
}

/* executed when program is idle */
void idle() { 

}

/* initialize OpenGL settings */
void initGL(int width, int height) {

  reshape(width, height);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

/* initialize GLUT settings, register callbacks, enter main loop */
int main(int argc, char** argv) {
  
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Perspective's GLUT Template");

  // register glut call backs
  glutKeyboardFunc(keyboardDown);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(keyboardSpecialDown);
  glutSpecialUpFunc(keyboardSpecialUp);
  glutMouseFunc(mouseClick);
  glutMotionFunc(mouseMotion);
  glutReshapeFunc(reshape);
  glutDisplayFunc(draw);  
  glutIdleFunc(idle);
  glutIgnoreKeyRepeat(true); // ignore keys held down

  // create a sub menu 
  int subMenu = glutCreateMenu(menu);
  glutAddMenuEntry("Do nothing", 0);
  glutAddMenuEntry("Really Quit", 'q');

  // create main "right click" menu
  glutCreateMenu(menu);
  glutAddSubMenu("Sub Menu", subMenu);
  glutAddMenuEntry("Quit", 'q');
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  initGL(800, 600);

  glutMainLoop();
  return 0;
}