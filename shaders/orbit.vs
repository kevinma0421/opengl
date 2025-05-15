#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float scaleMultiplier;

void main() {
    float earthRadiusKm = 6371.0;
    vec4 worldPos = model * vec4(aPos / earthRadiusKm, 1.0);
    gl_Position = projection * view * worldPos;

    float dist = length((view * worldPos).xyz);
    gl_PointSize = clamp(scaleMultiplier / dist, 2.0, 10.0);
}