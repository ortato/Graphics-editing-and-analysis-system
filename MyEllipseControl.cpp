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
//�趨Ϊ��ǰ��Բ
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
//����
void EllipseControl::onUndo()
{
}
//��������Ĳ���
void EllipseControl::onMousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) //������
    {
        if (curEllipse != NULL) //���ǻ�����Բ
        {
            bool flag = false;
            Point curPoint(event->x(), height - event->y());
            for (Point p : curEllipse->getMarkPoints())
                if (p.distanceTo(curPoint) <= 5)  //���������Ӿ��ζ���
                {
                    setEP = MARKPOINT;
                    flag = true;
                }
            if (curPoint.distanceTo(curEllipse->getCenter()) <= 5) //����������ĵ�
            {
                setEP = CENTERPOINT;
                flag = true;
            }
            else if (curPoint.distanceTo(curEllipse->getHandlePoint()) <= 5) //���handle_p
            {
                setEP = HANDLEPOINT;
                flag = true;
            }
            else if (curEllipse->isOn(curPoint)) //������ܳ���
            {
                flag = true;
            }
            if (flag)
            {
                pushForward(curEllipse);
                return;
            }
        }
        //������û�л�����Բ����������һ����Բ����
        curEllipse = new MyEllipse(Point(event->x(), height - event->y()), Point(event->x(), height - event->y()));
        Allellipses.push_back(curEllipse);
        allFigures->push_back(curEllipse);
        setEP = ENDPOINT;
    }
}
//����϶����ı���Բ
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
//����������Բ
void EllipseControl::onDraw()
{
    for (MyEllipse* ellipse : Allellipses)
        ellipse->draw();
}
//��ǵ�ǰ��Բ
void EllipseControl::onMarkDraw()
{
    if (curEllipse != NULL)
        curEllipse->markDraw();
}
//�Ե�ǰ��Բ��������
void EllipseControl::onScale(double r)
{
    if (curEllipse != NULL)
        curEllipse->scale(r);
}
//ɾ����ǰ��Բ
void EllipseControl::onDelete()
{
    if (curEllipse == NULL) //û��ָ����Բ���򲻲���
        return;
    for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end(); it++) //ɾ��������allFigures�������Բ
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
//���������Բ
void EllipseControl::onClear()
{
    for (MyEllipse* ellipse : Allellipses)
    {
        for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end();) //ɾ��allFigrues���汣�����Բ
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
//�����ɫ
void EllipseControl::onFill()
{
    if (curEllipse != NULL)
        curEllipse->fillColor();
}