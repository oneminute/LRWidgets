#include "FloatEditDualSlider.h"

#include <QLineEdit>
#include <QLocale>
#include <QBoxLayout>
#include <QDoubleValidator>

#include "QLineEditEx.h"

class FloatEditDualSliderPrivate
{
    Q_DECLARE_PUBLIC(FloatEditDualSlider)
public:
    FloatEditDualSliderPrivate(FloatEditDualSlider* ptr)
        : q_ptr(ptr)
        , orientation(Qt::Horizontal)
        , lowerEdit(nullptr)
        , higherEdit(nullptr)
        , lowerValidator(nullptr)
        , higherValidator(nullptr)
        , minimum(0)
        , maximum(100)
        , decimals(1)
        , step(0.1)
        , page(10)
    {}

    void updateLowerValue(qreal value);
    void updateHigherValue(qreal value);
    void updateLowerEditValue();
    void updateHigherEditValue();
    void updateSliderLowerValue();
    void updateSliderHigherValue();
    void updateStep(qreal value);
    void updatePage(qreal value);
    void updateMinimum(qreal value);
    void updateMaximum(qreal value);
    void updateDecimals(int value);

    FloatEditDualSlider* q_ptr;

    Qt::Orientation orientation;
    QLineEditEx* lowerEdit;
    QLineEditEx* higherEdit;
    DualSlider* slider;
    QDoubleValidator* lowerValidator;
    QDoubleValidator* higherValidator;
    qreal minimum;
    qreal maximum;
    int decimals;
    qreal step;
    qreal page;

    qreal lowerValue;
    qreal higherValue;
};

void FloatEditDualSliderPrivate::updateLowerValue(qreal value)
{
    lowerValue = qBound(minimum, value, higherValue);
    higherValidator->setRange(lowerValue, maximum);
}

void FloatEditDualSliderPrivate::updateHigherValue(qreal value)
{
    higherValue = qBound(lowerValue, value, maximum);
    lowerValidator->setRange(minimum, higherValue);
}

void FloatEditDualSliderPrivate::updateLowerEditValue()
{
    lowerEdit->blockSignals(true);
    lowerEdit->setText(QString::number(lowerValue));
    lowerEdit->blockSignals(false);
}

void FloatEditDualSliderPrivate::updateHigherEditValue()
{
    higherEdit->blockSignals(true);
    higherEdit->setText(QString::number(higherValue));
    higherEdit->blockSignals(false);
}

void FloatEditDualSliderPrivate::updateSliderLowerValue()
{
    int intValue = qRound(lowerValue / step);
    slider->blockSignals(true);
    slider->setLowerValue(intValue);
    slider->blockSignals(false);
}

void FloatEditDualSliderPrivate::updateSliderHigherValue()
{
    int intValue = qRound(higherValue / step);
    slider->blockSignals(true);
    slider->setHigherValue(intValue);
    slider->blockSignals(false);
}

void FloatEditDualSliderPrivate::updateStep(qreal value)
{
    if (step != value)
    {
        step = value;
        slider->setMinimum(qRound(minimum / step));
        slider->setMaximum(qRound(maximum / step));
        slider->setPageStep(qRound(page / step));
        updateSliderLowerValue();
        updateSliderHigherValue();
    }
}

void FloatEditDualSliderPrivate::updatePage(qreal value)
{
    if (page != value)
    {
        page = value;
        slider->setPageStep(page / step);
    }
}

void FloatEditDualSliderPrivate::updateMinimum(qreal value)
{
    if (minimum != value)
    {
        minimum = value;
        slider->setMinimum(minimum / step);
        lowerValidator->setRange(minimum, higherValue, decimals);
        lowerValue = qBound(minimum, lowerValue, higherValue);
        updateLowerEditValue();
    }
}

void FloatEditDualSliderPrivate::updateMaximum(qreal value)
{
    if (maximum != value)
    {
        maximum = value;
        slider->setMaximum(maximum / step);
        higherValidator->setRange(lowerValue, maximum, decimals);
        higherValue = qBound(lowerValue, higherValue, maximum);
        updateHigherEditValue();
    }
}

