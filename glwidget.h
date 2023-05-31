#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "LineControl.h"
#include "circlecontrol.h"
#include "MyEllipseControl.h"
#include "CurveControl.h"
#include "FigureControl.h"
#include "mypen.h"
#include "mypencontrol.h"
#include "rectangular.h"
#include "rectangularcontrol.h"
#include <QtOpenGL/QtOpenGL>
#include <GL/glut.h>
#include <QMouseEvent>
#include <vector>
enum Mode { LINE = 0, CIRCLE, ELLIPSE, CURVE, PEN, RECTANGLE };     //基本功能
//enum Edit{DRAW=0, FILL, CUT};                 //扩展功能
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget* parent, Mode m);
    ~GLWidget();
    virtual void setMode(Mode m);
    void onOpen();                  //打开文件
    void onSave(string fileName);   //保存文件
    virtual void onDelete(); //删除当前被选中的图形
    virtual void onClear(); //清空画布
    virtual void onFill();  //填充
    virtual void undo();    //撤销
signals:
    void changeMode(Mode m); //更新绘图状态
protected:
    //用于画图
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    //用于交互
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    int curCtrl; //当前FigureControl的索引
    vector<FigureControl*> figureControls;  //各个图形的控制，一开始就 push_bsck 5种图形的控制函数
    vector<Figure*> allFigures;             //本画布中的所有图形
    vector<Figure*> history;                //本画布的历史记录
    Figure* setFocusByPoint(const Point& p);//根据点击的点来设置curCtrl和对应FigureControl的curFigure
};
#endif // GLWIDGET_H
