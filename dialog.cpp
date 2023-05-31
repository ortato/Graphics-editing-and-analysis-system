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
    filename = QFileDialog::getOpenFileName(this, tr("Ñ¡ÔñÍ¼Ïñ"), "", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if (filename.isEmpty())
    {
        return;
    }
    else
    {
        QImage* img = new QImage;
        if (!(img->load(filename))) //¼ÓÔØÍ¼Ïñ
        {
            QMessageBox::information(this,
                tr("´ò¿ªÍ¼ÏñÊ§°Ü"),
                tr("´ò¿ªÍ¼ÏñÊ§°Ü!"));
            delete img;
            return;
        }
        ui->label->setPixmap(QPixmap::fromImage(*img));
    }
}
