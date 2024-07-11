#include "JalapenoMoveThread.h"
#include <QThread>
#include <QLabel>

JalapenoMoveThread::JalapenoMoveThread(QLabel *label, QWidget *field, int speed, QObject *parent)
    : QThread(parent), label(label), field(field), speed(speed), stopped(false)
{
}

void JalapenoMoveThread::run()
{
    while (!stopped && label->geometry().right() < field->geometry().right()) {
        QThread::msleep(speed);
        // Move jalapeno to the right
        QPoint newPos = label->pos();
        newPos.setX(newPos.x() + 10);
        label->move(newPos);
        // Check collision with zombies
        QList<QLabel *> zombies = field->findChildren<QLabel *>();
        foreach (QLabel *zombie, zombies) {
            if (zombie->property("isZombie").toBool() && zombie->geometry().intersects(label->geometry())) {
                emit energyChanged(zombie, 20);
                label->hide();
                label->deleteLater();
                stopped = true;
                return;
            }
        }
    }

    if (!stopped) {
        emit jalapenoFinished();
    }
}
