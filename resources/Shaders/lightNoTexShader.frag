#version 410 core

in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;

out vec4 outColor;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor[4];
uniform float u_intensity[4];

uniform float u_spectralReflectivity;
uniform float u_shineDamper;

void main() {
    
    vec4 totalDiffuse = vec4(0.0f);
    vec3 totalSpecular = vec3(0.0f);
    for(int i = 0; i < 4; i++) {
        // Diffuse lighting
        vec3 unitNormal = normalize(surfaceNormal);
        vec3 unitToLight = normalize(toLightVector[i]);
        float brightness = max(dot(unitNormal, unitToLight), 0.0f);
        totalDiffuse += vec4((brightness * u_lightColor[i]), 1.0f) * u_intensity[i];
        // Specular lighting
        vec3 unitToCamera = normalize(toCameraVector);
        vec3 lightDirection = -unitToLight;
        vec3 reflectedLightDir = reflect(lightDirection, unitNormal);
        float specularFactor = max(dot(reflectedLightDir, unitToCamera), 0.0f);
        float dampedFactor = pow(specularFactor, u_shineDamper);
        totalSpecular += max(dampedFactor * u_spectralReflectivity * u_lightColor[i], 0.0);
    }
    // Ambient light by letting diffuse not drop to 0
    totalDiffuse = max(totalDiffuse, 0.2f);
    
    outColor = (totalDiffuse * (vec4(u_objectColor, 1.0f) * vec4(1.0f))) + vec4(totalSpecular, 1.0f);
}





