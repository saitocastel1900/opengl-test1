#version 150 core
//uniform float aspect;
//uniform vec2 size;
//uniform float scale;
//uniform vec2 location;
uniform mat4 modelview;
uniform mat4 projection;
in vec4 position;
void main()
{
//’¸“_À•W‚Ìî•ñ‚ğ‘—‚é
gl_Position =projection* modelview *position;
}