#version 330
in highp vec4 vColor;
out highp vec4 fColor;

void main()
{
   fColor = vColor;
   //fColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
