#include<iostream>
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
						{ Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)),
						  Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,1.0)),
						  Vertex(glm::vec3(0,0.5,0), glm::vec2(1.0,0.0)) };
	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
	
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while (!display.IsClosed())
	{
		display.Clear( (42/255.0), (120/255.0), (99/255.0), 0.9);

		float sinCounter = sinf(counter), cosCounter = cos(counter);

		transform.GetPos().x = sinf(counter);
		transform.GetPos().z = sinf(counter);
		transform.GetRot().x = counter;
		transform.GetRot().y = counter;
		transform.GetRot().z = counter;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);


		mesh.Draw();

		display.Update();
		counter += 0.001f;
	}
	
	return 0;
}