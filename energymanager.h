#ifndef ENERGYMANAGER_H
#define ENERGYMANAGER_H

#include <QObject>
#include <QLabel>
#include <QProgressBar>
#include <QThread>
#include <QMutex>

class EnergyManager : public QObject
{
    Q_OBJECT

public:
    explicit EnergyManager(QObject *parent = nullptr);

    void monitorProgressBar(QProgressBar *progressBar, QLabel *associatedLabel);

signals:
    void energyDepleted(QLabel *associatedLabel);

private slots:
    void onValueChanged(int value);

private:
    QMutex mutex;
};

#endif // ENERGYMANAGER_H
