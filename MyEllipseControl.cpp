#include "MyEllipseControl.h"
#include <GL/glut.h>
EllipseControl::EllipseControl()
{
    curEllipse = NULL;
}
EllipseControl::EllipseControl(std::vector<Figure*>* figures, std::vector<Figure*>* history)
    :FigureControl(figures, history)
{
    curEllipse = NULL;
}
EllipseControl::EllipseControl(int width, int height) : FigureControl(width, height)
{
    curEllipse = NULL;
}
EllipseControl::~EllipseControl()
{
    for (MyEllipse* ellipse : Allellipses)
        delete ellipse;
}
//设定为当前椭圆
bool EllipseControl::setFocus(Figure* fg)
{
    for (MyEllipse* ellipse : Allellipses)
        if (ellipse == fg)
        {
            curEllipse = ellipse;
            return true;
        }
    return false;
}
//撤销
void EllipseControl::onUndo()
{
}
//单击左键的操作
void EllipseControl::onMousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) //点击左键
    {
        if (curEllipse != NULL) //若是画过椭圆
        {
            bool flag = false;
            Point curPoint(event->x(), height - event->y());
            for (Point p : curEllipse->getMarkPoints())
                if (p.distanceTo(curPoint) <= 5)  //点击的是外接矩形顶点
                {
                    setEP = MARKPOINT;
                    flag = true;
                }
            if (curPoint.distanceTo(curEllipse->getCenter()) <= 5) //点击的是中心点
            {
                setEP = CENTERPOINT;
                flag = true;
            }
            else if (curPoint.distanceTo(curEllipse->getHandlePoint()) <= 5) //点击handle_p
            {
                setEP = HANDLEPOINT;
                flag = true;
            }
            else if (curEllipse->isOn(curPoint)) //点击在周长上
            {
                flag = true;
            }
            if (flag)
            {
                pushForward(curEllipse);
                return;
            }
        }
        //若重来没有画过椭圆，则新生成一个椭圆对象
        curEllipse = new MyEllipse(Point(event->x(), height - event->y()), Point(event->x(), height - event->y()));
        Allellipses.push_back(curEllipse);
        allFigures->push_back(curEllipse);
        setEP = ENDPOINT;
    }
}
//鼠标拖动，改变椭圆
void EllipseControl::onMouseMoveEvent(QMouseEvent* event)
{
    if (curEllipse == NULL)
        return;
    Point cur_center_p = curEllipse->getCenter();
    switch (setEP)
    {
    case ENDPOINT: curEllipse->setEndPoint(Point(event->x(), height - event->y())); break;
    case MARKPOINT: curEllipse->setTwoAxes(abs(event->x() - cur_center_p.getX()), abs((height - event->y()) - cur_center_p.getY())); break;
    case CENTERPOINT: curEllipse->translate(Point(event->x(), height - event->y()) - cur_center_p); break;
    case HANDLEPOINT: curEllipse->setHandlePointByRef(Point(event->x(), height - event->y())); break;
    default:;
    }
}
//画出所有椭圆
void EllipseControl::onDraw()
{
    for (MyEllipse* ellipse : Allellipses)
        ellipse->draw();
}
//标记当前椭圆
void EllipseControl::onMarkDraw()
{
    if (curEllipse != NULL)
        curEllipse->markDraw();
}
//对当前椭圆进行缩放
void EllipseControl::onScale(double r)
{
    if (curEllipse != NULL)
        curEllipse->scale(r);
}
//删掉当前椭圆
void EllipseControl::onDelete()
{
    if (curEllipse == NULL) //没有指向椭圆，则不操作
        return;
    for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end(); it++) //删掉保存在allFigures里面的椭圆
        if (curEllipse == *it)
        {
            allFigures->erase(it);
            break;
        }
    //delete curEllipse;
    history->push_back(curEllipse);
    //historyEllipse.push(curEllipse);
    curEllipse = NULL;
}
//清除所有椭圆
void EllipseControl::onClear()
{
    for (MyEllipse* ellipse : Allellipses)
    {
        for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end();) //删掉allFigrues里面保存的椭圆
        {
            if (ellipse == *it)
                it = allFigures->erase(it);
            else
                it++;
        }
        delete ellipse;
    }
    Allellipses.clear();
    curEllipse = NULL;
}
//填充颜色
void EllipseControl::onFill()
{
    if (curEllipse != NULL)
        curEllipse->fillColor();
}