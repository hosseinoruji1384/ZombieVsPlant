#include "signup.h"
#include "ui_signup.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "login.h"
#include "mainwindow.h"
#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "form.h"
#include "ui_form.h"
Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
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
        centerLayout->addWidget(ui->emailLabel);
        centerLayout->addWidget(ui->emailLineEdit);
        centerLayout->addWidget(ui->phoneLabel);
        centerLayout->addWidget(ui->phoneLineEdit);
        centerLayout->addWidget(ui->userFieldLabel);
        centerLayout->addWidget(ui->userFieldLineEdit);

        centerLayout->addWidget(ui->signupButton);
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
    connect(ui->showPasswordCheckBox, &QCheckBox::clicked, this, &Signup::on_showPasswordCheckBox_clicked);
    updateBackground();
}

Signup::~Signup()
{
    delete ui;
}

bool Signup::validatePhoneNumber(const QString &phone)
{
    return phone.length() == 11 && phone.startsWith("09") && phone.toLongLong();
}

bool Signup::validateEmail(const QString &email)
{
    return email.endsWith("@gmail.com");
}

bool Signup::validatePassword(const QString &password)
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

void Signup::on_signupButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString phone = ui->phoneLineEdit->text();
    QString userField = ui->userFieldLineEdit->text();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username field cannot be empty.");
        return;
    }

    if (!validatePhoneNumber(phone)) {
        QMessageBox::warning(this, "Error", "Phone number must be 11 digits and start with 09.");
        return;
    }

    if (!validateEmail(email)) {
        QMessageBox::warning(this, "Error", "Email must be a valid Gmail address (example@gmail.com).");
        return;
    }

    if (!validatePassword(password)) {
        QMessageBox::warning(this, "Error", "Password must contain at least 8 characters, including a digit, a lowercase letter, and an uppercase letter.");
        return;
    }

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open users.txt for reading: " + file.errorString());
        return;
    }


    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        QString existingUsername = fields.at(0).trimmed();

        if (existingUsername == username) {
            file.close();
            QMessageBox::warning(this, "Error", "Username already exists. Please choose a different username.");
            return;
        }
    }

    file.close();

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open users.txt for writing.");
        return;
    }

    QTextStream out(&file);
    out << username << "," << password << "," << email << "," << phone << "," << userField << "\n";
    file.close();

    QMessageBox::information(this, "Success", "Signup successful.");
    MainWindow2* a= new MainWindow2();
    a->show();
    this->close();
}


void Signup::on_showPasswordCheckBox_clicked()
{
    bool checked = ui->showPasswordCheckBox->isChecked();
    setPasswordVisibility(checked);
}

void Signup::setPasswordVisibility(bool visible)
{
    if (visible) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    }
}

void Signup::on_backButton_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void Signup::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateBackground();
}

void Signup::updateBackground()
{
    QPixmap background(":/images/do.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->setPalette(palette);
}
