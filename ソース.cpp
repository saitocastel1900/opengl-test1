#include <cstdlib>
#include<iostream>
#include<fstream>
#include <GL/glew.h>
#include<vector>
#include<memory>
#include <GLFW/glfw3.h>
#include"Shape.h"
using namespace std;


// プログラムオブジェクトのリンク結果を表示する
// program: プログラムオブジェクト名
GLboolean printProgramInfoLog(GLuint program)
{
	// リンク結果を取得する
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;
	// シェーダのリンク時のログの長さを取得する
	GLsizei bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
	if (bufSize > 1)
	{
		// シェーダのリンク時のログの内容を取得する
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}
	return static_cast<GLboolean>(status);
}

/// <summary>
/// 
/// </summary>
/// <param name="shader"></param>
/// <param name="str"></param>
/// <returns></returns>
GLboolean printShaderInfoLog(GLuint shader,const char *str)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status==GL_FALSE)
	{
		cerr << "コンパイラエラーです" << str << endl;
	}
	// シェーダのコンパイル時のログの長さを取得する
	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
	if (bufSize > 1)
	{
		// シェーダのコンパイル時のログの内容を取得する
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}
	return static_cast<GLboolean>(status);
}


/// <summary>
/// 
/// </summary>
/// <param name="vsrc"></param>
/// <param name="fsrc"></param>
/// <returns></returns>
GLuint createProgram(const char* vsrc, const char* fsrc)
{
	const GLuint program(glCreateProgram());

	if (vsrc != NULL)
	{
		const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);

		if (printShaderInfoLog(vobj, "vertex shader"))glAttachShader(program, vobj);
		glDeleteShader(vobj);
	}

		if (fsrc!=NULL) 
		{
			const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
			glShaderSource(fobj,1,&fsrc,NULL);
			glCompileShader(fobj);

			if (printShaderInfoLog(fobj, "fragment shader"))glAttachShader(program,fobj);
			glDeleteShader(fobj);
		}

		glBindAttribLocation(program,0,"position");
		glBindFragDataLocation(program,0,"fragment");
		glLinkProgram(program);

		if (printProgramInfoLog(program))return program;

		glDeleteProgram(program);
		return 0;
	}

// シェーダのソースファイルを読み込んだメモリを返す
// name: シェーダのソースファイル名
// buffer: 読み込んだソースファイルのテキスト
bool readShaderSource(const char* name, std::vector<GLchar>& buffer)
{
	// ファイル名が NULL だった
	if (name == NULL) return false;
	// ソースファイルを開く
	std::ifstream file(name, std::ios::binary);
	if (file.fail())
	{
		// 開けなかった
		std::cerr << "Error: Can't open source file: " << name << std::endl;
		return false;
	}
	// ファイルの末尾に移動し現在位置（＝ファイルサイズ）を得る
	file.seekg(0L, std::ios::end);
	GLsizei length = static_cast<GLsizei>(file.tellg());
	// ファイルサイズのメモリを確保
	buffer.resize(length + 1);
	// ファイルを先頭から読み込む
	file.seekg(0L, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';
	if (file.fail())
	{
		// うまく読み込めなかった
		std::cerr << "Error: Could not read souce file: " << name << std::endl;
		file.close();
		return false;
	}
	// 読み込み成功
	file.close();
	return true;
}

GLuint loadProgram(const char* vert, const char* frag)
{
	// シェーダのソースファイルを読み込む
	std::vector<GLchar> vsrc;
	const bool vstat(readShaderSource(vert, vsrc));
	std::vector<GLchar> fsrc;
	const bool fstat(readShaderSource(frag, fsrc));
	// プログラムオブジェクトを作成する
	return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}
// 矩形の頂点の位置
constexpr Object::Vertex rectangleVertex[] =
{
{ -0.5f, -0.5f },
{ 0.5f, -0.5f },
{ 0.5f, 0.5f },
{ -0.5f, 0.5f }
};


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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	// 図形データを作成する
	unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

	/*
	static constexpr GLchar vsrc[] =
		"#version 150 core\n"
		"in vec4 position;\n"
		"void main()\n"
		"{\n"
		" gl_Position = position;\n"
		"}\n";
	static constexpr GLchar fsrc[] =
		"#version 150 core\n"
		"out vec4 fragment;\n"
		"void main()\n"
		"{\n"
		" fragment = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";
		*/

	const GLuint program(loadProgram("point.vert", "point.frag"));

	//ループすることで、ウィンドウを閉じないようにしている
	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		// ウィンドウを消去する(フレームバッファのカラーバッファ)
		//ウィンドウの塗りつぶし
		glClear(GL_COLOR_BUFFER_BIT);
		//
		// ここで描画処理を行う
		glUseProgram(program);

		// 図形を描画する
		shape->draw();
		// カラーバッファを入れ替える（ダブルバッファリング:ちらつきを防ぐ）
		glfwSwapBuffers(window);
		// イベントを取り出す
		glfwWaitEvents();
	}

	return 0;
}
