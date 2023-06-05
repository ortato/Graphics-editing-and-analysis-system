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
RectangularControl::RectangularControl(int width, int height) : FigureControl(width, height) // ����๹�캯�����б�
{
    currectangular = NULL;   // width �� height�Ǿ��ο�ͳ�
}
bool RectangularControl::setFocus(Figure* fg)  // ��̬���������ⷵ��ͼ���Ƿ��ڸ���������
{
    for (Rectangular* rectangular : Allrectangular)
        if (rectangular == fg)                    // �����
        {
            currectangular = rectangular;      //��ѡ���ǡ���Ա�����޸�Ϊ ��ͼ��
            return true;
        }
    return false;
}
//��������Ĳ���
void RectangularControl::onMousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) //������
    {
        if (currectangular != NULL)  //�����ǰ���δ���
        {
            bool flag = false;
            Point curPoint(event->x(), height - event->y());  //����һ������󣬼�¼��ǰ����
            for (Point p : currectangular->getMarkPoints())
                if (curPoint.distanceTo(currectangular->getCenter()) <= 5) //����������ĵ�
                {
                    setEP = CENTERPOINT;
                    flag = true;
                }
                else if (curPoint.distanceTo(currectangular->getHandlePoint()) <= 5) //���handle
                {
                    setEP = HANDLEPOINT;
                    flag = true;
                }
                else if (currectangular->isOn(curPoint)) //������ܳ���
                {
                    flag = true;
                }
            if (flag)
            {
                pushForward(currectangular);
                return;
            }
        }
        //���֮ǰ��û�����������
        currectangular = new Rectangular(Point(event->x(), height - event->y()), Point(event->x(), height - event->y()));
        Allrectangular.push_back(currectangular);
        allFigures->push_back(currectangular);
        setEP = ENDPOINT;//��ʱֻ����һ���㣬ģʽ����Ϊendpointģʽ���ȴ�mousemove����ڶ�����
    }
}
//����϶�
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
//�������о���
void RectangularControl::onDraw()
{
    for (Rectangular* rectangular : Allrectangular)
        rectangular->draw();
}
//��ǵ�ǰ����
void RectangularControl::onMarkDraw()
{
    if (currectangular != NULL)
        currectangular->markDraw();
}
//�Ե�ǰ���ν�������
void RectangularControl::onScale(double r)
{
    if (currectangular != NULL)
        currectangular->scale(r);
}
//ɾ����ǰ����
void RectangularControl::onDelete()
{
    if (currectangular == NULL) //û��ָ����Σ��򲻲���
        return;
    for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end(); it++) //ɾ��������allFigures����ľ���
        if (currectangular == *it)
        {
            allFigures->erase(it);
            break;
        }
    //delete currectangular;
    history->push_back(currectangular);
    currectangular = NULL;
}
//������о���
void RectangularControl::onClear()
{
    for (Rectangular* rectangular : Allrectangular)
    {
        for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end();) //ɾ��allFigrues���汣��ľ���
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