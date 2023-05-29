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
    void on_changeMode(Mode m); //��Ӧ��glwidget�������ź�
                                //�òۺ��������ı仭ͼ��ģʽ
private slots:
    //�˵���
    void on_actionNew_triggered();      //�½�
    void on_actionOpen_triggered();     //���ļ�
    void on_actionSave_triggered();     //�����ļ�
    //������
    void on_actionLine_triggered();     //ֱ��ģʽ
    void on_actionCurve_triggered();    //����ģʽ
    void on_actionCircle_triggered();   //Բģʽ
    void on_actionEllipse_triggered();  //��Բģʽ
    void on_actionColor_triggered();    //ѡ����ɫ
    void on_actionDelete_triggered();   //ɾ����ǰͼ��
    void on_actionClear_triggered();    //�������ͼ��
    void on_actionFill_triggered();     //���
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