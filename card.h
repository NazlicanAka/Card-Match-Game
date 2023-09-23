#ifndef CARD_H
#define CARD_H
#include <QPushButton>
#include <QQueue>
#include <QPalette>
/**
 * @brief The Card class
 * Every card has a closedText which is
 * a character of a "Harry Potter"
 * Selected cards are kept in a queue (selectedCard),
 * to compare later
 * Cards also has a color feature
 */

class Card : public QPushButton
{
    Q_OBJECT

public:
    Card(const QString& closedText, const QString& color, QQueue<Card*>* selectedCard,
         QWidget* parent = 0);
    QQueue<Card*>* selectedCard;
    QString color;
    QString openText;


public slots:
    void same_cards();
    void show_card();


signals:
    void check_card();
    void same_signal();
};


#endif // CARD_H
