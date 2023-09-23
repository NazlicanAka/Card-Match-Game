#include "try.h"

// constructor of the Try Object
Try::Try()
{
    //remtry = new QLabel(this);
    label = new QLabel("Number of Tries Remaining: 50");
    counter = 50;
}


void Try::finished()
{
    counter -= 1; // when clicked two button, decrement the counter
    label->setText("Number of tries remaining : "+
                   QString::number(this->counter));
    if(counter<=0){
        QMessageBox* msgBox = new QMessageBox();
        msgBox->setText("You spent all 50 tries! You missed Hogwarts Express!\nCome to Platform 9 3/4 next September 1st");
        msgBox->setWindowTitle("Oops! ");
        msgBox->setStandardButtons(QMessageBox::Ok);
        emit lost();
        msgBox->exec();
    }
}

