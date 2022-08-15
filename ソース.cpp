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
