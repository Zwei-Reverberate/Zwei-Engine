#version 450

 struct Trans
 {
     mat4 model;
     mat4 view;
     mat4 proj;
 };

 struct Light 
 {
    vec3 position;
    float intensity;
    vec3 color;
    float cutoff;
    vec3 direction;
    float outerCutoff;
    int type;
};

layout(binding = 0) uniform UniformBufferObject 
{
   Trans trans;
   Light lights[10];
   vec3 viewPos;
   int lightNum;
}ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec3 outNormal;

void main() 
{
    mat4 trans =  ubo.trans.proj * ubo.trans.view * ubo.trans.model;
    gl_Position = trans * vec4(inPosition, 1.0);

    outPosition = inPosition;
    outNormal = inNormal;
}