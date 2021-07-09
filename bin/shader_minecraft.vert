#version 330 core

layout (location = 0) in vec3 vector_position;
layout (location = 1) in vec2 texture_pos;

out vec2 texture_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
  gl_Position = proj * view * model * vec4(vector_position, 1.0f);
  texture_coord = texture_pos;
}



