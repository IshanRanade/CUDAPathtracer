#include "app.h"

#include "pathtracing/pathtracer.cuh"


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

void App::renderAndDisplayScene() {
    std::vector<float> frameBufferData = pathtracer->getFrameBuffer();
    gui->updateDisplay(frameBufferData);
}

App::App(int argc, char **argv) {
    app = new QApplication(argc, argv);
    gui = new GUI();
    pathtracer = new PathTracer(gui->imageWidth, gui->imageHeight);
    
    AppDialog *dialog = new AppDialog(app);
    app->installEventFilter(dialog);

    gui->show();
    

    // TEMP
    // Render the scene immediately and display it
    renderAndDisplayScene();

}
