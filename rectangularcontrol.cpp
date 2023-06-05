#include "rectangular.h"
#include "rectangularcontrol.h"
#include <GL/glut.h>
RectangularControl::RectangularControl()
{
    currectangular = NULL;
}
RectangularControl::RectangularControl(std::vector<Figure*>* figures, std::vector<Figure*>* history)
    :FigureControl(figures, history)
{
    currectangular = NULL;
}
RectangularControl::RectangularControl(int width, int height) : FigureControl(width, height) // 封闭类构造函数的列表
{
    currectangular = NULL;   // width 和 height是矩形宽和长
}
bool RectangularControl::setFocus(Figure* fg)  // 多态函数，不光返回图形是否在该派生类上
{
    for (Rectangular* rectangular : Allrectangular)
        if (rectangular == fg)                    // 如果是
        {
            currectangular = rectangular;      //则把“标记”成员变量修改为 该图形
            return true;
        }
    return false;
}
//单击左键的操作
void RectangularControl::onMousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) //点击左键
    {
        if (currectangular != NULL)  //如果当前矩形存在
        {
            bool flag = false;
            Point curPoint(event->x(), height - event->y());  //创建一个点对象，记录当前鼠标点
            for (Point p : currectangular->getMarkPoints())
                if (curPoint.distanceTo(currectangular->getCenter()) <= 5) //点击的是中心点
                {
                    setEP = CENTERPOINT;
                    flag = true;
                }
                else if (curPoint.distanceTo(currectangular->getHandlePoint()) <= 5) //点击handle
                {
                    setEP = HANDLEPOINT;
                    flag = true;
                }
                else if (currectangular->isOn(curPoint)) //点击在周长上
                {
                    flag = true;
                }
            if (flag)
            {
                pushForward(currectangular);
                return;
            }
        }
        //如果之前还没有派生类对象
        currectangular = new Rectangular(Point(event->x(), height - event->y()), Point(event->x(), height - event->y()));
        Allrectangular.push_back(currectangular);
        allFigures->push_back(currectangular);
        setEP = ENDPOINT;//此时只画了一个点，模式调整为endpoint模式，等待mousemove输入第二个点
    }
}
//鼠标拖动
void RectangularControl::onMouseMoveEvent(QMouseEvent* event)
{
    if (currectangular == NULL)
        return;
    Point cur_center_p = currectangular->getCenter();
    switch (setEP)
    {
    case ENDPOINT: currectangular->setEndPoint(Point(event->x(), height - event->y())); break;
        //  case MARKPOINT: currectangular->scale(abs(event->x()-cur_center_p.getX()), abs((height-event->y())-cur_center_p.getY())); break;
    case CENTERPOINT: currectangular->translate(Point(event->x(), height - event->y()) - cur_center_p); break;
    default:;
    }
}
//画出所有矩形
void RectangularControl::onDraw()
{
    for (Rectangular* rectangular : Allrectangular)
        rectangular->draw();
}
//标记当前矩形
void RectangularControl::onMarkDraw()
{
    if (currectangular != NULL)
        currectangular->markDraw();
}
//对当前矩形进行缩放
void RectangularControl::onScale(double r)
{
    if (currectangular != NULL)
        currectangular->scale(r);
}
//删掉当前矩形
void RectangularControl::onDelete()
{
    if (currectangular == NULL) //没有指向矩形，则不操作
        return;
    for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end(); it++) //删掉保存在allFigures里面的矩形
        if (currectangular == *it)
        {
            allFigures->erase(it);
            break;
        }
    //delete currectangular;
    history->push_back(currectangular);
    currectangular = NULL;
}
//清除所有矩形
void RectangularControl::onClear()
{
    for (Rectangular* rectangular : Allrectangular)
    {
        for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end();) //删掉allFigrues里面保存的矩形
        {
            if (rectangular == *it)
                it = allFigures->erase(it);
            else
                it++;
        }
        delete rectangular;
    }
    Allrectangular.clear();
    currectangular = NULL;
}
void RectangularControl::onUndo()
{
}
void RectangularControl::onFill()
{
    if (currectangular != NULL)
        currectangular->fillColor();
}