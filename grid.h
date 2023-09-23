#ifndef GRID_H
#define GRID_H
#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QQueue>
#include "card.h"
#include <QEventLoop>
#include <QApplication>
#include <QProcess>
#include <QList>
#include <QPalette>

/**
 * @brief The Grid class
 * Templete of the game
 */
class Grid : public QGridLayout
{
    Q_OBJECT

public:
    Grid();
    QQueue<Card*>* selectedCard;
    bool hint = false; //will be changed to true after giving one hint
    QList<Card*>* my_remaining_list;


public slots:
    void check_same();
    void bad_lost();
    void new_game();
    void give_hint();
    void rem_card();
    //    QString gr_color();
    //    QString hu_color();
    //    QString ra_color();
    //    QString sl_color();

signals:
    void gridsame();
    void gridnot();
    void gridhint();
};


#endif // GRID_H

