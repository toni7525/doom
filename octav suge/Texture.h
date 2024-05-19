#pragma once
#include <GL/glew.h>
#include<iostream>

class Textur
{
private:
	unsigned int m_renderid;
	std::string m_filepath;
	unsigned char* m_localbuffer;
	int m_width, m_height, m_bpp;
public:
	Textur(const std::string& path);
	~Textur();
	void Bind(unsigned int slot = 0)const;
	void UnBind()const;
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};
