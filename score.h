#ifndef SCORE_H
#define SCORE_H
#include <QLabel>
#include <QMessageBox>

/**
 * @brief The Score class
 * Keeps the score
 */

class Score : public QObject
{
    Q_OBJECT

public:
    Score();
    QLabel* label;
    int counter;

public slots:
    void increment();
};

#endif // SCORE_H


