#include "EditSlider.h"

#include <QBoxLayout>
#include <QtMath>

EditSlider::EditSlider(QWidget *parent) 
    : QWidget(parent)
    , m_dir(Qt::Horizontal)
{
    init();
}

EditSlider::EditSlider(Qt::Orientation dir, QWidget *parent) 
    : QWidget(parent)
    , m_dir(dir)
{
    init();
}

int EditSlider::minimum() const
{
    return m_slider->minimum();
}

void EditSlider::setMinimum(int minimum)
{
    m_slider->setMinimum(minimum);
    m_validator->setRange(m_slider->minimum(), m_slider->maximum());
    validateText();
}

int EditSlider::maximum() const
{
    return m_slider->maximum();
}

void EditSlider::setMaximum(int maximum)
{
    m_slider->setMaximum(maximum);
    m_validator->setRange(m_slider->minimum(), m_slider->maximum());
    validateText();
}

int EditSlider::singleStep() const
{
    return m_slider->singleStep();
}

void EditSlider::setSingleStep(int singleStep)
{
    m_slider->setSingleStep(singleStep);
}

int EditSlider::pageStep() const
{
    return m_slider->pageStep();
}

void EditSlider::setPageStep(int pageStep)
{
    m_slider->setPageStep(pageStep);
}

int EditSlider::value() const
{
    return m_slider->value();
}

void EditSlider::setValue(int value)
{
    m_slider->setValue(value);
    m_edit->blockSignals(true);
    m_edit->setText(QString::number(value));
    m_edit->blockSignals(false);

    emit valueChanged(value);
}

int EditSlider::sliderPosition() const
{
    return m_slider->sliderPosition();
}

void EditSlider::setSliderPosition(int pos)
{
    m_slider->setSliderPosition(pos);
}

bool EditSlider::tracking() const
{
    return m_slider->hasTracking();
}

void EditSlider::setTracking(bool tracking)
{
    m_slider->setTracking(tracking);
}

QSize EditSlider::maximumLineEditSize() const
{
    return m_edit->maximumSize();
}

void EditSlider::setMaximumLineEditSize(const QSize &size)
{
    m_edit->setMaximumSize(size);
}

QString EditSlider::text() const
{
    return m_edit->text();
}

void EditSlider::setText(const QString &text)
{
    int pos = 0;
    QString str = text;
    if (m_validator->validate(str, pos) == QValidator::Acceptable)
    {
        m_edit->setText(text);
        int value = text.toInt();
        m_slider->blockSignals(true);
        m_slider->setValue(value);
        m_slider->blockSignals(false);

        emit valueChanged(value);
    }
}

void EditSlider::onLineEditSizeChanged()
{
}

void EditSlider::onSliderRangeChanged()
{
}

void EditSlider::onTextChanged()
{
}

void EditSlider::onSliderValueChanged(int value)
{
    m_edit->blockSignals(true);
    m_edit->setText(QString::number(value));
    m_edit->blockSignals(false);
}

void EditSlider::onLineEditTextChanged(const QString &text)
{
    QString str = text;
    int pos = 0;
    if (m_validator->validate(str, pos) == QValidator::Acceptable)
    {
        m_slider->blockSignals(true);
        int value = qBound(m_slider->minimum(), text.toInt(), m_slider->maximum());
        m_slider->setValue(value);
        m_slider->blockSignals(false);
    }
}

void EditSlider::init()
{
    m_slider = new QSlider(m_dir);

    m_edit = new QLineEdit;
    m_edit->setMaximumWidth(30);
    m_edit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_edit->setText(QString::number(m_slider->minimum()));

    m_validator = new QIntValidator(m_slider->minimum(), m_slider->maximum(), this);
    m_edit->setValidator(m_validator);

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    if (m_dir == Qt::Horizontal)
        layout->setDirection(QBoxLayout::LeftToRight);
    else if (m_dir == Qt::Vertical)
        layout->setDirection(QBoxLayout::TopToBottom);

    layout->addWidget(m_slider);
    layout->addWidget(m_edit);
    layout->setStretch(0, 1);
    layout->setStretch(1, 0);
    layout->setMargin(0);

    setLayout(layout);

    connect(m_slider, &QSlider::valueChanged, this, &EditSlider::onSliderValueChanged);
    connect(m_edit, &QLineEdit::textChanged, this, &EditSlider::onLineEditTextChanged);
    connect(m_slider, &QSlider::valueChanged, this, &EditSlider::valueChanged);
}

void EditSlider::validateText()
{
    int value = m_edit->text().toInt();
    value = qBound(m_slider->minimum(), value, m_slider->maximum());
    m_edit->setText(QString::number(value));
}
