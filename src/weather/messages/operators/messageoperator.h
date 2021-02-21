#ifndef MESSAGEOPERATOR_H
#define MESSAGEOPERATOR_H

#include "../message.h"
#include <QObject>

class MessageOperator : public QObject {
    Q_OBJECT

public:
    explicit MessageOperator(QObject* parent = nullptr);

    virtual void operate(const Message& message) = 0;
};

#endif // MESSAGEOPERATOR_H