void FloatEditDualSliderPrivate::updateDecimals(int value)
{
    if (value != decimals)
    {
        decimals = value;
        lowerValidator->setRange(minimum, higherValue, decimals);
        higherValidator->setRange(lowerValue, maximum, decimals);
        updateLowerEditValue();
        updateHigherEditValue();
    }
}

FloatEditDualSlider::FloatEditDualSlider(QWidget* parent)
    : QWidget(parent)
    , m_ptr(new FloatEditDualSliderPrivate(this))
{
    init();
}

FloatEditDualSlider::FloatEditDualSlider(Qt::Orientation orientation, QWidget* parent)
    : QWidget(parent)
    , m_ptr(new FloatEditDualSliderPrivate(this))
{
    Q_D(FloatEditDualSlider);
    d->orientation = orientation;

    init();
}

Qt::Orientation FloatEditDualSlider::orientation() const
{
    Q_D(const FloatEditDualSlider);
    return d->orientation;
}

QString FloatEditDualSlider::textTemplate() const
{
    Q_D(const FloatEditDualSlider);
    return d->lowerEdit->textTemplate();
}

void FloatEditDualSlider::setTextTemplate(const QString& textTemplate)
{
    Q_D(FloatEditDualSlider);
    d->lowerEdit->setTextTemplate(textTemplate);
    d->higherEdit->setTextTemplate(textTemplate);
}

qreal FloatEditDualSlider::lowerValue() const
{
    Q_D(const FloatEditDualSlider);
    return d->lowerValue;
}

void FloatEditDualSlider::setLowerValue(qreal value)
{
    Q_D(FloatEditDualSlider);
    if (value != d->lowerValue)
    {
        d->updateLowerValue(value);
        d->updateLowerEditValue();
        d->updateSliderLowerValue();
        emit lowerValueChanged(d->lowerValue);
    }
}

qreal FloatEditDualSlider::higherValue() const
{
    Q_D(const FloatEditDualSlider);
    return d->higherValue;
}

void FloatEditDualSlider::setHigherValue(qreal value)
{
    Q_D(FloatEditDualSlider);
    if (value != d->higherValue)
    {
        d->updateHigherValue(value);
        d->updateHigherEditValue();
        d->updateSliderHigherValue();
        emit higherValueChanged(d->higherValue);
    }
}

qreal FloatEditDualSlider::step() const
{
    Q_D(const FloatEditDualSlider);
    return d->step;
}

void FloatEditDualSlider::setStep(qreal step)
{
    Q_D(FloatEditDualSlider);
    d->updateStep(step);
}

qreal FloatEditDualSlider::page() const
{
    Q_D(const FloatEditDualSlider);
    return d->page;
}

void FloatEditDualSlider::setPage(qreal page)
{
    Q_D(FloatEditDualSlider);
    d->updatePage(page);
}

qreal FloatEditDualSlider::minimum() const
{
    Q_D(const FloatEditDualSlider);
    return d->minimum;
}

void FloatEditDualSlider::setMinimum(qreal minimum)
{
    Q_D(FloatEditDualSlider);
    d->updateMinimum(minimum);
}

qreal FloatEditDualSlider::maximum() const
{
    Q_D(const FloatEditDualSlider);
    return d->maximum;
}

void FloatEditDualSlider::setMaximum(qreal maximum)
{
    Q_D(FloatEditDualSlider);
    d->updateMaximum(maximum);
}

int FloatEditDualSlider::editMaxWidth() const
{
    Q_D(const FloatEditDualSlider);
    return d->lowerEdit->maximumWidth();
}

void FloatEditDualSlider::setEditMaxWidth(int width)
{
    Q_D(FloatEditDualSlider);
    d->lowerEdit->setMaximumWidth(width);
    d->higherEdit->setMaximumWidth(width);
}

int FloatEditDualSlider::decimals() const
{
    Q_D(const FloatEditDualSlider);
    return d->decimals;
}

