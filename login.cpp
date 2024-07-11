#include "login.h"
#include "ui_login.h"
#include "forgetpassword.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "form.h"
#include "ui_form.h"


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QSpacerItem *topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        mainLayout->addItem(topSpacer);

        QVBoxLayout *centerLayout = new QVBoxLayout();

        centerLayout->addWidget(ui->usernameLabel);
        centerLayout->addWidget(ui->usernameLineEdit);
        centerLayout->addWidget(ui->passwordLabel);
        centerLayout->addWidget(ui->passwordLineEdit);
        centerLayout->addWidget(ui->showPasswordCheckBox);
        centerLayout->addWidget(ui->forgotPasswordButton);
        centerLayout->addWidget(ui->loginButton);
        centerLayout->addWidget(ui->backButton);

        QHBoxLayout *centerHLayout = new QHBoxLayout();
        QSpacerItem *leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        QSpacerItem *rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        centerHLayout->addItem(leftSpacer);
        centerHLayout->addLayout(centerLayout);
        centerHLayout->addItem(rightSpacer);

        mainLayout->addLayout(centerHLayout);

        QSpacerItem *bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        mainLayout->addItem(bottomSpacer);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->showPasswordCheckBox, &QCheckBox::clicked, this, &Login::on_showPasswordCheckBox_clicked);
    updateBackground();
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (authenticate(username, password)) {
        QMessageBox::information(this, "Success", "Login successful.");
           MainWindow2* a= new MainWindow2();
           a->show();
           this->close();
    } else {
        QMessageBox::warning(this, "Error", "Username or password is incorrect.");
    }
}

void Login::on_forgotPasswordButton_clicked()
{
    ForgetPassword *forgetWindow = new ForgetPassword();
    forgetWindow->show();
    this->close();
}

bool Login::authenticate(const QString &username, const QString &password)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields[0] == username && fields[1] == password) {
            return true;
        }
    }
    return false;
}

void Login::on_backButton_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void Login::on_showPasswordCheckBox_clicked()
{
    bool checked = ui->showPasswordCheckBox->isChecked();
    if (checked) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    }
}

void Login::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateBackground();
}

void Login::updateBackground()
{
    QPixmap background(":/images/chahar.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->setPalette(palette);
}
