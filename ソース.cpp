#include<iostream>
#include <GLFW/glfw3.h>
using namespace std;

int main()
{
	cout <<"Hello World"<<endl;

	//glfwInitを使用することでOpenGLを使う準備が行われる
	if (glfwInit() == GL_FALSE)
	{
		cerr << "初期化に失敗した" << endl;
		return 1;
	}

	GLFWwindow* const window(glfwCreateWindow(640, 480, "Hello!", NULL, NULL));
	glfwMakeContextCurrent(window);

	return 0;
}
