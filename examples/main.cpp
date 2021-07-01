#include <QApplication>
#include <QBoxLayout>
#include <QWidget>
#include "widget/QLineEditEx.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedWidth(300);

    QLineEditEx* lineEdit01 = new QLineEditEx(&window);
    QLineEditEx* lineEdit02 = new QLineEditEx(&window);
    lineEdit02->setTextTemplate("%1mm");

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom);
    layout->addWidget(lineEdit01);
    layout->addWidget(lineEdit02);
    window.setLayout(layout);
    
    window.show();
    return app.exec();
}
