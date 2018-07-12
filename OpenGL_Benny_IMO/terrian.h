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
	Terrian(float, float, unsigned int = 128, float = 800, TERRIAN_FLAG = TERRIAN_SHAPE_FLAT);
	~Terrian();
	
	void Draw() { mesh->Draw(); }
protected:
private:
	Mesh * mesh;
};
