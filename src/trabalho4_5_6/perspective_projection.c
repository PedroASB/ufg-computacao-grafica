#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

// gcc perspective_projection.c -I"../../include/freeglut/include" -L"../../include/freeglut/lib" -lfreeglut -lopengl32 -lglu32 -lm -o ./out/perspective_projection
// ./out/perspective_projection

#define LINE_WIDTH 3

// Vértices do cubo
float vertices[8][3] = {{50, 50, 0}, {100, 50, 0}, {100, 100, 0},
                        {50, 100, 0}, {50, 100, 50}, {100, 100, 50},
                        {100, 50, 50}, {50, 50, 50}};

// Posição do observador ("ponto de fuga")
float observer[3] = {120, 340, 400};


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glOrtho(0, 512, 0, 512, -1 ,1);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            vertices[i][j] *= 2.9;
}

// Desenha uma face de um cubo
void desenha_face(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float p4x, float p4y, int cor) {
    glBegin(GL_LINE_LOOP);
    // glColor3f(cor ? 0.0 : 1.0, cor ? 0.0 : 0.0, cor ? 1.0 : 0.0);
    glColor3f(1.0, 1.0, 1.0);

    // Desenha as linhas, formando a face
    glVertex2f(p1x, p1y);
    glVertex2f(p2x, p2y);
    glVertex2f(p3x, p3y);
    glVertex2f(p4x, p4y);
    glEnd();
}

// Desenha 4 arestas conectando as duas faces do cubo
void conecta_faces(float* vertices) {
    // glColor3f(0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES);
    glVertex2f(vertices[0], vertices[1]);
    glVertex2f(vertices[14], vertices[15]);

    glVertex2f(vertices[2], vertices[3]);
    glVertex2f(vertices[12], vertices[13]);

    glVertex2f(vertices[4], vertices[5]);
    glVertex2f(vertices[10], vertices[11]);

    glVertex2f(vertices[6], vertices[7]);
    glVertex2f(vertices[8], vertices[9]);
    glEnd();
}


/**
 * Calcula o ponto de interseção da linha formada pelo ponto P (xp, yp, zp) e
 * o ponto O(xo, yo, zo), o ponto do observador. Essas coordenadas então são adicionadas
 * ao vetor de vértices passado como parâmetro
 */
void intersecao(int xp, int yp, int zp, int xo, int yo, int zo, int d, int vertex_index, float* vertices_vector) {    
    // Calcula o ponto de interseção
    float t = (((float) d - (float) zp) / ((float) zo - (float) zp));
    float x = xp + t * (xo - xp);
    float y = yp + t * (yo - yp);

    // Adiciona o ponto de interseção ao vetor especificado
    vertices_vector[vertex_index*2] = x;
    vertices_vector[vertex_index*2+1] = y;
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    int k = 100; // Parâmetro

    // Recalcula os vértices em relação à perspectiva
    float persp_vertices[16];
    for (int i = 0; i < 8; i++)
        intersecao(vertices[i][0], vertices[i][1], vertices[i][2], k, observer[1], observer[2], 30, i, persp_vertices);

    // Ajusta a espessura da linha
    glLineWidth(LINE_WIDTH);
    
    // Desenha a primeira face
    desenha_face(persp_vertices[0], persp_vertices[1], persp_vertices[2],  persp_vertices[3], 
            persp_vertices[4], persp_vertices[5], persp_vertices[6], persp_vertices[7], 1);

    // Desenha a segunda face
    desenha_face(persp_vertices[8], persp_vertices[9], persp_vertices[10], persp_vertices[11], persp_vertices[12], 
            persp_vertices[13], persp_vertices[14], persp_vertices[15], 0);

    // Conecta as duas faces
    conecta_faces(persp_vertices);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                              
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (512, 512);           
    glutInitWindowPosition (400, 200);                  
    glutCreateWindow ("Projecao Perspectiva de um Cubo");  
    init();
    glutDisplayFunc(display);
    glutMainLoop();   
}