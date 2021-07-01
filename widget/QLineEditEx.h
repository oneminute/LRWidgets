#ifndef QLINEEDITEX_H
#define QLINEEDITEX_H

#include <QLineEdit>
#include <QScopedPointer>

class QLineEditExPrivate;
class QLineEditEx : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged DESIGNABLE true )
    Q_PROPERTY(QString textTemplate READ textTemplate WRITE setTextTemplate NOTIFY textTemplateChanged DESIGNABLE true)

public:
    explicit QLineEditEx(QWidget* parent = nullptr);
    ~QLineEditEx();

    QString text() const;
    void setText(const QString& text);

    QString textTemplate() const;
    void setTextTemplate(const QString& textTemplate);

protected:
    virtual void focusInEvent(QFocusEvent* e) override;

public slots:
    void updateText();

protected slots:
    void onEditingFinished();
    void onTextTemplateChanged(const QString& textTemplate);

signals:
    void textChanged(const QString& text);
    void textTemplateChanged(const QString& textTemplate);

private:
    QScopedPointer<QLineEditExPrivate> m_ptr;
    Q_DECLARE_PRIVATE_D(m_ptr, QLineEditEx)
    Q_DISABLE_COPY(QLineEditEx)
};

#endif // QLINEEDITEX_H
