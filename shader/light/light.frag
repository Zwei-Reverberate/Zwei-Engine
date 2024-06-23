#version 450

const int LIGHT_TYPE_POINT = 0;
const int LIGHT_TYPE_AMBIENT = 1;

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

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;


vec3 calPointLight(Light light)
{    
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(fragNormal, lightDir), 0.0);

    vec3 viewDir = normalize(ubo.viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(fragNormal, halfwayDir), 0.0), 64);

    vec3 diffuse = diff * light.color * light.intensity;
    vec3 specular = spec * light.color * light.intensity;

    return diffuse + specular;
}

vec3 claAmbient(Light light)
{
    return light.color * light.intensity;
}

void main() 
{
    vec3 resColor = vec3(0);

    for(int i = 0; i < ubo.lightNum; ++i)
    {
        if(ubo.lights[i].type == LIGHT_TYPE_POINT)
        {
            resColor += calPointLight(ubo.lights[i]);
        }
        else if(ubo.lights[i].type == LIGHT_TYPE_AMBIENT)
        {
            resColor += claAmbient(ubo.lights[i]);
        }
    }

    outColor = vec4(resColor, 1.0);
}

