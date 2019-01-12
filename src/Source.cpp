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

#include "GLM/glm.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "GLM/mat4x4.hpp"
#include "GLM/gtc/matrix_transform.hpp"

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
		-1.0f, -1.0f, 0.0f,
		 0.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	VertexArray *va = new VertexArray();
	VertexBuffer * vb = new VertexBuffer(positions, 4* 3 * sizeof(float));
	VertexBufferLayout *layout = new VertexBufferLayout();
	layout->Push<float>(3);
	va->AddBuffer(*vb,*layout);

	//Code with index buffer
	IndexBuffer * ib = new IndexBuffer(indices, 12);
	
	
	Shader *shader = new Shader("res/shaders/basic.shader");
	shader->Bind();
	
	va->Unbind();
	vb->UnBind();
	ib->UnBind();
	shader->Unbind();
	
	Renderer renderer;
	renderer.EnableFetures(GL_DEPTH_TEST);
	//Animation stuff
	float r = 0.0f;
	float incr = 0.05f;

	float trans_incr = 0.005f;
	float triOffset = 0.0f;
	float max_limit = 0.7f;
	int direction = 1 ;
	
	float curAngle = 0.0f;
	const float toRadians = 3.14159265f / 180.0f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();
		
		//Tramnslation stuff
		if (direction)
		{
			triOffset += trans_incr;
		}
		else {
			triOffset -= trans_incr;
		}

		if (abs(triOffset) >= max_limit)
		{
			direction = !direction;
		}
		
		//Rotation stuff
		curAngle += 0.5f;
		if (curAngle >= 360)
		{
			curAngle -= 360;
		}

		glm::mat4 model{ 1.0f };
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(triOffset, 0.0f,  triOffset));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		shader->Bind();
		shader->SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		shader->SetUniformMatrix4f("u_Model", model);

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