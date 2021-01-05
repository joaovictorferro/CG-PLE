#include <vector>
#include <cmath>
#include "CG.h"
#include "textura.h"

void react(float p1[3], float p2[3], float p3[3], float p4[3], color cor)
{
	glColor3fv(cor);
	glBegin(GL_QUADS);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glEnd();
}

void reactTex(float p1[3], float p2[3], float p3[3], float p4[3])
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);	 glVertex3fv(p1);
	glTexCoord2f(1.0, 0.0);  glVertex3fv(p2);
	glTexCoord2f(1.0, 1.0);  glVertex3fv(p3);
	glTexCoord2f(0.0, 1.0);  glVertex3fv(p4);
	glEnd();
}

void desenhaCuboTex(unsigned int id, float largura, float altura, float expessura, textura* textura)
{
	float v1[3] = { -largura, altura, expessura };
	float v2[3] = { -largura, -altura, expessura };
	float v3[3] = { largura, -altura, expessura };
	float v4[3] = { largura, altura, expessura };

	float v5[3] = { largura, altura, -expessura };
	float v6[3] = { largura, -altura, -expessura };
	float v7[3] = { -largura, -altura, -expessura };
	float v8[3] = { -largura, altura, -expessura };

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	textura->Bind();
	//frente
	reactTex(v1, v2, v3, v4);

	//direita
	reactTex(v4, v3, v6, v5);

	//back
	reactTex(v5, v8, v7, v6);

	//esquerda
	reactTex(v1, v8, v7, v2);

	//topo
	reactTex(v1, v4, v5, v8);

	//bottom
	reactTex(v2, v7, v6, v3);
	textura->UnBind();
	glEndList();
}

void desenhaCubo(unsigned int id, float largura, float altura, float expessura, color cor)
{
	float v1[3] = { -largura, altura, expessura };
	float v2[3] = { -largura, -altura, expessura };
	float v3[3] = { largura, -altura, expessura };
	float v4[3] = { largura, altura, expessura };

	float v5[3] = { largura, altura, -expessura };
	float v6[3] = { largura, -altura, -expessura };
	float v7[3] = { -largura, -altura, -expessura };
	float v8[3] = { -largura, altura, -expessura };
	
	float matSpecular[] = { 1.f,1.f,1.f,1.f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128);

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//frente
	glNormal3f(0.f, 0.f, 1.f);
	react(v1, v2, v3, v4, cor);

	//direita
	glNormal3f(1.f, 0.f, 0.f);
	react(v4, v3, v6, v5, cor);

	//back
	glNormal3f(0.f, 0.f, -1.f);
	react(v5, v8, v7, v6, cor);

	//esquerda
	glNormal3f(-1.f, 0.f, 0.f);
	react(v1, v8, v7, v2, cor);

	//topo
	glNormal3f(0.f, 1.f, 0.f);
	react(v1, v4, v5, v8, cor);

	//bottom
	glNormal3f(0.f, -1.f, 0.f);
	react(v2, v7, v6, v3, cor);
	glEndList();
}


void desenharEsfera(unsigned int& id, color cor, float raio, int nStacks, int nSectors)
{
	std::vector< std::vector<int>> indices;
	std::vector<vec3> pontos;

	const float PI = 3.14;

	float deltaPhi = PI / nStacks;
	float deltaTheta = 2 * PI / nSectors;

	for (int i = 0; i <= nStacks; i++)
	{
		float phi = -PI / 2.0 + i * deltaPhi;
		float temp = raio * cos(phi);
		float y = raio * sin(phi);

		std::vector<int> pt;
		for (int j = 0; j < nSectors; j++)
		{
			float theta = j * deltaTheta;
			float x = temp * sin(theta);
			float z = temp * cos(theta);

			pontos.push_back(vec3(x, y, z));
			int index = pontos.size() - 1;
			pt.push_back(pontos.size() - 1);
		}

		indices.push_back(pt);
	}

	glNewList(id, GL_COMPILE);

	glColor3fv(cor);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	for (int i = 0; i < nStacks; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < nSectors; j++)
		{
			int index = indices[i][j];
			glVertex3fv(&pontos[index].x);
			index = indices[i + 1][j];
			glVertex3fv(&pontos[index].x);

			if (j == nSectors - 1)
			{
				index = indices[i][0];
				glVertex3fv(&pontos[index].x);
				index = indices[i + 1][0];
				glVertex3fv(&pontos[index].x);
			}
		}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
	glEndList();
}

void reactTexDireita(float p1[3], float p2[3], float p3[3], float p4[3])
{
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0);	 glVertex3fv(p1);
	glTexCoord2f(1.0, 1.0);  glVertex3fv(p2);
	glTexCoord2f(0.0, 1.0);  glVertex3fv(p3);
	glTexCoord2f(0.0, 0.0);  glVertex3fv(p4);
	glEnd();
}

void desenhaPorta(unsigned int id, float largura, float altura, float expessura, textura* textura)
{
	float v1[3] = { -largura, altura, expessura };
	float v2[3] = { -largura, -altura, expessura };
	float v3[3] = { largura, -altura, expessura };
	float v4[3] = { largura, altura, expessura };

	float v5[3] = { largura, altura, -expessura };
	float v6[3] = { largura, -altura, -expessura };
	float v7[3] = { -largura, -altura, -expessura };
	float v8[3] = { -largura, altura, -expessura };

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	textura->Bind();
	//frente
	reactTex(v1, v2, v3, v4);

	//direita
	reactTexDireita(v4, v3, v6, v5);

	//back
	reactTex(v5, v8, v7, v6);

	//esquerda
	reactTex(v1, v8, v7, v2);

	//topo
	reactTex(v1, v4, v5, v8);

	//bottom
	reactTex(v2, v7, v6, v3);
	textura->UnBind();
	glEndList();
}