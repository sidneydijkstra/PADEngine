#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform MaterialBufferObject{
  vec3 color;
} fragMaterial;
layout(binding = 3) uniform LightBufferObject{
  vec3 position;
} fragLight;

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec3 fragPosition;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(0.2, 1.0, 0.2);

    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(fragLight.position - fragPosition);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.2, 1.0, 0.2);

    vec3 result = (ambient + diffuse) * fragMaterial.color;

    outColor = vec4(result * texture(texSampler, fragTexCoord).rgb, 1.0);
}
