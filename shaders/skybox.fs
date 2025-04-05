#version 330 core

in vec3 TexCoords;       // from vertex shader
out vec4 FragColor;

uniform samplerCube skybox;

void main() {
    FragColor = texture(skybox, TexCoords);
}

