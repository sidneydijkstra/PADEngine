#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform DataBuffer{
  vec2 center;
  vec2 zoom;
  int maxIts;
} fragBuffer;

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec3 fragPosition;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragP;

layout(location = 0) out vec4 outColor;

float map(float value, float min1, float max1, float min2, float max2){
  float perc = (value - min1) / (max1 - min1);
  return perc * (max2 - min2) + min2;
}

void main() {

  //float x0 = map(fragPosition.x, -1, 1, -1.25, 1);
  //float y0 = map(fragPosition.y, -1, 1, -0.5, 1);

  float x0 = fragBuffer.center.x + (fragPosition.x / fragBuffer.zoom.x);
  float y0 = fragBuffer.center.y + (fragPosition.y / fragBuffer.zoom.y);

  float x = 0;
  float y = 0;

  int iteration = 0;
  int max_iteration = fragBuffer.maxIts;
  while((x*x + y*y) < (2*2) && iteration < max_iteration){
    float xtemp = x*x - y*y + x0;
    y = 2 * x * y + y0;
    x = xtemp;
    iteration++;
  }

  float c = ((iteration * 16) % 255) / 255.0f;

  if(iteration == max_iteration){
    c = 0;
  }

  outColor = vec4(c, c, c, 1.0);
}
