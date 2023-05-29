#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include "dialog.h"
#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("ͼ�α༭��"));
    setCentralWidget(ui->mdiArea);
    ui->mdiArea->setViewMode(QMdiArea::TabbedView); //�����ӿ�ģʽ��tabBarģʽ
    ui->mdiArea->setTabPosition(QTabWidget::North); //����tabBar�ķ�λ
    ui->mdiArea->setTabsClosable(true);             //�رհ�ť
    setMode(LINE);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setMode(Mode m)
{
    this->m = m;
    for (QMdiSubWindow* w : ui->mdiArea->subWindowList())
    {
        static_cast<GLWidget*>(w->widget())->setMode(m);
    }
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionCurve->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionRectangle->setChecked(false);
    switch (m)
    {
    case LINE: ui->actionLine->setChecked(true); break;
    case CIRCLE: ui->actionCircle->setChecked(true); break;
    case ELLIPSE: ui->actionEllipse->setChecked(true); break;
    case CURVE: ui->actionCurve->setChecked(true); break;
    case PEN: ui->actionPen->setChecked(true); break;
    case RECTANGLE: ui->actionRectangle->setChecked(true); break;
    default:;
    }
}
void MainWindow::on_changeMode(Mode m)
{
    setMode(m);
}
void MainWindow::on_actionNew_triggered()
{
    GLWidget* glw = new GLWidget(this, m);//�½�һ��GLWidget����
    connect(glw, SIGNAL(changeMode(Mode)), this, SLOT(on_changeMode(Mode)));
    QMdiSubWindow* w = ui->mdiArea->addSubWindow(glw);
    ui->mdiArea->setActiveSubWindow(w);
    w->setWindowTitle(tr("ͼ%1").arg(ui->mdiArea->subWindowList().size()));
    w->show();
}
void MainWindow::on_actionCurve_triggered()
{
    setMode(CURVE);
}
void MainWindow::on_actionLine_triggered()
{
    setMode(LINE);
}
void MainWindow::on_actionCircle_triggered()
{
    setMode(CIRCLE);
}
void MainWindow::on_actionEllipse_triggered()
{
    setMode(ELLIPSE);
}
void MainWindow::on_actionSave_triggered()
{
    if (ui->mdiArea->subWindowList().empty())
        return;
    QMdiSubWindow* w = ui->mdiArea->activeSubWindow();
    QString path = QFileDialog::getSaveFileName(this, tr("�����ļ�"), ".", tr("BMP Files(*.bmp)"));
    ui->mdiArea->setActiveSubWindow(w); //����FileDialog֮��ᵼ��activeSubWindowΪ�գ���Ҫ��������
    if (!path.isNull())
        static_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onSave(path.toStdString());
}
void MainWindow::on_actionOpen_triggered()
{
    Dialog* dlg = new Dialog(this);
    dlg->onOpen();
    dlg->show();
}
void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    Area::setColor(make_tuple(color.redF(), color.greenF(), color.blueF()));
    SimpleFigure::setColor(make_tuple(color.redF(), color.greenF(), color.blueF()));
}
void MainWindow::on_actionDelete_triggered()
{
    if (ui->mdiArea->subWindowList().empty())
        return;
    static_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onDelete();
}
void MainWindow::on_actionClear_triggered()
{
    if (ui->mdiArea->subWindowList().empty())
        return;
    static_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onClear();
}
void MainWindow::on_actionFill_triggered()
{
    if (ui->mdiArea->subWindowList().empty())
        return;
    static_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->onFill();
}
void MainWindow::on_actionUndo_triggered()
{
    if (ui->mdiArea->subWindowList().empty())
        return;
    static_cast<GLWidget*>(ui->mdiArea->activeSubWindow()->widget())->undo();
}
void MainWindow::on_actionwidth_1_triggered()
{
    SimpleFigure::setPSize(1.0);
}
void MainWindow::on_actionwidth_2_triggered()
{
    SimpleFigure::setPSize(2.0);
}
void MainWindow::on_actionwidth_3_triggered()
{
    SimpleFigure::setPSize(3.0);
}
void MainWindow::on_actionwidth_5_triggered()
{
    SimpleFigure::setPSize(5.0);
}
void MainWindow::on_actionPen_triggered()
{
    setMode(PEN);
}
void MainWindow::on_actionRectangle_triggered()
{
    setMode(RECTANGLE);
}