#pragma once

#include <glutil.h>

class Cube
{
	f32 width;
	f32 height;
	f32 depth;
	f32* vertices;
	ui32* indices;
	ui32 vao;
	ui32 vbo;
	ui32 ebo;
	bool rgb;
	bool texture;
	bool select;
	int nvert;
	
public:
	Cube(bool select = true, int nvert = 8,f32 width = 1.0f, f32 height = 1.0f, f32 depth = 1.0f)
		: width(width), height(height), depth(depth),nvert(nvert),
		vertices(new f32[24 * nvert]), indices(new ui32[6 * 6]){
		
		f32 wm = width / 2.0f;
		f32 hm = height / 2.0f;
		f32 dm = depth / 2.0f;
		/*f32 temp[] = {
			// posiciones        Normales(colores)          texturas
		   -wm,  hm,  dm,  0.0f,1.0f,1.0f,  0.0f, 1.0f,  // 0
			wm,  hm,  dm,  0.0f,0.0f,0.0f,  1.0f, 1.0f,  // 1
		   -wm, -hm,  dm,  0.0f,0.0f,1.0f,   0.0f, 0.0f,  // 2
			wm, -hm,  dm,  1.0f,0.0f,1.0f,   1.0f, 0.0f,  // 3

			-wm,  hm, -dm, 0.0f,1.0f,0.0f,   1.0f, 1.0f,  // 4
			wm,  hm, -dm,  1.0f,1.0f,1.0f,   0.0f, 1.0f,  // 5 //this
		   -wm, -hm, -dm,  0.0f,0.0f,0.0f,   1.0f, 0.0f,  // 6
			wm, -hm, -dm,  1.0f,0.0f,0.0f,   0.0f, 0.0f,  // 7	

		   -wm,  hm,  dm,  0.0f,1.0f,1.0f,   0.0f, 0.0f,  // 8
			wm,  hm,  dm,  0.0f,0.0f,0.0f, 1.0f, 0.0f,  // 9
		   -wm, -hm,  dm, 0.0f,0.0f,1.0f, 0.0f, 0.0f,  // 10
			wm, -hm,  dm,  1.0f,0.0f,1.0f, 1.0f, 0.0f,  // 11

			-wm,  hm, -dm, 0.0f,1.0f,0.0f, 0.0f, 1.0f,  // 12
			wm,  hm, -dm,  1.0f,1.0f,0.0f, 1.0f, 1.0f,  // 13
		   -wm, -hm, -dm,  0.0f,0.0f,0.0f, 0.0f, 1.0f,  // 14
			wm, -hm, -dm,  1.0f,0.0f,0.0f, 1.0f, 1.0f }; // 15

		for (ui32 i = 0; i < 16 * 8; ++i) {
			vertices[i] = temp[i];
		}*/
		
		if (select == true) {
			f32 temp[] = {
				// posiciones       colores(normales)  texturas   colores
				-wm,  hm,  dm,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // 0
				 wm,  hm,  dm,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  // 1
				-wm, -hm,  dm,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // 2
				 wm, -hm,  dm,     0.0f, 0.0f, 1.0f,   1.0f, 0.0f,  // 3

				-wm,  hm,  dm,      0.0f, 1.0f, 0.0f,  0.0f, 1.0f,   // 4
				 wm,  hm,  dm,      0.0f, 1.0f, 0.0f,  1.0f, 1.0f,   // 5
				-wm,  hm, -dm,      0.0f, 1.0f, 0.0f,  0.0f, 0.0f,   // 6
				 wm,  hm, -dm,      0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // 7

				 wm,  hm,  dm,      1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // 8
				 wm,  hm, -dm,      1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // 9
				 wm, -hm,  dm,      1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // 10
				 wm, -hm, -dm,      1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // 11

				-wm, -hm,  dm,      0.0f, -1.0f, 0.0f,  0.0f, 1.0f, // 12
				 wm, -hm,  dm,      0.0f, -1.0f, 0.0f,  1.0f, 1.0f, // 13
				-wm, -hm, -dm,      0.0f, -1.0f, 0.0f,  0.0f, 0.0f, // 14
				 wm, -hm, -dm,      0.0f, -1.0f, 0.0f,  1.0f, 0.0f, // 15

				-wm,  hm,  dm,      -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 16
				-wm,  hm, -dm,      -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // 17
				-wm, -hm,  dm,      -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // 18
				-wm, -hm, -dm,      -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 19

				-wm,  hm, -dm,      0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // 20
				 wm,  hm, -dm,      0.0f, 0.0f, -1.0f,  0.0f, 1.0f,// 21
				-wm, -hm, -dm,      0.0f, 0.0f, -1.0f,  1.0f, 0.0f, // 22
				 wm, -hm, -dm,      0.0f, 0.0f, -1.0f,  0.0f, 0.0f// 23

			};
			for (ui32 i = 0; i < 24 * nvert; ++i) {
				vertices[i] = temp[i];
			}
		}
		else
		{
			f32 temp[] = {
				// posiciones       colores            normales
				-wm,  hm,  dm,    0.8f, 0.9f, 1.0f,  0.0f, 0.0f, 1.0f,   // 0
				 wm,  hm,  dm,    0.8f, 0.9f, 1.0f,  0.0f, 0.0f, 1.0f,   // 1
				-wm, -hm,  dm,    0.8f, 0.9f, 1.0f,  0.0f, 0.0f, 1.0f,   // 2
				 wm, -hm,  dm,    0.8f, 0.9f, 1.0f,  0.0f, 0.0f, 1.0f,   // 3

				-wm,  hm,  dm,     0.9f, 0.1f, 0.2f,  0.0f, 1.0f, 0.0f,   // 4
				 wm,  hm,  dm,     0.9f, 0.1f, 0.2f,  0.0f, 1.0f, 0.0f,   // 5
				-wm,  hm, -dm,     0.9f, 0.1f, 0.2f,  0.0f, 1.0f, 0.0f,   // 6
				 wm,  hm, -dm,     0.9f, 0.1f, 0.2f,  0.0f, 1.0f, 0.0f,   // 7

				 wm,  hm,  dm,     0.8f, 0.8f, 0.2f,  1.0f, 0.0f, 0.0f,  // 8
				 wm,  hm, -dm,     0.8f, 0.8f, 0.2f,  1.0f, 0.0f, 0.0f,  // 9
				 wm, -hm,  dm,     0.8f, 0.8f, 0.2f,  1.0f, 0.0f, 0.0f,  // 10
				 wm, -hm, -dm,     0.8f, 0.8f, 0.2f,  1.0f, 0.0f, 0.0f,  // 11

				-wm, -hm,  dm,      0.3f, 0.9f, 0.8f, 0.0f, -1.0f, 0.0f, // 12
				 wm, -hm,  dm,      0.3f, 0.9f, 0.8f, 0.0f, -1.0f, 0.0f, // 13
				-wm, -hm, -dm,      0.3f, 0.9f, 0.8f, 0.0f, -1.0f, 0.0f, // 14
				 wm, -hm, -dm,      0.3f, 0.9f, 0.8f, 0.0f, -1.0f, 0.0f, // 15

				-wm,  hm,  dm,     1.0f, 0.5f, 0.2f,  -1.0f, 0.0f, 0.0f,// 16
				-wm,  hm, -dm,     1.0f, 0.5f, 0.2f,  -1.0f, 0.0f, 0.0f,// 17
				-wm, -hm,  dm,     1.0f, 0.5f, 0.2f,  -1.0f, 0.0f, 0.0f,// 18
				-wm, -hm, -dm,     1.0f, 0.5f, 0.2f,  -1.0f, 0.0f, 0.0f,// 19

				-wm,  hm, -dm,      0.2f, 0.9f, 0.3f, 0.0f, 0.0f, -1.0f,  // 20
				 wm,  hm, -dm,      0.2f, 0.9f, 0.3f, 0.0f, 0.0f, -1.0f, // 21
				-wm, -hm, -dm,      0.2f, 0.9f, 0.3f, 0.0f, 0.0f, -1.0f,  // 22
				 wm, -hm, -dm,      0.2f, 0.9f, 0.3f,  0.0f, 0.0f, -1.0f// 23

			};
			for (ui32 i = 0; i < 24 * nvert; ++i) {
				vertices[i] = temp[i];
			}
		}
		
		
		/*for (ui32 i = 0; i < 24*8; ++i) {
			vertices[i] = temp[i];
		}*/
		for (ui32 i = 0; i < 6; ++i) {
			indices[i * 6 + 0] = i * 4 + 0;
			indices[i * 6 + 1] = i * 4 + 1;
			indices[i * 6 + 2] = i * 4 + 2;
			indices[i * 6 + 3] = i * 4 + 1;
			indices[i * 6 + 4] = i * 4 + 2;
			indices[i * 6 + 5] = i * 4 + 3;
		}
		/*ui32 temp2[] = {
			 0,  1,  2,   1,  2,  3,
			 8,  9, 12,   9, 12, 13,
			 1,  5,  3,   3,  5,  7,
			11, 14, 15,  10, 11, 14,
			 0,  4,  6,   0,  2,  6,
			 4,  5,  6,   5,  6,  7 };
		for (ui32 i = 0; i < 6 * 6; ++i) {
			indices[i] = temp2[i];
		}*/
	}
	~Cube() {
		delete[] vertices;
		delete[] indices;
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}
	f32* getVertices() {
		return vertices;
	}
	ui32* getIndices() {
		return indices;
	}
	ui32 getVSize() {
		return 24 * nvert;
	}
	ui32 getISize() {
		return 6 * 6;
	}
	
	ui32 get_VAO() { return vao; }
	ui32 get_VBO() { return vbo; }
	ui32 get_EBO() { return ebo; }

};