// cube_default.frag
#version 330 core
out vec4 FragColor;

uniform vec4 uColor;
uniform vec3 uLightDir;

in vec3 fragNormal;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(uLightDir);

    float diff = max(dot(norm, lightDir), 0.0);
    float ambient = 0.1;
    float brightness = ambient + diff;

    FragColor = uColor * brightness;
}