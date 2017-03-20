#version 410 core
in vec2 textureCoords;

out vec4 color;

uniform vec3 u_objectColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main() {
    vec4 textureColor = texture(texture_diffuse1, textureCoords);
    
    color = vec4(u_objectColor, 1.0f) * textureColor;
}
