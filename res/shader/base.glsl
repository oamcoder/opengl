#glsl vertex
#version 330 core
layout (location = 0) in vec2 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
}

#glsl fragment
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(0.2f, 0.5f, 0.2f, 1.0f);
}