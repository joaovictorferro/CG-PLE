#include <Windows.h>
#include <GLFW/glfw3.h>
#include <gl/GLU.h>
#include <iostream>
#include "cores.h"
#include "primitivas.h"
#include "camera.h"
#include "textura.h"

static float angulo = 45.0;
static float lastMousePos = 0.0;
static bool firstTimeMouse = true;
static int control_port = 0;
static int control_janela = 0;

//display list
unsigned int esferaID[5];
unsigned int cuboID[40];

Camera camera(vec3(0.0, 0.0, -70.0));

enum{PORTA,RELOGIO,TAPETE,PISO,QUADRO,MESA,JANELA};
textura cuboTex[5];
void redimensiona(int w, int h)
{
	glViewport(0, 0, w, h);

	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
}

void luz()
{
	float light0[4][4] = {
		{0.1f,0.1f,0.1f,0.1f}, // ambient
		{0.8f,0.8f,0.8f,0.8f},	// diffuse
		{0.1f,0.1f,0.1f,0.1f}, // specular
		{0.0f,0.0f,-50.0f,1.0f} // position
	};

	glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);
	glLightfv(GL_LIGHT0, GL_POSITION, &light0[3][0]);
}

void ventilador(float angulo)
{
	glTranslatef(-15.0, 2.0, -76.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(esferaID[4]);

	//helice 1
	glPushMatrix();
	glRotatef(angulo, 0.0, 0.0, 1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[30]);
	glPopMatrix();
	//helice 2
	glPushMatrix();
	glRotatef(angulo, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[31]);
	glPopMatrix();
	//helice 3
	glPushMatrix();
	glRotatef(angulo, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[32]);
	glPopMatrix();
	//helice 4
	glPushMatrix();
	glRotatef(angulo, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 1.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[32]);
	glPopMatrix();
}

void desenho(float dt)
{
	float velocidade_ang = 25.f * dt; // 60 graus por segundo
	glLoadIdentity();

	camera.ativar();
	luz();
	//piso
	glPushMatrix();
	glTranslatef(0.0, -11.0, -50.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[0]);
	glPopMatrix();
	
	//base cama
	glPushMatrix();
	glTranslatef(0.0, -10.5, -69.9);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[1]);
	glPopMatrix();

	//colchao
	glPushMatrix();
	glTranslatef(0.0, -9.0, -69.9);
	//glRotatef(angulo, 1.0, 1.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[2]);
	glPopMatrix();
	
	//travesseiro
	glPushMatrix();
	glTranslatef(0.0, -8.0, -77.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[3]);
	glPopMatrix();

	// mesa pregada na parede
	glPushMatrix();
	glTranslatef(21.0, -4.0, -75.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[4]);
	glPopMatrix();

	//gaveteiro base
	glPushMatrix();
	glTranslatef(-15.0, -6.0, -77.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[5]);
	glPopMatrix();

	//gaveta 1
	glPushMatrix();
	glTranslatef(-15.0, -4.0, -74.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[6]);
	glPopMatrix();

	//gaveta 2
	glPushMatrix();
	glTranslatef(-15.0, -8.0, -74.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[7]);
	glPopMatrix();

	//macaneta 1
	glPushMatrix();
	glTranslatef(-15.0, -4.0, -73.2);
	glScalef(1.0, 1.0, 1.0);
	glCallList(esferaID[0]);
	glPopMatrix();

	//macaneta 2
	glPushMatrix();
	glTranslatef(-15.0, -8.0, -73.2);
	glScalef(1.0, 1.0, 1.0);
	glCallList(esferaID[1]);
	glPopMatrix();

	//guarda-roupa base
	glPushMatrix();
	glTranslatef(28.0, -2.0, -45.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[8]);
	glPopMatrix();
	
	//porta guarda-roupa 1
	glPushMatrix();
	glTranslatef(26.0, -2.0, -49.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[9]);
	glPopMatrix();

	//porta guarda-roupa 2
	glPushMatrix();
	glTranslatef(26.0, -2.0, -41.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[9]);
	glPopMatrix();

	//porta guarda-roupa macaneta 1
	glPushMatrix();
	glTranslatef(25.0, -2.0, -47.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(esferaID[2]);
	glPopMatrix();

	//porta guarda-roupa maceneta 2
	glPushMatrix();
	glTranslatef(25.0, -2.0, -43.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(esferaID[3]);
	glPopMatrix();
	
	//parede fundo
	glPushMatrix();
	glTranslatef(0.0, 1.0, -81.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[11]);
	glPopMatrix();
	
	//parede lateral direito
	glPushMatrix();
	glTranslatef(30.0, 1.0, -50.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[12]);
	glPopMatrix();

	//teto
	glPushMatrix();
	glTranslatef(0.0, 13.0, -50.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[0]);
	glPopMatrix();

	//quadro
	glPushMatrix();
	glTranslatef(0.0, 6.0, -80.0);
	glRotatef(180.0, 0.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[14]);
	glPopMatrix();

	//relogoio
	glPushMatrix();
	glTranslatef(24.0, 6.0, -80.0);
	glRotatef(180.0, 0.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[15]);
	glPopMatrix();

	//tapete
	glPushMatrix();
	glTranslatef(0.0, -10.0, -50.0);
	glScalef(1.0, 1.0, 1.0);
	glCallList(cuboID[16]);
	glPopMatrix();
	
	//porta
		glPushMatrix();
		if (control_port == 0)
		{
			glTranslatef(-30.0, -2.0, -24.0);
			glScalef(1.0, 1.0, 1.0);
			glCallList(cuboID[17]);
		}
		else if (control_port == 1)
		{
			glTranslatef(-30.0, -2.0, -20.0);
			glRotatef(90.0, 0.0, -1.0, 0.0);
			glScalef(1.0, 1.0, 1.0);
			glCallList(cuboID[17]);
		}
		glPopMatrix();
	
	//Janela 1 
		glPushMatrix();
		if (control_janela == 0)
		{
			glTranslatef(-30.0, 0.0, -51.0);
			glScalef(1.0, 1.0, 1.0);
			glCallList(cuboID[18]);
		}
		else if (control_janela == 1)
		{
			glTranslatef(-30.0, 0.0, -48.0);
			glRotatef(90.0, 0.0, -1.0, 0.0);
			glScalef(1.0, 1.0, 1.0);
			glCallList(cuboID[18]);
		}
		glPopMatrix();
		
	//Janela 2 
		glPushMatrix();
		if (control_janela == 0)
		{
			glTranslatef(-30.0, 0.0, -57.0);
			glScalef(1.0, 1.0, 1.0);
			glCallList(cuboID[19]);
		}
		else if (control_janela == 1)
		{
			glTranslatef(-30.0, 0.0, -60.0);
			glRotatef(90.0, 0.0, -1.0, 0.0);
			glScalef(1.0, 1.0, 1.0);
			glCallList(cuboID[19]);
		}
		glPopMatrix();

		//parede lateral esquerda 1
		glPushMatrix();
		glTranslatef(-30.0, 9.0, -50.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[20]);
		glPopMatrix();

		// parede lateral esqueda 2
		glPushMatrix();
		glTranslatef(-30.0, -2.0, -38.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[21]);
		glPopMatrix();

		// parede lateral esqueda 3
		glPushMatrix();
		glTranslatef(-30.0, -2.0, -70.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[22]);
		glPopMatrix();
		
		// parede lateral esqueda 4
		glPushMatrix();
		glTranslatef(-30.0, -8.0, -54.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[23]);
		glPopMatrix();
		
		// parede de fundo
		glPushMatrix();
		glTranslatef(0.0, 0.0, -20.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[24]);
		glPopMatrix();
		
		//assento cadeira
		glPushMatrix();
		glTranslatef(23.0, -7.0, -65.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[25]);
		glPopMatrix();

		//apoio cadeira
		glPushMatrix();
		glTranslatef(23.0, -9.0, -67.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[26]);
		glPopMatrix();

		//atras cadeira
		glPushMatrix();
		glTranslatef(23.0, -7.0, -63.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[27]);
		glPopMatrix();

		//base do ventilador
		glPushMatrix();
		glTranslatef(-15.0, -1.0, -77.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[28]);
		glPopMatrix();
		
		//segurar as helices ventilador
		glPushMatrix();
		glTranslatef(-15.0, 0.0, -77.0);
		glScalef(1.0, 1.0, 1.0);
		glCallList(cuboID[29]);
		glPopMatrix();

		glPushMatrix();
		ventilador(-angulo);
		glPopMatrix();
		
	angulo += velocidade_ang;

	if (angulo >= 360.0)
	{
		angulo = 0.0;
	}
}

void teclado(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//forward
		camera.forward();
	}
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//back
		camera.back();
	}
	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//left
		camera.left();
	}
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//right
		camera.right();
	}
	else if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		control_port = 1;
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		control_port = 0;
	}
	else if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		control_janela = 1;
	}
	else if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		control_janela = 0;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float dx;

	if (firstTimeMouse)
	{
		dx = 0.0;
		lastMousePos = xpos;
		firstTimeMouse = false;
	}
	dx = xpos - lastMousePos;
	lastMousePos = xpos;
	camera.updateYaw(dx);
	camera.update();
}

