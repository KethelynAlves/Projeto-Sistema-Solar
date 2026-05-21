#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>

//para rodar no terminal g++ main.cpp -lGL -lGLU -lglut -o temp.out

// Variáveis globais para controlar a animação e interações
float tempoDecorrido = 0.0f;
GLfloat luzBranca[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat luzAmbiente[] = {0.1f, 0.1f, 0.1f, 1.0f};

int larguraJanela = 1000;
int alturaJanela = 800;

int xAnterior = larguraJanela/2;
int yAnterior = alturaJanela/2;

float rotaEsDi = -90.0f;
float rotaCiBai = 0.0f;

float camX = 0.0f, camY = 0.0f, camZ = -1.0f;
float posX = 0.0f, posY = 2.0f, posZ = 10.0f;

bool ratoPrensado = false;

GLuint texSol, texMer, texVen, texTerra, texMart, texLua, texEstrela;
GLUquadric* esferaQuadrica;


void luz() {
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    
    //ambiente
    glEnable(GL_LIGHT0);
    GLfloat luzFraca[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzFraca);
    GLfloat posicaoLuz0[] = { 0.0f, 10.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);

    // Luz centro do Sol
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzBranca);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luzBranca);
    
    GLfloat posicaoLuz1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
}


void desenhaOrbita(float raio) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float angulo = 2.0f * M_PI * i / 100.0f;
        glVertex3f(cos(angulo) * raio, 0.0f, sin(angulo) * raio);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
    gluLookAt(posX, posY, posZ,  
        posX + camX, posY + camY, posZ + camZ,  
        0.0, 1.0, 0.0);
    luz();
    
    float velocidadeBola = 110.0f;
    
    float distaciaBola[] ={1.5f, 2.5f, 3.8f, 5.0f}; //mercurio, venus, terra, marte

    desenhaOrbita(distaciaBola[0]);
    desenhaOrbita(distaciaBola[1]);
    desenhaOrbita(distaciaBola[2]);
    desenhaOrbita(distaciaBola[3]);
        

	// sol    
    glPushMatrix();       
        glRotatef(tempoDecorrido*velocidadeBola*0.5f, 0.0f, 1.0f, 0.0f);      

        glBindTexture(GL_TEXTURE_2D, texSol);
        glColor3f(1.0f, 1.0f, 1.0f); 

        GLfloat emissaoSol[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, emissaoSol);
            
        gluSphere(esferaQuadrica, 0.6, 36, 36);

        GLfloat semEmissao[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, semEmissao);
    glPopMatrix();


    //mercurio        
    glPushMatrix();        
        glRotatef(tempoDecorrido*velocidadeBola*1.5f, 0.0f, 1.0f, 0.0f); //angulo*velocidade              
        glTranslatef(distaciaBola[0], 0.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, texMer);
        glColor3f(1.0f, 1.0f, 1.0f); 
        
        gluSphere(esferaQuadrica, 0.13, 36, 36);
        
    glPopMatrix();   
    
    //venus    
    glPushMatrix();
        glRotatef(tempoDecorrido*velocidadeBola*1.0f, 0.0f, 1.0f, 0.0f); 
        glTranslatef(distaciaBola[1], 0.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, texVen);
        glColor3f(1.0f, 1.0f, 1.0f); 
        
        gluSphere(esferaQuadrica, 0.25, 36, 36);
        
    glPopMatrix();

    //terra        
    glPushMatrix();       
        glRotatef(tempoDecorrido*velocidadeBola*0.8f, 0.0f, 1.0f, 0.0f);         
        glTranslatef(distaciaBola[2], 0.0f, 0.0f);                
        
        glBindTexture(GL_TEXTURE_2D, texTerra);
        glColor3f(1.0f, 1.0f, 1.0f); 
        
        gluSphere(esferaQuadrica, 0.3, 36, 36);
        
        glPushMatrix();
            glRotatef(tempoDecorrido*velocidadeBola, 0.0f, 1.0f, 0.0f);         
            glTranslatef(0.5f, 0.0f, 0.0f);      

            glBindTexture(GL_TEXTURE_2D, texLua);          
            glColor3f(1.0f, 1.0f, 1.0f);                
            gluSphere(esferaQuadrica, 0.05, 36, 36);
        glPopMatrix();              
    glPopMatrix();

    //marte        
    glPushMatrix();        
        glRotatef(tempoDecorrido*velocidadeBola*0.5f, 0.0f, 1.0f, 0.0f);      
        glTranslatef(distaciaBola[3], 0.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, texMart);
        glColor3f(1.0f, 1.0f, 1.0f); 
        
        gluSphere(esferaQuadrica, 0.16, 36, 36);
          
    glPopMatrix();

    glutSwapBuffers();
}