void FloatEditDualSlider::setDecimals(int decimals)
{
    Q_D(FloatEditDualSlider);
    d->updateDecimals(decimals);
}

void FloatEditDualSlider::init()
{
    Q_D(FloatEditDualSlider);
    d->lowerValue = d->minimum = 0;
    d->higherValue = d->maximum = 100;
    d->step = 0.1;
    d->page = 10;

    QLocale lo(QLocale::C);
    lo.setNumberOptions(QLocale::RejectGroupSeparator);

    d->lowerEdit = new QLineEditEx;
    d->lowerValidator = new QDoubleValidator(d->minimum, d->higherValue - 1, d->decimals, this);
    d->lowerValidator->setLocale(lo);
    d->lowerEdit->setValidator(d->lowerValidator);
    d->lowerEdit->setMaximumWidth(60);
    d->lowerEdit->setText(QString::number(d->lowerValue));

    d->higherEdit = new QLineEditEx;
    d->higherValidator = new QDoubleValidator(d->lowerValue + 1, d->maximum, d->decimals, this);
    d->higherValidator->setLocale(lo);
    d->higherEdit->setValidator(d->higherValidator);
    d->higherEdit->setMaximumWidth(60);
    d->higherEdit->setText(QString::number(d->higherValue));

    d->slider = new DualSlider(d->orientation);
    d->slider->setMinimum(d->minimum / d->step);
    d->slider->setMaximum(d->maximum / d->step);
    d->updateSliderLowerValue();
    d->updateSliderHigherValue();

    QBoxLayout* layout = d->orientation == Qt::Horizontal ? new QBoxLayout(QBoxLayout::LeftToRight, this) : new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->addWidget(d->lowerEdit);
    layout->addWidget(d->slider);
    layout->addWidget(d->higherEdit);
    layout->setStretch(0, 0);
    layout->setStretch(1, 1);
    layout->setStretch(2, 0);
    layout->setMargin(0);
    layout->setSpacing(2);

    connect(d->slider, &DualSlider::lowerValueChanged, this, &FloatEditDualSlider::onSliderLowerValueChanged);
    connect(d->slider, &DualSlider::higherValueChanged, this, &FloatEditDualSlider::onSliderHigherValueChanged);
    connect(d->lowerEdit, &QLineEditEx::editingFinished, this, &FloatEditDualSlider::onMinEditEditingFinished);
    connect(d->higherEdit, &QLineEditEx::editingFinished, this, &FloatEditDualSlider::onMaxEditEditingFinished);
}

void FloatEditDualSlider::onSliderLowerValueChanged(int value)
{
    Q_D(FloatEditDualSlider);
    qreal realValue = value * d->step;
    if (realValue != d->lowerValue)
    {
        d->updateLowerValue(realValue);
        d->updateLowerEditValue();
        emit lowerValueChanged(realValue);
    }
}

void FloatEditDualSlider::onSliderHigherValueChanged(int value)
{
    Q_D(FloatEditDualSlider);
    qreal realValue = value * d->step;
    if (realValue != d->higherValue)
    {
        d->updateHigherValue(realValue);
        d->updateHigherEditValue();
        emit higherValueChanged(realValue);
    }
}

void FloatEditDualSlider::onMinEditEditingFinished()
{
    Q_D(FloatEditDualSlider);
    bool ok;
    qreal realValue = d->lowerEdit->text().toDouble(&ok);
    if (!ok)
    {
        return;
    }
    if (realValue != d->lowerValue)
    {
        d->updateLowerValue(realValue);
        d->updateSliderLowerValue();
        emit lowerValueChanged(realValue);
    }
}

void FloatEditDualSlider::onMaxEditEditingFinished()
{
    Q_D(FloatEditDualSlider);
    bool ok;
    qreal realValue = d->higherEdit->text().toDouble(&ok);
    if (!ok)
    {
        return;
    }
    if (realValue != d->higherValue)
    {
        d->updateHigherValue(realValue);
        d->updateSliderHigherValue();
        emit higherValueChanged(realValue);
    }
}



