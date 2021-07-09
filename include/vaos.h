#pragma once
#include <glutil.h>
#include <figures.h>

class VAO
{
	ui32 vao;
	ui32 vbo;
	ui32 ebo;
	bool rgb;
	bool texture;
	bool normal;
	Cube* cubito;
public:
	VAO(Cube* cubito):cubito(cubito){}

	void inicializar_vaos(bool rgb,bool texture,bool normal) 
	{
		glGenVertexArrays(1,&vao);
		glGenBuffers(1, &vbo);		
		glBindVertexArray(vao);

		if (cubito->getISize() > 0) {
			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i32) * cubito->getISize(), cubito->getIndices(), GL_STATIC_DRAW);
		}
		
		if (rgb == false && texture == false && normal==false ) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * cubito->getVSize(), cubito->getVertices(), GL_STATIC_DRAW);
			// posiciones
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
			glEnableVertexAttribArray(0);
		}
		else if(rgb == true && texture == false && normal == true)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * cubito->getVSize(), cubito->getVertices(), GL_STATIC_DRAW);
			// posiciones
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(f32), (void*)0);
			glEnableVertexAttribArray(0);
			// colores
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(f32), (void*)(3 * sizeof(f32)));
			glEnableVertexAttribArray(1);
			//normal
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(f32), (void*)(6 * sizeof(f32)));
			glEnableVertexAttribArray(2);

		}
		else if (texture==true && rgb == false && normal == false)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * cubito->getVSize(), cubito->getVertices(), GL_STATIC_DRAW);
			// posiciones
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
			glEnableVertexAttribArray(0);
			// textures
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
			glEnableVertexAttribArray(2);
		}
		else if(rgb == true && texture == true && normal == false)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * cubito->getVSize(), cubito->getVertices(), GL_STATIC_DRAW);
			// posiciones
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)0);
			glEnableVertexAttribArray(0);
			// colores
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(3 * sizeof(f32)));
			glEnableVertexAttribArray(1);
			// textures
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(6 * sizeof(f32)));
			glEnableVertexAttribArray(2);
		}

		glEnable(GL_DEPTH_TEST);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
		//lCullFace(GL_FRONT_AND_BACK);
		//glFrontFace(GL_CW);
		
	}
	ui32 get_VAO() { return vao; }
	ui32 get_VBO() { return vbo; }
	ui32 get_EBO() { return ebo; }
	~VAO()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}
};