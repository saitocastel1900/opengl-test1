#include<iostream>
#include <GLFW/glfw3.h>
using namespace std;

int main()
{
	cout <<"Hello World"<<endl;

	//glfwInit���g�p���邱�Ƃ�OpenGL���g���������s����
	if (glfwInit() == GL_FALSE)
	{
		cerr << "�������Ɏ��s����" << endl;
		return 1;
	}

	GLFWwindow* const window(glfwCreateWindow(640, 480, "Hello!", NULL, NULL));
	glfwMakeContextCurrent(window);

	return 0;
}
