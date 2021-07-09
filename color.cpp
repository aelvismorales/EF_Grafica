#include <glutil.h>
#include <figures.h>
#include <vaos.h>
#include <camara.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>


const ui32 FSIZE = sizeof(f32);
const ui32 ISIZE = sizeof(i32);
const ui32 SCR_WIDTH = 960;
const ui32 SCR_HEIGHT = 540;
const f32  ASPECT = (f32)SCR_WIDTH / (f32)SCR_HEIGHT;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Camara* camara=new Camara();
bool firstMouse = true;
f32 lastX = SCR_WIDTH / 2.0f;  //Posicionando el mouse su inicio
f32 lastY = SCR_HEIGHT / 2.0f;
f32 deltaTime = 0.0f;
f32 lastFrame = 0.0f;

f32* makeVertices(ui32 xblocks, ui32 yblocks, ui32 comps,
	f32 from, f32 to) {
	f32* vertices = new f32[xblocks * yblocks * comps];
	f32 incx = (to - from) / (xblocks - 1);
	f32 incy = (to - from) / (yblocks - 1);
	f32* c = new f32[comps];
	for (ui32 i = 0; i < comps; ++i) {
		c[i] = 0.0f;
	}
	c[2] = to;                             // z component
	for (ui32 x = 0; x < xblocks; ++x) {
		c[0] = from;                         // x component
		ui32 offx = x * yblocks * comps;
		for (ui32 y = 0; y < yblocks; ++y) {
			c[1] = sin(c[0] * c[2] * 3.0f);  // y component
			c[3] = 1.0f - c[1] / 2.0f + 0.5f;//colores
			ui32 offy = offx + y * comps;
			for (ui32 k = 0; k < comps; ++k) {
				vertices[offy + k] = c[k];
			}
			c[0] += incy;
		}
		c[2] -= incx;
	}
	return vertices;
}

ui32* makeIdxs(ui32 xblocks, ui32 yblocks) {
	ui32* idxs = new ui32[(xblocks - 1) * (yblocks - 1) * 6];

	for (ui32 x = 1; x < xblocks; ++x) {
		ui32 offx = (x - 1) * (yblocks - 1) * 6;
		for (ui32 y = 1; y < yblocks; ++y) {
			ui32 offy = offx + (y - 1) * 6;
			idxs[offy + 0] = (x - 1) * yblocks + y - 1;
			idxs[offy + 1] = (x - 1) * yblocks + y;
			idxs[offy + 2] = x * yblocks + y - 1;
			idxs[offy + 3] = (x - 1) * yblocks + y;
			idxs[offy + 4] = x * yblocks + y - 1;
			idxs[offy + 5] = x * yblocks + y;
		}
	}
	return idxs;
}

/**
 * keyboard input processing
 **/
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camara->inputprocces(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camara->inputprocces(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camara->inputprocces(DOWN, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camara->inputprocces(RIGHT, deltaTime);
	}
}
void mouse_Callback(GLFWwindow* window, f64 xpos, f64 ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	f32 xoffset = xpos - lastX; // cuanto se ha movido en X 
	f32 yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	camara->mouse_proccess(xoffset, yoffset);
}

void scroll_Callback(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
	camara->scroll_mouse(xoffset, yoffset);
}

i32 main() {
	GLFWwindow* window = glutilInit(3, 3, SCR_WIDTH, SCR_HEIGHT, "Terrain?", mouse_Callback, scroll_Callback);
	Shader* shader = new Shader(); //lightingShader
	
	Shader* lightCubeshader = new Shader("bin","resources/textures","shader.vert","shader2.frag");

	Cube* cubex = new Cube();

	ui32 n = 1; // cantidad de cubos que tendremos
	std::vector<glm::vec3> positions(n*n);
	for (ui32 i = 0; i < n; ++i)
	{
		for (ui32 j = 0; j < n; ++j)
		{
			f32 x = i - n / 2.0f;
			f32 z = j - n / 2.0f;
			f32 y = 0.0f;
			positions[i * n + j] = glm::vec3(x, y, z);

		}

	}
	VAO* vao_simple = new VAO(shader,cubex);
	VAO* vao_lightCube = new VAO(lightCubeshader, cubex);

	vao_simple->inicializar_vaos();
	vao_lightCube->inicializar_vaos();

	
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader->useProgram();
		shader->setVec3("objectColor",1.0f,0.5f,0.31f);
		shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);


		glm::mat4 projection = glm::perspective(glm::radians(camara->getFov()), ASPECT, 0.1f, 100.0f);
		shader->setMat4("proj", projection);
		shader->setMat4("view",camara->getViewM4());

		glBindVertexArray(vao_simple->get_VAO());
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, positions[0]);
		//f32 theta = (f32)glfwGetTime();
		//model = glm::rotate(model, theta, glm::vec3(0.3f, 0.6f, 0.9f));
		shader->setMat4("model", model);

		glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
		
		lightCubeshader->useProgram();
		lightCubeshader->setMat4("proj", projection);
		lightCubeshader->setMat4("view", camara->getViewM4());
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightCubeshader->setMat4("model", model);
		glBindVertexArray(vao_lightCube->get_VAO());
		glDrawElements(GL_TRIANGLES, 6 * 6,GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	vao_lightCube->~VAO();
	vao_simple->~VAO();

	delete shader;
	delete lightCubeshader;
	cubex->~Cube();

	return 0;
}