#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform MaterialBufferObject{
  vec3 color;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
} fragMaterial;
layout(binding = 3) uniform LightBufferObject{
  vec3 position;
  vec3 cameraPosition;
  vec3 color;
} fragLight;

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec3 fragPosition;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragP;

layout(location = 0) out vec4 outColor;

void main() {
  vec3 ambient = fragMaterial.ambient * fragLight.color;

  vec3 normal = normalize(fragNormal);
  vec3 lightDir = normalize(fragLight.position - fragP);

  float diff = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = fragLight.color * (diff * fragMaterial.diffuse);

  vec3 viewDir = normalize(fragLight.cameraPosition - fragP);
  vec3 reflectDir = reflect(-lightDir, normal);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), fragMaterial.shininess);
  vec3 specular = fragLight.color * (spec * fragMaterial.specular);

  vec3 result = (ambient + diffuse + specular) * fragMaterial.color;

  outColor = vec4(result * texture(texSampler, fragTexCoord).rgb, 1.0);
}
