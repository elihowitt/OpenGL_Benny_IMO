#include"terrian.h"

static void SetNormals(Vertex& verA, Vertex& verB, Vertex& verC);

//const float SIZE = 800;
//const int VERTEX_COUNT = 128;

Terrian::Terrian(float startX, float startZ, unsigned int VERTEX_COUNT, float SIZE, Terrian::TERRIAN_FLAG flag_shape)
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
	float* vertices = new float[count * 3];
	float* normals = new float[count * 3];
	float* textureCoords = new float[count * 2];
	int* indices = new int[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)];
	int vertexPointer = 0;
	for (int i = 0; i<VERTEX_COUNT; i++) {
		for (int j = 0; j<VERTEX_COUNT; j++) {
			vertices[vertexPointer * 3] = ((float)j / ((float)VERTEX_COUNT - 1) * SIZE) + startX;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = ((float)i / ((float)VERTEX_COUNT - 1) * SIZE) + startZ;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	std::vector<Vertex> resVertices;
	for (int i = 0; i < count; i++)
		resVertices.push_back(Vertex(glm::vec3(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]), glm::vec2(textureCoords[i * 2], textureCoords[i * 2 + 1]), glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2])));
	std::vector<int> resIndices;
	for (int i = 0; i < 6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1); i++)
		resIndices.push_back(indices[i]);

	delete[] vertices;
	delete[] normals;
	delete[] textureCoords;
	delete[] indices;

	mesh = new Mesh(resVertices.data(), (unsigned int)resVertices.size(), (unsigned int*)resIndices.data(), (unsigned int)resIndices.size());
}
//{
//	//(rand() / RAND_MAX - 0.5) * 0.5
//
//	mesh = nullptr;
//
//	std::vector<Vertex> vertices;
//	std::vector<int> indices;
//
//	for (unsigned int z = 0; z < length; z++)
//		for (int x = 0; x < width; x++)
//		{
//			vertices.push_back(Vertex(glm::vec3(x*distance, 0, z*distance) + glm::vec3(startX, 0, startZ) , glm::vec2(0, 0)));
//		}
//		/*{
//			if (x % 2) {
//				vertices.push_back(Vertex(glm::vec3(x++*distance, 0, z*distance), glm::vec2(0, 0)));
//				if (x < width)
//				{
//					vertices.push_back(Vertex(glm::vec3(x++*distance, 0, z*distance), glm::vec2(0.0, 1.0)));
//					if (x < width)
//					{
//						vertices.push_back(Vertex(glm::vec3(x*distance, 0, z*distance), glm::vec2(1, 1.0)));
//					}
//				}
//			}
//			else {
//				vertices.push_back(Vertex(glm::vec3(x++*distance, 0, z*distance), glm::vec2(0, 0)));
//				if (x < width)
//				{
//					vertices.push_back(Vertex(glm::vec3(x++*distance, 0, z*distance), glm::vec2(1.0, 0.0)));
//					if (x < width)
//					{
//						vertices.push_back(Vertex(glm::vec3(x*distance, 0, z*distance), glm::vec2(1, 1.0)));
//					}
//				}
//			}
//		}*/
//
//	for (unsigned int z = 0; z < length-1; z++)
//		for (int x = 0; x < width-1; x++)
//		{
//			indices.push_back(x + z * width);
//			indices.push_back(x + z * width + 1);
//			indices.push_back(x + (1 + z) * width);
//
//			indices.push_back(x + z * width + 1);
//			indices.push_back(x + (1 + z) * width);
//			indices.push_back(x + (1 + z) * width + 1);
//		}
//
//	switch (flag_shape)
//	{
//	case Terrian::TERRIAN_SHAPE_FLAT:
//
//		for (unsigned int z = 0; z < length; z++)
//			for (int x = 0; x < width; x++)
//			{
//				vertices[x + z * width].SetNormal(glm::vec3(0, 1, 0));
//
//			}
//
//		for (int i = 0; i < indices.size(); i += 3)
//		{
//			if (i % 2)
//			{
//				vertices[indices[i]].SetTexCoord(glm::vec2(0, 0));
//				vertices[indices[i + 1]].SetTexCoord(glm::vec2(0, 1));
//				vertices[indices[i + 2]].SetTexCoord(glm::vec2(1, 0));
//			}
//			else
//			{
//				//vertices[indices[i]].SetTexCoord(glm::vec2(0, 0));
//				//vertices[indices[i + 1]].SetTexCoord(glm::vec2(1, 1));
//				vertices[indices[i + 2]].SetTexCoord(glm::vec2(1, 0));
//			}
//		}
//
//		break;
//	case Terrian::TERRIAN_SHAPE_PERLIN:
//		for (unsigned int z = 0; z < length; z++)
//			for (int x = 0; x < width; x++)
//				vertices[x + z * width].SetPos(*vertices[x + z * width].GetPos() + glm::vec3(0, (rand() / RAND_MAX - 0.5) * 4, 0));
//	
//		//Normals.
//		for (int i = 0; i < indices.size(); i += 3)
//		{
//			SetNormals(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
//			if (i % 2)
//			{
//				vertices[indices[i]].SetTexCoord(glm::vec2(0, 0));
//				vertices[indices[i+1]].SetTexCoord(glm::vec2(0, 1));
//				vertices[indices[i+2]].SetTexCoord(glm::vec2(1, 0));
//			}
//			else
//			{
//				vertices[indices[i]].SetTexCoord(glm::vec2(1, 1));
//				vertices[indices[i + 1]].SetTexCoord(glm::vec2(0, 1));
//				vertices[indices[i + 2]].SetTexCoord(glm::vec2(1, 0));
//			}
//		}
//		break;
//	default:
//		break;
//	}
//	mesh = new Mesh(vertices.data(), (unsigned int)vertices.size(), (unsigned int*)indices.data(), (unsigned int)indices.size());
//}

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
	//delete mesh;
}

/////
//
//
//	int count = VERTEX_COUNT * VERTEX_COUNT;
//	float* vertices = new float[count * 3];
//	float* normals = new float[count * 3];
//	float* textureCoords = new float[count * 2];
//	int* indices = new int[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)];
//	int vertexPointer = 0;
//	for (int i = 0; i<VERTEX_COUNT; i++) {
//		for (int j = 0; j<VERTEX_COUNT; j++) {
//			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
//			vertices[vertexPointer * 3 + 1] = 0;
//			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
//			normals[vertexPointer * 3] = 0;
//			normals[vertexPointer * 3 + 1] = 1;
//			normals[vertexPointer * 3 + 2] = 0;
//			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
//			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
//			vertexPointer++;
//		}
//	}
//	int pointer = 0;
//	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
//		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
//			int topLeft = (gz*VERTEX_COUNT) + gx;
//			int topRight = topLeft + 1;
//			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
//			int bottomRight = bottomLeft + 1;
//			indices[pointer++] = topLeft;
//			indices[pointer++] = bottomLeft;
//			indices[pointer++] = topRight;
//			indices[pointer++] = topRight;
//			indices[pointer++] = bottomLeft;
//			indices[pointer++] = bottomRight;
//		}
//	}
//
//	std::vector<Vertex> resVertices;
//	for (int i = 0; i < count; i++)
//		resVertices.push_back(Vertex(glm::vec3(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]), glm::vec2(textureCoords[i * 2], textureCoords[i * 2 + 1]), glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2])));
//	std::vector<int> resIndices;
//	for (int i = 0; i < 6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1); i++)
//		resIndices.push_back(indices[i]);
//
//	delete[] vertices;
//	delete[] normals;
//	delete[] textureCoords;
//	delete[] indices;
//
//	///