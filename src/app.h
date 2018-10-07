#pragma once

#include <globals.h>
#include <QApplication>
#include <QDialog>
#include <QKeyEvent>
#include <ui.h>


class PathTracer;

/*
 * This class is the main app and implements an MVC.
 * It contains a reference to the GUI, the PathTracer, and the QApplication.
 */
class App {
public:
    GUI *gui;
    PathTracer *pathtracer;
    QApplication *qApplication;

	int imageWidth;
	int imageHeight;

	bool render;
	float frame;

    App(int argc, char **argv);

    int startApp();

    void runCuda();
};

/*
 * This class attaches to a QApplication and listens to keyboard inputs.
 */
class AppDialog : public QObject {
public:
	QApplication *qApplication;
	App *app;

	AppDialog(QApplication *parentApp, App *app);

	bool eventFilter(QObject* obj, QEvent* event);
};
