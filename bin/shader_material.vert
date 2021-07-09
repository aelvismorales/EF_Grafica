#version 330 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in vec3 aNormal;
//vertColor


out vec3 Normal;
out vec3 frag_Pos;
out vec3 fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() 
{
	frag_Pos=vec3(model * vec4(vertPos, 1.0));
	//fragColor = mat3(transpose(inverse(model)))*aNormal;
	Normal = mat3(transpose(inverse(model))) * aNormal;
	fragColor=vertColor;
	gl_Position = proj * view * vec4(frag_Pos, 1.0);
	

}



