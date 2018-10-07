#include "app.h"

#include "pathtracing/pathtracer.cuh"
#include <glm/exponential.hpp>
#include <cuda_gl_interop.h>
#include <QtConcurrent/qtconcurrentrun.h>

AppDialog::AppDialog(QApplication *parentApp, App *app) :
    qApplication(parentApp), app(app), x(0) {
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
		else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
		// Run the pathtrace routine
		if (x >= 0) {
			x++;
			//std::cout << "pathtrace" << std::endl;
			//app->qApplication->processEvents();
			app->runCuda();
			app->gui->displayImage->update();
			//app->nothing();
			//app->gui->displayImage->paintGL();
			//return true;
			//app->qApplication->processEvents();
			return QObject::eventFilter(obj, event);
		}
		return QObject::eventFilter(obj, event);
    }
    return false;
}

int App::startApp() {
    return qApplication->exec();
}

App::App(int argc, char **argv) :
	render(true), imageWidth(1280), imageHeight(720), frame(0) {

    qApplication = new QApplication(argc, argv);
	renderThread = new QThread(qApplication);
    gui = new GUI(imageWidth, imageHeight, this);
	gui->initLayout();
    pathtracer = new PathTracer(imageWidth,	imageHeight);

	gui->show();

	std::cout << qApplication->focusWidget() << std::endl;
    
    AppDialog *dialog = new AppDialog(qApplication, this);
    qApplication->installEventFilter(dialog);

    // Pathtrace based on current frame
	//while (true) {
	//QProcess *process = new QProcess((QObject*)this);
		
	//}
	//runCuda();
	
	//QFuture<void> future = QtConcurrent::run(this, &App::runCuda);
}



void App::runCuda() {
	//while (true) {
		//std::cout << "here" << std::endl;
		//continue;
		void *pbo_dptr = NULL;

		cudaGraphicsResource_t resource = 0;
		cudaGraphicsGLRegisterBuffer(&resource, gui->displayImage->pbo, cudaGraphicsRegisterFlagsNone);
		cudaGraphicsMapResources(1, &resource, NULL);
		size_t size;
		cudaGraphicsResourceGetMappedPointer(&pbo_dptr, &size, resource);

		
		pathtracer->pathtrace(pbo_dptr, frame);

		cudaGraphicsUnmapResources(1, &resource, NULL);
		cudaGraphicsUnregisterResource(resource);

		//std::cout << frame << std::endl;
		frame++;

		//gui->displayImage->repaint();

		//gui->displayImage->paintGL();
		//gui->update();
		
	//}
	//std::vector<float> frameBufferData = pathtracer->getFrameBuffer();
	//gui->updateDisplay(frameBufferData);
}
