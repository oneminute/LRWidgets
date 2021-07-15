#ifndef FLOATEDITDUALSLIDER_H
#define FLOATEDITDUALSLIDER_H

#include "ExportLRWidgets.h"
#include "DualSlider.h"

class QLineEditEx;
class FloatEditDualSliderPrivate;
class LRWIDGET_EXPORT FloatEditDualSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString textTemplate READ textTemplate WRITE setTextTemplate)
    Q_PROPERTY(qreal lowerValue READ lowerValue WRITE setLowerValue)
    Q_PROPERTY(qreal higherValue READ higherValue WRITE setHigherValue)
    Q_PROPERTY(qreal step READ step WRITE setStep)
    Q_PROPERTY(qreal page READ page WRITE setPage)
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int editMaxWidth READ editMaxWidth WRITE setEditMaxWidth)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)

public:
    explicit FloatEditDualSlider(QWidget* parent = nullptr);
    explicit FloatEditDualSlider(Qt::Orientation orientation, QWidget* parent = nullptr);

    Qt::Orientation orientation() const;

    QString textTemplate() const;
    void setTextTemplate(const QString& textTemplate);

    qreal lowerValue() const;
    void setLowerValue(qreal value);
    
    qreal higherValue() const;
    void setHigherValue(qreal value);

    qreal step() const;
    void setStep(qreal step);

    qreal page() const;
    void setPage(qreal page);

    qreal minimum() const;
    void setMinimum(qreal minimum);

    qreal maximum() const;
    void setMaximum(qreal maximum);

    int editMaxWidth() const;
    void setEditMaxWidth(int width);

    int decimals() const;
    void setDecimals(int decimals);

protected:
    void init();
    void onSliderLowerValueChanged(int value);
    void onSliderHigherValueChanged(int value);
    void onMinEditEditingFinished();
    void onMaxEditEditingFinished();

signals:
    void lowerValueChanged(qreal value);
    void higherValueChanged(qreal value);

private:
    QScopedPointer<FloatEditDualSliderPrivate> m_ptr;

    Q_DECLARE_PRIVATE_D(m_ptr, FloatEditDualSlider)
    Q_DISABLE_COPY(FloatEditDualSlider)
};

#endif // FLOATEDITDUALSLIDER_H
