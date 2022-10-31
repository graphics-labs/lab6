#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

bool IS_LEFT_BTN_PRESSED = false;
GLdouble CAMERA_X, CAMERA_Y, CAMERA_Z;

double RADIUS = 10;

double YZ_ANGLE = 0;
double ZX_ANGLE = 0;

int TEMP = 0;

double PREV_MOUSE_X_POS, PREV_MOUSE_Y_POS;
double CURR_MOUSE_X_POS, CURR_MOUSE_Y_POS;

void init();
void resize(int width, int height);
void display();  // отрисовка всего поля
void OnMouse(int, int, int, int);
void OnMouseMotion(int, int);

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Lab4");

  glutMouseFunc(OnMouse);
  glutMotionFunc(OnMouseMotion);

  glutDisplayFunc(display);
  glutPostRedisplay();
  glutIdleFunc(display);

  glutReshapeFunc(resize);

  init();

  glutMainLoop();
  return 0;
}

void OnMouse(int button, int state, int x, int y) {
  IS_LEFT_BTN_PRESSED = state == GLUT_LEFT_BUTTON;

  CURR_MOUSE_X_POS = PREV_MOUSE_X_POS = x;
  CURR_MOUSE_Y_POS = PREV_MOUSE_Y_POS = y;

  TEMP += 2;
}

void OnMouseMotion(int x, int y) {
  PREV_MOUSE_X_POS = CURR_MOUSE_X_POS;
  PREV_MOUSE_Y_POS = CURR_MOUSE_Y_POS;
  CURR_MOUSE_X_POS = x;
  CURR_MOUSE_Y_POS = y;

  YZ_ANGLE += (CURR_MOUSE_Y_POS - PREV_MOUSE_Y_POS) / WINDOW_HEIGHT;
  ZX_ANGLE += (CURR_MOUSE_X_POS - PREV_MOUSE_X_POS) / WINDOW_WIDTH;

  if (YZ_ANGLE > M_PI) {
    YZ_ANGLE = M_PI;
  }

  if (YZ_ANGLE < 0) {
    YZ_ANGLE = 0;
  }

  if (ZX_ANGLE > M_PI * 2) {
    ZX_ANGLE = 0;
  }

  if (ZX_ANGLE < -M_PI * 2) {
    ZX_ANGLE *= -1;
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 2, 20);

  double a = cos(YZ_ANGLE);

  gluLookAt(0, 2, 5, 0, 0, 0, 0, 1, 0);
  // gluLookAt(RADIUS * sin(M_PI - YZ_ANGLE) * cos(ZX_ANGLE),
  //           RADIUS * sin(M_PI - YZ_ANGLE) * sin(ZX_ANGLE),
  //           RADIUS * cos(M_PI - YZ_ANGLE), 0, 0, 0, 0, 1, 0);
  gluLookAt(RADIUS * sin(YZ_ANGLE) * sin(ZX_ANGLE), RADIUS * cos(YZ_ANGLE),
            RADIUS * sin(YZ_ANGLE) * cos(ZX_ANGLE), 0, 0, 0, 0, 1, 0);

  // printf("%f, %f\n", RADIUS * cos(YZ_ANGLE), RADIUS * sin(YZ_ANGLE));

  glMatrixMode(GL_MODELVIEW);
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
  glFrustum(-1, 1, -1, 1, 2, 20);
  gluLookAt(RADIUS, RADIUS, RADIUS, 0, 0, 0, 0, 1, 0);
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  colorcube();

  // glPopMatrix();

  glutSwapBuffers();
}
