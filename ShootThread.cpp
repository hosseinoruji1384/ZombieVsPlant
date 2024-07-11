#include "ShootThread.h"
#include <QDebug>
#include <QApplication>
#include <QTimer>

ShootThread::ShootThread(QLabel *shoot, QWidget *frame, QWidget *parent)
    : QThread(parent), shoot(shoot), frame(frame)
{
    connect(this, &ShootThread::finished, shoot, &QObject::deleteLater); // Cleanup when thread finishes
}

ShootThread::~ShootThread()
{
    if (timer) {
        timer->stop();
        delete timer;
    }
}

void ShootThread::run()
{
    // Ensure this code runs on the main thread
    QMetaObject::invokeMethod(QApplication::instance(), [this]() {
        timer = new QTimer();
        // Connect the QTimer to the performShootActions slot
        connect(timer, &QTimer::timeout, this, &ShootThread::performShootActions);
        // Start the QTimer with an interval of 50 milliseconds (or any desired interval)
        timer->start(40);
    }, Qt::BlockingQueuedConnection);
    exec();
}

void ShootThread::performShootActions()
{
    if (shoot) {
        qDebug() << "Shoot widget is initialized.";
        qDebug() << "Shoot visibility: " << shoot->isVisible();
        qDebug() << "Shoot enabled: " << shoot->isEnabled();
        if (shoot->isVisible() && shoot->isEnabled()) {
            qDebug() << "Performing shoot actions";
            shoot->move(shoot->x() + 4, shoot->y());
            if (shoot->x() > frame->width()) {
                shoot->hide();
                timer->stop();
                exit();
            }
        }
    } else {
        qDebug() << "Shoot widget is not initialized.";
    }
}
