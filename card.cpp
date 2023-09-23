#include "card.h"
#include <QEventLoop>
#include <QTimer>
// Card constructor
Card::Card(const QString& closedText,  const QString& color, QQueue<Card*>* selectedCard,
           QWidget* parent)
    : QPushButton(closedText, parent)
{
    // add colors to our palatte
    this->color = color;
    QPalette pal = palette();
    if(color == "yellow"){
        pal.setColor(QPalette::Button, QColor(Qt::yellow));
    }else if (color == "red") {
        pal.setColor(QPalette::Button, QColor(Qt::red));
    }else if (color == "cyan") {
        pal.setColor(QPalette::Button, QColor(Qt::cyan));
    }else if (color == "green") {
        pal.setColor(QPalette::Button, QColor(Qt::green));
    }
    setFlat(true);
    setAutoFillBackground(true);
    setPalette(pal);
    this->selectedCard = selectedCard;
    this->setText("?"); // when the card is closed "?" will be displayed
    this->openText = closedText;
    update();
}

//void Card::change_color(){
//    QPalette pal = palette();
//    int color = rand() % 2;
//    if(color == 0){
//        this->color = "yellow";
//        pal.setColor(QPalette::Button, QColor(Qt::yellow));
//    }else{
//        this->color = "red";
//        pal.setColor(QPalette::Button, QColor(Qt::red));
//    }
//    setFlat(true);
//    setAutoFillBackground(true);
//    setPalette(pal);
//    update();
//}

// this slot will be connected in the main
// if card is clicked, this slot will be called
void Card::show_card(){
    // if the queue is empty, enqueue the card
    // this card is going to be the first card
    if (selectedCard->empty()) {
        this->setText(openText); //turn the back of the card, show the name of the character
        update();
        selectedCard->enqueue(this);
    }
    // enqueue the second card to compare
    else{
        this->setText(openText); //turn the back of the card, show the name of the character
        update();
        selectedCard->enqueue(this);
        emit check_card(); // we have two cards, now check whether they are the same
    }
}

// if the clicked cards are the same, set texts to empty, disable the cards
void Card::same_cards() {
    QEventLoop el;
    QTimer::singleShot(100, &el, SLOT(quit())); // show the user they are the same before disabling
    el.exec();
    this->setText("");
    this->setDisabled(true);
    emit same_signal(); //used in main
}


