// default.frag
#version 330 core

in vec3 vNormal;
in vec3 vFragPos;

uniform vec4 uColor;
uniform vec3 uLightDir;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightDir);

    float ambient = 0.2;
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 result = (ambient + diff) * uColor.rgb;
    FragColor = vec4(result, uColor.a);
}