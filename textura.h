#pragma once
#include<iostream>

class textura
{
private:
	unsigned int m_id;
	int m_largura, m_altura, m_canais;

public:
	textura();
	~textura();
	void load(std::string filePath);
	void Bind();
	void UnBind();
};