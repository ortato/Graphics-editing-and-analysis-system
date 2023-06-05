#include "rectangular.h"
#include <cassert>
#include <cmath>
Rectangular::Rectangular()
{
    this->length = this->width = -1;  //�޲ι��캯�������ɾ���
}
Rectangular::Rectangular(const Point& begin, const Point& end) //���������յ�������һ����Բ
{
    this->begin = begin;
    this->end = end;
    length = abs(end.getX() - begin.getX()) / 2;
    width = abs(end.getY() - end.getY()) / 2;
    center.setPoint((begin.getX() + end.getX()) / 2, (begin.getY() + end.getY()) / 2);
    //    calculatePoints(); //����������ϵĵ�
    calculateHandle(); //����ת���������handle����Ϊ���εĲ����ı��ˣ�handleҲҪ��֮�ı�
}
//�Ѿ��εĶ��㣬���ĵ��handle����ʾ����
void Rectangular::markDraw()
{
    markPoints.erase(markPoints.begin(), markPoints.end()); //�����һ�εĵ�
    markPoints.push_back(Point(center.getX() - 0.5 * length, center.getY() - 0.5 * width));
    markPoints.push_back(Point(center.getX() - 0.5 * length, center.getY() + 0.5 * width));
    markPoints.push_back(Point(center.getX() + 0.5 * length, center.getY() + 0.5 * width));
    markPoints.push_back(Point(center.getX() + 0.5 * length, center.getY() - 0.5 * width));
    for (Point p : markPoints) //����Ӿ����ĸ����ǻ�����
        p.markDraw();
    center.centerMarkDraw(); //������ĵ�
    handle.handleDraw(center); //�����ĵ��handle_p����
}
Point Rectangular::getCenter() const
{
    return center;
}
vector<Point> Rectangular::getMarkPoints() const
{
    return markPoints;
}
Point Rectangular::getHandlePoint() const
{
    return handle;
}
//��������һ��ʸ�� (0,0)->move_p ƽ��
void Rectangular::translate(const Point& move_p)
{
    center.translate(move_p);
    begin.translate(move_p);
    end.translate(move_p);
    for (Point* p : points)
        p->translate(move_p);
    for (Point* p : fillPoints)
        p->translate(move_p);
    calculateHandle();
}
void Rectangular::setEndPoint(const Point& end)
{
    bool isFilled = !fillPoints.empty();
    clear();
    this->end = end; //���εĵڶ����㸳ֵ���
    length = abs(end.getX() - begin.getX());
    width = abs(end.getY() - begin.getY());
    center.setPoint((begin.getX() + end.getX()) / 2, (begin.getY() + end.getY()) / 2);
    calculatePoints();
    calculateHandle();
    if (isFilled)
        fillColor();
}
//��r�ı����Ŵ����С
//void Rectangular::scale(double r)
//{
 //     setTwoAxes(a*r, b*r);
//}
//�ж��Ƿ���ͼ��ƽ���ϻ�������Բ���ġ�handle_p
bool Rectangular::isOn(const Point& p)
{
    if (p.distanceTo(center) <= 5 || p.distanceTo(handle) <= 5 || isOnPlain(p))
        return true;
    for (Point mp : markPoints)
        if (mp.distanceTo(p) <= 5)
            return true;
    return false;
}
//�ж��Ƿ���ͼ��ƽ����
bool Rectangular::isOnPlain(const Point& p)
{
    if (SimpleFigure::isOn(p)) //�ж��Ƿ�����Բ�ܳ���
        return true;
    return false;
}
//ȷ��handle_p��λ�ã��루a,b)���������й�
const int Rectangular::h = 30; //��ʼ��handle����
void Rectangular::calculateHandle()
{
    if (length <= 0 || width <= 0)
    {
        handle.setPoint(center.getX(), center.getY() + h);
        return;
    }
    double temp = sqrt(length * length + width * width);
    handle.setPoint(center.getX() + int(h * length / (2 * temp) + 0.5), center.getY() + int(h * width / (2 * temp) + 0.5));
}
void Rectangular::calculatePoints()    //�������λ�ò���ŵ���Ա����points����
{
    if (width < 0 || length < 0)
        return;                 //is not a legal rectangluar
    //������ʼ�����ֹ�����λ�ò�ͬ��������Ҫ�ҵ����ʵĲο���
    Point begin_p(begin.getX(), begin.getY());
    Point end_p(end.getX(), end.getY());
    if (begin.getX() < end.getX() && begin.getY() < end.getY())
    {
        begin_p.setPoint(begin.getX(), end.getY());
        end_p.setPoint(end.getX(), begin.getY());
    }
    if (begin.getX() > end.getX() && begin.getY() > end.getY())
    {
        begin_p.setPoint(end.getX(), begin.getY());
        end_p.setPoint(begin.getX(), end.getY());
    }
    if (begin.getX() > end.getX() && begin.getY() < end.getY())
    {
        begin_p.setPoint(end.getX(), end.getY());
        end_p.setPoint(begin.getX(), begin.getY());
    }
    //��ʽ������α��ϵĵ�
    long sx = begin_p.getX();
    long sy = begin_p.getY();
    while (sx < begin_p.getX() + length)
    {
        points.push_back(new Point(sx, sy));
        points.push_back(new Point(sx, 2 * center.getY() - sy));
        sx++;
    }
    while (sy > begin_p.getY() - width)
    {
        points.push_back(new Point(sx, sy));
        points.push_back(new Point(2 * center.getX() - sx, sy));
        sy--;
    }
}
//��������
void Rectangular::calculateFillPoints()
{
    for (Point* p : points)
    {
        int x = p->getX();
        int y = p->getY();
        if (x <= this->begin.getX())
        {
            while (x < this->end.getX())
                fillPoints.push_back(new Point(x++, y));
        }
    }
}
//�������
void Rectangular::clear()
{
    SimpleFigure::clear();
    Area::clearColor();
}
void Rectangular::fillColor()
{
    if (!fillPoints.empty())
        return;
    calculateFillPoints();
}
void Rectangular::draw()
{
    SimpleFigure::draw(); //����
    Area::fillColor(); //���
}
void Rectangular::rotate(double angle)
{
}
void Rectangular::scale(double s)
{
}