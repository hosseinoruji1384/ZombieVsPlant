#include "progressbarwindow.h"

ProgressBarWindow::ProgressBarWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 100);

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(progressBar);
    setLayout(layout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ProgressBarWindow::updateProgress);
    timer->start(20);

    updateLayout();
    updateBackground();
}

void ProgressBarWindow::updateProgress() {
    int value = progressBar->value();
    if (value < 100) {
        progressBar->setValue(value + 1);
    } else {
        timer->stop();
        emit progressComplete();
    }
}

void ProgressBarWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updateLayout();
    updateBackground();
}

void ProgressBarWindow::updateLayout() {
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(layout());
    if (mainLayout) {
        mainLayout->setAlignment(Qt::AlignCenter);
    }
}

void ProgressBarWindow::updateBackground() {
    QPixmap background(":/images/yek.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setPalette(palette);
}