void init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, teclado);
	glfwSetCursorPosCallback(window,mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
	glfwMaximizeWindow(window);
	glClearColor(0.0, 0.15, 0.25, 1.0); // cor de fundo
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	float globalAmb[] = { 0.5f,0.5f,0.5f,0.5f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmb);
	
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	cuboTex[PORTA].load("images/PORTA.png");
	cuboTex[TAPETE].load("images/TAPETE.png");
	cuboTex[RELOGIO].load("images/RELOGIO.png");
	cuboTex[PISO].load("images/PISO.png");
	cuboTex[QUADRO].load("images/QUADRO.png");
	cuboTex[MESA].load("images/MESA.png");
	cuboTex[JANELA].load("images/JANELA.png");

	cuboID[0] = glGenLists(40); // piso
	cuboID[1] = cuboID[0] + 1;// base cama
	cuboID[2] = cuboID[0] + 2; // colchao
	cuboID[3] = cuboID[0] + 3; // travesseiro
	cuboID[4] = cuboID[0] + 4; // mesa
	cuboID[5] = cuboID[0] + 5; // gaveteiro base
	cuboID[6] = cuboID[0] + 6; // gaveta1
	cuboID[7] = cuboID[0] + 7; // gaveta2
	esferaID[0] = cuboID[0] + 8; // gaveteiro macaneta 1
	esferaID[1] = cuboID[0] + 9; // gaveteiro maceneta 2
	cuboID[8] = cuboID[0] + 10; // guarda-roupa base
	cuboID[9] = cuboID[0] + 11; // porta guarda-roupa 1
	cuboID[10] = cuboID[0] + 12; // porta guarda-roupa 1
	esferaID[2] = cuboID[0] + 13; // porta guarda-roupa maceneta 1
	esferaID[3] = cuboID[0] + 14; // porta guarda-roupa maceneta 2
	cuboID[11] = cuboID[0] + 15; // parede fundo
	cuboID[12] = cuboID[0] + 16; // parede lateral direito
	cuboID[13] = cuboID[0] + 17; // teto
	cuboID[14] = cuboID[0] + 18; // quadro
	cuboID[15] = cuboID[0] + 19; // relogio
	cuboID[16] = cuboID[0] + 20; // tapete
	cuboID[17] = cuboID[0] + 21; // porta
	cuboID[18] = cuboID[0] + 22; //janela 1
	cuboID[19] = cuboID[0] + 23; //janela 2
	cuboID[20] = cuboID[0] + 24; //parede lateral 1
	cuboID[21] = cuboID[0] + 25; //parede lateral 2
	cuboID[22] = cuboID[0] + 26; //parede lateral 3
	cuboID[23] = cuboID[0] + 27; //parede lateral 4
	cuboID[24] = cuboID[0] + 28; // parede de frente
	cuboID[25] = cuboID[0] + 29; // assento cadeira
	cuboID[26] = cuboID[0] + 30; //frente cadeira
	cuboID[27] = cuboID[0] + 31; //atras cadeira
	cuboID[28] = cuboID[0] + 32; //base ventilador
	cuboID[29] = cuboID[0] + 33; //tronco ventilador
	esferaID[4] = cuboID[0] + 34; //esfera ventilador
	cuboID[30] = cuboID[0] + 35; //helice 1
	cuboID[31] = cuboID[0] + 36; //helice 2
	cuboID[32] = cuboID[0] + 37; //helice 3
	cuboID[33] = cuboID[0] + 38; //helice 4
	textura* tex;
	tex = &cuboTex[PISO];
	desenhaCuboTex(cuboID[0], 30.0, 1.0, 30.0,tex); // piso
	desenhaCubo(cuboID[1], 5.0, 1.5, 10.0,marrom); //base cama
	desenhaCubo(cuboID[2], 5.0, 1.5, 10.0, vermelho); //colchao
	desenhaCubo(cuboID[3], 2.0, 1.0, 1.0, branco_gelo); //travesseiro
	textura* tex5;
	tex5 = &cuboTex[MESA];
	desenhaCuboTex(cuboID[4], 8.0, 0.5, 5.0, tex5); //mesa
	desenhaCubo(cuboID[5], 3.0, 5.0, 3.0, laranja); //gaveteiro base
	desenhaCubo(cuboID[6], 2.0, 1.5, 0.3, amarelo); //gaveteiro gaveta 1
	desenhaCubo(cuboID[7], 2.0, 1.5, 0.3, amarelo); //gaveteiro gaveta 2
	desenharEsfera(esferaID[0], preto, 0.5, 20.0, 20.0); // gaveteiro maceneta 1
	desenharEsfera(esferaID[1], preto, 0.5, 20.0, 20.0); // gaveteiro maceneta 2
	desenhaCubo(cuboID[8], 2.0, 8.0, 8.0, laranja); //guarda-roupa base
	desenhaCubo(cuboID[9], 0.3, 6.0, 3.0, verde); //porta guarda-roupa 1
	desenhaCubo(cuboID[10], 0.3, 6.0, 3.0, verde); //porta guarda-roupa 2
	desenharEsfera(esferaID[2], preto, 0.5, 20.0, 20.0); // porta guarda-roupa maceneta 1
	desenharEsfera(esferaID[3], preto, 0.5, 20.0, 20.0); // porta guarda-roupa maceneta 2
	desenhaCuboTex(cuboID[11], 30.0, 13.0, 1.0, tex); // parede fundo
	desenhaCuboTex(cuboID[12], 1.0, 13.0, 30.0, tex); // parede lateral direito
	desenhaCuboTex(cuboID[13], 30.0, 1.0, 30.0, tex); // teto
	textura* tex2;
	tex2 = &cuboTex[QUADRO];
	desenhaCuboTex(cuboID[14], 5.0, 5.0, 0.1, tex2); // quadro
	textura* tex3;
	tex3 = &cuboTex[RELOGIO];
	desenhaCuboTex(cuboID[15], 2.0, 2.0, 0.1, tex3); //relogio
	textura* tex4;
	tex4 = &cuboTex[TAPETE];
	desenhaCuboTex(cuboID[16], 8.0, 0.1, 8.0, tex4); //tapete
	textura *tex6;
	tex6 = &cuboTex[PORTA];
	desenhaPorta(cuboID[17], 0.1, 8.0, 4.0, tex6); //porta
	textura* tex7;
	tex7 = &cuboTex[JANELA];
	desenhaCuboTex(cuboID[18], 0.1, 6.0, 3.0, tex7); //janela 1
	desenhaCuboTex(cuboID[19], 0.1, 6.0, 3.0, tex7); // janela 2
	desenhaCuboTex(cuboID[20], 1.0, 3.0, 30.0, tex); // parede lateral 1
	desenhaCuboTex(cuboID[21], 1.0, 8.0, 10.0, tex); // parede lateral 2
	desenhaCuboTex(cuboID[22], 1.0, 8.0, 10.0, tex); // parede lateral 3
	desenhaCuboTex(cuboID[23], 1.0, 2.0, 7.0, tex); // parede lateral 4
	desenhaCuboTex(cuboID[24], 30.0, 13.0, 1.0, tex); // parede frente
	desenhaCubo(cuboID[25], 2.0, 0.1, 2.0, violeta); // assento cadeira
	desenhaCubo(cuboID[26], 2.0, 2.0, 0.1, violeta); // frente cadeira
	desenhaCubo(cuboID[27], 2.0, 5.0, 0.1, violeta); // atras cadeira
	desenhaCubo(cuboID[28], 2.0, 0.1, 2.0, vermelho); // base ventilador
	desenhaCubo(cuboID[29], 0.1, 2.0, 0.1, vermelho); // tronco ventilador
	desenharEsfera(esferaID[4], laranja, 0.5, 20.0, 20.0); // encaixe central do ventilador
	desenhaCubo(cuboID[30], 1.0, 0.3, 0.5, preto); // helice 1
	desenhaCubo(cuboID[31], 1.0, 0.3, 0.5, preto); // helice 2
	desenhaCubo(cuboID[32], 0.3, 1.0, 0.5, preto); // helice 3
	desenhaCubo(cuboID[33], 0.3, 1.0, 0.5, preto); // helice 4
}

int main(void)
{
	const int LARGURA = 800;
	const int ALTURA = 600;

	/* Initialize the library */
	glfwInit();

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(LARGURA, ALTURA, "Desenha Esfera", NULL, NULL);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// -- inicio
	init(window);

	float valor = 0.0;
	float lastTime = 0.0;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = (float)glfwGetTime();
		float dt = currentTime - lastTime;
		lastTime = currentTime;

		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

		redimensiona(largura, altura);

		desenho(dt);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}
	glDisable(GL_TEXTURE_2D);
	glDeleteLists(cuboID[0], 38);
	glfwTerminate();
	return 0;
}