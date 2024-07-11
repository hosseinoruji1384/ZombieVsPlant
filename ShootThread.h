#ifndef SHOOTTHREAD_H
#define SHOOTTHREAD_H

#include <QThread>
#include <QLabel>
#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>

class ShootThread : public QThread
{
    Q_OBJECT

public:
    explicit ShootThread(QLabel *shoot, QWidget *frame, QWidget *parent = nullptr);
    ~ShootThread();
     QLabel* getShootLabel() const;

protected:
    void run() override;

signals:
    void hitZombie(QLabel *shoot);

private:
    QLabel *shoot;
    QWidget *frame;
    QMutex mutex1; // Mutex for thread safety
     mutable QMutex mutex;
     QTimer *timer;
private slots:
    void performShootActions();

};

#endif // SHOOTTHREAD_H
