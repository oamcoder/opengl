#glsl vertex
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
out vec4 vertexColor;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
    vertexColor = vec4(aColor.rgb, 1.0f);
}

#glsl fragment
#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
//uniform vec4 vertexColor;

void main() {
    FragColor = vertexColor;
}