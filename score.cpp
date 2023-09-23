#include "score.h"
#include <QEventLoop>
#include <QTimer>

// constructor of Score object
Score::Score() : QObject()
{
    this->label = new QLabel("Score: 0");
    this->counter = 0;
}


void Score::increment() // this slot will be called when a match happens
{

    this->counter += 1;
    this->label->setText("Score: " + QString::number(counter));

    if (this->counter >= 15)
    {
        QMessageBox *qm = new QMessageBox();
        qm->setText("Wow, you won 1000 Gringotts money! \nTake it from Gringotts Wizarding Bank/Diagon Alley ");
        qm->setWindowTitle("Congratulations! ");
        qm->setStandardButtons(QMessageBox::Close);
        qm->exec();
    }
}
