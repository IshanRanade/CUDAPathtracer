#include "app.h"

#include "pathtracing/pathtracer.cuh"
#include <glm/exponential.hpp>
#include <cuda_gl_interop.h>

AppDialog::AppDialog(QApplication *parentApp) :
    app(parentApp) {
}

bool AppDialog::eventFilter(QObject* obj, QEvent* event) {
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key()==Qt::Key_Escape) {
            app->exit();
        } else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}

int App::startApp() {
    return app->exec();
}

App::App(int argc, char **argv) {
	imageWidth = 1280;
	imageHeight = 720;

    app = new QApplication(argc, argv);
    gui = new GUI(imageWidth, imageHeight);
    pathtracer = new PathTracer(imageWidth,	imageHeight);
    
    AppDialog *dialog = new AppDialog(app);
    app->installEventFilter(dialog);

    gui->show();

    
    // Pathtrace based on current frame
	//while (true) {
	//QProcess *process = new QProcess((QObject*)this);
		void *pbo_dptr = NULL;

		cudaGraphicsResource_t resource = 0;
		cudaGraphicsGLRegisterBuffer(&resource, gui->displayImage->pbo, cudaGraphicsRegisterFlagsNone);
		cudaGraphicsMapResources(1, &resource, NULL);
		size_t size;
		cudaGraphicsResourceGetMappedPointer(&pbo_dptr, &size, resource);

		pathtracer->pathtrace(pbo_dptr, 0);

		cudaGraphicsUnmapResources(1, &resource, NULL);
		cudaGraphicsUnregisterResource(resource);

		gui->displayImage->paintGL();
	//}

}

void App::runCuda() {
	//std::vector<float> frameBufferData = pathtracer->getFrameBuffer();
	//gui->updateDisplay(frameBufferData);
}
