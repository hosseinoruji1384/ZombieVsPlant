#include "form.h"
#include "ui_form.h"
#include <QDrag>
#include <QMimeData>
#include <QLabel>
#include <stdexcept>


MainWindow2::MainWindow2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Form)
    , currentLabel(nullptr)
    , gameEnded(false)
    , timer(new QTimer(this))
    , elapsedTime(0)

{
    ui->setupUi(this);
    ////////////////////////////////
    QTimer *fallingObjectTimer = new QTimer(this);
    connect(fallingObjectTimer, &QTimer::timeout, this, &MainWindow2::dropRandomObject);
    fallingObjectTimer->start(4000);
    QStringList plantNames = {"peashooter", "two_peashooter", "walnut", "plum_mine", "jelapino", "boomerang"};
    zombieNames = {"regular", "bucked_head", "leafhead", "tall", "astronaut", "purplehair"};
       for (const QString &name : plantNames + zombieNames) {
           QLabel *label = findChild<QLabel*>(name);
           if (label) {
               label->setAcceptDrops(true);
           }
       }
       setAcceptDrops(true);
//impelement the ui picture for drag and drop
ui->peashooter->setAcceptDrops(true);
ui->two_peashooter->setAcceptDrops(true);
ui->walnut->setAcceptDrops(true);
ui->plum_mine->setAcceptDrops(true);
ui->jelapino->setAcceptDrops(true);
ui->boomerang->setAcceptDrops(true);
ui->regular->setAcceptDrops(true);
ui->bucked_head->setAcceptDrops(true);
ui->leafhead->setAcceptDrops(true);
ui->tall->setAcceptDrops(true);
ui->astronaut->setAcceptDrops(true);
ui->purplehair->setAcceptDrops(true);
//setAcceptDrops(true);
 // Map source labels to the specific appearing labels
  labelMap["regular"] = ":/regular zombie_transparent.png";
  labelMap["bucked_head"] = ":/Bucket head zombie_trasparent.png";
  labelMap["leafhead"] = ":/leaf hair zombie_transparent.png";
  labelMap["tall"] = ":/tall zombie_transparent.png";
  labelMap["astronaut"] = ":/astronaut zombie_transparent.png";
  labelMap["purplehair"] = ":/purple hair zombie_transparent.png";
/////////////////////
  plantslabel["boomerang"]=":/boomrang_transparent.png";
  plantslabel["jelapino"]=":/jalapino_transparent.png";
  plantslabel["peashooter"]=":/peashooter";
  plantslabel["plum_mine"]=":/plum mine_transparent.png";
  plantslabel["two_peashooter"]=":/two_peashooter_transparent.png";
  plantslabel["walnut"]=":/walnut_transparent.png";
  ///////////////////
  speedMap["regular"] = 200;
  speedMap["bucked_head"] = 400;
  speedMap["leafhead"] = 200;
  speedMap["astronaut"] = 200;
  speedMap["purplehair"] = 200;
  speedMap["tall"] = 200;
  ////////////////////////////////
  shoot["peashooter"]=":/shoot.png";
  shoot["two_peashooter"]=":/shoot2.png";
  shoot["boomerang"]=":/shoot3.png";
  ///////////////////
food["sun"]=":/sun.png";
food["brain"]=":/Brain.png";
  // Calculate grid cell dimensions
      gridRows = 6;
      gridCols = 15;
      cellWidth = (width() ) / gridCols;
      cellHeight = (height()) / gridRows;
 /////////////////////////////////////
  //ui->cornometerProgressBar->setStyleSheet(
    //  "QProgressBar {"
    //  "    border: 2px solid grey;"
     // "    border-radius: 5px;"
    //  "    text-align: center;"
     // "    background: white;"
     // "}"
     // "QProgressBar::chunk {"
     // "    background-color: green;"
     // "    width: 20px;"
     // "}" );

  // Connect the timer signal to the update slot
  connect(timer, &QTimer::timeout, this, &MainWindow2::updateCornometer);
  timer->start(1000);
}
MainWindow2::~MainWindow2()
{
    stopThreads();

    for (auto it = zombieProgressBars.begin(); it!= zombieProgressBars.end(); ++it) {
        delete it.key();
        delete it.value();
    }
    zombieProgressBars.clear();
    delete ui;
}

