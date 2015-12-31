#include <math.h>
#include <GL/glut.h>

float factor = 0.01;

void DrawSine(float factor);

void MyDisplay()
{
Start:
    glClear(GL_COLOR_BUFFER_BIT);
    DrawSine(factor);
    if (factor < 0.1) {
        factor += 0.01;
        sleep(1);
        glFlush();
        goto Start;
    }

    glFlush();
}

void Init()
{
    glColor3f(0.62f, 0.7f, 1.0f);
    //glClearColor(1.0f, 0.5f, 0.0f, 0.6f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void DrawSine(float factor)
{
    //const float factor = 0.1;
    float x;

    glBegin(GL_LINES);
    glVertex2f(-1, 0);
    glVertex2f(1, 0);
    glVertex2f(0, -1);
    glVertex2f(0, 1);
    glEnd();

    glBegin(GL_LINE_STRIP);

    for (x = -1 / factor; x < 1 / factor; x += 0.001) {
        glVertex2f(x * factor, sin(x) * factor);
    }

    glEnd();
    glutSwapBuffers();
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(400, 150);
    glutCreateWindow("Sine");

    Init();
    glutDisplayFunc(MyDisplay);
    glutMainLoop();

    return 0;
}
