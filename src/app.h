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

/*
 * This class attaches to a QApplication and listens to keyboard inputs.
 */
class AppDialog : public QObject {
public:
    QApplication *app;

    AppDialog(QApplication *parentApp);

    bool eventFilter(QObject* obj, QEvent* event);
};

/*
 * This class is the main app and implements an MVC.
 * It contains a reference to the GUI, the PathTracer, and the QApplication.
 */
class App {
public:
    GUI *gui;
    PathTracer *pathtracer;
    QApplication *app;

	int imageWidth;
	int imageHeight;

    App(int argc, char **argv);

    int startApp();

    void runCuda();
};
