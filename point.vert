#version 150 core
in vec4 position;
void main()
{
//頂点座標の情報を送る
gl_Position = position;
}