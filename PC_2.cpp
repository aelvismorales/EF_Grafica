#include <glutil.h>
#include <figures.h>
#include <vaos.h>
#include <camara.h>

#include<cstdio>
#include <random>

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"

using namespace std;

const ui32 FSIZE = sizeof(f32);
const ui32 ISIZE = sizeof(i32);
const ui32 SCR_WIDTH = 960;
const ui32 SCR_HEIGHT = 540;
const f32  ASPECT = (f32)SCR_WIDTH / (f32)SCR_HEIGHT;

Camara* camara = new Camara();
bool firstMouse = true;
f32 yaw = -90.0f;
f32 pitch = 0.0f;
f32 lastX = SCR_WIDTH / 2.0f;  //Posicionando el mouse su inicio
f32 lastY = SCR_HEIGHT / 2.0f;
f32 fov = 45.0f; //Angulo de inclinacion que tendremos y cambiara nuestra pespectiva
f32 sensitivity = 0.1f;

f32 deltaTime = 0.0f;
f32 lastFrame = 0.0f;

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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camara->inputprocces(GOUP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camara->inputprocces(GODOWN, deltaTime);
	}
}

void mouse_Callback(GLFWwindow* window, f64 xpos, f64 ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
			return;
		}
		camara->mouse_proccess((f32)(xpos - lastX), (f32)(lastY - ypos));
		lastX = xpos;
		lastY = ypos;
	}
	else
	{
		firstMouse = true;
	}
}


void scroll_Callback(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
	camara->scroll_mouse(xoffset, yoffset);
}

