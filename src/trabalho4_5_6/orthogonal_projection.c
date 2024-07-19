#include <GL/glut.h>

// gcc orthogonal_projection.c -I"../../include/freeglut/include" -L"../../include/freeglut/lib" -lfreeglut -lopengl32 -lglu32 -o ./out/orthogonal_projection
// ./out/orthogonal_projection

// Desenha um cubo com projeção paralela ortogonal
void desenha_cubo() {
    // Define a cor do cubo
    // glColor3f(0.2f, 0.8f, 1.0f); // Ciano
    glColor3f(1.0f, 1.0f, 1.0f); // Branco

    glBegin(GL_LINES);

    // Face frontal
    glVertex3f(-0.5, -0.5, 0.5);  // A 
    glVertex3f(0.5, -0.5, 0.5);   // B

    glVertex3f(0.5, -0.5, 0.5);   // B 
    glVertex3f(0.5, 0.5, 0.5);    // C

    glVertex3f(0.5, 0.5, 0.5);    // C
    glVertex3f(-0.5, 0.5, 0.5);   // D

    glVertex3f(-0.5, 0.5, 0.5);   // D
    glVertex3f(-0.5, -0.5, 0.5);  // A 

    // Face traseira
    glVertex3f(-0.5, -0.5, -0.5); // E
    glVertex3f(0.5, -0.5, -0.5);  // F

    glVertex3f(0.5, -0.5, -0.5);  // F
    glVertex3f(0.5, 0.5, -0.5);   // G

    glVertex3f(0.5, 0.5, -0.5);   // G
    glVertex3f(-0.5, 0.5, -0.5);  // H

    glVertex3f(-0.5, 0.5, -0.5);  // H
    glVertex3f(-0.5, -0.5, -0.5); // E

    // Arestas conectando as faces
    glVertex3f(-0.5, -0.5, 0.5);  // A
    glVertex3f(-0.5, -0.5, -0.5); // E

    glVertex3f(0.5, -0.5, 0.5);   // B
    glVertex3f(0.5, -0.5, -0.5);  // F

    glVertex3f(0.5, 0.5, 0.5);    // C
    glVertex3f(0.5, 0.5, -0.5);   // G

    glVertex3f(-0.5, 0.5, 0.5);   // D
    glVertex3f(-0.5, 0.5, -0.5);  // H

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Aplica rotações para inclinar o cubo
    glRotatef(30.0, 1.0, 0.0, 0.0); // Rotaciona em torno do eixo X
    glRotatef(30.0, 0.0, 1.0, 0.0); // Rotaciona em torno do eixo Y

    glLineWidth(3);

    // Chama a função para desenhar o cubo
    desenha_cubo();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de fundo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Projeção ortogonal
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition (400, 100);
    glutCreateWindow("Projecao Paralela Ortogonal de um Cubo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
