#include "Circle.h"
#include <GL/glut.h>
#include <algorithm>
Circle::Circle()
{
}
Circle::Circle(Point center, int radius)
{
    this->center = center;
    this->radius = radius;
    calculatePoints(); //����������
    calculateHandle(); //����handle��
}
Circle::~Circle()
{
    for (Point* p : fillPoints)
        delete p;
    for (Point* p : points)
        delete p;
}
Point Circle::getCenter() const
{
    return center;
}
//���ر�ǵ�
vector<Point> Circle::getMarkPoints() const
{
    return markPoints;
}
//���ذ��ֵ�
Point Circle::getHandlePoint() const
{
    return handle;
}
//set radius �����¼����������handle��
void Circle::setRadius(int radius)
{
    bool isFilled = !fillPoints.empty();
    clear();
    this->radius = radius;
    calculatePoints();
    calculateHandle();
    if (isFilled)
        fillColor();
}
const int Circle::h = 30; //��ʼ��handle��Գ���
void Circle::setHandlePointByRef(const Point& ref)
{
    if (center == ref)
        return;
    //����base->ref
    double c = ref.getX() - center.getX();
    double d = ref.getY() - center.getY();
    double rRef = center.distanceTo(ref); //center-ref�����ĳ���
    int x = int(center.getX() + h * c / rRef + 0.5);
    int y = int(center.getY() + h * d / rRef + 0.5);
    handle.setPoint(x, y);
}
//ƽ�ƣ�ͨ��ƽ�������㣬�����»�Բ
void Circle::translate(const Point& offset)
{
    center.translate(offset);
    for (Point* p : points)
        p->translate(offset);
    for (Point* p : fillPoints)
        p->translate(offset);
    calculateHandle();
}
//Բ����ת����Ҫ
void Circle::rotate(double angle)
{
}
void Circle::scale(double s)
{
    setRadius(int(radius * s + 0.5));
    calculateHandle();
}
//�ж��Ƿ���Բ��
bool Circle::isOn(const Point& p) //��Բ�ϣ���ǵ㣬handle���϶���
{
    if (isOnPlain(p) || p.distanceTo(center) <= 5 || p.distanceTo(handle) <= 5) //Բ�ڣ�Բ�ģ�handle��
        return true;
    for (Point mp : markPoints) //markpoint
        if (mp.distanceTo(p) <= 5)
            return true;
    return false;
}
//�ж��Ƿ���Բ����
bool Circle::isOnPlain(const Point& p)
{
    if (SimpleFigure::isOn(p)) //��������
        return true;
    return false;
}
void Circle::draw()
{
    SimpleFigure::draw(); //������
    Area::fillColor(); //����ڲ�
}
void Circle::clear()
{
    SimpleFigure::clear(); //���������
    Area::clearColor();
}
int Circle::isFigure()
{
    return 1;
}
//������ǵ㣬�������ĵ㡢���ֵ����������ζ���
void Circle::markDraw()
{
    markPoints.erase(markPoints.begin(), markPoints.end());
    markPoints.push_back(Point(center.getX() - radius, center.getY() - radius));
    markPoints.push_back(Point(center.getX() - radius, center.getY() + radius));
    markPoints.push_back(Point(center.getX() + radius, center.getY() + radius));
    markPoints.push_back(Point(center.getX() + radius, center.getY() - radius));
    drawRect(markPoints[0], markPoints[1], markPoints[2], markPoints[3]);
    for (Point p : markPoints)
        p.markDraw();
    center.centerMarkDraw();
    handle.handleDraw(center);
}
void Circle::drawRect(const Point& a, const Point& b, const Point& c, const Point& d)
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
void Circle::fillColor()
{
    if (radius <= 0 || !fillPoints.empty())
        return;
    calculateFillPoints();
}
//�����Բ���ϵĵ㣬�����
void Circle::calculatePoints() //����������
{
    int x, y, d, r;
    x = 0;
    r = this->radius;
    if (r <= 0)
        return;
    y = r;
    d = 3 - 2 * r;
    //�˷�֮һ
    points.push_back(new Point(center.getX(), center.getY() + radius)); //����
    points.push_back(new Point(center.getX() + radius, center.getY())); //����
    points.push_back(new Point(center.getX(), center.getY() - radius)); //����
    points.push_back(new Point(center.getX() - radius, center.getY())); //����
    while (x < y)
    {
        if (d < 0) //ȡP1��dΪ��һ������б�ʽ
        {
            d = d + 4 * x + 6;
        }
        else //ȡP2��dΪ��һ������б�ʽ
        {
            d = d + 4 * (x - y) + 10;
            y--; //ѡP2��--
        }
        x++; //ÿ��ѡ����һ���㶼Ҫx++
        points.push_back(new Point(center.getX() + x, center.getY() + y));
        points.push_back(new Point(center.getX() + y, center.getY() + x));
        points.push_back(new Point(center.getX() + y, center.getY() - x));
        points.push_back(new Point(center.getX() + x, center.getY() - y));
        points.push_back(new Point(center.getX() - x, center.getY() - y));
        points.push_back(new Point(center.getX() - y, center.getY() - x));
        points.push_back(new Point(center.getX() - y, center.getY() + x));
        points.push_back(new Point(center.getX() - x, center.getY() + y));
    }
}
void Circle::calculateFillPoints() //��������
{
    for (Point* p : points) //����������
    {
        int x = p->getX();
        int y = p->getY();
        while (x < this->center.getX()) //������������һ�����ϵ�Բ�ڵĵ�
        {
            fillPoints.push_back(new Point(x++, y));
            fillPoints.push_back(new Point(2 * center.getX() - x, y));
        }
    }
}
void Circle::calculateHandle()
{
    handle.setHandlePoint(center - Point(radius, 0), center + Point(radius, 0), h);
}