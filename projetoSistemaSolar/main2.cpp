#include <GL/glut.h>

// Variáveis globais para controlar a animação
float tempoDecorrido = 0.0f;
GLfloat luzBranca[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat luzAmbiente[] = {0.2f, 0.2f, 0.2f, 1.0f};


void luz() {
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    
    //ambiente
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzBranca);
    
    GLfloat posicaoLuz[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);    

    //sol
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzBranca);
    
    GLfloat posicaoLuz1[] = { 0.0f, 1.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
    gluLookAt(0.0, 2.0, 10.0,  
        0.0, 0.0, 0.0,  
        0.0, 1.0, 0.0);
    luz();
    
    float velocidadeBola = 110.0f;
    
	//sol    
    glPushMatrix();       
        glRotatef(tempoDecorrido*velocidadeBola*0.5f, 0.0f, 1.0f, 0.0f);      
        glColor3f(1.0f, 0.5f, 0.0f);                
        glutSolidSphere(0.5, 36, 36); // mudar para glutSolidSphere deixar completo    
    glPopMatrix();

    //mercurio        
    glPushMatrix();        
        glRotatef(tempoDecorrido*velocidadeBola*1.5f, 0.0f, 1.0f, 0.0f); //angulo*velocidade              
        glTranslatef(1.0f, 0.0f, 0.0f);       //o primeiro parametro é a distancia do centro(sol) 
        glColor3f(1.0f, 0.6f, 0.5f);        
        glutSolidSphere(0.1, 36, 36);    //primeiro parametro é o tamanho da esfera
    glPopMatrix();   
    
    //venus    
    glPushMatrix();
        glRotatef(tempoDecorrido*velocidadeBola*1.0f, 0.0f, 1.0f, 0.0f); 
        glTranslatef(1.5f, 0.0f, 0.0f);
        glColor3f(1.0f, 0.3f, 0.0f); 
        glutSolidSphere(0.2, 36, 36);
    glPopMatrix();

    //terra        
    glPushMatrix();       
        glRotatef(tempoDecorrido*velocidadeBola*0.8f, 0.0f, 1.0f, 0.0f);         
        glTranslatef(2.5f, 0.0f, 0.0f);                
        glColor3f(0.0f, 0.0f, 1.0f);                
        glutSolidSphere(0.3, 36, 36);
        
        //lua
        glPushMatrix();
            glRotatef(tempoDecorrido*velocidadeBola, 0.0f, 1.0f, 0.0f);         
            glTranslatef(0.5f, 0.0f, 0.0f);                
            glColor3f(1.0f, 1.0f, 1.0f);                
            glutSolidSphere(0.05, 36, 36);
        glPopMatrix();        
    glPopMatrix();

    //marte        
    glPushMatrix();        
        glRotatef(tempoDecorrido*velocidadeBola*0.5f, 0.0f, 1.0f, 0.0f);      
        glTranslatef(3.5f, 0.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);                
        glutSolidSphere(0.4, 36, 36);    
    glPopMatrix();



    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void inicializa() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}


void atualizaAnimacao(int valor) {
    tempoDecorrido = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

    glutPostRedisplay();

    glutTimerFunc(16, atualizaAnimacao, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(900, 700);
    glutCreateWindow("Animacao com OpenGL e GLUT");
    
    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutTimerFunc(16, atualizaAnimacao, 0);
    
    glutMainLoop();
    
    return 0;
}