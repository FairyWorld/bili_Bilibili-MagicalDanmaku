#ifndef FREECOPYEDIT_H
#define FREECOPYEDIT_H

#include <QApplication>
#include <QLineEdit>
#include <QKeyEvent>

class FreeCopyEdit : public QLineEdit
{
public:
    FreeCopyEdit(QWidget* parent = nullptr) : QLineEdit(parent)
    {}

protected:
    void focusOutEvent(QFocusEvent *) override
    {
        this->deleteLater();
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Escape)
            this->deleteLater();
        return QLineEdit::keyPressEvent(event);
    }
};

class TransparentEdit : public QLineEdit
{
    Q_OBJECT
public:
    TransparentEdit(QWidget* parent = nullptr) : QLineEdit(parent)
    {
        focusOutEvent(nullptr);
    }

signals:
    void signalESC();

protected:
    void focusInEvent(QFocusEvent *) override
    {
        this->setStyleSheet("");
    }

    void focusOutEvent(QFocusEvent *) override
    {
        this->setStyleSheet("QLineEdit{background: transparent;}");
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Escape)
            emit signalESC();
        return QLineEdit::keyPressEvent(event);
    }
};

#endif // FREECOPYEDIT_H

