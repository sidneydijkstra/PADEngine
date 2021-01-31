#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform MaterialBufferObject{
  vec3 color;
} fragMaterial;

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    //outColor = texture(texSampler, fragTexCoord * 2.0);
    outColor = vec4(fragMaterial.color * texture(texSampler, fragTexCoord).rgb, 1.0);
}
