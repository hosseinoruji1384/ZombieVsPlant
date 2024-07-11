#ifndef PROGRESSBARWINDOW_H
#define PROGRESSBARWINDOW_H

#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QTimer>

class ProgressBarWindow : public QWidget {
    Q_OBJECT

public:
    ProgressBarWindow(QWidget *parent = nullptr);

public slots:
    void updateProgress();

signals:
    void progressComplete();

private:
    QProgressBar *progressBar;
    QTimer *timer;
    void updateBackground();
    void resizeEvent(QResizeEvent *event);
    void updateLayout();

};

#endif // PROGRESSBARWINDOW_H
