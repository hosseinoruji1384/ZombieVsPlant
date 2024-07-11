#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QScreen>
#include <QApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_LoginButton_clicked();
    void on_SignupButton_clicked();

private:
    Ui::MainWindow *ui;
    void updateBackground();
    void centerMainWindow();
};

#endif // MAINWINDOW_H
