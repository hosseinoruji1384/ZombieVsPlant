#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include <QProgressBar>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QTimer>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QThreadPool>
#include "movethread.h"
#include "JalapenoMoveThread.h"
#include "ShootThread.h"
#include "energymanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void closeEvent(QCloseEvent *event)override;
private slots:
    void gameOver();
    void onProjectileHitZombie(QLabel *projectile);
   void updateCornometer();

private:
    Ui::MainWindow *ui;
    QList<MoveThread *> moveThreads;
    QList<QLabel *> zombies;
    QList<QLabel *> plants;
    QMap<QString, QString> labelMap;
    QMap<QString, int> speedMap;
    QMap<QString, QString> plantslabel;
    QMap<QString, QString> shoot;
    QMap<QString, QString> food;
    QMap<QLabel*, QProgressBar*> zombieProgressBars;
    QLabel *currentProjectile;
    QProgressBar *energyProgressBar;
    QLabel *currentLabel;
    bool gameEnded;
    QStringList zombieNames ;
    int gridRows;
    int gridCols;
    int cellWidth;
    int cellHeight;
    EnergyManager *energyManager;
    QMap<QLabel*, int> zombieEnergyMap;
    QPoint snapToCell(const QPoint &pos);
    bool isZombieInRow(int y);
    void updateProjectilePosition();
    void updateEnergy(int currentEnergy);
    void updateEnergyProgressBar(int currentEnergy);
    bool checkProjectileZombieCollision(QLabel *projectile, QLabel *zombie);
    void dropRandomObject();
    void setupZombieLabels();
    void jalapenoEnergyChanged(QLabel *zombie, int damage);
    void stopThreads();
    ShootThread *shootThread;
    QTimer *timer;
    int elapsedTime;

 };

#endif // MAINWINDOW2_H