i32 main() {

	GLFWwindow* window = glutilInit(3, 3, SCR_WIDTH, SCR_HEIGHT, "Terrain?", mouse_Callback, scroll_Callback);

	Shader* shader = new Shader();

	Shader* shader_tierra = new Shader("shader.vert", "shader_tierra.frag");

	Shader* shader_material = new Shader();

	Cube* cubex = new Cube();
	


	vector<vector<int>> maze = mkMaze(20);

	VAO* vao_cubo = new VAO(cubex);
	VAO* vao_cubo_light = new VAO(cubex);

	vao_cubo->inicializar_vaos(true, true, false);
	vao_cubo_light->inicializar_vaos(true, true, false);


	ui32 texture_gold = shader_material->loadTexture("oro_texture.jpg", texture_gold);
	ui32 texture_jade = shader_material->loadTexture("jade.jpg", texture_jade);
	ui32 texture_perla = shader_material->loadTexture("perla.jpg", texture_perla);
	ui32 texture_ruby = shader_material->loadTexture("ruby.jpg", texture_ruby);
	
	vector<glm::vec3> metaposition;
	for (ui32 x = 0; x < maze.size(); x++)
	{
		for (ui32 y = 0; y < maze.size(); y++)
		{
			if (maze[x][y] == 3)
			{
				metaposition.push_back(glm::vec3(float(x), 12.0f, float(y)));
			}
		}
	}

	float distancia = 0.0f;
	
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Ligth Properties - cubo de luz
		
		//light properties 
		
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.8f); // low influence
		glm::mat4 projection = glm::perspective(glm::radians(camara->getFov()), ASPECT, 0.1f, 100.0f);
		f32 theta = (f32)glfwGetTime();
		glm::mat4 model = glm::mat4(1.0f);
		
		//Wall
		shader_material->useProgram();
		shader_material->setVec3("objectColor", 1.0f, 1.0f, 1.0f);

		shader_material->setVec3("material.ambient", 0.135f, 0.2225f, 0.1575f);
		shader_material->setVec3("material.diffuse", 0.54f, 0.89f, 0.63f);
		shader_material->setVec3("material.specular", 0.316228f, 0.316228f, 0.316228f);
		shader_material->setF32("material.shininess", 0.1f*128);

		//light properties 
		shader_material->setVec3("light.ambient", ambientColor.x, ambientColor.y, ambientColor.z);
		shader_material->setVec3("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);
		shader_material->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		shader_material->setVec3("viewPos", camara->getPos().x, camara->getPos().y, camara->getPos().z);
		shader_material->setVec3("lightPos", camara->getPos().x, camara->getPos().y, camara->getPos().z);
		shader_material->setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);
		shader_material->setMat4("modelo", glm::mat4(1.0f));

		//Laberinto
		shader_material->setMat4("proj", projection);
		shader_material->setMat4("view", camara->getViewM4());

		glBindVertexArray(vao_cubo->get_VAO());
		
		for (ui32 x = 0; x < maze.size(); x++)
		{
			for (ui32 y = 0; y < maze.size(); y++)
			{
				if (maze[x][y] == 0)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, texture_gold);
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(float(x), 12.0f, float(y)));
					distancia = sqrtl(pow((camara->getPos().x - float(x)), 2) + pow((camara->getPos().z - float(y)), 2));
			
					if (distancia < 2.0f)
					{
						shader_material->setVec3("material.ambient", 0.05375f, 0.05f, 0.06625);
						shader_material->setVec3("material.diffuse", 0.18275f, 0.17f, 0.22525f);
						shader_material->setVec3("material.specular", 0.332741f, 0.328634f, 0.346435f);
						shader_material->setF32("material.shininess", 0.3f * 128);
					
					}
					else
					{
						shader_material->setVec3("material.ambient", 0.135f, 0.2225f, 0.1575f);
						shader_material->setVec3("material.diffuse", 0.54f, 0.89f, 0.63f);
						shader_material->setVec3("material.specular", 0.316228f, 0.316228f, 0.316228f);
						shader_material->setF32("material.shininess", 0.1f * 128);
					
					}

					shader_material->setMat4("model", model);
					glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);

				}
				if (maze[x][y] == 3)
				{
					model = glm::mat4(1.0f);
					glBindTexture(GL_TEXTURE_2D, texture_ruby);
					model = glm::translate(model, glm::vec3(float(x),12.0f,float(y)));
					shader_material->setMat4("model", model);
					glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
				}
			
			}
		}
		
		distancia = sqrtl(pow((camara->getPos().x - metaposition[1].x), 2) + pow((camara->getPos().z - metaposition[1].z),2));
		if(distancia<2.0f)
		{
			
			glm::vec3 lightColor2(1.0f, 1.0f, 1.0f);
			lightColor2.x = sin(glfwGetTime() * 2.0f);
			lightColor2.y = sin(glfwGetTime() * 0.7f);
			lightColor2.z = sin(glfwGetTime() * 1.3f);

			lightColor.x = lightColor2.x;
			lightColor.y = lightColor2.y;
			lightColor.z = lightColor2.z;
			shader_tierra->useProgram();
			

			shader_tierra->setMat4("proj", projection);
			shader_tierra->setVec3("mycolor", lightColor2.x, lightColor2.y, lightColor2.z);
			shader_tierra->setMat4("view", camara->getViewM4());

			glBindVertexArray(vao_cubo_light->get_VAO());

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(metaposition[1].x, metaposition[1].y + 2.0f, metaposition[1].z+2.0));
			shader_tierra->setMat4("model", model);

			glBindVertexArray(vao_cubo->get_VAO());
			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);


			///////////////////////////////////////////////
			
			shader->useProgram();
			shader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
			//Material properties
			shader->setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
			shader->setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
			shader->setVec3("material.specular", 1.0f, 1.0f, 1.0f);
			shader->setF32("material.shininess",32.0f);

			//light properties 
			glm::vec3 diffuseColor = lightColor2 * glm::vec3(0.5f); // decrease the influence lightColor2
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
			shader->setVec3("light.ambient", ambientColor.x, ambientColor.y, ambientColor.z);
			shader->setVec3("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);
			shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

			shader->setVec3("viewPos", camara->getPos().x, camara->getPos().y, camara->getPos().z);
			shader->setVec3("lightPos", metaposition[1].x, metaposition[1].y + 2.0f, metaposition[1].z + 2.0);
			shader->setVec3("lightColor", lightColor2.x, lightColor2.y, lightColor2.z); //lightColor2.x, lightColor2.y, lightColor2.z
			shader->setMat4("modelo", glm::mat4(1.0f));
		
			/*shader->setMat4("proj", projection);
			shader->setMat4("view", camara->getViewM4());
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(metaposition[1].x, metaposition[1].y + 5.0f, metaposition[1].z + 2.0));
			shader->setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);*/

			//Jade
			shader_material->useProgram();
			shader_material->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
			//Material properties
			shader_material->setVec3("material.ambient", 0.135f, 0.2225f, 0.1575f);
			shader_material->setVec3("material.diffuse", 0.54f, 0.89f, 0.63f);
			shader_material->setVec3("material.specular", 0.316228f, 0.316228f, 0.316228f);
			shader_material->setF32("material.shininess", 0.1f*128);

			glBindVertexArray(vao_cubo->get_VAO());
			//glActiveTexture(GL_TEXTURE1);
			model = glm::mat4(1.0f);
			glBindTexture(GL_TEXTURE_2D, texture_jade);
			model = glm::translate(model, glm::vec3(metaposition[1].x, metaposition[1].y + 2.0f, metaposition[1].z + 6.0)); // x,y,z
			shader_material->setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
			
			//Perla
			shader_material->useProgram();
			shader_material->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
			//Material properties
			shader_material->setVec3("material.ambient", 0.25f, 0.20725f, 0.20725f);
			shader_material->setVec3("material.diffuse", 1.0f, 0.829f, 0.829f);
			shader_material->setVec3("material.specular", 0.296648f, 0.296648f, 0.296648f);
			shader_material->setF32("material.shininess", 0.088f);

			glBindVertexArray(vao_cubo->get_VAO());
			glBindTexture(GL_TEXTURE_2D, texture_perla);
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(metaposition[1].x+2.0f, metaposition[1].y + 2.0f, metaposition[1].z + 6.0)); // x,y,z
			shader_material->setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);

			//Ruby
			shader_material->useProgram();
			shader_material->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
			//Material properties
			shader_material->setVec3("material.ambient", 0.1745f, 0.01175f, 0.01175f);
			shader_material->setVec3("material.diffuse", 0.61424f, 0.04136f, 0.04136f);
			shader_material->setVec3("material.specular", 0.727811f, 0.626959f, 0.626959f);
			shader_material->setF32("material.shininess", 0.6f);

			glBindVertexArray(vao_cubo->get_VAO());
			
			model = glm::mat4(1.0f);
			glBindTexture(GL_TEXTURE_2D, texture_ruby);
			model = glm::translate(model, glm::vec3(metaposition[1].x - 2.0f, metaposition[1].y + 2.0f, metaposition[1].z + 6.0)); // x,y,z
			shader_material->setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
		
		}
		else
		{
			lightColor.x = 1.0f;
			lightColor.y = 1.0f;
			lightColor.z = 1.0f;
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	delete shader_tierra;
	delete shader;
	delete shader_material;
	delete vao_cubo;
	delete vao_cubo_light;

	maze.clear();
	cubex->~Cube();
	return 0;
}