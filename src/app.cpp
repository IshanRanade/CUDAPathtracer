#include "app.h"

#include "pathtracing/pathtracer.cuh"
#include <glm/exponential.hpp>


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
    gui = new GUI(imageWidth, imageHeight, pbo);
    pathtracer = new PathTracer(imageWidth,	imageHeight);
    
    AppDialog *dialog = new AppDialog(app);
    app->installEventFilter(dialog);

    gui->show();

    
    // TEMPss
    // Render the scene immediately and display it
    runCuda();

}

void App::runCuda() {
	std::vector<float> frameBufferData = pathtracer->getFrameBuffer();
	//gui->updateDisplay(frameBufferData);
}
