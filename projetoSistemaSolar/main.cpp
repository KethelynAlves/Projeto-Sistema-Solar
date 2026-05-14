#include <GL/glut.h>
#include <math.h>

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
    
    GLfloat posicaoLuz1[] = { 0.0f, 1.0f, 3.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
}

void desenhaOrbita(float raio) {
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float angulo = 2.0f * M_PI * i / 100.0f;
        glVertex3f(cos(angulo) * raio, 0.0f, sin(angulo) * raio);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
    gluLookAt(0.0, 2.0, 10.0,  
        0.0, 0.0, 0.0,  
        0.0, 1.0, 0.0);
    luz();
    
    float velocidadeBola = 110.0f;
    
    float distaciaBola[] ={1.0f, 1.7f, 2.7f, 3.7f}; //mercurio, venus, terra, marte

    desenhaOrbita(distaciaBola[0]);
    desenhaOrbita(distaciaBola[1]);
    desenhaOrbita(distaciaBola[2]);
    desenhaOrbita(distaciaBola[3]);
        

	//sol    
    glPushMatrix();       
        glRotatef(tempoDecorrido*velocidadeBola*0.5f, 0.0f, 1.0f, 0.0f);      
        glColor3f(1.0f, 1.0f, 0.0f);          
        
        GLfloat emissaoSol[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, emissaoSol);
               
        glutSolidSphere(0.5, 36, 36); 
        
        glDepthMask(GL_FALSE);
        
        glColor4f(1.0f, 0.9f, 0.0f, 0.2f);
        glutSolidSphere(0.53, 36, 36);
        glColor4f(1.0f, 0.9f, 0.0f, 0.1f);
        glutSolidSphere(0.55, 36, 36);
        
        // Reativa o Depth Buffer e limpa emissão para os outros planetas
        glDepthMask(GL_TRUE);
        GLfloat semEmissao[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, semEmissao);
    
    glPopMatrix();

    //mercurio        
    glPushMatrix();        
        glRotatef(tempoDecorrido*velocidadeBola*1.5f, 0.0f, 1.0f, 0.0f); //angulo*velocidade              
        glTranslatef(distaciaBola[0], 0.0f, 0.0f);
        glColor3f(1.0f, 0.6f, 0.2f);        
        glutSolidSphere(0.13, 36, 36);//primeiro parametro é o tamanho da esfera
    glPopMatrix();   
    
    //venus    
    glPushMatrix();
        glRotatef(tempoDecorrido*velocidadeBola*1.0f, 0.0f, 1.0f, 0.0f); 
        glTranslatef(distaciaBola[1], 0.0f, 0.0f);
        glColor3f(1.0f, 0.3f, 0.0f); 
        glutSolidSphere(0.25, 36, 36);
    glPopMatrix();

    //terra        
    glPushMatrix();       
        glRotatef(tempoDecorrido*velocidadeBola*0.8f, 0.0f, 1.0f, 0.0f);         
        glTranslatef(distaciaBola[2], 0.0f, 0.0f);                
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
        glTranslatef(distaciaBola[3], 0.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);                
        glutSolidSphere(0.16, 36, 36);    
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
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void atualizaAnimacao(int valor) {
    tempoDecorrido = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

    glutPostRedisplay();

    glutTimerFunc(16, atualizaAnimacao, 0);
}

void tecladoNormal(unsigned char key, int x, int y) {
    if (key == 27) { 
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(900, 700);
    glutCreateWindow("Animacao com OpenGL e GLUT");
    
    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(tecladoNormal);
    
    glutTimerFunc(16, atualizaAnimacao, 0);
    
    glutMainLoop();
    
    return 0;
}
