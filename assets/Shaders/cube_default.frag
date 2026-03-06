// cube_default.frag
#version 330 core
out vec4 FragColor;

in vec3 fragNormal;

uniform vec3 uLightDir;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(uLightDir);

    float diff = max(dot(norm, lightDir), 0.0); // never negative
    float ambient = 0.1; // minimum brightness so dark sides aren't pitch black

    float brightness = ambient + diff;
    FragColor = vec4(vec3(0.8, 0.3, 0.02) * brightness, 1.0);
}