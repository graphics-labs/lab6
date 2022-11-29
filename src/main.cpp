#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_WIDTH = 800
#define WINDOW_HEIGHT = 800

//GLfloat mat_ambient[] = { 0.0, 0.1, 0.06};
//GLfloat mat_diffuse[] = { 0.0, 0.50980392, 0.50980392};
//GLfloat mat_specular[] = { 0.50196078,	0.50196078,	0.50196078};
//GLfloat mat_shininess[] = { 0.25 * 128.0 };


GLfloat mat_ambient[] = { 0.2125, 0.1275, 0.054 };
GLfloat mat_diffuse[] = { 0.714, 0.4284, 0.18144 };
GLfloat mat_specular[] = { 0.393548, 0.271906, 0.166721 };
GLfloat mat_shininess[] = { 0.2 * 128.0 };

GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };



void init(void);
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void enable_background_light();
void enable_pointer_light_source();
void enable_remote_light_source();
void enable_projector();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // enable_background_light();
    // enable_pointer_light_source();
    enable_remote_light_source();
    // enable_projector();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

}

void enable_background_light()
{
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

void enable_pointer_light_source()
{
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void enable_remote_light_source()
{
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void enable_projector()
{
    glLightf(GL_SPOT_DIRECTION, GL_SPOT_EXPONENT, GL_SPOT_CUTOFF);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.8, 0.5, 0.2);

    glutSolidSphere(1, 100, 100);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
            1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
            1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}
