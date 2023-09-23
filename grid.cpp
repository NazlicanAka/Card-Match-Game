#include "grid.h"

// constructor of Grid
Grid::Grid() : QGridLayout(){
    this->selectedCard = new QQueue<Card*>();
    this->hint = false;
    this->my_remaining_list = new QList<Card*>();
}

// check whether two cards are the same or not
void Grid::check_same(){
    Card* firstcard = selectedCard->dequeue(); //dequeue the first clicked button
    Card* secondcard = selectedCard->dequeue();//dequeue the second clicked button
    // check if characters are the same but the cards are different
    if((firstcard->openText == secondcard->openText) && firstcard != secondcard){
        emit gridsame();
        firstcard->same_cards();
        secondcard->same_cards();
    }
    // if characters are different, turn bak to "?"
    else {
        QEventLoop el;
        QTimer::singleShot(500, &el, SLOT(quit())); // show the cards 500ms
        emit gridnot();
        el.exec();
        firstcard->setText("?");
        secondcard->setText("?");
    }
}

// when your tries are done, you lost
// show all the cards, and disable cards
void Grid::bad_lost() {
    int i = 0;
    while(i < this->count()){
        Card* but = qobject_cast<Card*>(this->itemAt(i)->widget());
        but->setText(but->openText);
        but->setDisabled(true);
        i++;
    }
}

// keeps the unmached cards in a QList
void Grid::rem_card(){
    for (int i = 0; i < count(); i++) {
        Card* c = qobject_cast<Card*>(this->itemAt(i)->widget());
        if(c->text() == "?"){
            my_remaining_list->append(c);
        }
    }
}

// this function gives only one hint and the "Hint" function will be disabled
// hint will be chosen in unmatched cards
// one hint is implemeneted with a boolean
// in each game a random card is selected as a hint
void Grid::give_hint(){
    rem_card();
    if (hint == false){
        int random_number = rand() % my_remaining_list->size();
        for (int i = 0; i < my_remaining_list->size(); i++) {
            Card* hint1 = my_remaining_list->at(random_number);
            Card* hint2 = my_remaining_list->at(random_number);
            hint1->setText(hint1->openText);
            QEventLoop el;
            QTimer::singleShot(25, &el, SLOT(quit())); // open the card 25ms
            emit gridhint();
            el.exec();
            hint2->setText("?"); // turn back the card
            this->hint = true; // set hint boolean true to disable the button
        }
    }
}
//void Grid::change_color(){
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
//QString Grid::gr_color(){
//    my_text = "red";
//    return my_text;
//}

//QString Grid::hu_color(){
//    my_text = "blue";
//    return my_text;
//}

//QString Grid::ra_color(){
//    my_text = "yellow";
//    return my_text;
//}

//QString Grid::sl_color(){
//    my_text = "green";
//    return my_text;
//}


// when the "new game" button is cliked this slot is called
void Grid::new_game() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

