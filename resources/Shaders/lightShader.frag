#version 410 core

in vec2 textureCoords;
in mat3 tbnMatrix;
in vec3 toLightVector[4];
in vec3 toCameraVector;

out vec4 outColor;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor[4];
uniform float u_intensity[4];
uniform vec3 u_attenuation[4];

uniform float u_spectralReflectivity;
uniform float u_shineDamper;

uniform sampler2D texture_diffuse;
uniform sampler2D normal_MAP;


void main() {
    vec4 textureColor = texture(texture_diffuse, textureCoords);

    vec4 totalDiffuse = vec4(0.0f);
    vec3 totalSpecular = vec3(0.0f);
    for(int i = 0; i < 4; i++) {
        // Point light extras
        float dist = length(toLightVector[i]);
        float attFactor = u_attenuation[i].x + (u_attenuation[i].y * dist) + (u_attenuation[i].z * (dist * dist));
        // Diffuse lighting with normal map normals
        vec3 unitNormal = normalize(tbnMatrix * (((255.0f/128.0f) * texture(normal_MAP, textureCoords).rgb - 1.0f)));
        vec3 unitToLight = normalize(toLightVector[i]);
        float brightness = max(dot(unitNormal, unitToLight), 0.0f);
        totalDiffuse += (vec4((brightness * u_lightColor[i]), 1.0f) / attFactor) * u_intensity[i];
        // Specular lighting
        vec3 unitToCamera = normalize(toCameraVector);
        vec3 lightDirection = -unitToLight;
        vec3 reflectedLightDir = reflect(lightDirection, unitNormal);
        float specularFactor = max(dot(reflectedLightDir, unitToCamera), 0.0f);
        float dampedFactor = pow(specularFactor, u_shineDamper);
        totalSpecular += (max(dampedFactor * u_spectralReflectivity * u_lightColor[i], 0.0) / (attFactor * 2.0f));
    }
    // Ambient light by letting diffuse not drop to 0
    totalDiffuse = max(totalDiffuse, 0.2f);
    
    outColor = (totalDiffuse * (vec4(u_objectColor, 1.0f) * textureColor)) + vec4(totalSpecular, 1.0f);
}





