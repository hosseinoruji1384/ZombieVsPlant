#ifndef MOVETHREAD_H
#define MOVETHREAD_H

#include <QThread>
#include <QLabel>
#include <QWidget>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

class MoveThread : public QThread
{
    Q_OBJECT

public:
    explicit MoveThread(QLabel *label, QWidget *frame, int speed, QObject *parent = nullptr);

    int getEnergy() const;
    void setEnergy(int energy);

    bool isStopped() const;
    void setStopped(bool stop);

    QLabel *getLabel() const;

signals:
    void gameOver();
    void energyChanged(int currentEnergy);
    void positionChanged(const QPoint &pos);
    void energyDepleted(QLabel *associatedLabel);
    void projectileHitZombie(QLabel *projectile, QLabel *zombie);
protected:
    void run() override;

private:
    QLabel *label;
    QWidget *field;
    int speed;
    int initialEnergy;
    bool stopped;
    QTimer stopTimer;
     mutable QMutex mutex;
    void checkCollisionWithBullets();
    bool checkCollisionWithWalnut();

};

#endif // MOVETHREAD_H
