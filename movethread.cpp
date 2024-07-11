#include "movethread.h"
#include <QDebug>
#include <QThread>

MoveThread::MoveThread(QLabel *label, QWidget *frame, int speed, QObject *parent)
    : QThread(parent), label(label), field(frame), speed(speed), initialEnergy(100), stopped(false)
{
    connect(this, &MoveThread::energyChanged, this, [this,label](int currentEnergy) {
        if (currentEnergy <= 0) {
            QMetaObject::invokeMethod(label, "hide");
            QMetaObject::invokeMethod(label, "deleteLater");
            this->quit(); // Ensure thread cleanup
        }
    });

    connect(this, &MoveThread::positionChanged, this, [this]() {
        emit energyChanged(getEnergy());
    });
}

int MoveThread::getEnergy() const {
    QMutexLocker locker(&mutex);
    return initialEnergy;
}

void MoveThread::setEnergy(int energy) {
    {
        QMutexLocker locker(&mutex);
        initialEnergy = energy;
    }
    emit energyChanged(initialEnergy);
}

bool MoveThread::isStopped() const {
    QMutexLocker locker(&mutex);
    return stopped;
}

void MoveThread::setStopped(bool stop) {
    QMutexLocker locker(&mutex);
    stopped = stop;
}

QLabel* MoveThread::getLabel() const {
    return label;
}

void MoveThread::run() {
    while (!isStopped() && label->geometry().right() < field->geometry().right()) {
        QMetaObject::invokeMethod(label, [this]() {
            label->move(label->x() - 1, label->y());
            emit positionChanged(label->pos());
        }, Qt::QueuedConnection);

        checkCollisionWithBullets();
        QThread::msleep(100);

        if (checkCollisionWithWalnut()) {
            setStopped(true);
            stopTimer.start(10000);
        }
    }

    if (!isStopped()) {
        emit gameOver();
    }

    this->quit();
    wait();       // Wait for the thread to finish and cleanup
}


void MoveThread::checkCollisionWithBullets() {
    QList<QLabel *> bullets = field->findChildren<QLabel *>("bullet");

    foreach (QLabel *bullet, bullets) {
        QRect bulletRect = bullet->geometry();
        QRect zombieRect = label->geometry();

        if (bulletRect.intersects(zombieRect)) {
            {
                QMutexLocker locker(&mutex);
                initialEnergy -= initialEnergy * 0.05;
            }
            emit energyChanged(getEnergy()); // Signal to update energy in UI
            QMetaObject::invokeMethod(bullet, "deleteLater", Qt::QueuedConnection);
            if (getEnergy() <= 0) {
                emit gameOver(); // Signal to handle game over in UI
                setStopped(true);
                break;
            }
        }
    }
}

bool MoveThread::checkCollisionWithWalnut() {
    QList<QLabel *> walnuts = field->findChildren<QLabel *>("walnut");

    for (QLabel *walnut : walnuts) {
        QRect walnutRect = walnut->geometry();
        QRect zombieRect = label->geometry();
        if (zombieRect.intersects(walnutRect)) {
            // Hide and delete walnut in main thread
            QMetaObject::invokeMethod(walnut, "hide", Qt::QueuedConnection);
            QMetaObject::invokeMethod(walnut, "deleteLater", Qt::QueuedConnection);
            // Handle energy change and zombie deletion in main thread
            {
                QMutexLocker locker(&mutex);
                initialEnergy = 0; // Or adjust as needed
            }
            emit energyChanged(getEnergy());
            emit gameOver();

            setStopped(true); // Stop the zombie movement
            return true; // Collision detected and handled
        }
    }
    return false; // No collision detected
}
