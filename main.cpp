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
#include"inputManager.h"

#define WIDTH 800
#define HEIGHT 600

const int TERR_LEN = 10;
const float TERR_DIS = 1;

const float PLAYER_HEIGHT = 10;

int main(int argc, char**argv)
{
	Display display(WIDTH, HEIGHT, "Hello world");

	std::vector<Terrian> worldTerrian;// (20, 20, 5, Terrian::TERRIAN_SHAPE_FLAT);
	for (int y = 1; y <= 1; y++)
		for (int x = 1; x <= 1; x++)
			worldTerrian.push_back(Terrian(x*TERR_LEN, y*TERR_LEN, 256, 1600));

	Vertex vertices[] =
	{ Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,1.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0,0.5,0), glm::vec2(1.0,0.0), glm::vec3(0,0,1)) };

	unsigned int indices[] = { 0,1,2 };
	
	glm::vec3 pos(0, 0, 0);
	glm::vec3 rot(0, 0, 0);

	InputManager* inputManager;
	inputManager = InputManager::Instace();

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

	Transform terrainTrans;

	float velocityY = 0.0;
	float accY = -1;

	float speed = 0.1;
	float turnFactor = 0.5;

	float counter = 0.0;

	/*SDL_Event e;
	SDL_PollEvent(&e);
	glm::vec2 mouseCur, mousePrev,mouseDelta;
	mouseCur.x = e.button.x, mouseCur.y = e.button.y;*/
	POINT mouseCur, mousePrev, mouseDelta;
	GetCursorPos(&mouseCur);

	glm::vec3 lightVec(glm::normalize(glm::vec3(0.0, -1, -0.0)));
	glm::vec3 skyVec((42 / 255.0f), (120 / 255.0f), (99 / 255.0f));

	float temp;

	srand(time(NULL));

	glm::vec3 arrTransTree[25];
	glm::vec3 arrRotTree[25];
	glm::vec3 arrScaleTree[25];
	for (int i = 0; i < 25; i++)
	{
		arrTransTree[i] = glm::vec3(rand() % 800, 0, rand() % 800);
		arrRotTree[i] = glm::vec3(0, rand() % 360, 0);
		int scale = rand() % 4 + 2;
		arrScaleTree[i] = glm::vec3(scale, scale, scale);
	}
	
	while (!display.IsClosed())
	{
		inputManager->Update();

		/*SDL_PollEvent(&e);
		if (e.type == SDL_MOUSEMOTION) {
			mousePrev = mouseCur;
			mouseCur.x = e.button.x, mouseCur.y = e.button.y;
			mouseDelta.x = mouseCur.x - mousePrev.x;
			mouseDelta.y = mouseCur.y - mousePrev.y;
		}*/
		mousePrev = mouseCur;
		GetCursorPos(&mouseCur);
		mouseDelta.x = mouseCur.x - mousePrev.x;
		mouseDelta.y = mouseCur.y - mousePrev.y;

		display.Clear(skyVec.x, skyVec.y, skyVec.z, 1.0);

		texture.Bind(0);

		if (inputManager->KeyDown(SDL_SCANCODE_A))
			camera.GetPosition() -= glm::normalize(glm::cross(camera.GetForward(), camera.GetUp())) * speed;
		if (inputManager->KeyDown(SDL_SCANCODE_D))
			camera.GetPosition() += glm::normalize(glm::cross(camera.GetForward(), camera.GetUp())) * speed;
		//if (GetAsyncKeyState('W'))
		if (inputManager->KeyDown(SDL_SCANCODE_W))
			//if(!GetAsyncKeyState(VK_SHIFT))
			if (!inputManager->KeyDown(SDL_SCANCODE_LSHIFT))
				camera.GetPosition() += camera.GetForward()*speed;
			else
				camera.GetPosition() += camera.GetForward()*(speed*5);
		if (inputManager->KeyDown(SDL_SCANCODE_S))
			camera.GetPosition() -= camera.GetForward()*speed;

		//if (GetAsyncKeyState(VK_SPACE) && camera.GetPosition().y <= PLAYER_HEIGHT)
		if(inputManager->KeyDown(SDL_SCANCODE_SPACE) && camera.GetPosition().y <= PLAYER_HEIGHT)
			velocityY = 10;

		if (velocityY < 0 && camera.GetPosition().y <= PLAYER_HEIGHT)velocityY = 0.0;
		camera.GetPosition().y += velocityY * speed;
		if (camera.GetPosition().y > PLAYER_HEIGHT)velocityY += accY * speed;
		
		camera.Yaw(mouseDelta.x *turnFactor);
		camera.Pitch(-mouseDelta.y *turnFactor);
		
		lightVec.x = sinf(counter);

		counter += 0.002;

		//textureRed.Bind(0);
		terrainTrans.GetPos() = glm::vec3(-70, 0, -70);

		terrainShader.Bind();
		terrainShader.Update(terrainTrans, camera, lightVec, skyVec);

		textureGrass.Bind(0);
		for (auto i : worldTerrian)
			i.Draw();

		transformTree.GetPos() = glm::vec3(30, -1, 30);

		shader.Bind();
		shader.Update(transformTree, camera, lightVec, skyVec);

		lowPolyTreeTex.Bind(0);
		for (int i = 0; i < 25; i++)
		{
			transformTree.GetPos() = arrTransTree[i];
			transformTree.GetRot() = arrRotTree[i];
			transformTree.GetScale() = arrScaleTree[i];
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

	inputManager->Release();
	inputManager = NULL;

	return 0;
}