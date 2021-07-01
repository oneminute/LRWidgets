#include "QLineEditEx.h"
#include <QDebug>

class QLineEditExPrivate
{
    Q_DECLARE_PUBLIC(QLineEditEx)
public:
    QLineEditExPrivate(QLineEditEx* ptr)
        : q_ptr(ptr)
        , textTemplate("%1")
    {}

    QLineEditEx* q_ptr;

    QString textTemplate;
    QString text;
};

QLineEditEx::QLineEditEx(QWidget* parent)
    : QLineEdit(parent)
    , m_ptr(new QLineEditExPrivate(this))
{
    Q_D(QLineEditEx);
    d->text = "";

    connect(this, &QLineEditEx::textTemplateChanged, this, &QLineEditEx::onTextTemplateChanged);
    connect(this, &QLineEditEx::editingFinished, this, &QLineEditEx::onEditingFinished);
}

QLineEditEx::~QLineEditEx()
{

}

QString QLineEditEx::text() const
{
    Q_D(const QLineEditEx);
    return d->textTemplate.arg(d->text);
}

void QLineEditEx::setText(const QString& text)
{
    Q_D(QLineEditEx);
    if (text != d->text)
    {
        QLineEdit::setText(this->text());
        emit textChanged(text);
    }
}

QString QLineEditEx::textTemplate() const
{
    Q_D(const QLineEditEx);
    return d->textTemplate;
}

void QLineEditEx::setTextTemplate(const QString& textTemplate)
{
    Q_D(QLineEditEx);
    if (textTemplate != d->textTemplate)
    {
        d->textTemplate = textTemplate;
        emit textTemplateChanged(textTemplate);
    }
}

void QLineEditEx::focusInEvent(QFocusEvent* e)
{
    Q_D(QLineEditEx);
    QLineEdit::setText(d->text);
    this->selectAll();
}

void QLineEditEx::updateText()
{
    QLineEdit::setText(text());
}

void QLineEditEx::onEditingFinished()
{
    Q_D(QLineEditEx);
    d->text = QLineEdit::text();
    QString text = this->text();
    QLineEdit::setText(text);
    emit textChanged(text);
}

void QLineEditEx::onTextTemplateChanged(const QString& textTemplate)
{
    updateText();
}

