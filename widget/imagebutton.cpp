#include "ImageButton.h"
#include "ui_ImageButton.h"
#include <QDebug>
#include <QFont>
ImageButton::ImageButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageButton)
{
    ui->setupUi(this);
    ui->img->setAlignment(Qt::AlignCenter);


    //QPixmap pix(":/imgs/images/icon.png");
    //ui->img->setScaledContents(true);
    //ui->img->resize(QSize(60, 60));

    //pix.scaled(QSize(60, 60), Qt::IgnoreAspectRatio);

    //ui->img->setPixmap(pix);
    //ui->text->setText("123");
    //ui->text->resize(ui->img->width(), ui->text->height());


    ui->text->adjustSize();
    QFont textFont("Helvetica");
    textFont.setPointSize(12);
    ui->text->setFont(textFont);

    //ui->text->setAlignment(Qt::AlignHCenter);
    //qDebug()<<ui->text->fontInfo().pointSize()<<endl;
    QPalette pe;
    //设置黑底红字
    pe.setColor(QPalette::Background,Qt::black);
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->text->setAutoFillBackground(true);
    //ui->text->setPalette(pe);


    //ui->verticalLayout->setGeometry(QRect(0, 0, 50, 50));
    //this->setGeometry(0, 0, 50, 50);
    //qDebug()<<this->width()<<endl;
}

ImageButton::~ImageButton()
{
    delete ui;
}

void ImageButton::setImagePath(const char* _path)
{
    QPixmap pix(":/imgs/images/chart.png");
    ui->img->setPixmap(pix);

}
