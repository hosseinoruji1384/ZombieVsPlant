#include "resetpassword.h"
#include "ui_resetpassword.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ResetPassword::ResetPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResetPassword)
{
    ui->setupUi(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QSpacerItem *topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        mainLayout->addItem(topSpacer);

        QVBoxLayout *centerLayout = new QVBoxLayout();

        centerLayout->addWidget(ui->usernameLabel);
        centerLayout->addWidget(ui->usernameLineEdit);
        centerLayout->addWidget(ui->passwordLabel);
        centerLayout->addWidget(ui->confirmLabel);
        centerLayout->addWidget(ui->confirmPasswordLineEdit);
        centerLayout->addWidget(ui->newPasswordLineEdit);
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

ResetPassword::~ResetPassword()
{
    delete ui;
}

void ResetPassword::on_submitButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString newPassword = ui->newPasswordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    if (resetUserPassword(username, newPassword, confirmPassword)) {
        QMessageBox::information(this, "Success", "Password reset successfully.");
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Passwords do not match, username is incorrect, or password does not meet criteria.");
    }
}

bool ResetPassword::validatePassword(const QString &password)
{
    bool hasDigit = false;
    bool hasLower = false;
    bool hasUpper = false;

    if (password.length() < 8)
        return false;

    for (const QChar &ch : password) {
        if (ch.isDigit())
            hasDigit = true;
        else if (ch.isLower())
            hasLower = true;
        else if (ch.isUpper())
            hasUpper = true;

        if (hasDigit && hasLower && hasUpper)
            return true;
    }

    return false;
}

bool ResetPassword::resetUserPassword(const QString &username, const QString &newPassword, const QString &confirmPassword)
{
    if (newPassword != confirmPassword || !validatePassword(newPassword))
        return false;

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;

    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }

    file.resize(0);

    QTextStream out(&file);
    bool userFound = false;
    for (QString &line : lines) {
        QStringList fields = line.split(",");
        if (fields[0] == username) {
            fields[1] = newPassword;
            userFound = true;
        }
        out << fields.join(",") << "\n";
    }

    return userFound;
}

void ResetPassword::on_backButton_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void ResetPassword::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateBackground();
}

void ResetPassword::updateBackground()
{
    QPixmap background(":/images/akhari.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->setPalette(palette);
}
