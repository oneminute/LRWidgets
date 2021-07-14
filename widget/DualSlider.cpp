#include "DualSlider.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionSlider>

class DualSliderPrivate
{
    Q_DECLARE_PUBLIC(DualSlider)
public:
    DualSliderPrivate(DualSlider* ptr)
        : q_ptr(ptr)
    {}

    int pixelPosToRangeValue(int pos, DualSlider::HandleType ht) const;
    inline int pick(const QPoint& pt) const;
    int bound(int pos, DualSlider::HandleType ht) const;

    DualSlider* q_ptr;
    int lowerValue;
    int higherValue;

    QStyle::SubControl pressedControl;
    int clickOffset;
    DualSlider::HandleType currentHandle;
};

int DualSliderPrivate::pixelPosToRangeValue(int pos, DualSlider::HandleType ht) const
{
    Q_Q(const DualSlider);
    QStyleOptionSlider opt;
    q->initStyleOption(&opt);
    QRect gr = q->subControlRect(QStyle::SC_SliderGroove, &opt);
    QRect sr = q->subControlRect(QStyle::SC_SliderHandle, &opt, ht);
    int sliderMin, sliderMax, sliderLength;

    if (q->orientation() == Qt::Horizontal) {
        sliderLength = sr.width();
        sliderMin = gr.x();
        sliderMax = gr.right() - sliderLength + 1;
    }
    else {
        sliderLength = sr.height();
        sliderMin = gr.y();
        sliderMax = gr.bottom() - sliderLength + 1;
    }
    return QStyle::sliderValueFromPosition(q->minimum(), q->maximum(), pos - sliderMin,
        sliderMax - sliderMin, opt.upsideDown);
}

inline int DualSliderPrivate::pick(const QPoint& pt) const
{
    Q_Q(const DualSlider);
    return q->orientation() == Qt::Horizontal ? pt.x() : pt.y();
}

int DualSliderPrivate::bound(int pos, DualSlider::HandleType ht) const
{
    Q_Q(const DualSlider);
    if (ht == DualSlider::HT_Lower)
    {
        return qBound(q->minimum(), pos, higherValue - 1);
    }
    else if (ht == DualSlider::HT_Higher)
    {
        return qBound(lowerValue + 1, pos, q->maximum());
    }
}

DualSlider::DualSlider(QWidget* parent)
    : QSlider(parent)
    , m_ptr(new DualSliderPrivate(this))
{
    init();
}

DualSlider::DualSlider(Qt::Orientation orientation, QWidget* parent)
    : QSlider(orientation, parent)
    , m_ptr(new DualSliderPrivate(this))
{
    init();
}

DualSlider::~DualSlider()
{
}

int DualSlider::lowerValue() const
{
    Q_D(const DualSlider);
    return d->lowerValue;
}

void DualSlider::setLowerValue(int value)
{
    Q_D(DualSlider);
    value = d->bound(value, HT_Lower);
    if (value == d->lowerValue)
        return;
    d->lowerValue = value;
    update();
}

int DualSlider::higherValue() const
{
    Q_D(const DualSlider);
    return d->higherValue;
}

void DualSlider::setHigherValue(int value)
{
    Q_D(DualSlider);
    value = d->bound(value, HT_Higher);
    if (value == d->higherValue)
        return;
    d->higherValue = value;
    update();
}

void DualSlider::setSliderPosition(int position, HandleType ht)
{
    if (ht == HT_Lower)
    {
        setLowerValue(position);
    }
    else if (ht == HT_Higher)
    {
        setHigherValue(position);
    }
}

void DualSlider::init()
{
    Q_D(DualSlider);
    d->lowerValue = minimum();
    d->higherValue = maximum();
}

void DualSlider::paintEvent(QPaintEvent* evt)
{
    Q_D(DualSlider);

    QPainter p(this);
    QStyleOptionSlider opt;

    initStyleOption(&opt);
    opt.subControls = QStyle::SC_SliderGroove;
    opt.rect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    opt.activeSubControls = QStyle::SC_SliderGroove;
    style()->drawComplexControl(QStyle::CC_Slider, &opt, &p, this);

    initStyleOption(&opt);
    opt.sliderPosition = d->lowerValue;
    opt.subControls = QStyle::SC_SliderHandle;
    opt.rect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    style()->drawComplexControl(QStyle::CC_Slider, &opt, &p, this);

    initStyleOption(&opt);
    opt.sliderPosition = d->higherValue;
    opt.subControls = QStyle::SC_SliderHandle;
    opt.rect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    style()->drawComplexControl(QStyle::CC_Slider, &opt, &p, this);
}

