#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "signup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_LoginButton_clicked);
    connect(ui->signupButton, &QPushButton::clicked, this, &MainWindow::on_SignupButton_clicked);

    updateBackground();
    centerMainWindow();

    setWindowTitle("Main Window");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
    centerMainWindow();

    Q_UNUSED(event);
}

void MainWindow::on_LoginButton_clicked()
{
    Login *loginWindow = new Login();
    loginWindow->show();
    this->close();
}

void MainWindow::on_SignupButton_clicked()
{
    Signup *signupWindow = new Signup();
    signupWindow->show();
    this->close();
}

void MainWindow::updateBackground()
{
    QPixmap background(":/images/yek.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->setPalette(palette);
}

void MainWindow::centerMainWindow()
{
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}
