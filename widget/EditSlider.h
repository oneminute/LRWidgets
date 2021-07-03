#ifndef EDITSLIDER_H
#define EDITSLIDER_H

#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QIntValidator>
#include <QtUiPlugin/QDesignerExportWidget>

#include "ExportLRWidgets.h"

class EditSliderPrivate;
class LRWIDGET_EXPORT EditSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int minimum READ minimum WRITE setMinimum DESIGNABLE true)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum DESIGNABLE true)
    Q_PROPERTY(int singleStep READ singleStep WRITE setSingleStep DESIGNABLE true)
    Q_PROPERTY(int pageStep READ pageStep WRITE setPageStep DESIGNABLE true)
    Q_PROPERTY(int value READ value WRITE setValue DESIGNABLE true)
    Q_PROPERTY(bool tracking READ tracking WRITE setTracking DESIGNABLE true)
    Q_PROPERTY(int maximumLineEditWidth READ maximumLineEditWidth WRITE setMaximumLineEditWidth DESIGNABLE true)
    Q_PROPERTY(QString textTemplate READ textTemplate WRITE setTextTemplate DESIGNABLE true)

public:
    EditSlider(QWidget *parent = 0);
    EditSlider(Qt::Orientation dir, QWidget *parent = 0);

    int minimum() const;
    void setMinimum(int minimum);

    int maximum() const;
    void setMaximum(int maximum);

    int singleStep() const;
    void setSingleStep(int singleStep);

    int pageStep() const;
    void setPageStep(int pageStep);

    int value() const;
    void setValue(int value);

    bool tracking() const;
    void setTracking(bool tracking);

    int maximumLineEditWidth() const;
    void setMaximumLineEditWidth(int width);

    QString text() const;

    QString textTemplate() const;
    void setTextTemplate(const QString& textTemplate);

protected slots:
    void onSliderValueChanged(int value);
    void onLineEditTextChanged(const QString& text);
    void initialize(Qt::Orientation orientation);

signals:
    void valueChanged(int value);

private:

private:
    QScopedPointer<EditSliderPrivate> m_ptr;

    Q_DECLARE_PRIVATE_D(m_ptr, EditSlider)
    Q_DISABLE_COPY(EditSlider)
    
};

#endif // EDITSLIDER_H
