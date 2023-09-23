#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "card.h"
#include "try.h"
#include "grid.h"
#include "score.h"
#include <QTime>
#include <QProcess>
#include <QVector>
#include <QMessageBox>
#include <QPushButton>
#include <QEventLoop>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * the main part of the game is controlled in here
 */
int main(int argc, char *argv[])
{
    // creating QObjects
    QApplication app(argc, argv);
    QWidget *cw = new QWidget;
    QVBoxLayout *vb = new QVBoxLayout();
    QHBoxLayout *hb = new QHBoxLayout();
    QPushButton *ng = new QPushButton("New Game");
    //QPushButton *gryffindor = new QPushButton("Gryffindor");
    //QPushButton *hufflepuff = new QPushButton("Hufflepuff");
    //QPushButton *ravenclaw = new QPushButton("Ravenclaw");
    //QPushButton *slytherin = new QPushButton("Slytherin");
    QPushButton *gh = new QPushButton("Hint");
    Try *t = new Try();
    Score *s = new Score();
    s->label->setStyleSheet("font: 15pt");
    t->label->setStyleSheet("font: 15pt");
    QVector <QString> houses{"Gryffindor", "Hufflepuff","Ravenclaw","Slytherin"}; // vector keeping the house names
    QVector <QString> colors{"red","cyan","yellow","green"}; // keeps the color names
    QMessageBox *qm = new QMessageBox();// when the game is started, this message box will appear
    //QPushButton *sb = new QPushButton("Start");
    qm->setText("Try to find pairs of 15 Harry Potter characters hidden under the cards\n \t\t You have 50 tries\n\t\t You have 1 hint, use wisely\n\n\t Hold on, Sorting Hat tries to decide your house...\n\n\t\tAre you ready ? ");
    qm->setWindowTitle("Welcome to Wizarding World of Harry Potter!");
    QPushButton *yesButton = qm->addButton(QMessageBox::Yes);
    //QObject::connect(yesButton, SIGNAL(clicked()), qm, SLOT(restart()));
    //qm->setStandardButtons(QMessageBox::Close);
    qm->exec();

    // after 500 ms the game will start
    QEventLoop loop;
    QTimer::singleShot(500, &loop, SLOT(quit()));
    loop.exec();
    std::srand(time(0));

    //pick a random number, the hat will choose the randomly onr of them for each game
    int random_number = rand() % 4;
    QString your_house= houses.at(random_number);
    QString mytxt = colors.at(random_number);
    QLabel *house = new QLabel();
    house->setStyleSheet("font: 17pt");
    house->setText("Your Hogwarts House is " + houses.at(random_number) +"!");
    hb->addWidget(house);

    // to put space between the labels for visual puposes
    QSpacerItem *sill = new QSpacerItem(5, 0,
                                       QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);
    hb->addSpacerItem(sill);
    hb->addWidget(s->label);
    QSpacerItem *sis = new QSpacerItem(5, 0,
                                       QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);
    hb->addSpacerItem(sis);
    hb->addWidget(t->label);
    QSpacerItem *si = new QSpacerItem(5, 0,
                                      QSizePolicy::Expanding,
                                      QSizePolicy::Expanding);
    hb->addSpacerItem(si);
    hb->addWidget(ng);
    hb->addWidget(gh);
    //hb->addWidget(gryffindor);
    //hb->addWidget(hufflepuff);
    //hb->addWidget(ravenclaw);
    //hb->addWidget(slytherin);
    vb->addLayout(hb);

    // create the grid object that will hold our buttons
    bool grid[5][6] = {false};

    Grid *gl = new Grid();

    QObject::connect(ng, SIGNAL(clicked()), gl, SLOT(new_game()));
    QObject::connect(gh, SIGNAL(clicked()), gl, SLOT(give_hint()));
    //QObject::connect(gryffindor, SIGNAL(clicked()), gl, SLOT(gr_color()));
    //QObject::connect(hufflepuff, SIGNAL(clicked()), gl, SLOT(hu_color()));
    //QObject::connect(ravenclaw, SIGNAL(clicked()), gl, SLOT(ra_color()));
    //QObject::connect(slytherin, SIGNAL(clicked()), gl, SLOT(sl_color()));
    QObject::connect(t, SIGNAL(lost()), gl, SLOT(bad_lost()));
    QObject::connect(gl, SIGNAL(gridsame()), s, SLOT(increment()));
    QObject::connect(gl, SIGNAL(gridsame()), t, SLOT(finished()));
    QObject::connect(gl, SIGNAL(gridnot()), t, SLOT(finished()));

    // holds the 15 card names in a vector, randomly assign them to cards
    QString text;
    QVector <QString> cards{"dobby","hagrid","mcgonagall","harry","hermione","ron","snape","dumbledore","malfoy","sirius","bellatrix","hedwig","lupin","cedric","neville"};
    std::srand(time(0));
    for(int i=0; i<15; i++){
        text = cards[i];
        for(int j = 0; j <2; j++) {
            Card *randButton = new Card(text,mytxt, gl->selectedCard);
            QObject::connect(randButton, SIGNAL(clicked()),
                             randButton, SLOT(show_card()));
            QObject::connect(randButton, SIGNAL(check_card()), gl, SLOT(check_same()));
            //QObject::connect(randButton, SIGNAL(same_signal()), gl, SLOT(change_color()));
            int row = std::rand() % 5;
            int col = std::rand() % 6;


            while (grid[row][col]) {
                row = std::rand() % 5;
                col = std::rand() % 6;
            }
            gl->addWidget(randButton, row, col, 1, 1);
            grid[row][col] = true;
        }
    }
    vb->addLayout(gl);
    QSpacerItem *si2 = new QSpacerItem(0, 10,
                                       QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);
    vb->addSpacerItem(si2);


    cw->setWindowTitle("Card Match Game");
    cw->resize(800, 600);
    cw->setLayout(vb);
    cw->show();


    return app.exec();
}
