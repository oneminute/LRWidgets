#include "FloatEditSlider.h"
#include "QLineEditEx.h"

class FloatEditSliderPrivate
{
    Q_DECLARE_PUBLIC(FloatEditSlider)
public:
    FloatEditSliderPrivate(FloatEditSlider* ptr)
        : q_ptr(ptr)
    {}

    FloatEditSlider* q_ptr;

    Qt::Orientation orientation;
    QLineEditEx* edit;
    QSlider* slider;
    QDoubleValidator* validator;

    qreal step;
    qreal page;
    qreal minValue;
    qreal maxValue;
    int decimals;
    qreal value;
    QString textTemplate;
};

FloatEditSlider::FloatEditSlider(Qt::Orientation orientation, QWidget* parent)
    : QWidget(parent)
    , m_ptr(new FloatEditSliderPrivate(this))
{
    Q_D(FloatEditSlider);
    d->orientation = orientation;
}

qreal FloatEditSlider::minimum() const
{
    Q_D(const FloatEditSlider);
    return d->minValue;
}

void FloatEditSlider::setMinimum(qreal minimum)
{
    Q_D(FloatEditSlider);
    if (minimum != d->minValue)
    {
        d->minValue = minimum;
        emit rangeChanged(d->minValue, d->maxValue);
    }
}

qreal FloatEditSlider::maximum() const
{
    Q_D(const FloatEditSlider);
    return d->maxValue;
}

void FloatEditSlider::setMaximum(qreal maximum)
{
    Q_D(FloatEditSlider);
    if (maximum != d->maxValue)
    {
        d->maxValue = maximum;
        emit rangeChanged(d->minValue, d->maxValue);
    }
}

qreal FloatEditSlider::step() const
{
    Q_D(const FloatEditSlider);
    return d->step;
}

void FloatEditSlider::setStep(qreal step)
{
    Q_D(FloatEditSlider);
    if (step != d->step)
    {
        d->step = step;
        emit stepChanged(step);
    }
}

qreal FloatEditSlider::page() const
{
    Q_D(const FloatEditSlider);
    return d->page;
}

void FloatEditSlider::setPage(qreal page)
{
    Q_D(FloatEditSlider);
    if (page != d->page)
    {
        d->page = page;
        emit pageChanged(page);
    }
}

qreal FloatEditSlider::value() const
{
    Q_D(const FloatEditSlider);
    return d->value;
}

void FloatEditSlider::setValue(qreal value)
{
    Q_D(FloatEditSlider);
    if (value != d->value)
    {
        d->value = value;
        emit valueChanged(value);
    }
}

int FloatEditSlider::sliderPosition() const
{
    Q_D(const FloatEditSlider);
    return d->slider->sliderPosition();
}

bool FloatEditSlider::tracking() const
{
    Q_D(const FloatEditSlider);
    return d->slider->hasTracking();
}

int FloatEditSlider::maximumLineEditWidth() const
{
    Q_D(const FloatEditSlider);
    return d->edit->maximumWidth();
}

void FloatEditSlider::setMaximumLineEditWidth(int width)
{
    Q_D(FloatEditSlider);
    d->edit->setMaximumWidth(width);
}

QString FloatEditSlider::text() const
{
    Q_D(const FloatEditSlider);
    return d->edit->text();
}

QString FloatEditSlider::textTemplate() const
{
    Q_D(const FloatEditSlider);
    return d->edit->textTemplate();
}

void FloatEditSlider::setTextTemplate(const QString& textTemplate)
{
    Q_D(FloatEditSlider);
    d->edit->setTextTemplate(textTemplate);
}

void FloatEditSlider::onSliderValueChanged(int value)
{

}

void FloatEditSlider::onLineEditEditingFinished()
{

}

void FloatEditSlider::onRangeChanged(qreal min, qreal max)
{

}

void FloatEditSlider::onStepChanged(qreal step)
{
}

void FloatEditSlider::onPageChanged(qreal page)
{
}

void FloatEditSlider::validateText()
{
}

