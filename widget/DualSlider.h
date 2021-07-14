#ifndef DUALSLIDER_H
#define DUALSLIDER_H

#include <QSlider>
#include <QStyle>

class QStyleOptionSlider;
class DualSliderPrivate;
class DualSlider : public QSlider
{
    Q_OBJECT
public:
    enum HandleType
    {
        HT_Lower,
        HT_Higher
    };

    explicit DualSlider(QWidget* parent = nullptr);
    explicit DualSlider(Qt::Orientation orientation, QWidget* parent = nullptr);

    ~DualSlider();

    int lowerValue() const;
    void setLowerValue(int value);

    int higherValue() const;
    void setHigherValue(int value);

    void setSliderPosition(int position, HandleType ht);

protected:
    void init();
    virtual void paintEvent(QPaintEvent* evt) override;
    virtual void mousePressEvent(QMouseEvent* evt) override;
    virtual void mouseReleaseEvent(QMouseEvent* evt) override;
    virtual void mouseMoveEvent(QMouseEvent* evt) override;

    QRect subControlRect(QStyle::SubControl subControl, const QStyleOptionSlider* option, HandleType ht = HT_Lower) const;
    QStyle::SubControl hitTestComplexControl(const QStyleOptionSlider* option, const QPoint &pt, HandleType& handleType) const;

signals:
    void lowerValueChanged(int value);
    void higherValueChanged(int value);

private:
    QScopedPointer<DualSliderPrivate> m_ptr;
    Q_DECLARE_PRIVATE_D(m_ptr, DualSlider)
    Q_DISABLE_COPY(DualSlider)
};

#endif // DUALSLIDER_H