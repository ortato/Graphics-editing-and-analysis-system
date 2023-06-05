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
    // glLineWidth(2.0);  //设置线宽度
    glBegin(GL_LINES);   //这里是底层的绘图操作，是整个绘图的基础
   // glPointSize(2000);
    Point* first_p, * second_p;
    first_p = points[0];
    for (auto it : points)  //points为Point类型的指针
    {
        second_p = it;
        glVertex2d(first_p->getX(), first_p->getY());  //把前后两个点用直线连接起来
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
    for (Point* p : points)        //平移曲线上的所有点
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
    //在曲线上
    if (isOnPlain(p))
        return true;
    return false;
}
bool Pen::isOnPlain(const Point& p)
{
    return SimpleFigure::isOn(p);
}
