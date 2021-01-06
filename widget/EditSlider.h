#ifndef EDITSLIDER_H
#define EDITSLIDER_H

#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QIntValidator>
#include <QtUiPlugin/QDesignerExportWidget>

#include "ExportLRWidgets.h"

class LRWIDGET_EXPORT EditSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int minimum READ minimum WRITE setMinimum DESIGNABLE true)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum DESIGNABLE true)
    Q_PROPERTY(int singleStep READ singleStep WRITE setSingleStep DESIGNABLE true)
    Q_PROPERTY(int pageStep READ pageStep WRITE setPageStep DESIGNABLE true)
    Q_PROPERTY(int value READ value WRITE setValue DESIGNABLE true)
    Q_PROPERTY(int sliderPosition READ sliderPosition WRITE setSliderPosition DESIGNABLE true)
    Q_PROPERTY(bool tracking READ tracking WRITE setTracking DESIGNABLE true)

    Q_PROPERTY(QString text READ text WRITE setText DESIGNABLE false)
    Q_PROPERTY(QSize maximumLineEditSize READ maximumLineEditSize WRITE setMaximumLineEditSize DESIGNABLE true)
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

    int sliderPosition() const;
    void setSliderPosition(int pos);

    bool tracking() const;
    void setTracking(bool tracking);

    QSize maximumLineEditSize() const;
    void setMaximumLineEditSize(const QSize& size);

    QString text() const;
    void setText(const QString& text);

public slots:
    void onLineEditSizeChanged();
    void onSliderRangeChanged();
    void onTextChanged();

    void onSliderValueChanged(int value);
    void onLineEditTextChanged(const QString& text);

signals:
    void valueChanged(int value);

private:
    void init();
    void validateText();

private:
    Qt::Orientation m_dir;
    QLineEdit* m_edit;
    QSlider* m_slider;
    QIntValidator* m_validator;
};

#endif // EDITSLIDER_H
