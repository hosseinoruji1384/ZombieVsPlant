#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_loginButton_clicked();
    void on_forgotPasswordButton_clicked();
    void on_backButton_clicked();
    void on_showPasswordCheckBox_clicked();

private:
    Ui::Login *ui;
    QString loggedInUsername;
    bool authenticate(const QString &username, const QString &password);
    void updateBackground();
};

#endif // LOGIN_H