///------------------------------------------------------------------
void MainWindow2::stopThreads()
{
    for (auto thread : moveThreads) {
        if (thread->isRunning()) {
            thread->requestInterruption();
            thread->wait(); // Wait for the thread to finish
        }
        delete thread;
    }
    moveThreads.clear();
}

///-----------------------------------------------------------------
    void MainWindow2::mousePressEvent(QMouseEvent *event)
    {
        try {
            if (event->button() == Qt::LeftButton) {
                QLabel *label = dynamic_cast<QLabel*>(childAt(event->pos()));
                if (label && label->objectName().startsWith("regular")) {
                    int brainProgress = ui->zombiesProgressBar->value();
                    if (brainProgress < 10) {
                        qDebug() << "Cannot pick regular zombie yet. Brain progress: " << brainProgress;
                        return;
                    }else
                         ui->zombiesProgressBar->setValue(brainProgress - 10);
                }
                if (label && (label->objectName().startsWith("tall") || label->objectName().startsWith("leafhead"))) {
                    int brainProgress = ui->zombiesProgressBar->value();
                    if (brainProgress < 15) {
                        qDebug() << "Cannot pick tall or leafhead zombie yet. Brain progress: " << brainProgress;
                        return;
                    }else
                     ui->zombiesProgressBar->setValue(brainProgress - 15);
                }
                if (label && (label->objectName().startsWith("bucked_head") || label->objectName().startsWith("astronaut"))) {
                    int brainProgress = ui->zombiesProgressBar->value();
                    if (brainProgress < 20) {
                        qDebug() << "Cannot pick buckethead or astronaut zombie yet. Brain progress: " << brainProgress;
                        return;
                    }else
                        ui->zombiesProgressBar->setValue(brainProgress - 20);
                }
                if (label && label->objectName().startsWith("purplehair")) {
                    int brainProgress = ui->zombiesProgressBar->value();
                    if (brainProgress < 80) {
                        qDebug() << "Cannot pick purplehair zombie yet. Brain progress: " << brainProgress;
                        return;
                    }else
                         ui->zombiesProgressBar->setValue(brainProgress - 80);
                }
                if (label && label->objectName().startsWith("peashooter")) {
                    int sunProgress = ui->plantsProgressBar->value();
                    if (sunProgress < 10) {
                        qDebug() << "Cannot pick peashooter plant yet. Sun progress: " << sunProgress;
                        return;
                    }else
                         ui->plantsProgressBar->setValue(sunProgress - 10);
                }
                if (label && (label->objectName().startsWith("two_peashooter") || label->objectName().startsWith("walnut"))) {
                    int sunProgress = ui->plantsProgressBar->value();
                    if (sunProgress < 15) {
                        qDebug() << "Cannot pick two_peashooter or walnut plant yet. Sun progress: " << sunProgress;
                        return;
                    }else
                        ui->plantsProgressBar->setValue(sunProgress - 15);
                }
                if (label && label->objectName().startsWith("boomerang")) {
                    int sunProgress = ui->plantsProgressBar->value();
                    if (sunProgress < 20) {
                        qDebug() << "Cannot pick boomerang plant yet. Sun progress: " << sunProgress;
                        return;
                    }else
                         ui->plantsProgressBar->setValue(sunProgress - 20);
                }
                if (label && label->objectName().startsWith("jelapino")) {
                    int sunProgress = ui->plantsProgressBar->value();
                    if (sunProgress < 30) {
                        qDebug() << "Cannot pick jelapino plant yet. Sun progress: " << sunProgress;
                        return;
                    }else
                         ui->plantsProgressBar->setValue(sunProgress - 30);
                }
                if (label && label->objectName().startsWith("plum_mine")) {
                    int sunProgress = ui->plantsProgressBar->value();
                    if (sunProgress < 40) {
                        qDebug() << "Cannot pick plum_mine plant yet. Sun progress: " << sunProgress;
                        return;
                    }else
                          ui->plantsProgressBar->setValue(sunProgress - 40);
                }
                currentLabel = label;
                // Create a QDrag object
                QDrag *drag = new QDrag(this);
                QMimeData *mimeData = new QMimeData;
                // Set a textual representation of the object being dragged
                mimeData->setText("DraggedLabel");
                drag->setMimeData(mimeData);
                // Set the pixmap to be dragged (scaled to the label size)
                drag->setPixmap(label->pixmap().scaled(label->size(), Qt::KeepAspectRatio));
                // Start the drag operation
                Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
            }
            QLabel *label = dynamic_cast<QLabel*>(childAt(event->pos()));
            // Handling the sun and brain items for the game
            if (label && (label->objectName() == "sun" || label->objectName() == "brain")) {
                if (label->objectName() == "sun") {
                    int newValue = ui->plantsProgressBar->value() + 5;
                    ui->plantsProgressBar->setValue(newValue > 100 ? 100 : newValue);
                } else if (label->objectName() == "brain") {
                    int newValue = ui->zombiesProgressBar->value() + 5;
                    ui->zombiesProgressBar->setValue(newValue > 100 ? 100 : newValue);
                }
                label->deleteLater();
            } else {
                QMainWindow::mousePressEvent(event);
            }
        } catch (const std::exception &e) {
            qDebug() << "Exception in mousePressEvent: " << e.what();
        } catch (...) {
            qDebug() << "Unknown exception in mousePressEvent";
        }
    }