void mousePrensado(int butao, int estado, int x, int y){
    if (butao == GLUT_LEFT_BUTTON){
        if (estado == GLUT_DOWN){
            ratoPrensado = true;
            xAnterior = x; 
            yAnterior = y;
        } else {
            ratoPrensado = false;
        }
    }
}

void gerenciaMovimentoMouse(int x, int y){    
    if(!ratoPrensado) return;
    
    int deltaX = x - xAnterior;
    int deltaY = y - yAnterior;

    float sensibility = 0.1f;
    rotaEsDi += deltaX * sensibility;
    rotaCiBai -= deltaY * sensibility;
   
    if (rotaCiBai > 89.0f) rotaCiBai = 89.0f;
    if (rotaCiBai < -89.0f) rotaCiBai = -89.0f;

    float radRotaCB = rotaCiBai * M_PI/180.0f;
    float radRotaED = rotaEsDi * M_PI/180.0f;

    camX = cos(radRotaCB) * cos(radRotaED);
    camY = sin(radRotaCB);
    camZ = cos(radRotaCB) * sin(radRotaED);       
    
    xAnterior = x;
    yAnterior = y;  

    glutPostRedisplay();
}


GLuint carregarBMP(const char* arquivo){
    std::ifstream fs(arquivo, std::ios::binary);
    if(!fs) return 0;

    unsigned char cabecalho[54];
    fs.read((char*) cabecalho, 54);

    int largura = *(int*)&(cabecalho[18]);
    int altura = *(int*)&(cabecalho[22]);
    int tamanhoImagem = *(int*)&(cabecalho[34]);
    if (tamanhoImagem == 0) tamanhoImagem = largura * altura * 3;

    unsigned char* dados = new unsigned char[tamanhoImagem];
    fs.read((char*)dados, tamanhoImagem);
    fs.close();

    for (int i = 0; i < tamanhoImagem; i += 3) {
        std::swap(dados[i], dados[i + 2]);
    }

    GLuint idTextura;
    glGenTextures(1, &idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, dados);

    delete[] dados;
    return idTextura;
}


void reshape(int w, int h) {
    larguraJanela = w;
    alturaJanela = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
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


void inicializa() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_TEXTURE_2D);

    texSol = carregarBMP("texturas/sol.bmp");
    texMer = carregarBMP("texturas/mercurio.bmp");
    texVen = carregarBMP("texturas/venus.bmp");
    texTerra = carregarBMP("texturas/terra.bmp");
    texMart = carregarBMP("texturas/marte.bmp");
    texLua = carregarBMP("texturas/lua.bmp");
    texEstrela = carregarBMP("texturas/estrelas.bmp");

    esferaQuadrica = gluNewQuadric();
    gluQuadricTexture(esferaQuadrica, GL_TRUE); 
    gluQuadricNormals(esferaQuadrica, GLU_SMOOTH);

    
    glutSetCursor(GLUT_CURSOR_INHERIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutCreateWindow("Animacao com OpenGL e GLUT");

    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(tecladoNormal);

    glutMouseFunc(mousePrensado);
    glutMotionFunc(gerenciaMovimentoMouse);

    glutWarpPointer(larguraJanela / 2, alturaJanela / 2);
    
    glutTimerFunc(16, atualizaAnimacao, 0);
    glutMainLoop();
    
    return 0;
}
