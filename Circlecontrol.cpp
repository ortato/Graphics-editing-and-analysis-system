#include "CircleControl.h"
#include <cmath>
#include <iostream>
using namespace std;
CircleControl::CircleControl()
{
    curCircle = NULL;
}
CircleControl::CircleControl(std::vector<Figure*>* figures, std::vector<Figure*>* history)
    :FigureControl(figures, history)
{
    curCircle = NULL;
}
CircleControl::CircleControl(int width, int height) : FigureControl(width, height)
{
    curCircle = NULL;
}
CircleControl::~CircleControl()
{
}
bool CircleControl::setFocus(Figure* fg) //设置当前圆
{
    for (Circle* circle : circles)
        if (circle == fg)
        {
            curCircle = circle;
            return true;
        }
    return false;
}
void CircleControl::onUndo()
{
    /*
    if( !history.empty() )
    {
        Figure* topFigure = history.top();
        if(topFigure->isFigure() == 1)
        {
            allFigures->push_back(history.top());
            //circles.push_back(historyCircles.top());
            historyCircles.pop();
            history.pop();
            return 1;
        }
    }
    return 0;*/
}
void CircleControl::onMousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        //接下来有4个情况
        //-1.控制圆的 markpoints
        //-2.控制圆的 center
        //-3.控制圆的 handle point
        //-4.以当前点创建新圆的圆心
        if (curCircle != NULL)
        {
            Point currentPoint(event->x(), height - event->y()); //y轴由向下转为向上
            for (Point p : curCircle->getMarkPoints()) //在markpoint附近
                if (p.distanceTo(currentPoint) <= 5)
                {
                    setCV = -1;
                    pushForward(curCircle);
                    return;
                }
            if (currentPoint.distanceTo(curCircle->getCenter()) <= 5) //在圆心附近
            {
                setCV = -2;
                pushForward(curCircle);
                return;
            }
            else if (currentPoint.distanceTo(curCircle->getHandlePoint()) <= 5) //在handle附件
            {
                setCV = -3;
                pushForward(curCircle);
                return;
            }
            else if (curCircle->isOn(currentPoint)) //在圆上
            {
                pushForward(curCircle);
                return;
            }
        }
        setCV = -4;
        // 如果没有圆，创建半径为1的圆并设为当前圆
        curCircle = new Circle(Point(event->x(), height - event->y()), 1);
        circles.push_back(curCircle);
        allFigures->push_back(curCircle);
    }
}
void CircleControl::onMouseMoveEvent(QMouseEvent* event)
{
    if (curCircle == NULL || !(event->buttons() & Qt::LeftButton)) //检查是否为左键按下状态
        return;
    int x = event->x();
    int glY = height - event->y();
    Point center = curCircle->getCenter();
    switch (setCV)
    {
    case -1: curCircle->setRadius((int)max(abs(x - center.getX()), abs(glY - center.getY()))); break;
    case -2: curCircle->translate(Point(x, glY) - center); break;
    case -3: curCircle->setHandlePointByRef(Point(x, glY)); break;
    case -4: curCircle->setRadius((int)sqrt(
        (x - center.getX()) * (x - center.getX()) + (glY - center.getY()) * (glY - center.getY()))); break;
    default:;
    }
}
void CircleControl::onDraw()
{
    for (Circle* circle : circles)
        circle->draw();
}
void CircleControl::onMarkDraw()
{
    if (curCircle != NULL)
        curCircle->markDraw();
}
void CircleControl::onDelete()
{
    if (curCircle == NULL)
        return;
    for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end(); it++)
    {
        if (curCircle == *it)
        {
            allFigures->erase(it);
            break;
        }
    }
    //delete curCircle;
    history->push_back(curCircle);
    //historyCircles.push(curCircle);
    curCircle = NULL;
}
//清除所有圆
void CircleControl::onClear()
{
    for (Circle* circle : circles)
    {
        for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end();)
        {
            if (circle == *it)
                it = allFigures->erase(it);
            else
                it++;
        }
        delete circle;
    }
    circles.clear();
    curCircle = NULL;
}
void CircleControl::onFill()
{
    if (curCircle != NULL)
        curCircle->fillColor();
}