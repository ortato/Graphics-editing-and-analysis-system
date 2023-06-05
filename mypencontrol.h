#ifndef MYPENCONTROL_H
#define MYPENCONTROL_H
#include "mypen.h"
#include "Point.h"
#include "FigureControl.h"
#include <QPainter>
//#include <vector>
using namespace std;
class myPenControl :public FigureControl
{
public:
    myPenControl();
    myPenControl(std::vector<Figure*>* figures, std::vector<Figure*>* history);
    myPenControl(int width, int height);
    myPenControl(std::vector<Figure*>* figures, int width, int height);
    ~myPenControl();
    virtual bool setFocus(Figure* fg);
    virtual void onMousePressEvent(QMouseEvent* event);
    virtual void onMouseMoveEvent(QMouseEvent* event);
    virtual void onMousePassiveMoveEvent(QMouseEvent* event);
    virtual void onDraw();     //画线，存储所有捕捉到的点
    virtual void onMarkDraw(); //画标记点，这里无
    //virtual void onDelete(); //删除
    virtual void onClear();  //清除
private:
    //enum SetLP{SETBEGIN, SETEND, SETCENTER, SETHANDLE} setLP; //目前更改的是起点/终点
   // vector<Line*> lines;
    Pen* curPen;
    vector<Pen*> Allpens; //包括所有绘制好的画笔线
};
#endif // MYPENCONTROL_H