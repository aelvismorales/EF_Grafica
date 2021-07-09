#pragma once
#include <glutil.h>

enum MovimientoCamara {
	LEFT, RIGHT, UP, DOWN,GOUP,GODOWN
};

class Camara
{
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldup;

	f32 yaw;
	f32 pitch;
	f32 fov;
	f32 speed;
	f32 sensitivity;

public:
	Camara(f32 px=1.0f,f32 py=12.0f,f32 pz=1.0f ,f32 fx=0.0f ,f32 fy=0.0f, f32 fz=-1.0f ,f32 ux=0.0f,f32 uy=1.0f,f32 uz=0.0f,
		f32 yaw = -90.0f, f32 pitch = 0.0f, f32 fov = 45.0f, f32 speed = 8.5, f32 sensitivity = 0.1) :position({ px,py,pz }), front({fx,fy,fz}),
		up({ ux,uy,uz }), worldup({px,py,pz}), yaw(yaw), pitch(pitch), fov(fov), speed(speed), sensitivity(sensitivity)
	{
		updateVectors();
	}
	void inputprocces(MovimientoCamara direccion,f32 deltatime)
	{
		f32 velocidad = speed * deltatime;
		if(direccion==UP)
		{
			position += velocidad * front;
		}
		if(direccion==GOUP)
		{
			
			position += velocidad*up;
		
		}
		if(direccion==LEFT)
		{
			position -= glm::normalize(glm::cross(front, up)) * velocidad;
		}
		if(direccion==DOWN)
		{
			position -= velocidad * front;
		}
		if (direccion == GODOWN)
		{
			position -= velocidad * up;
		}
		if(direccion==RIGHT)
		{
			position += glm::normalize(glm::cross(front, up)) * velocidad;
		}
	}
	
	void mouse_proccess(f32 xoffset, f32 yoffset,bool constrainPitch=true) 
	{
		yaw += xoffset*sensitivity;
		pitch += yoffset*sensitivity;
		if(constrainPitch)
		{
			if (pitch > 89.0f)
			{
				pitch = 89.0f;
		
			}
			else if (pitch < -89.0f)
			{
				pitch = -89.0f;
			}
		}
		updateVectors();
	}
	void scroll_mouse(f64 xoffset,f64 yoffset)
	{
		fov -= (f32)yoffset; //Zoom
		if (fov < 1.0f) { fov = 1.0f; }
		else if (fov > 45.0f) { fov = 45.0f; }
	}
	glm::mat4 getViewM4()
	{
		return glm::lookAt(position, position + front, up);
	}
	
	f32 getFov()
	{
		return fov;
	}
	glm::vec3& getPos() 
	{
		return position;
	}
	void set_speed(f32 spedy)
	{
		speed = spedy;
	}
	glm::vec3& getFront() {
		return front;
	}
private:
	void updateVectors()
	{
		glm::vec3 temp;
		temp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		temp.y = sin(glm::radians(pitch));
		temp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(temp);
		
	}
};