#include <QApplication>
#include <QBoxLayout>
#include <QWidget>
#include "widget/QLineEditEx.h"
#include "widget/EditSlider.h"
#include "widget/FloatEditSlider.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QWidget window;

    QLineEditEx* lineEdit01 = new QLineEditEx(&window);
    QLineEditEx* lineEdit02 = new QLineEditEx(&window);
    lineEdit02->setTextTemplate("%1mm");

    FloatEditSlider* slider01 = new FloatEditSlider(Qt::Horizontal);
    slider01->setStep(0.1);
    slider01->setMinimum(0);
    slider01->setMaximum(300);
    slider01->setPage(10);
    slider01->setMaximumLineEditWidth(50);

    EditSlider* slider02 = new EditSlider(Qt::Horizontal);
    slider02->setSingleStep(1);
    slider02->setMinimum(0);
    slider02->setMaximum(200);
    slider02->setPageStep(10);
    slider02->setMaximumLineEditWidth(50);

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom);
    layout->addWidget(lineEdit01);
    layout->addWidget(lineEdit02);
    layout->addWidget(slider02);
    layout->addWidget(slider01);
    window.setLayout(layout);
    
    window.show();
    return app.exec();
}
