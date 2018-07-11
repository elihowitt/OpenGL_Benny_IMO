#include"terrian.h"

static void SetNormals(Vertex& verA, Vertex& verB, Vertex& verC);

Terrian::Terrian(unsigned int width, unsigned int length, float distance = 0.1, Terrian::TERRIAN_FLAG flag_shape = Terrian::TERRIAN_SHAPE_FLAT)
{
	//(rand() / RAND_MAX - 0.5) * 0.5

	mesh = nullptr;

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	for (unsigned int z = 0; z < length; z++)
		for (int x = 0; x < width; x++)
		{
			vertices.push_back(Vertex(glm::vec3(x++*distance, 0, z*distance), glm::vec2(0, 0)));
			if (x < width)
			{
				vertices.push_back(Vertex(glm::vec3(x++*distance, 0, z*distance), glm::vec2(0.5, 1.0)));
				if(x<width)
					vertices.push_back(Vertex(glm::vec3(x*distance, 0, z*distance), glm::vec2(1, 1.0)));
			}
		}
	for (unsigned int z = 0; z < length-1; z++)
		for (int x = 0; x < width-1; x++)
		{
			indices.push_back(x + z * width);
			indices.push_back(x + z * width + 1);
			indices.push_back(x + (1 + z) * width);

			indices.push_back(x + z * width + 1);
			indices.push_back(x + (1 + z) * width);
			indices.push_back(x + (1 + z) * width + 1);
		}

	switch (flag_shape)
	{
	case Terrian::TERRIAN_SHAPE_FLAT:

		for (unsigned int z = 0; z < length; z++)
			for (int x = 0; x < width; x++)
			{
				vertices[x + z * width].SetNormal(glm::vec3(0, 1, 0));
			}

		break;
	case Terrian::TERRIAN_SHAPE_PERLIN:
		for (unsigned int z = 0; z < length; z++)
			for (int x = 0; x < width; x++)
				vertices[x + z * width].SetPos(*vertices[x + z * width].GetPos() + glm::vec3(0, (rand() / RAND_MAX - 0.5) * 4, 0));
	
		//Normals.
		for (int i = 0; i < indices.size(); i += 3)
		{
			SetNormals(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
		}
		break;
	default:
		break;
	}
	mesh = new Mesh(vertices.data(), (unsigned int)vertices.size(), (unsigned int*)indices.data(), (unsigned int)indices.size());
}

static void SetNormals(Vertex& verA, Vertex& verB, Vertex& verC)
{
	glm::vec3 V, W;
	V = *verB.GetPos() - *verA.GetPos();
	W = *verC.GetPos() - *verA.GetPos();
	verA.SetNormal(glm::cross(V, W));
	V = *verA.GetPos() - *verB.GetPos();
	W = *verC.GetPos() - *verB.GetPos();
	verB.SetNormal(glm::cross(V, W));
	V = *verB.GetPos() - *verC.GetPos();
	W = *verA.GetPos() - *verC.GetPos();
	verC.SetNormal(glm::cross(V, W));
}

Terrian::~Terrian()
{

}
