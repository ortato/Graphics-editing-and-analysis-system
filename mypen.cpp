#include "mypen.h"
#include <GL/glut.h>
#include <QPainter>
#include <cmath>
#include <iostream>
#include <QtOpenGL/QtOpenGL>
Pen::Pen()
{
    lastPoint = NULL;
    penColor = make_tuple(-1.0, -1.0, -1.0);
}
Pen::~Pen()
{
}
void Pen::addPoint(Point* p)
{
    this->points.push_back(p);
}
void Pen::draw()
{
    if (std::get<0>(penColor) < 0)
        penColor = SimpleFigure::defaultColor;
    glPointSize(getPointSize());
    glLineWidth(getPointSize());
    glColor3f(std::get<0>(penColor), std::get<1>(penColor), std::get<2>(penColor));
    // glColor3f(0.0, 0.0, 0.0);
    // glLineWidth(2.0);  //�����߿��
    glBegin(GL_LINES);   //�����ǵײ�Ļ�ͼ��������������ͼ�Ļ���
   // glPointSize(2000);
    Point* first_p, * second_p;
    first_p = points[0];
    for (auto it : points)  //pointsΪPoint���͵�ָ��
    {
        second_p = it;
        glVertex2d(first_p->getX(), first_p->getY());  //��ǰ����������ֱ����������
        glVertex2d(second_p->getX(), second_p->getY());
        //QPainter painter();
         //painter.drawLine(first_p->getX(),first_p->getY(),second_p->getX(),second_p->getY());
         //DrawLine(first_p->getX(),first_p->getY(),second_p->getX(),second_p->getY());
        first_p = second_p;
    }
    glEnd();
    glFlush();
}
void Pen::markDraw()
{
}
void Pen::clear()
{
    SimpleFigure::clear();
}
void Pen::translate(const Point& offset)
{
    for (Point* p : points)        //ƽ�������ϵ����е�
        p->translate(offset);
}
void Pen::rotate(double angle)
{
}
void Pen::scale(double s)
{
}
bool Pen::isOn(const Point& p)
{
    //��������
    if (isOnPlain(p))
        return true;
    return false;
}
bool Pen::isOnPlain(const Point& p)
{
    return SimpleFigure::isOn(p);
}
