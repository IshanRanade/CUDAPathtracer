#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLBuffer>


class GUI;
class App;

/*
 * This class is the button that Renders the framebuffer.
 */
class RenderButtonWidget : public QWidget {
public:
    RenderButtonWidget(QWidget *parent);

private:
    QPushButton *button;
    QVBoxLayout *layout;
};

/*
 * The OpenGL QWidget that holds the buffer to display the rendered image.
 */
class DisplayImageWidget : public QOpenGLWidget, protected QOpenGLFunctions_2_0 {
public:
	DisplayImageWidget(int imageWidth, int imageHeight);

	void initializeGL();
	void initializeBuffers();
	void deleteBuffers();
	void paintGL();

	int imageWidth;
	int imageHeight;

	GLuint pbo;
	GLuint displayTexture;
};

/*
 * This class encapsulates the entire GUI, using QMainWindow.  It holds all the buttons
 * and inputs that affect the path tracer and also an image area that displays the path traced
 * final framebuffer.
 */
class GUI : public QMainWindow {
public:
    GUI(int imageWidth, int imageHeight, App* app);

	App *app;

    void show();

    int imageWidth;
    int imageHeight;

    QWidget *mainWidget;
    QHBoxLayout *layout;
    RenderButtonWidget *renderButtonWidget;
	DisplayImageWidget *displayImageWidget;
};
