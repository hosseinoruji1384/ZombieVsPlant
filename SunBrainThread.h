// SunBrainThread.h
#ifndef SUNBRAINTHREAD_H
#define SUNBRAINTHREAD_H

#include <QThread>
#include <QLabel>
#include <QTimer>

class SunBrainThread : public QThread
{
    Q_OBJECT
public:
    explicit SunBrainThread(QLabel *object, QWidget *parent = nullptr);
    void run() override;

signals:
    void sunBrainCollected(QLabel *object);

private:
    QLabel *fallingObject;
    QTimer *moveTimer;
};

#endif // SUNBRAINTHREAD_H
