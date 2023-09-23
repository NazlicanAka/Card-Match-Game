#ifndef TRY_H
#define TRY_H
#include <QLabel>
#include <QMessageBox>
#include "grid.h"
#include "card.h"

/**
 * @brief The Try class
 * Keeps the remaining tries
 */
class Try : public QObject
{
    Q_OBJECT

public:
    Try();
    QLabel *label;
    int counter;

public slots:
    void finished();

signals:
    void lost();
};

#endif // TRY_H


