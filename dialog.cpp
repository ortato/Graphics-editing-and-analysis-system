#include "dialog.h"
#include "ui_dialog.h"
Dialog::Dialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}
Dialog::~Dialog()
{
    delete ui;
}
void Dialog::onOpen()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("ѡ��ͼ��"), "", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if (filename.isEmpty())
    {
        return;
    }
    else
    {
        QImage* img = new QImage;
        if (!(img->load(filename))) //����ͼ��
        {
            QMessageBox::information(this,
                tr("��ͼ��ʧ��"),
                tr("��ͼ��ʧ��!"));
            delete img;
            return;
        }
        ui->label->setPixmap(QPixmap::fromImage(*img));
    }
}
