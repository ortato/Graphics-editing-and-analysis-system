#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMenu>
#include <QTextEdit>
#include "glwidget.h"
namespace Ui
{
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
public slots:
    void on_changeMode(Mode m); //响应从glwidget发来的信号
                                //该槽函数用来改变画图的模式
private slots:
    //菜单栏
    void on_actionNew_triggered();      //新建
    void on_actionOpen_triggered();     //打开文件
    void on_actionSave_triggered();     //保存文件
    //工具栏
    void on_actionLine_triggered();     //直线模式
    void on_actionCurve_triggered();    //曲线模式
    void on_actionCircle_triggered();   //圆模式
    void on_actionEllipse_triggered();  //椭圆模式
    void on_actionColor_triggered();    //选择颜色
    void on_actionDelete_triggered();   //删除当前图形
    void on_actionClear_triggered();    //清除所有图形
    void on_actionFill_triggered();     //填充
    void on_actionUndo_triggered();
    void on_actionwidth_1_triggered();
    void on_actionwidth_2_triggered();
    void on_actionwidth_3_triggered();
    void on_actionwidth_5_triggered();
    void on_actionPen_triggered();
    void on_actionRectangle_triggered();
private:
    Ui::MainWindow* ui;
    Mode m;
    void setMode(Mode m);
};
#endif // MAINWINDOW_H