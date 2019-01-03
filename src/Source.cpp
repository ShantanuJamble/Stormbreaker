#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f, 0.5f,
		 -0.5f,0.5f

	};

	unsigned int indices[] = {
		0,1,2,
		3,2,0
	};

	VertexArray *va = new VertexArray();
	VertexBuffer * vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));
	VertexBufferLayout *layout = new VertexBufferLayout();
	layout->Push<float>(2);
	va->AddBuffer(*vb,*layout);

	//Code with index buffer
	IndexBuffer * ib = new IndexBuffer(indices, 6);
	
	
	Shader *shader = new Shader("res/shaders/basic.shader");
	shader->Bind();
	
	va->Unbind();
	vb->UnBind();
	ib->UnBind();
	shader->Unbind();
	
	Renderer renderer;
	float r = 0.0f;
	float incr = 0.05f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		shader->Bind();
		shader->SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		renderer.Draw(*va, *ib, *shader);

		if (r > 1)
			incr = -0.05f;
		else if(r<0.0f)
			incr = 0.05f;
		r += incr;
		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));


		/* Poll for and process events */
		GLCall(glfwPollEvents());
	}
	
	delete(va);
	delete(vb);
	delete(ib);
	delete(shader);

	glfwTerminate();
	return 0;
}