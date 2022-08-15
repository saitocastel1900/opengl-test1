#include <cstdlib>
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

int main()
{
	//glfwInitを使用することでOpenGLを使う準備が行われる
	if (glfwInit() == GL_FALSE)
	{
		cerr << "初期化に失敗した" << endl;
		return 1;
	}

	//opengl 3.2を使ってみる
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//ウィンドウを作成する
	GLFWwindow* const window(glfwCreateWindow(640, 480, "HelloWolrd", NULL, NULL));
	if (window==NULL)
	{
		//ウィンドウが作成出来なかった
		cerr << "ウィンドウの作成が出来ませんでした" << endl;
		return 1;
	}

	//プログラム終了時に必ずglfwTerminateが実行される
	//終了直前にglfwTerminateを実行する必要があるが、すべてに追加するのがめんどいためatexitで登録
	//glfwTerminateは終了処理を行う関数(初期化前に戻す)
	atexit(glfwTerminate);

	//作成したウィンドウをOpenGLの処理対象にする
	glfwMakeContextCurrent(window);

	//GLEW
	glewExperimental = GL_TRUE;
	if (glewInit()!=GLEW_OK)
	{
		//GLEWの初期化に失敗した
		cerr << "GLEWの初期化に失敗しました" << endl;
		return 1;
	}

	//カラーバッファの入れ替えタイミングを指定
	glfwSwapInterval(1);

	//背景色の設定（マゼンタ,RGBA）
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

	//ループすることで、ウィンドウを閉じないようにしている
	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		// ウィンドウを消去する(フレームバッファのカラーバッファ)
		//ウィンドウの塗りつぶし
		glClear(GL_COLOR_BUFFER_BIT);
		//
		// ここで描画処理を行う
		//
		// カラーバッファを入れ替える（ダブルバッファリング:ちらつきを防ぐ）
		glfwSwapBuffers(window);
		// イベントを取り出す
		glfwWaitEvents();
	}

	return 0;
}
