#include<iostream>
	#include<Windows.h>
#include<GL/glew.h>

#include"display.h"
#include"mesh.h"
#include"shader.h"
#include"texture.h"
#include"transform.h"
#include"camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char**argv)
{
	Display display(WIDTH, HEIGHT, "Hello world");


	Vertex vertices[] =
	{ Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,1.0), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0,0.5,0), glm::vec2(1.0,0.0), glm::vec3(0,0,1)) };

	unsigned int indices[] = { 0,1,2 };
	
	glm::vec3 pos(0, 0, 0);
	glm::vec3 rot(0, 0, 0);

	Mesh triangle(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh("./res/monkey3.txt");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Texture textureRed("./res/red texture.jpg");
	Camera camera(glm::vec3(0,0,-3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float speed = 0.004;
	float turnFactor = 0.5;

	POINT mouseCur, mousePrev,mouseDelta;
	mouseCur.x = 0.0, mouseCur.y = 0.0;
	GetCursorPos(&mousePrev);

	float temp;
	while (!display.IsClosed())
	{
		mousePrev = mouseCur;
		GetCursorPos(&mouseCur);
		mouseDelta.x = mouseCur.x - mousePrev.x;
		mouseDelta.y = mouseCur.y - mousePrev.y;

		display.Clear((42 / 255.0), (120 / 255.0), (99 / 255.0), 0.9);

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);

	//	if (GetAsyncKeyState('A'))
	//		transform.GetPos().x -= speed;
	//	if (GetAsyncKeyState('D'))
	//		transform.GetPos().x += speed;
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

		//if (GetAsyncKeyState('E'))
		//{
			camera.Yaw(mouseDelta.x *turnFactor);
			camera.Pitch(-mouseDelta.y *turnFactor);
		//}

		triangle.Draw();
		//textureRed.Bind(0);
		mesh.Draw();
		display.Update();

		if (GetAsyncKeyState('I'))
		{
			std::cout << "Forward: (" << camera.GetForward().x << ',' << camera.GetForward().y << ',' << camera.GetForward().z << ")\n";
			std::cout << "Up: (" << camera.GetUp().x << ',' << camera.GetUp().y << ',' << camera.GetUp().z << ")\n";
		}
	}

	return 0;
}