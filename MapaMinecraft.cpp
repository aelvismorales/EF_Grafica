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

using namespace std;
//*****************************************


//******************************************
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

glm::vec3 PosCuboLuz(1.0f, 10.0f, 1.0f);
glm::vec3 PosComida(5.0f, 10.0f, 1.0f);

glm::vec3 Snake(1.0f,1.0f,1.0f);
/**
 * keyboard input processing
 **/
void processInput(GLFWwindow* window) {
	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
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
	}*/

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) 
	{
		PosCuboLuz.x = PosCuboLuz.x;
		PosCuboLuz.y =PosCuboLuz.y;
		PosCuboLuz.z += 0.2;

	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		PosCuboLuz.x = PosCuboLuz.x;
		PosCuboLuz.y =PosCuboLuz.y;
		PosCuboLuz.z -= 0.2;

	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		PosCuboLuz.x +=0.2f ;
		PosCuboLuz.y=PosCuboLuz.y;
		PosCuboLuz.z = PosCuboLuz.z;

	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		PosCuboLuz.x -= 0.2f;
		PosCuboLuz.y =PosCuboLuz.y;
		PosCuboLuz.z = PosCuboLuz.z;

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
	
	Shader* figure_avion = new Shader("shader_avion.vert", "shader_avion.frag");

	

	ui32 g = 30;
	std::vector<glm::vec3> positions_tierra(g * g);//PINTA
	for (ui32 i = 0; i < g; ++i) {
		for (ui32 j = 0; j < g; ++j) {
			f32 x = i - g / 2.0f;
			f32 z = j - g / 2.0f;
			f32 y = 10.f;
			positions_tierra[i * g + j] = glm::vec3(x, y, z);
		}
	}


	VAO* vao_cubo = new VAO(cubex);
	VAO* vao_cubo_light = new VAO(cubex);


	vao_cubo->inicializar_vaos(true, true,false);
	vao_cubo_light->inicializar_vaos(true, true, false);


	//ui32 texture1 = shader->loadTexture("arena.jpg", texture1);
	//ui32 texture2 = shader->loadTexture("tierra.jpg", texture2);
	ui32 texture3 = shader->loadTexture("roca.jpg", texture3);
	ui32 texture4 = shader->loadTexture("cesped.jpg", texture4);

	//ui32 texture_gold = shader_material->loadTexture("oro_texture.jpg", texture_gold);
	//ui32 texture_jade = shader_material->loadTexture("jade.jpg", texture_jade);
	//ui32 texture_perla = shader_material->loadTexture("perla.jpg", texture_perla);
	ui32 texture_ruby = shader_material->loadTexture("ruby.jpg", texture_ruby);

	ui32 limite = 0.5;
	

	srand(time(NULL));

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader_tierra->useProgram();
		//Ligth Properties
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);


		glm::mat4 projection = glm::perspective(glm::radians(camara->getFov()), ASPECT, 0.1f, 100.0f);
		f32 theta = (f32)glfwGetTime();

		glm::mat4 model = glm::mat4(1.0f);


		
		shader->useProgram();
		shader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
		//Material properties
		shader->setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
		shader->setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
		shader->setVec3("material.specular", 1.0f, 1.0f, 1.0f);
		shader->setF32("material.shininess", 32.0f);

		//light properties 
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
		shader->setVec3("light.ambient", ambientColor.x, ambientColor.y, ambientColor.z);
		shader->setVec3("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);
		shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		shader->setVec3("viewPos", camara->getPos().x, camara->getPos().y, camara->getPos().z);
		shader->setVec3("lightPos", 0.0f,25.0f,0.0f);
		shader->setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);
		shader->setMat4("modelo", glm::mat4(1.0f));


		shader->setMat4("proj", projection);
		shader->setMat4("view", camara->getViewM4());

		glBindVertexArray(vao_cubo->get_VAO());



		shader_material->useProgram();
		shader_material->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
		//Material properties
		shader_material->setVec3("material.ambient", 0.24725f, 0.1995f, 0.0745f);
		shader_material->setVec3("material.diffuse", 0.75164f, 0.60648f, 0.22648f);
		shader_material->setVec3("material.specular", 0.628281f, 0.555802f, 0.366065f);
		shader_material->setF32("material.shininess", 0.4f);

		//light properties 
		shader_material->setVec3("light.ambient", ambientColor.x, ambientColor.y, ambientColor.z);
		shader_material->setVec3("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);
		shader_material->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		shader_material->setVec3("viewPos", camara->getPos().x, camara->getPos().y, camara->getPos().z);
		shader_material->setVec3("lightPos", 0.0f, 25.0f, 0.0f);
		shader_material->setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);
		shader_material->setMat4("modelo", glm::mat4(1.0f));


		shader_material->setMat4("proj", projection);
		shader_material->setMat4("view", camara->getViewM4());

		glBindVertexArray(vao_cubo->get_VAO());
		//glm::mat4 
		model = glm::mat4(1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_ruby);
		model = glm::translate(model, PosComida);
		shader_material->setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);

		if (sqrtl(pow((PosCuboLuz.x - PosComida.x), 2) + pow((PosCuboLuz.y - PosComida.y ), 2) + pow((PosCuboLuz.z - PosComida.z ), 2)) < 1.0f)
		{
			PosComida.x = 1 + rand() % (10);

			PosComida.z = 1 + rand() % (10);

			Snake.z += 0.5f;
			
		}

		//Ruby
		shader_material->useProgram();
		shader_material->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
		//Material properties
		shader_material->setVec3("material.ambient", 0.1745f, 0.01175f, 0.01175f);
		shader_material->setVec3("material.diffuse", 0.61424f, 0.04136f, 0.04136f);
		shader_material->setVec3("material.specular", 0.727811f, 0.626959f, 0.626959f);
		shader_material->setF32("material.shininess", 0.6f);

		glBindVertexArray(vao_cubo->get_VAO());
		//glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture4);
		model = glm::mat4(1.0f);
		model = glm::translate(model, PosCuboLuz); // x,y,z
		model = glm::scale(model, glm::vec3(Snake.x, Snake.y, Snake.z));
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
;
		glBindTexture(GL_TEXTURE_2D, texture3);

		for (ui32 i = 0; i < positions_tierra.size(); ++i) 
		{
			model = glm::mat4(1.0f);
			if (i >= 0 && i <= 29 || i%30==0 || i >= 870 && i <= 899  || i % 30 == 29)
			{
				model = glm::translate(model, glm::vec3(positions_tierra[i].x, positions_tierra[i].y, positions_tierra[i].z)); // x,y,z
				
				shader_material->setMat4("model", model);
				glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
			}

			}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	delete shader_tierra;
	delete shader;
	delete shader_material;

	delete figure_avion;

	cubex->~Cube();

	return 0;
}