#include "app.h"

#include "pathtracing/pathtracer.cuh"
#include <cuda_gl_interop.h>
#include <sceneloader.h>
#include <iostream>


AppDialog::AppDialog(QApplication *parentApp, App *app) :
    qApplication(parentApp), app(app) {
}

bool AppDialog::eventFilter(QObject* obj, QEvent* event) {
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key()==Qt::Key_Escape) {
            qApp->exit();
		}
		else if (key->key()==Qt::Key_Q) {
			app->render = false;
		}
    } else {
		// Run the pathtrace routine
		if (app->render) {
			app->runCuda();
			app->gui->displayImageWidget->update();
		}
    }
	return QObject::eventFilter(obj, event);
}


int App::startApp() {
    return qApplication->exec();
}

App::App(int argc, char **argv) :
	render(false), imageWidth(1280), imageHeight(720), frame(0) {

    qApplication = new QApplication(argc, argv);
    gui = new GUI(imageWidth, imageHeight, this);
    pathtracer = new PathTracer(imageWidth,	imageHeight);

	gui->show();
    
    AppDialog *dialog = new AppDialog(qApplication, this);
    qApplication->installEventFilter(dialog);

	loadScene("../scenes/test.json");
}

void App::runCuda() {
	void *pbo_dptr = NULL;

	cudaGraphicsResource_t resource = 0;
	cudaGraphicsGLRegisterBuffer(&resource, gui->displayImageWidget->pbo, cudaGraphicsRegisterFlagsNone);
	cudaGraphicsMapResources(1, &resource, NULL);
	size_t size;
	cudaGraphicsResourceGetMappedPointer(&pbo_dptr, &size, resource);

	pathtracer->pathtrace(pbo_dptr, frame);

	cudaGraphicsUnmapResources(1, &resource, NULL);
	cudaGraphicsUnregisterResource(resource);

	frame++;
}

void App::loadScene(std::string file) {
	imageWidth = 1280;
	imageHeight = 720;
	frame = 0;

	gui->imageWidth = imageWidth;
	gui->imageHeight = imageHeight;
	gui->displayImageWidget->imageWidth = imageWidth;
	gui->displayImageWidget->imageHeight = imageHeight;
	gui->displayImageWidget->setFixedSize(imageWidth, imageHeight);
	gui->displayImageWidget->deleteBuffers();
	gui->displayImageWidget->initializeBuffers();
	gui->displayImageWidget->update();
	gui->update();

	pathtracer = new PathTracer(imageWidth, imageHeight);
	render = true;

	gui->show();
}
