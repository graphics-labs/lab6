#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 800

double RADIUS = 10;
double YZ_ANGLE = M_PI / 4;
double ZX_ANGLE = 0;

GLfloat VERTICES[][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, 
                         {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0},  {1.0, -1.0, 1.0},  
                         {1.0, 1.0, 1.0},  {-1.0, 1.0, 1.0}};

GLfloat COLORS[][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0},
                       {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0},
                       {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

void init();
void resize(int, int);
void display();
void resize(int, int);

double getXEye();

double getYEye();
double getZEye();

void setCameraPosition();
void OnKeyboard(int, int, int);

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Lab4");

  glutSpecialFunc(OnKeyboard);

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(resize);

  init();
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
}

void resize(int width, int height) {}

void setCameraPosition() {
  double a = cos(YZ_ANGLE);
  gluLookAt(
    getXEye(), getYEye(), getZEye(),
    0, 0, 0,
    0, YZ_ANGLE < 0 || YZ_ANGLE > M_PI ? -1 : 1, 0
  );
}

double getXEye() { return RADIUS * sin(YZ_ANGLE) * sin(ZX_ANGLE); }

double getYEye() { return RADIUS * cos(YZ_ANGLE); }

double getZEye() { return RADIUS * sin(YZ_ANGLE) * cos(ZX_ANGLE); }

void OnKeyboard(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
    YZ_ANGLE -= M_PI / 10;
  }

  if (key == GLUT_KEY_DOWN) {
    YZ_ANGLE += M_PI / 10;
  }

  if (key == GLUT_KEY_LEFT) {
    ZX_ANGLE -= M_PI / 10;
  }

  if (key == GLUT_KEY_RIGHT) {
    ZX_ANGLE += M_PI / 10;
  }

  if (YZ_ANGLE > M_PI) {
    YZ_ANGLE = -M_PI;
  }

  if (YZ_ANGLE < -M_PI) {
    YZ_ANGLE = M_PI;
  }

  if (ZX_ANGLE > M_PI * 2) {
    ZX_ANGLE = 0;
  }

  if (ZX_ANGLE < -M_PI * 2) {
    ZX_ANGLE = -1;
  }
}

void polygon(int a, int b, int c, int d) {
  glBegin(GL_POLYGON);
  glColor3fv(COLORS[a]);
  glVertex3fv(VERTICES[a]);
  glColor3fv(COLORS[b]);
  glVertex3fv(VERTICES[b]);
  glColor3fv(COLORS[c]);
  glVertex3fv(VERTICES[c]);
  glColor3fv(COLORS[d]);
  glVertex3fv(VERTICES[d]);
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3, 3, -3, 3, 2, 20);
    

  setCameraPosition();
  glMatrixMode(GL_MODELVIEW);

  colorcube();

  glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 2, 20);
  setCameraPosition();
  glMatrixMode(GL_MODELVIEW);

  colorcube();

  glutSwapBuffers();
}
