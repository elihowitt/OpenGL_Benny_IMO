#pragma once

#include"mesh.h"

class Terrian
{
public:
	enum TERRIAN_FLAG
	{
		TERRIAN_SHAPE_FLAT,
		TERRIAN_SHAPE_PERLIN
	};
	Terrian(unsigned int, unsigned int, float, TERRIAN_FLAG);
	~Terrian();
	
	void Draw() { mesh->Draw(); }
protected:
private:
	Mesh * mesh;
};
