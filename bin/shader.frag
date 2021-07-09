#version 330 core


uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform mat4 modelo;

in vec3 fragColor; // Dato que recibe de colores del vertex shader
in vec2 texCoord;

in vec3 frag_Pos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light; 
uniform sampler2D texture1; //sampler son especificos para los valores de textura
uniform sampler2D texture2;

out vec4 color; //color que finalmente se mostrara en pantalla
  


void main() 
{
	// ambient
    //float ambientStrength = 0.1;
    //vec3 ambient =  material.ambient* lightColor;
  	vec3 ambient  = light.ambient * material.ambient;
	
	// diffuse 
    vec3 norm = normalize(fragColor); //fragColor lo  estoy tomando como mi normal dado que no me reconoce la otra variable
    vec3 lightDir = normalize(vec3(modelo*vec4(lightPos,1.0)) - frag_Pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * lightColor;    // add material.diffuse then i have to delete this
    
	//Specular
	//float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - frag_Pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    vec3 result = (ambient + diffuse + specular)*objectColor; // objectColor
	
	color=texture(texture1,texCoord)*vec4(result,1.0);
}



