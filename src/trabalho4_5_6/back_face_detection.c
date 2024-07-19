#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

// gcc back_face_detection.c -I"../../include/freeglut/include" -L"../../include/freeglut/lib" -lfreeglut -lopengl32 -lglu32 -o ./out/back_face_detection
// ./out/back_face_detection

// Coordenadas dos vértices do cubo (8 vértices)
float vertices[8][3] = {
    {-0.5, -0.5,  0.5}, // A
    { 0.5, -0.5,  0.5}, // B
    { 0.5,  0.5,  0.5}, // C
    {-0.5,  0.5,  0.5}, // D
    {-0.5, -0.5, -0.5}, // E
    { 0.5, -0.5, -0.5}, // F
    { 0.5,  0.5, -0.5}, // G
    {-0.5,  0.5, -0.5}  // H
};

// Indices das faces do cubo (6 faces, cada uma com 4 vértices)
int faces[6][4] = {
    {0, 1, 2, 3}, // Face frontal
    {1, 5, 6, 2}, // Face lateral direita
    {5, 4, 7, 6}, // Face traseira
    {4, 0, 3, 7}, // Face lateral esquerda
    {3, 2, 6, 7}, // Face superior
    {4, 5, 1, 0}  // Face inferior
};


// Função que calcula o produto vetorial de dois vetores
// O produto vetorial é usado para encontrar uma normal perpendicular a um plano definido por dois vetores
void produto_vetorial(float* a, float* b, float* result) {
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

// Função que calcula o produto escalar de dois vetores
// O produto escalar é usado para determinar a orientação relativa entre dois vetores
float produto_escalar(float* a, float* b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

// Função que calcula a normal de uma face do cubo
// A normal é um vetor perpendicular à face, calculada usando o produto vetorial de dois vetores da face
void calcula_normal(float* v0, float* v1, float* v2, float* normal) {
    float u[3], v[3];
    for (int i = 0; i < 3; i++) {
        u[i] = v1[i] - v0[i];
        v[i] = v2[i] - v0[i];
    }
    produto_vetorial(u, v, normal);
}

// Função que verifica se uma face do cubo é uma back-face
// Uma face é considerada uma back-face se o vetor normal estiver voltado para o observador
bool verifica_back_face(float* v0, float* v1, float* v2, float* observerPosition) {
    float normal[3];
    calcula_normal(v0, v1, v2, normal);

    float viewVector[3];
    for (int i = 0; i < 3; i++) {
        viewVector[i] = observerPosition[i] - v0[i];
    }

    // Retorna true se a face estiver voltada para longe do observador (back-face)
    return produto_escalar(normal, viewVector) >= 0;
}

// Função para desenhar o cubo
void desenha_cubo() {
    float observerPosition[3] = {0.0, 0.0, -2.0}; // Posição do observador (câmera)
    
    glBegin(GL_QUADS); // Início da definição das faces do cubo
    
    for (int i = 0; i < 6; i++) {
        float* v0 = vertices[faces[i][0]];
        float* v1 = vertices[faces[i][1]];
        float* v2 = vertices[faces[i][2]];
        float* v3 = vertices[faces[i][3]];
        
        // Verifica se a face é uma back-face e a descarta se for o caso
        if (!verifica_back_face(v0, v1, v2, observerPosition)) {
            // Define a cor da face com base no índice da face
            glColor3f(0.2f + 0.1f * i, 0.8f - 0.1f * i, 1.0f - 0.1f * i);
            // Especifica os vértices da face
            glVertex3fv(v0);
            glVertex3fv(v1);
            glVertex3fv(v2);
            glVertex3fv(v3);
        }
    }
    
    glEnd(); // Fim da definição das faces do cubo
}

// Função de exibição
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Aplica translação para posicionar a câmera
    glTranslatef(0.0, 0.0, -2.0);
    
    // Aplica rotações para inclinar o cubo
    glRotatef(30.0, 1.0, 0.0, 0.0); // Rotaciona em torno do eixo X
    glRotatef(30.0, 0.0, 1.0, 0.0); // Rotaciona em torno do eixo Y
    
    // Chama a função para desenhar o cubo
    desenha_cubo();
    
    glutSwapBuffers();
}

// Função de inicialização
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Projecao com Back-Face Detection de um Cubo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
