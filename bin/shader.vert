#version 330 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in vec2 myTexCoord;

out vec3 fragColor;
out vec2 texCoord;
out vec3 frag_Pos;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() 
{
	frag_Pos=vec3(model * vec4(vertPos, 1.0));
	//fragColor = mat3(transpose(inverse(model)))*vertColor;
	fragColor = mat3(transpose(inverse(model))) * vertColor;
	gl_Position = proj * view * vec4(frag_Pos, 1.0);
	
	texCoord = vec2(myTexCoord.x, myTexCoord.y);
}



