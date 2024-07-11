#include "energymanager.h"

EnergyManager::EnergyManager(QObject *parent)
    : QObject(parent)
{
}

void EnergyManager::monitorProgressBar(QProgressBar *progressBar, QLabel *associatedLabel)
{
    connect(progressBar, &QProgressBar::valueChanged, this, &EnergyManager::onValueChanged);
}

void EnergyManager::onValueChanged(int value)
{
    QProgressBar *progressBar = qobject_cast<QProgressBar *>(sender());
    if (progressBar && value <= 0) {
        // Assuming associatedLabel is supposed to be deleted when energy is depleted
        QLabel *associatedLabel = progressBar->parent()->findChild<QLabel *>(progressBar->objectName().replace("ProgressBar", "Label"));
        if (associatedLabel) {
            associatedLabel->deleteLater(); // Delete associated label when energy is depleted
        }
        emit energyDepleted(associatedLabel); // Signal energy depletion
    }
}
