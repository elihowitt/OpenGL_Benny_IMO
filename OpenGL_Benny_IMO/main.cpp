#include<iostream>
#include<GL/glew.h>

#include"display.h"
#include"mesh.h"
#include"shader.h"
#include"texture.h"

int main(int argc, char**argv)
{
	Display display(800, 600, "Hello world");


	Vertex vertices[] = 
						{ Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)),
						  Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,1.0)),
						  Vertex(glm::vec3(0,0.5,0), glm::vec2(1.0,0.0)) };
	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
	
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");

	while (!display.IsClosed())
	{
		display.Clear( (158/255.0), (100/255.0), (215/255.0), 1.0);
		shader.Bind();
		texture.Bind(0);
		mesh.Draw();

		display.Update();
	}
	
	return 0;
}