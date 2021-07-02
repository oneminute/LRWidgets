#include "EditSlider.h"
#include "QLineEditEx.h"

#include <QBoxLayout>
#include <QtMath>

class EditSliderPrivate
{
    Q_DECLARE_PUBLIC(EditSlider)
public:
    EditSliderPrivate(EditSlider* ptr)
        : q_ptr(ptr)
    {}

    EditSlider* q_ptr;

    QLineEditEx* edit;
    QSlider* slider;
    QIntValidator* validator;
};

EditSlider::EditSlider(Qt::Orientation orientation, QWidget *parent) 
    : QWidget(parent)
    , m_ptr(new EditSliderPrivate(this))
{
    Q_D(EditSlider);
    d->slider = new QSlider(orientation, this);

    d->edit = new QLineEditEx(this);
    d->edit->setText(QString::number(d->slider->minimum()));

    d->validator = new QIntValidator(d->slider->minimum(), d->slider->maximum(), this);
    d->edit->setValidator(d->validator);

    QBoxLayout* layout = (orientation == Qt::Horizontal) ? new QBoxLayout(QBoxLayout::LeftToRight, this) : new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->setMargin(0);
    layout->addWidget(d->slider);
    layout->addWidget(d->edit);
    layout->setStretch(0, 1);
    layout->setStretch(1, 0);
    layout->setMargin(0);
    setLayout(layout);

    connect(d->slider, &QSlider::valueChanged, this, &EditSlider::onSliderValueChanged);
    connect(d->slider, &QSlider::valueChanged, this, &EditSlider::valueChanged);
    connect(d->edit, &QLineEditEx::textChanged, this, &EditSlider::onLineEditTextChanged);
}

int EditSlider::minimum() const
{
    Q_D(const EditSlider);
    return d->slider->minimum();
}

void EditSlider::setMinimum(int minimum)
{
    Q_D(EditSlider);
    d->slider->setMinimum(minimum);
    d->validator->setRange(d->slider->minimum(), d->slider->maximum());
    //validateText();
}

int EditSlider::maximum() const
{
    Q_D(const EditSlider);
    return d->slider->maximum();
}

void EditSlider::setMaximum(int maximum)
{
    Q_D(EditSlider);
    d->slider->setMaximum(maximum);
    d->validator->setRange(d->slider->minimum(), d->slider->maximum());
    //validateText();
}

int EditSlider::singleStep() const
{
    Q_D(const EditSlider);
    return d->slider->singleStep();
}

void EditSlider::setSingleStep(int singleStep)
{
    Q_D(EditSlider);
    d->slider->setSingleStep(singleStep);
}

int EditSlider::pageStep() const
{
    Q_D(const EditSlider);
    return d->slider->pageStep();
}

void EditSlider::setPageStep(int pageStep)
{
    Q_D(EditSlider);
    d->slider->setPageStep(pageStep);
}

int EditSlider::value() const
{
    Q_D(const EditSlider);
    return d->slider->value();
}

void EditSlider::setValue(int value)
{
    Q_D(EditSlider);
    d->slider->setValue(value);
    d->edit->blockSignals(true);
    d->edit->setText(QString::number(value));
    d->edit->blockSignals(false);

    emit valueChanged(value);
}

bool EditSlider::tracking() const
{
    Q_D(const EditSlider);
    return d->slider->hasTracking();
}

void EditSlider::setTracking(bool tracking)
{
    Q_D(EditSlider);
    d->slider->setTracking(tracking);
}

int EditSlider::maximumLineEditWidth() const
{
    Q_D(const EditSlider);
    return d->edit->maximumWidth();
}

void EditSlider::setMaximumLineEditWidth(int width)
{
    Q_D(EditSlider);
    d->edit->setMaximumWidth(width);
}

QString EditSlider::text() const
{
    Q_D(const EditSlider);
    return d->edit->text();
}

void EditSlider::onSliderValueChanged(int value)
{
    Q_D(EditSlider);
    d->edit->blockSignals(true);
    d->edit->setText(QString::number(value));
    d->edit->blockSignals(false);
}

void EditSlider::onLineEditTextChanged(const QString& text)
{
    Q_D(EditSlider);
    d->slider->blockSignals(true);
    int value = qBound(d->slider->minimum(), d->edit->text().toInt(), d->slider->maximum());
    d->slider->setValue(value);
    d->slider->blockSignals(false);
}

