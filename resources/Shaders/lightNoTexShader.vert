#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;

uniform vec3 u_lightPosition[4];
uniform mat4 u_transform;
uniform mat4 u_projection;
uniform mat4 u_view;

void main() {
    vec4 objPosition = u_transform * vec4(position, 1.0);
    gl_Position = u_projection * u_view * objPosition;
    
    surfaceNormal = (u_transform * vec4(normal, 0.0)).xyz;
    for(int i = 0; i < 4; i++) { toLightVector[i] = u_lightPosition[i] - objPosition.xyz; }
    toCameraVector = (inverse(u_view) * vec4(0.0,0.0,0.0,1.0)).xyz - objPosition.xyz;
}
