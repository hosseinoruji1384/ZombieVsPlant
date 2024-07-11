#include "forgetpassword.h"
#include "ui_forgetpassword.h"
#include "resetpassword.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "login.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ForgetPassword::ForgetPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgetPassword)
{
    ui->setupUi(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QSpacerItem *topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        mainLayout->addItem(topSpacer);

        QVBoxLayout *centerLayout = new QVBoxLayout();

        centerLayout->addWidget(ui->usernameLabel);
        centerLayout->addWidget(ui->usernameLineEdit);
        centerLayout->addWidget(ui->phoneLabel);
        centerLayout->addWidget(ui->PhoneLineEdit);
        centerLayout->addWidget(ui->submitButton);
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
    updateBackground();
}

ForgetPassword::~ForgetPassword()
{
    delete ui;
}

void ForgetPassword::on_submitButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString input = ui->PhoneLineEdit->text();

    if (verifyPhone(username, input)) {
        ResetPassword *resetWindow = new ResetPassword();
        resetWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Username or phone number is incorrect.");
    }
}

bool ForgetPassword::verifyPhone(const QString &username, const QString &phone)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields[0] == username && fields[3] == phone) {
            return true;
        }
    }
    return false;
}

void ForgetPassword::on_backButton_clicked()
{
    Login *loginWindow = new Login();
    loginWindow->show();
    this->close();
}

void ForgetPassword::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateBackground();
}

void ForgetPassword::updateBackground()
{
    QPixmap background(":/images/baadi.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->setPalette(palette);
}
