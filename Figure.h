#pragma once
#include <glutil.h>


#include <fstream>
using namespace std;
struct Figure {
	float* Vertices;
	unsigned int* Triangles;
	int nVertices;
	int nTriangles;
	bool rgb = false, texture = false;
	unsigned int VAO, VBO, EBO;

	~Figure() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		delete[] Vertices;
		delete[] Triangles;
	}

	void registerFigure() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);


		glBindVertexArray(VAO);


		if (this->nTriangles > 0) {
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * this->nTriangles * sizeof(unsigned int), this->Triangles, GL_STATIC_DRAW);
		}

		if (!this->rgb && !this->texture) {
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, 3 * this->nVertices * sizeof(float), this->Vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		else if (this->rgb) {
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, 6 * this->nVertices * sizeof(float), this->Vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}

		else if (this->texture) {
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, 5 * this->nVertices * sizeof(float), this->Vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);

		}
	}

	void drawFigure() {
		glBindVertexArray(this->VAO);
		if (this->nTriangles > 0)
			glDrawElements(GL_TRIANGLES, this->nTriangles * 3, GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, this->nVertices);
	}

	void loadTexture(std::string path, unsigned int& texture)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;

		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	glm::mat4 translate(glm::mat4 transformacion, float a, float b, float c) {
		return glm::translate(transformacion, glm::vec3(a, b, c));
	}

	glm::mat4 rotate(glm::mat4 transformacion, float angle, float a, float b, float c) {
		return glm::rotate(transformacion, angle, glm::vec3(a, b, c));
	}

	glm::mat4 scale(glm::mat4 transformacion, float a, float b, float c) {
		return glm::scale(transformacion, glm::vec3(a, b, c));
	}

	void read(std::string nameFile, Figure* figure, bool texture, bool rgb) {
		ifstream file(nameFile, ios::_Noreplace);
		char line[128];
		string aux;

		if (file.fail())
			cout << "Can't read the file" << endl;
		else {

			file.getline(line, '\n');

			file >> figure->nVertices >> figure->nTriangles >> aux;
			if (!rgb && !texture) {
				figure->Vertices = new float[int(figure->nVertices) * 3];
				for (int i = 0; i < figure->nVertices; i++)
					file >> figure->Vertices[3 * i] >> figure->Vertices[3 * i + 1] >> figure->Vertices[3 * i + 2];
			}

			else if (texture) {
				figure->Vertices = new float[int(figure->nVertices) * 5];
				for (int i = 0; i < figure->nVertices; i++)
					file >> figure->Vertices[5 * i] >> figure->Vertices[5 * i + 1] >> figure->Vertices[5 * i + 2] >> figure->Vertices[5 * i + 3] >> figure->Vertices[5 * i + 4];
				figure->texture = true;
			}
			else if (rgb) {
				figure->Vertices = new float[int(figure->nVertices) * 6];
				for (int i = 0; i < figure->nVertices; i++)
					file >> figure->Vertices[6 * i] >> figure->Vertices[6 * i + 1] >> figure->Vertices[6 * i + 2] >> figure->Vertices[6 * i + 3] >> figure->Vertices[6 * i + 4] >> figure->Vertices[6 * i + 5];
				figure->rgb = true;
			}

			figure->Triangles = new unsigned int[int(figure->nTriangles) * 3];

			for (int i = 0; i < figure->nTriangles; i++)
				file >> aux >> figure->Triangles[3 * i] >> figure->Triangles[3 * i + 1] >> figure->Triangles[3 * i + 2];

			file.close();
		}
	}

};