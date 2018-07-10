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
	Transform transform(pos, rot);

	float speed = 0.004;
	float turnFactor = 2;
	float turnCountX = 0.0;
	float turnCountY = 0.0;

	float temp;
	while (!display.IsClosed())
	{
		display.Clear((42 / 255.0), (120 / 255.0), (99 / 255.0), 0.9);

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);

		if (GetAsyncKeyState('A'))
			transform.GetPos().x -= speed;
		if (GetAsyncKeyState('D'))
			transform.GetPos().x += speed;
		if (GetAsyncKeyState('W'))
			transform.GetPos().z -= speed;
		if (GetAsyncKeyState('S'))
			transform.GetPos().z += speed;
		if (GetAsyncKeyState(VK_SHIFT))
			transform.GetPos().y -= speed;
		if (GetAsyncKeyState(VK_CONTROL))
			transform.GetPos().y += speed;
		
		if (GetAsyncKeyState(VK_LEFT))		
			turnCountX = speed * turnFactor;		
		else if (GetAsyncKeyState(VK_RIGHT))
			turnCountX = -speed*turnFactor;
		else turnCountX = 0.0;
		
		if (GetAsyncKeyState(VK_UP))
			turnCountY = speed*turnFactor;
		else if (GetAsyncKeyState(VK_DOWN))
			turnCountY = -speed*turnFactor;
		else turnCountY = 0.0;

		if (GetAsyncKeyState('Q'))
			transform.GetScale() = glm::vec3(5, 5, 5);
		else transform.GetScale() = glm::vec3(1, 1, 1);

		//Around Y.
		temp = camera.GetForward().x;
		camera.GetForward().x = camera.GetForward().z*sin(turnCountX) + temp * cos(turnCountX);
		camera.GetForward().z = camera.GetForward().z*cos(turnCountX) - temp * sin(turnCountX);

		//Around X.
		temp = camera.GetForward().z;
		camera.GetForward().z = camera.GetForward().y*sin(turnCountY) + temp * cos(turnCountY);
		camera.GetForward().y = camera.GetForward().y*cos(turnCountY) - temp * sin(turnCountY);
		
		triangle.Draw();
		textureRed.Bind(0);
		mesh.Draw();

		display.Update();

	}

	return 0;
}