#include "FloatEditSlider.h"
#include "QBoxLayout"
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
    d->slider = new QSlider(orientation, this);
    d->edit = new QLineEditEx(this);

    QBoxLayout* layout = (orientation == Qt::Horizontal) ? new QBoxLayout(QBoxLayout::LeftToRight, this) : new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->addWidget(d->slider);
    layout->addWidget(d->edit);
    layout->setStretch(0, 1);
    layout->setStretch(1, 0);

    setLayout(layout);

    connect(this, &FloatEditSlider::rangeChanged, this, &FloatEditSlider::onRangeChanged);
    connect(this, &FloatEditSlider::stepChanged, this, &FloatEditSlider::onStepChanged);
    connect(this, &FloatEditSlider::pageChanged, this, &FloatEditSlider::onPageChanged);
    connect(d->slider, &QSlider::valueChanged, this, &FloatEditSlider::onSliderValueChanged);
    connect(d->edit, &QLineEditEx::textChanged, this, &FloatEditSlider::onLineEditTextChanged);
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
    return d->edit->renderText();
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
    Q_D(FloatEditSlider);
    d->value = value * d->step;
    d->edit->blockSignals(true);
    updateText();
    d->edit->blockSignals(false);
    emit valueChanged(d->value);
}

void FloatEditSlider::onLineEditTextChanged(const QString& text)
{
    Q_D(FloatEditSlider);
    d->value = text.toDouble();
    d->slider->setValue(d->value / d->step);
    emit valueChanged(d->value);
}

void FloatEditSlider::updateText()
{
    Q_D(FloatEditSlider);
    d->edit->setText(QString::number(d->value));
}

void FloatEditSlider::updateWidget()
{
    Q_D(FloatEditSlider);
    d->slider->setValue(d->value / d->step);
    d->slider->setMinimum(d->minValue / d->step);
    d->slider->setMaximum(d->maxValue / d->step);
    d->slider->setPageStep(d->page / d->step);
    updateText();
}

void FloatEditSlider::onRangeChanged(qreal min, qreal max)
{
    updateWidget();
}

void FloatEditSlider::onStepChanged(qreal step)
{
    updateWidget();
}

void FloatEditSlider::onPageChanged(qreal page)
{
    updateWidget();
}

void FloatEditSlider::validateText()
{
}

