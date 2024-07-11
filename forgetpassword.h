#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QWidget>

namespace Ui {
class ForgetPassword;
}

class ForgetPassword : public QWidget
{
    Q_OBJECT

public:
    explicit ForgetPassword(QWidget *parent = nullptr);
    ~ForgetPassword();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_submitButton_clicked();
    void on_backButton_clicked();

private:
    Ui::ForgetPassword *ui;
    bool verifyPhone(const QString &username, const QString &phone);
    void updateBackground();
};

#endif // FORGETPASSWORD_H
