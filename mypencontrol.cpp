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
//���ʹ켣����ѡ��
bool myPenControl::setFocus(Figure* fg)
{
    return false;
}
//��ʼ������
void myPenControl::onMousePressEvent(QMouseEvent* event)
{
    //����������
    if (curPen == NULL)  //���ǻ�û�л��� ����
    {
        Pen* p = new Pen();
        //  p = new Pen;
        curPen = p;  //ÿ�ε��������¿�ʼ��һ����
        curPen->addPoint(new Point(event->x(), height - event->y()));
    }
}
void myPenControl::onMouseMoveEvent(QMouseEvent* event)
{
    // ���������µ�ͬʱ�ƶ����
    if (event->buttons() & Qt::LeftButton)
    {
        curPen->addPoint(new Point(event->x(), height - event->y())); //�������λ��
    }
}
void myPenControl::onMousePassiveMoveEvent(QMouseEvent* event)
{
    //�������ͷ�
    if (curPen != NULL)
    {
        allFigures->push_back(curPen);  //����ͷź�����һ�������Ķ���
        Allpens.push_back(curPen);
        curPen = NULL;
    }
}
//����ͼ�α���
void myPenControl::onDraw()
{
    for (Pen* mypen : Allpens)
        mypen->draw();
}
//ʵʱ���º���ʾ��ǰ������
void myPenControl::onMarkDraw()
{
    if (curPen == NULL)
        return;
    else
        curPen->draw();
}
//���
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
