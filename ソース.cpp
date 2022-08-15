#include <cstdlib>
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

int main()
{
	//glfwInit���g�p���邱�Ƃ�OpenGL���g���������s����
	if (glfwInit() == GL_FALSE)
	{
		cerr << "�������Ɏ��s����" << endl;
		return 1;
	}

	//�E�B���h�E���쐬����
	GLFWwindow* const window(glfwCreateWindow(640, 480, "HelloWolrd", NULL, NULL));
	if (window==NULL)
	{
		//�E�B���h�E���쐬�o���Ȃ�����
		cerr << "�E�B���h�E�̍쐬���o���܂���ł���" << endl;
		return 1;
	}

	//�v���O�����I�����ɕK��glfwTerminate�����s�����
	//�I�����O��glfwTerminate�����s����K�v�����邪�A���ׂĂɒǉ�����̂��߂�ǂ�����atexit�œo�^
	//glfwTerminate�͏I���������s���֐�(�������O�ɖ߂�)
	atexit(glfwTerminate);

	//�쐬�����E�B���h�E��OpenGL�̏����Ώۂɂ���
	glfwMakeContextCurrent(window);

	//�w�i�F�̐ݒ�i�}�[���^,RGBA�j
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

	//���[�v���邱�ƂŁA�E�B���h�E����Ȃ��悤�ɂ��Ă���
	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		// �E�B���h�E����������(�t���[���o�b�t�@�̃J���[�o�b�t�@)
		//�E�B���h�E�̓h��Ԃ�
		glClear(GL_COLOR_BUFFER_BIT);
		//
		// �����ŕ`�揈�����s��
		//
		// �J���[�o�b�t�@�����ւ���i�_�u���o�b�t�@�����O:�������h���j
		glfwSwapBuffers(window);
		// �C�x���g�����o��
		glfwWaitEvents();
	}

	return 0;
}
