#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init();
void resize(int width, int height);
void display(); // отрисовка всего поля

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Lab2");
  glutReshapeFunc(resize);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

void init() {
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 2, 12);
  gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);
  // gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
}

void resize(int width, int height) {}

GLfloat vertices[][3] = {
    {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0},
    {-1.0, -1.0, 1.0},  {1.0, -1.0, 1.0},  {1.0, 1.0, 1.0},  {-1.0, 1.0, 1.0}};

GLfloat colors[][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0},
                       {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0},
                       {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

void polygon(int a, int b, int c, int d) {
  glBegin(GL_POLYGON);
  glColor3fv(colors[a]);
  glVertex3fv(vertices[a]);
  glColor3fv(colors[b]);
  glVertex3fv(vertices[b]);
  glColor3fv(colors[c]);
  glVertex3fv(vertices[c]);
  glColor3fv(colors[d]);
  glVertex3fv(vertices[d]);
  glEnd();
}
void colorcube() {
  polygon(0, 3, 2, 1);
  polygon(2, 3, 7, 6);
  polygon(0, 4, 7, 3);
  polygon(1, 2, 6, 5);
  polygon(4, 5, 6, 7);
  polygon(0, 1, 5, 4);
}

void display() {
  colorcube();
  glFlush();
}
