#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QWidget>
/**
 *使用时，需要在界面中添加一个和此自定义控件一样大小的widget（60*80）
 * 图片的尺寸为50*50
 */
namespace Ui {
class ImageButton;
}

class ImageButton : public QWidget
{
    Q_OBJECT

public:
    explicit ImageButton(QWidget *parent = 0);
    ~ImageButton();
    void setImagePath(const char* _path);

private:
    Ui::ImageButton *ui;
};

#endif // IMAGEBUTTON_H
