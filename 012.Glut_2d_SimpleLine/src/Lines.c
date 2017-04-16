
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
/*ne marche pas
 * pour eviter la fenetre glut, ajouter -mwindows aux options...
 ============================================================================
 Name        : SimpleLine.c
 Author      : ms
 Version     :
 Copyright   : 
 Description : GL line in C, Ansi-style
 ============================================================================
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


/*
 ============================================================================
 voir Note (1)
 ============================================================================
*/

float f1, f2, f3, f4;
FILE *fp;

void readfile (void)
{
	if 
	( (fp = fopen("coordonees.txt", "r")) == NULL)
		{
		fprintf(stderr, "Error opening file.\n");
		exit(1);
		}
	
fscanf(fp, "%f %f %f %f", &f1, &f2, &f3, &f4);
fclose(fp);
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
/* select white for all lines  */
   
   glColor3f (1.0, 1.0, 1.0);
   glLineWidth (1.0);
   
   glBegin(GL_LINES);  
      	glVertex2f (f1, f2); 
   		glVertex2f (f3, f4); 
      glEnd();

   glLineWidth (5.0);
   
   glBegin(GL_LINES);  
       	glVertex2f (50.0, 100.0); 
    		glVertex2f (350.0, 100.0); 
       glEnd();
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0) ;
         break;
      default:
         readfile();
         display();
   }
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (400, 150); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   readfile();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
