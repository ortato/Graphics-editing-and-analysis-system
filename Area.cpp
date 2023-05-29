#include "Area.h"
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <algorithm>
tuple<float, float, float> Area::defaultColor(0.0, 1.0, 0.0); //��ʼ�����ɫΪ��ɫ
Area::Area()
{
    color = make_tuple(-1.0, -1.0, -1.0);
}
void Area::setColor(tuple<float, float, float> newColor)
{
    defaultColor = newColor;
}
void Area::fillColor()
{
    if (fillPoints.empty())
        return;
    if (std::get<0>(color) < 0)
        color = defaultColor;
    glPointSize(1.0);
    glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));
    //	glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (auto it : fillPoints)
        it->draw();
    glEnd();
    glFlush();
}
void Area::clearColor()
{
    for (Point* p : fillPoints)
        delete p;
    fillPoints.erase(fillPoints.begin(), fillPoints.end());
}
void Area::drawRect(const Point& a, const Point& b, const Point& c, const Point& d)
{
    glLineWidth(1.0f); //���Ϊ1
    glEnable(GL_LINE_STIPPLE); //�������߻��ƹ���
    glLineStipple(1, 0x0f0f); //����
    glColor3f(0.0, 0.0, 1.0); //��ɫ
    glBegin(GL_LINE_LOOP);
    glVertex2i(a.getX(), a.getY());
    glVertex2i(b.getX(), b.getY());
    glVertex2i(c.getX(), c.getY());
    glVertex2i(d.getX(), d.getY());
    glEnd();
    glFlush();
    glDisable(GL_LINE_STIPPLE); //�ر����߻��ƹ���
}
