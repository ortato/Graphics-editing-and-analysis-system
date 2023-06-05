#include "mypencontrol.h"
#include <QPainter>
myPenControl::myPenControl()
{
    curPen = NULL;
}
myPenControl::myPenControl(std::vector<Figure*>* figures, std::vector<Figure*>* history) :FigureControl(figures, history)
{
    curPen = NULL;
}
myPenControl::myPenControl(int width, int height) : FigureControl(width, height)
{
    curPen = NULL;
}
myPenControl::myPenControl(std::vector<Figure*>* figures, int width, int height) : FigureControl(figures, width, height)
{
    curPen = NULL;
}
myPenControl::~myPenControl()
{
}
//画笔轨迹不能选中
bool myPenControl::setFocus(Figure* fg)
{
    return false;
}
//开始点击左键
void myPenControl::onMousePressEvent(QMouseEvent* event)
{
    //鼠标左键按下
    if (curPen == NULL)  //若是还没有画过 画笔
    {
        Pen* p = new Pen();
        //  p = new Pen;
        curPen = p;  //每次单击，重新开始画一条线
        curPen->addPoint(new Point(event->x(), height - event->y()));
    }
}
void myPenControl::onMouseMoveEvent(QMouseEvent* event)
{
    // 鼠标左键按下的同时移动鼠标
    if (event->buttons() & Qt::LeftButton)
    {
        curPen->addPoint(new Point(event->x(), height - event->y())); //保持鼠标位置
    }
}
void myPenControl::onMousePassiveMoveEvent(QMouseEvent* event)
{
    //鼠标左键释放
    if (curPen != NULL)
    {
        allFigures->push_back(curPen);  //鼠标释放后，生成一个完整的对象
        Allpens.push_back(curPen);
        curPen = NULL;
    }
}
//画出图形本身
void myPenControl::onDraw()
{
    for (Pen* mypen : Allpens)
        mypen->draw();
}
//实时更新和显示当前画的线
void myPenControl::onMarkDraw()
{
    if (curPen == NULL)
        return;
    else
        curPen->draw();
}
//清除
void myPenControl::onClear()
{
    for (Pen* mypen : Allpens)
    {
        for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end();)
        {
            if (mypen == *it)
                it = allFigures->erase(it);
            else
                it++;
        }
        delete mypen;
    }
    Allpens.clear();
    // curPen->clear();
    // curPen = NULL;
}
