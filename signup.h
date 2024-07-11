#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

namespace Ui {
class Signup;
}

class Signup : public QWidget
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_signupButton_clicked();
    void on_backButton_clicked();
    void on_showPasswordCheckBox_clicked();

private:
    Ui::Signup *ui;
    void setPasswordVisibility(bool visible);
    bool validatePhoneNumber(const QString &phone);
    bool validateEmail(const QString &email);
    bool validatePassword(const QString &password);
    void updateBackground();
};

#endif // SIGNUP_H