///----------------------------------------------------------------
    void MainWindow2::mouseMoveEvent(QMouseEvent *event)
    {
          try {
        if (currentLabel && event->buttons() & Qt::LeftButton) {
            // Move the label with the mouse movement
            currentLabel->move(event->globalPos() - QPoint(currentLabel->width() / 2, currentLabel->height() / 2));
        }
        } catch (const std::exception &e) {
              qDebug() << "Exception in mouseMoveEvent: " << e.what();
          } catch (...) {
              qDebug() << "Unknown exception in mouseMoveEvent";
          }
    }

    void MainWindow2::dragEnterEvent(QDragEnterEvent *event)
    {
         try {
        // Accept drag events if they contain text indicating they are a "DraggedLabel"
        if (event->mimeData()->hasText() && event->mimeData()->text() == "DraggedLabel") {
            event->acceptProposedAction();
        }
        } catch (const std::exception &e) {
              qDebug() << "Exception in dragEnterEvent: " << e.what();
          } catch (...) {
              qDebug() << "Unknown exception in dragEnterEvent";
          }
    }
///-------------------------------------------------------------
    void MainWindow2::dropEvent(QDropEvent *event)
    {
        try {
            if (event->mimeData()->hasText() && event->mimeData()->text() == "DraggedLabel" && ui->widget->geometry().contains(event->position().toPoint())) {
                QString labelName = currentLabel->objectName();
                QPoint dropPos = event->position().toPoint();

                if (labelMap.contains(labelName) && speedMap.contains(labelName)) {
                    int dropAreaStartX = ui->widget->width() * 4 / 5;
                    if (dropPos.x() < dropAreaStartX) {
                        return;
                    }
                    // Check if there is already a plant at the drop position
                    bool isPlantPresent = false;
                    for (QLabel *plant : plants) {
                        if (plant->geometry().contains(dropPos)) {
                            isPlantPresent = true;
                            break;
                        }
                    }
                    if (isPlantPresent) {
                        return;
                    }

                    QString pixmapPath = labelMap[labelName];
                    int speed = speedMap[labelName];
                    QLabel *newLabel = new QLabel(this);
                    newLabel->setPixmap(QPixmap(pixmapPath).scaled(50, 50, Qt::KeepAspectRatio));
                    newLabel->setGeometry(dropPos.x(), dropPos.y(), 50, 50);
                    newLabel->setParent(this);
                    newLabel->setScaledContents(true);
                    newLabel->show();

                    QProgressBar *zombieEnergyProgressBar = new QProgressBar(this);
                    zombieEnergyProgressBar->setMinimum(0);
                    zombieEnergyProgressBar->setMaximum(100);
                    zombieEnergyProgressBar->setValue(100); // Initial energy value
                    zombieEnergyProgressBar->setGeometry(newLabel->x(), newLabel->y() - 10, 50, 10);
                    zombieEnergyProgressBar->show();

                    QPoint snappedPos = snapToCell(dropPos);
                    newLabel->move(snappedPos);

                    MoveThread *moveThread = new MoveThread(newLabel, ui->widget, speed, this);
                    connect(moveThread, &MoveThread::gameOver, this, &MainWindow2::gameOver);
                    connect(moveThread, &MoveThread::energyChanged, zombieEnergyProgressBar, &QProgressBar::setValue);
                    connect(moveThread, &MoveThread::energyChanged, this, [=](int currentEnergy) {
                        if (currentEnergy <= 0) {
                            newLabel->hide();
                            zombieEnergyProgressBar->hide();
                            newLabel->deleteLater();
                            zombieEnergyProgressBar->deleteLater();
                        }
                    });

                    connect(moveThread, &MoveThread::positionChanged, this, [=](const QPoint &pos) {
                        zombieEnergyProgressBar->move(pos.x(), pos.y() - 10);
                    });

                    moveThreads.append(moveThread);
                    moveThread->start();

                    zombies.append(newLabel);
                } else if (plantslabel.contains(labelName)) {
                    QString pixmapPath = plantslabel[labelName];
                    int dropAreaEndX = ui->widget->width() / 2;
                    if (dropPos.x() > dropAreaEndX) {
                        return;
                    }
                    QLabel *newLabel = new QLabel(this);
                    newLabel->setPixmap(QPixmap(pixmapPath).scaled(50, 50, Qt::KeepAspectRatio));
                    newLabel->setGeometry(dropPos.x(), dropPos.y(), 50, 50);
                    newLabel->setParent(this);
                    newLabel->setScaledContents(true);
                    newLabel->show();

                    QPoint snappedPos = snapToCell(dropPos);
                    newLabel->move(snappedPos);

                    QString plantType = labelName;
                    if (plantType == "jelapino") {
                        JalapenoMoveThread *jalapenoThread = new JalapenoMoveThread(newLabel, ui->widget, 50, this);
                        connect(jalapenoThread, &JalapenoMoveThread::energyChanged, this, [=](QLabel *zombie, int damage) {
                            int currentEnergy = energyProgressBar->value();
                            int newEnergy = currentEnergy - damage;
                            energyProgressBar->setValue(newEnergy);
                            if (newEnergy <= 0) {
                                zombie->hide();
                                zombie->deleteLater();
                            }
                        });
                        connect(jalapenoThread, &JalapenoMoveThread::jalapenoFinished, this, [=]() {
                            newLabel->hide();
                            newLabel->deleteLater();
                        });
                        jalapenoThread->start();
                    } else if (shoot.contains(plantType)) {
                        QTimer *shootTimer = new QTimer(this);
                        connect(shootTimer, &QTimer::timeout, this, [this, newLabel, plantType]() {
                            QString pixmapPath2 = shoot[plantType];

                            QLabel *projectile = new QLabel(this);
                            projectile->setPixmap(QPixmap(pixmapPath2).scaled(10, 10, Qt::KeepAspectRatio));
                            projectile->setParent(this);
                            projectile->setFixedSize(10, 10);
                            projectile->move(newLabel->geometry().right(), newLabel->geometry().center().y() - 5);

                            projectile->setObjectName("bullet");
                            projectile->setScaledContents(true);
                            projectile->show();
                            projectile->raise();

                            ShootThread *shootThread = new ShootThread(projectile, ui->widget, this);
                            connect(shootThread, &ShootThread::hitZombie, this, &MainWindow2::onProjectileHitZombie);
                            connect(shootThread, &ShootThread::finished, shootThread, &QObject::deleteLater); // Ensure thread cleanup
                            shootThread->start();
                        });
                        shootTimer->start(2000);
                    }

                    plants.append(newLabel);
                }
                event->acceptProposedAction();
            }
        } catch (const std::exception &e) {
            qDebug() << "Exception in dropEvent: " << e.what();
        } catch (...) {
            qDebug() << "Unknown exception in dropEvent";
        }
    }
