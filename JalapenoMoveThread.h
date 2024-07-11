#ifndef JALAPENOMOVETHREAD_H
#define JALAPENOMOVETHREAD_H

#include <QThread>
#include <QLabel>
#include <QWidget>

class JalapenoMoveThread : public QThread
{
    Q_OBJECT

public:
    explicit JalapenoMoveThread(QLabel *label, QWidget *field, int speed, QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void energyChanged(QLabel *zombie, int newEnergy);
    void jalapenoFinished();

private:
    QLabel *label;
    QWidget *field;
    int speed;
    bool stopped;
};

#endif // JALAPENOMOVETHREAD_H
