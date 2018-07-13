#include<iostream>
#include<Windows.h>
#include<ctime>
#include<GL/glew.h>

#include"display.h"
#include"mesh.h"
#include"shader.h"
#include"texture.h"
#include"transform.h"
#include"camera.h"
#include"terrian.h"

#define WIDTH 800
#define HEIGHT 600

const int TERR_LEN = 10;
const float TERR_DIS = 1;

const float PLAYER_HEIGHT = 5;

int main(int argc, char**argv)
{
	Display display(WIDTH, HEIGHT, "Hello world");

	std::vector<Terrian> worldTerrian;// (20, 20, 5, Terrian::TERRIAN_SHAPE_FLAT);
	for (int y = 1; y <= 1; y++)
		for (int x = 1; x <= 1; x++)
			worldTerrian.push_back(Terrian(x*TERR_LEN, y*TERR_LEN));

	Vertex vertices[] =
	{ Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,1.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0,0.5,0), glm::vec2(1.0,0.0), glm::vec3(0,0,1)) };

	unsigned int indices[] = { 0,1,2 };
	
	glm::vec3 pos(0, 0, 0);
	glm::vec3 rot(0, 0, 0);

	

	Mesh triangle(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh("./res/monkey3.txt"); 
	Mesh meshStall("./res/stall.obj"); 
	Shader shader("./res/basicShader");
	Shader shaderByHeight("./res/shader by height");

	Shader terrainShader("./res/terrainShader");

	Texture texture("./res/Machpod_choice.jpg");
	Texture textureRed("./res/red texture.jpg");
	Texture textureStall("./res/stallTexture.png");
	Texture textureGrass("./res/grass_pattern.jpg");

	Mesh lowpolyTree("./res/lowPolyTree.obj");
	Texture lowPolyTreeTex("./res/lowPolyTree.png");

	Camera camera(glm::vec3(0,0,-3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;
	Transform transformTree;

	float speed = 0.1;
	float turnFactor = 0.5;

	float counter = 0.0;

	POINT mouseCur, mousePrev,mouseDelta;
	mouseCur.x = 0.0, mouseCur.y = 0.0;
	GetCursorPos(&mousePrev);

	glm::vec3 lightVec(glm::normalize(glm::vec3(0.0, -1, -0.0)));
	glm::vec3 skyVec((42 / 255.0f), (120 / 255.0f), (99 / 255.0f));

	float temp;

	srand(time(NULL));

	glm::vec3 arrTransTree[10];
	for(int i=0;i<10;i++)
		arrTransTree[i] = glm::vec3(rand() % 600, 0, rand() % 600);

	while (!display.IsClosed())
	{
		mousePrev = mouseCur;
		GetCursorPos(&mouseCur);
		mouseDelta.x = mouseCur.x - mousePrev.x;
		mouseDelta.y = mouseCur.y - mousePrev.y;

		display.Clear(skyVec.x, skyVec.y, skyVec.z, 1.0);

		texture.Bind(0);
		
		//if (GetAsyncKeyState(VK_SPACE))
		//{
		//	shader.Bind();
		//	shader.Update(transform, camera, lightVec);
		//}
		//else
		//{
		//	shaderByHieght.Bind();
		//	shaderByHieght.Update(transform, camera, lightVec);
		//}

		if (GetAsyncKeyState('A'))
			camera.GetPosition() -= glm::normalize(glm::cross(camera.GetForward(), camera.GetUp())) * speed;
		if (GetAsyncKeyState('D'))																  
			camera.GetPosition() += glm::normalize(glm::cross(camera.GetForward(), camera.GetUp())) * speed;
		if (GetAsyncKeyState('W'))
			camera.GetPosition() += camera.GetForward()*speed;
		if (GetAsyncKeyState('S'))
			camera.GetPosition() -= camera.GetForward()*speed;
		if (GetAsyncKeyState(VK_SHIFT))
			camera.GetPosition() += camera.GetUp()*speed;
		if (GetAsyncKeyState(VK_CONTROL))
			camera.GetPosition() -= camera.GetUp()*speed;
	
		if (GetAsyncKeyState('Q'))
			transform.GetScale() = glm::vec3(5, 5, 5);
		else transform.GetScale() = glm::vec3(1, 1, 1);

		camera.Yaw(mouseDelta.x *turnFactor);
		camera.Pitch(-mouseDelta.y *turnFactor);
		
		lightVec.x = sinf(counter);
		if (GetAsyncKeyState('U'))
			lightVec.y = cos(counter);
		if (GetAsyncKeyState('Y'))
			std::cout << lightVec.y;
		counter += 0.005;

		//textureRed.Bind(0);

		terrainShader.Bind();
		terrainShader.Update(transform, camera, lightVec, skyVec);

		textureGrass.Bind(0);
		for (auto i : worldTerrian)
			i.Draw();

		transformTree.GetPos() = glm::vec3(30, -1, 30);

		shader.Bind();
		shader.Update(transformTree, camera, lightVec, skyVec);

		lowPolyTreeTex.Bind(0);
		for (int i = 0; i < 10; i++)
		{
			transformTree.GetPos() = arrTransTree[i];
			shader.Update(transformTree, camera, lightVec, skyVec);
			lowpolyTree.Draw();
		}

		shaderByHeight.Bind();
		shaderByHeight.Update(transform, camera, lightVec);
		
		//textureStall.Bind(0);
		//meshStall.Draw();

		//triangle.Draw();
		//mesh.Draw();
		display.Update();

		if (camera.GetPosition().y < PLAYER_HEIGHT)camera.GetPosition().y = PLAYER_HEIGHT;
	}

	return 0;
}