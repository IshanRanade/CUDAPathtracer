#pragma once

#include <globals.h>
#include <iostream>
#include <QtWidgets>
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QKeyEvent>
#include <ui.h>


class PathTracer;

class RenderThread : public QThread {
public:
	RenderThread(QObject *parent) :
		QThread(parent) {
	};

	void run() override {
		std::cout << "here" << std::endl;
	}
};



/*
 * This class is the main app and implements an MVC.
 * It contains a reference to the GUI, the PathTracer, and the QApplication.
 */
class App {
public:
    GUI *gui;
    PathTracer *pathtracer;
    QApplication *qApplication;

	QThread *renderThread;

	int imageWidth;
	int imageHeight;

	bool render;
	float frame;

    App(int argc, char **argv);

    int startApp();

    void runCuda();
	void nothing() {

	}
};

/*
 * This class attaches to a QApplication and listens to keyboard inputs.
 */
class AppDialog : public QObject {
public:
	QApplication *qApplication;
	App *app;

	int x;

	AppDialog(QApplication *parentApp, App *app);

	bool eventFilter(QObject* obj, QEvent* event);
};
