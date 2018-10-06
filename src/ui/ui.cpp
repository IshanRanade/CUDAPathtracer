#include "ui.h"

#include <QSize>
#include <QPixmap>
#include <QColor>
#include <QPoint>
#include <iostream>


/*
*/
RenderButtonWidget::RenderButtonWidget(QWidget *parent) :
    QWidget(parent) {

    layout = new QVBoxLayout();
    button = new QPushButton("Render");
    layout->addWidget(button);
    setLayout(layout);
}

/*
*/
DisplayImageWidget::DisplayImageWidget(int imageWidth, int imageHeight) :
	imageWidth(imageWidth), imageHeight(imageHeight) {
}

void DisplayImageWidget::initializeGL() {
	initializeOpenGLFunctions();

	int num_texels = imageWidth * imageHeight;
	int num_values = num_texels * 4;
	int size_tex_data = sizeof(GLubyte) * num_values;

	glGenBuffers(1, &pbo);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, size_tex_data, NULL, GL_DYNAMIC_COPY);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &displayTexture);
	glBindTexture(GL_TEXTURE_2D, displayTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void DisplayImageWidget::paintGL() {
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
	glBindTexture(GL_TEXTURE_2D, displayTexture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imageWidth, imageHeight, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
		glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
		glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
		glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
	glEnd();
}

/*
*/
GUI::GUI(int imageWidth, int imageHeight) :
    QMainWindow(), imageWidth(imageWidth), imageHeight(imageHeight) {

    initLayout();
}

void GUI::show() {
    mainWidget->show();
}

void GUI::initLayout() {
    mainWidget = new QWidget();
    mainWidget->setWindowTitle("Path Tracer");

    layout = new QHBoxLayout(this);

    // Add the render button
    renderButtonWidget = new RenderButtonWidget(this);
    layout->addWidget(renderButtonWidget);

	// Add the OpenGL display window
	displayImage = new DisplayImageWidget(imageWidth, imageHeight);
	displayImage->setFixedSize(imageWidth, imageHeight);
	layout->addWidget(displayImage);

    mainWidget->setLayout(layout);
}
