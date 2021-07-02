#ifndef FLOATEDITSLIDER_H
#define FLOATEDITSLIDER_H

#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QDoubleValidator>
#include <QtUiPlugin/QDesignerExportWidget>

#include "ExportLRWidgets.h"

class FloatEditSliderPrivate;
class LRWIDGET_EXPORT FloatEditSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum DESIGNABLE true)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum DESIGNABLE true)
    Q_PROPERTY(qreal value READ value WRITE setValue DESIGNABLE true)
    Q_PROPERTY(qreal sliderPosition READ sliderPosition)
    Q_PROPERTY(bool tracking READ tracking)
    Q_PROPERTY(int maximumLineEditWidth READ maximumLineEditWidth WRITE setMaximumLineEditWidth DESIGNABLE true)
    Q_PROPERTY(QString textTemplate READ textTemplate WRITE setTextTemplate DESIGNABLE true)

public:
    FloatEditSlider(QWidget *parent = nullptr);
    FloatEditSlider(Qt::Orientation orientation, QWidget *parent = nullptr);

    qreal minimum() const;
    void setMinimum(qreal minimum);

    qreal maximum() const;
    void setMaximum(qreal maximum);

    qreal step() const;
    void setStep(qreal step);

    qreal page() const;
    void setPage(qreal page);

    int decimals() const;
    void setDecimals(int decimals);

    qreal value() const;
    void setValue(qreal value);

    int sliderPosition() const;

    bool tracking() const;

    int maximumLineEditWidth() const;
    void setMaximumLineEditWidth(int width);

    QString text() const;

    QString textTemplate() const;
    void setTextTemplate(const QString& textTemplate);

public slots:
    void onSliderValueChanged(int value);
    void onLineEditTextChanged(const QString& text);
    void updateText();
    void updateWidget();

protected slots:
    void onRangeChanged(qreal min, qreal max);
    void onStepChanged(qreal step);
    void onPageChanged(qreal page);
    void onDecimalsChanged(int decimals);
    void initialize(Qt::Orientation orientation);

signals:
    void valueChanged(qreal value);
    void rangeChanged(qreal min, qreal max);
    void stepChanged(qreal step);
    void pageChanged(qreal page);
    void decimalsChanged(int decimals);

private:

private:
    QScopedPointer<FloatEditSliderPrivate> m_ptr;

    Q_DECLARE_PRIVATE_D(m_ptr, FloatEditSlider)
    Q_DISABLE_COPY(FloatEditSlider)
};

#endif // FLOATEDITSLIDER_H