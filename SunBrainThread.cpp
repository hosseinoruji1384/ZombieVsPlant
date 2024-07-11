#include "SunBrainThread.h"

SunBrainThread::SunBrainThread(QLabel *object, QWidget *parent)
    : QThread(parent), fallingObject(object), moveTimer(nullptr)
{
    // Ensure fallingObject is set as a child of the parent widget (if necessary)
    if (fallingObject)
        fallingObject->setParent(parent);
}

void SunBrainThread::run()
{
    moveTimer = new QTimer();
    connect(moveTimer, &QTimer::timeout, this, [this]() {
        if (fallingObject) {
            fallingObject->move(fallingObject->x(), fallingObject->y() + 5);
            if (fallingObject->y() > fallingObject->parentWidget()->height()) {
                emit sunBrainCollected(fallingObject); // Signal when the object is collected
                moveTimer->stop();
                moveTimer->deleteLater();
                this->quit();
            }
        }
    });

    moveTimer->start(50);
    exec();
}