void DualSlider::mousePressEvent(QMouseEvent* evt)
{
    Q_D(DualSlider);

    if (maximum() == minimum() || (evt->buttons() ^ evt->buttons()))
    {
        evt->ignore();
        return;
    }

    evt->accept();
    Qt::MouseButton button = evt->button();
    if ((button & style()->styleHint(QStyle::SH_Slider_AbsoluteSetButtons)) == button)
    {
        qDebug() << "mouse middle button pressed";
    }
    else if ((button & style()->styleHint(QStyle::SH_Slider_PageSetButtons)) == button)
    {
        QStyleOptionSlider opt;
        initStyleOption(&opt);
        d->pressedControl = hitTestComplexControl(&opt, evt->pos(), d->currentHandle);
    }
    else
    {
        evt->ignore();
        return;
    }

    if (d->pressedControl == QStyle::SC_SliderHandle)
    {
        QStyleOptionSlider opt;
        initStyleOption(&opt);
        setRepeatAction(SliderNoAction);
        QRect sr = subControlRect(QStyle::SC_SliderHandle, &opt, d->currentHandle);
        //qDebug() << "mouse left button pressed";
        d->clickOffset = d->pick(evt->pos() - sr.topLeft());
        update(sr);
        setSliderDown(true);
    }
}

void DualSlider::mouseReleaseEvent(QMouseEvent* evt)
{
    Q_D(DualSlider);
    if (d->pressedControl == QStyle::SC_None || evt->buttons())
    {
        evt->ignore();
        return;
    }
    evt->accept();

    QStyle::SubControl oldPressed = QStyle::SubControl(d->pressedControl);
    d->pressedControl = QStyle::SC_None;
    setRepeatAction(SliderNoAction);
    if (oldPressed == QStyle::SC_SliderHandle)
        setSliderDown(false);
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    opt.subControls = oldPressed;
    update(subControlRect(oldPressed, &opt, d->currentHandle));
}

void DualSlider::mouseMoveEvent(QMouseEvent* evt)
{
    Q_D(DualSlider);
    if (d->pressedControl != QStyle::SC_SliderHandle) {
        evt->ignore();
        return;
    }
    evt->accept();

    QStyleOptionSlider opt;
    initStyleOption(&opt);
    
    int newPosition = d->pixelPosToRangeValue(d->pick(evt->pos()) - d->clickOffset, d->currentHandle);
    qDebug() << d->currentHandle << "newPosition:" << newPosition;
    setSliderPosition(newPosition, d->currentHandle);
}

QRect DualSlider::subControlRect(QStyle::SubControl subControl, const QStyleOptionSlider* option, HandleType ht) const
{
    Q_D(const DualSlider);
    QRect ret;
    int tickOffset = style()->pixelMetric(QStyle::PM_SliderTickmarkOffset, option, this);
    int thickness = style()->pixelMetric(QStyle::PM_SliderControlThickness, option, this);
    int pos = ht == HT_Lower ? d->lowerValue : d->higherValue;
    switch (subControl) {
    case QStyle::SC_SliderHandle: {
        int sliderPos = 0;
        int len = style()->pixelMetric(QStyle::PM_SliderLength, option, this);
        bool horizontal = option->orientation == Qt::Horizontal;
        sliderPos = style()->sliderPositionFromValue(option->minimum, option->maximum,
            pos,
            (horizontal ? option->rect.width()
                : option->rect.height()) - len,
            option->upsideDown);
        if (horizontal)
            ret.setRect(option->rect.x() + sliderPos, option->rect.y() + tickOffset, len, thickness);
        else
            ret.setRect(option->rect.x() + tickOffset, option->rect.y() + sliderPos, thickness, len);
        break; }
    case QStyle::SC_SliderGroove:
        if (option->orientation == Qt::Horizontal)
            ret.setRect(option->rect.x(), option->rect.y() + tickOffset,
                option->rect.width(), thickness);
        else
            ret.setRect(option->rect.x() + tickOffset, option->rect.y(),
                thickness, option->rect.height());
        break;
    default:
        break;
    }
    ret = style()->visualRect(option->direction, option->rect, ret);

    return ret;
}

QStyle::SubControl DualSlider::hitTestComplexControl(const QStyleOptionSlider* option, const QPoint& pt, HandleType& handleType) const
{
    Q_D(const DualSlider);
    QStyle::SubControl sc = QStyle::SC_None;
    QRect r = subControlRect(QStyle::SC_SliderHandle, option, HT_Lower);
    if (r.isValid() && r.contains(pt)) {
        sc = QStyle::SC_SliderHandle;
        handleType = HT_Lower;
    }
    else {
        r = subControlRect(QStyle::SC_SliderGroove, option, HT_Higher);
        if (r.isValid() && r.contains(pt)) {
            sc = QStyle::SC_SliderHandle;
            handleType = HT_Higher;
        }
        else
        {
            r = subControlRect(QStyle::SC_SliderGroove, option);
            if (r.isValid() && r.contains(pt))
                sc = QStyle::SC_SliderGroove;
        }
    }
    return sc;
}