///-------------------------------------------------------------
void MainWindow2::onProjectileHitZombie(QLabel *projectile)
{
    try {
        bool hitZombie = false;
        for (int i = 0; i < zombies.size(); ++i) {
            QLabel *zombie = zombies[i];
            if (checkProjectileZombieCollision(projectile, zombie)) {
                hitZombie = true;
                // Calculate damage based on the projectile
                int damage =   zombieEnergyMap[zombie] * 0.05;
                // Reduce zombie's energy
                int currentEnergy = zombieEnergyMap[zombie];
                int newEnergy = currentEnergy - damage;
                // Update zombie's energy
                zombieEnergyMap[zombie] = newEnergy;
                zombieProgressBars[zombie]->setValue(newEnergy);
                // If zombie's energy is depleted, remove it from the game
                if (newEnergy <= 0) {
                    zombies.removeAt(i);
                    zombie->hide();
                   zombieProgressBars[zombie]->hide();
                    zombie->deleteLater();
                  zombieProgressBars[zombie]->deleteLater();
                }
                // Delete the projectile after it hits a zombie
                projectile->deleteLater();
                break;
            }
        }
        if (!hitZombie) {
            projectile->deleteLater(); // Delete projectile if it didn't hit any zombie
        }

    } catch (const std::exception &e) {
        qDebug() << "Exception in onProjectileHitZombie: " << e.what();
    } catch (...) {
        qDebug() << "Unknown exception in onProjectileHitZombie";
    }
}
///-------------------------------------------------------------
QPoint MainWindow2::snapToCell(const QPoint &pos)
{
    try {
    int x = pos.x() - this->x() - 50;
     int y = pos.y() - this->y() - 50;
     x = (x / cellWidth) * cellWidth +this->x() + 50;
     y = (y / cellHeight) * cellHeight +this->y() + 50;
     return QPoint(x, y);
    } catch (const std::exception &e) {
           qDebug() << "Exception in snapToCell: " << e.what();
           return QPoint();
       } catch (...) {
           qDebug() << "Unknown exception in snapToCell";
           return QPoint();
       }
}
///--------------------------------------------------------
void MainWindow2::gameOver()
{
      try {
    if (!gameEnded) {
            gameEnded = true;
            QMessageBox::information(this, "Game Over", "A zombie reached the end of the frame. Game Over!");
            // Stop all running threads
            for (auto thread : moveThreads) {
                if (thread) {
                    thread->quit();
                    thread->wait();
                    delete thread;
                }
            }
            moveThreads.clear();
        }
    } catch (const std::exception &e) {
          qDebug() << "Exception in gameOver: " << e.what();
      } catch (...) {
          qDebug() << "Unknown exception in gameOver";
      }

}
///------------------------------------------------------------
bool MainWindow2::isZombieInRow(int y)
{
    for (QLabel *zombie : zombies) {
        if (abs(zombie->geometry().center().y() - y) < cellHeight / 2) {
            return true;
        }
    }
    return false;
}
///-------------------------------------------------------------
void MainWindow2::updateProjectilePosition()
{
    if (currentProjectile) {
        // Update the position of the current projectile
        currentProjectile->move(currentProjectile->x() , currentProjectile->y()); // Adjust the movement as needed
        // Check if the projectile has moved out of bounds
        if (currentProjectile->x() > this->width()) {
            currentProjectile->deleteLater(); // Remove the projectile if it's out of bounds
            currentProjectile = nullptr; // Reset currentProjectile pointer
        }
    }
}
///------------------------------------------------------------
void MainWindow2::updateEnergy(int currentEnergy)
{
    // Update progress bar or any other UI element with the current energy value
    energyProgressBar->setValue(currentEnergy);
    //qDebug() << "Energy updated: " << currentEnergy;
}
///-----------------------------------------------------------
void MainWindow2::updateEnergyProgressBar(int currentEnergy)
{
    // Update the progress bar value based on currentEnergy
    energyProgressBar->setValue(currentEnergy);
}
///-----------------------------------------------------------
bool MainWindow2::checkProjectileZombieCollision(QLabel *projectile, QLabel *zombie) {
    if (!projectile || !zombie) {
        return false; // Return false if either label is null
    }

    QRect projectileRect = projectile->geometry();
    QRect zombieRect = zombie->geometry();

    return projectileRect.intersects(zombieRect);
}
///-----------------------------------------------------------
void MainWindow2::dropRandomObject()
{
    // Randomly decide between sun and brain
    bool isSun = QRandomGenerator::global()->bounded(2) == 0;
    QLabel *fallingObject = new QLabel(this); // Add the label to the frame
    if (isSun) {
        fallingObject->setPixmap(QPixmap(food["sun"]).scaled(30, 30, Qt::KeepAspectRatio));
        fallingObject->setObjectName("sun");
    } else {
        fallingObject->setPixmap(QPixmap(food["brain"]).scaled(30, 30, Qt::KeepAspectRatio));
        fallingObject->setObjectName("brain");
    }
    // Ensure the object starts falling within the widget boundaries
    int x = QRandomGenerator::global()->bounded(this->width() - 30);
    fallingObject->setGeometry(x, 0, 30, 30);
    fallingObject->show();
    QTimer *moveTimer = new QTimer(fallingObject);
     connect(moveTimer, &QTimer::timeout, this, [fallingObject, moveTimer, this]() {
         fallingObject->move(fallingObject->x(), fallingObject->y() + 5);
         if (fallingObject->y() > this->height()) {
             moveTimer->stop();
             delete fallingObject;
             delete moveTimer;
         }
     });
     moveTimer->start(50);
}
///----------------------------------------------------
void MainWindow2::setupZombieLabels()
{
    QStringList zombieNames = {"regular", "bucked_head", "leafhead", "tall", "astronaut", "purplehair"};

    for (const QString &name : zombieNames) {
        QLabel *label = findChild<QLabel*>(name);
        if (label) {
            label->setAcceptDrops(true);
            label->setProperty("isZombie", true); // Optionally, set a property to identify as a zombie
        }
    }
}
///-----------------------------------------------------
void MainWindow2::closeEvent(QCloseEvent *event)
{
    // Ensure all threads are properly terminated
    for (auto thread : moveThreads) {
        thread->quit();
        thread->wait();
        delete thread;
    }
    moveThreads.clear();

    QMainWindow::closeEvent(event);
}
///-----------------------------------------------------
void MainWindow2::jalapenoEnergyChanged(QLabel *zombie, int damage)
{
    // Adjust the energy of the zombie
    int currentEnergy = zombieEnergyMap.value(zombie, 100);
    int newEnergy = qMax(currentEnergy - damage, 0);
    zombieEnergyMap[zombie] = newEnergy;
    // Update the corresponding progress bar
    QProgressBar *zombieProgressBar = zombieProgressBars.value(zombie, nullptr);
    if (zombieProgressBar) {
        zombieProgressBar->setValue(newEnergy);
        if (newEnergy <= 0) {
            zombie->hide(); // Example: Hide zombie when energy is depleted
            zombieProgressBar->hide();
        }
    }
}
///-------------------------------------------------------
void MainWindow2::updateCornometer() {
    elapsedTime++;
    int maxTime = 210;
    int remainingTime = maxTime - elapsedTime;
    if (remainingTime >= 0) {
        ui->cornometerProgressBar->setValue(remainingTime);
       // qDebug() << "Cornometer Progress Bar Updated:" << remainingTime;
        // Change color in the last 30 seconds
        if (remainingTime <= 30) {
            ui->cornometerProgressBar->setStyleSheet(
                "QProgressBar {"
                "    border: 2px solid grey;"
                "    border-radius: 5px;"
                "    text-align: center;"
                "    background: white;"
                "}"
                "QProgressBar::chunk {"
                "    background-color: red;"
                "    width: 20px;"
                "}"
            );
        } else {
            ui->cornometerProgressBar->setStyleSheet(
                "QProgressBar {"
                "    border: 2px solid grey;"
                "    border-radius: 5px;"
                "    text-align: center;"
                "    background: white;"
                "}"
                "QProgressBar::chunk {"
                "    background-color: green;"
                "    width: 20px;"
                "}"
            );
        }
    } else {
        timer->stop();
        QMessageBox::information(this, "Time's up!", "Game over!");
       // qDebug() << "Timer stopped. Cornometer Progress Bar reached 0.";
    }
}
