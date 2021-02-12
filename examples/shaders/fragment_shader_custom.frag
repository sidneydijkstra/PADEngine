#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_gpu_shader_fp64 : enable

layout(binding = 1) uniform DataBuffer{
  dvec2 center;
  double zoom;
  int maxIts;
} fragBuffer;

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec3 fragPosition;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragP;

layout(location = 0) out vec4 outColor;

const int color_steps = 4;
vec4 gradient(vec4 spectrum[color_steps], float step) {
  step = clamp(step, 0.0, 1.0);

  const int lowerbound = int(floor(step*(color_steps-1)));
  const int upperbound = int(ceil(step*(color_steps-1)));

  return mix(spectrum[lowerbound], spectrum[upperbound], step - (lowerbound/(color_steps-1)));
}

void main() {

  double x0 = fragBuffer.center.x + (fragPosition.x / fragBuffer.zoom);
  double y0 = fragBuffer.center.y + (fragPosition.y / fragBuffer.zoom);

  double x = 0;
  double y = 0;

  int iteration = 0;
  int max_iteration = fragBuffer.maxIts;
  while((x*x + y*y) < (2*2) && iteration < max_iteration){
    double xtemp = x*x - y*y + x0;
    y = 2 * x * y + y0;
    x = xtemp;
    iteration++;
  }

  double c = ((iteration * 16) % 1000) / 1000.0f;

  if(iteration == max_iteration){
    c = 0;
  }

  //vec4 colorsA[color_steps] = {vec4(0.0, 1.0, 0, 0), vec4(0.0, 0.0, 1.0, 0), vec4(1.0, 0.0, 0, 0), vec4(1.0, 1.0, 0, 0)};
  //vec4 colorsB[color_steps] = {vec4(1.0, 0, 0, 0), vec4(0.0, 1.0, 0, 0), vec4(0.0, 0.0, 1.0, 0), vec4(1.0, 0.0, 1.0, 0)};
  //vec4 colorsC[color_steps] = {vec4(0.0, 0, 1.0, 0), vec4(1.0, 0.0, 0, 0), vec4(0.0, 1.0, 0, 0), vec4(0.0, 1.0, 1.0, 0)};
  //vec4 colorsD[color_steps] = {vec4(1.0, 1.0, 0, 0.0), vec4(1.0, 0.0, 1.0, 0), vec4(1.0, 1.0, 0, 0), vec4(1.0, 0.0, 0, 0)};
  //float c_step = (int (fragBuffer.zoom.x) % 255) / 255.0f;
  //vec4 colors[color_steps] = {gradient(colorsA, c_step), gradient(colorsB, c_step), gradient(colorsC, c_step), gradient(colorsD, c_step)};

  vec4 colors[color_steps] = {vec4(0.0, 0.0, 0, 0), vec4(0, 1.0, 0.0, 0), vec4(0.0, 1.0, 0, 0), vec4(0, 0, 1.0, 0)};

  outColor = gradient(colors, float(c));
}
