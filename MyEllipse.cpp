#include "MyEllipse.h"
#include <cassert>
#include <cmath>
MyEllipse::MyEllipse()
{
    this->a = this->b = -1;
}
MyEllipse::MyEllipse(const Point& begin, const Point& end) //���������յ�������һ����Բ
{
    this->begin_p = begin;
    this->end_p = end;
    a = abs(end_p.getX() - begin_p.getX()) / 2;
    b = abs(end_p.getY() - end_p.getY()) / 2;
    center_p.setPoint((begin_p.getX() + end_p.getX()) / 2, (begin.getY() + end.getY()) / 2);
    calculatePoints(); //����bressenham method��������Բ�ܳ��ϵĵ�
    calculateHandle(); //����ת���������handle����Ϊ��Բ�Ĳ����ı��ˣ�handleҲҪ��֮�ı�
}
MyEllipse::MyEllipse(const Point& center, int rx, int ry)
{
    this->center_p = center;
    this->a = rx;
    this->b = ry;
    calculatePoints(); //��������Բ
    calculateHandle(); //����handle
}
MyEllipse::~MyEllipse()
{
    for (Point* p : fillPoints)
        delete p;
    for (Point* p : points)
        delete p;
}
//����Բ���еı�ǵ���ʾ������������Ӿ���4�����㡢���ĵ��handle
void MyEllipse::markDraw()
{
    markPoints.erase(markPoints.begin(), markPoints.end());
    markPoints.push_back(Point(center_p.getX() - a, center_p.getY() - b)); //�����ĸ���ǵ�
    markPoints.push_back(Point(center_p.getX() - a, center_p.getY() + b));
    markPoints.push_back(Point(center_p.getX() + a, center_p.getY() + b));
    markPoints.push_back(Point(center_p.getX() + a, center_p.getY() - b));
    Area::drawRect(markPoints[0], markPoints[1], markPoints[2], markPoints[3]); //�õ���Բ����Ӿ��ε��ĸ�����
    for (Point p : markPoints) //����Ӿ����ĸ����ǻ�����
        p.markDraw();
    center_p.centerMarkDraw(); //������ĵ�
    handle_p.handleDraw(center_p); //�����ĵ��handle_p����
}
Point MyEllipse::getCenter() const
{
    return center_p;
}
vector<Point> MyEllipse::getMarkPoints() const
{
    return markPoints;
}
Point MyEllipse::getHandlePoint() const
{
    return handle_p;
}
//���¶�һ��end_p��Ȼ��һ���µ���Բ
void MyEllipse::setEndPoint(const Point& end)
{
    clear();
    end_p = end;
    a = abs(end_p.getX() - begin_p.getX()) / 2;
    b = abs(end_p.getY() - begin_p.getY()) / 2;
    center_p.setPoint((begin_p.getX() + end_p.getX()) / 2, (begin_p.getY() + end_p.getY()) / 2);
    calculatePoints(); //���µ�Բ��
    calculateHandle(); //����handle_p
}
//�����趨������Ͷ̰��ᣬ��Բ�����Ĳ���
void MyEllipse::setTwoAxes(int ra, int rb)
{
    bool isFilled = !fillPoints.empty();
    clear();
    this->begin_p.setPoint(center_p.getX() - ra, center_p.getY() - rb); //beginΪ����Ӿ������½�
    this->end_p.setPoint(center_p.getX() + ra, center_p.getY() + rb); //endΪ����Ӿ������Ͻ�
    this->a = ra;
    this->b = rb;
    calculatePoints(); //���µ�Բ��
    calculateHandle();
    if (isFilled)
        fillColor();
}
//������handle����Բ������ת
void MyEllipse::setHandlePointByRef(const Point& ref)
{
    if (ref.getX() == center_p.getX() || ref.getY() == center_p.getY()) //��(center,ref)ˮƽ��ֱ������ת90��
        setTwoAxes(b, a);
}
//��������һ��ʸ�� (0,0)->move_p ƽ��
void MyEllipse::translate(const Point& move_p)
{
    center_p.translate(move_p);
    begin_p.translate(move_p);
    end_p.translate(move_p);
    for (Point* p : points)
        p->translate(move_p);
    for (Point* p : fillPoints)
        p->translate(move_p);
    calculateHandle();
}
//ֻ�ǽ��д�ֱ��ת
void MyEllipse::rotate(double angle)
{
    int temp = abs((int)angle) % 180;
    if (temp >= 0 && temp < 90) //abs(angle%180)��[0,90)���䣬�򲻱�
        return;
    else //abs(angle%180)��[90,180)���䣬��ת90��
        setTwoAxes(b, a);
}
//��r�ı����Ŵ����С
void MyEllipse::scale(double r)
{
    setTwoAxes(a * r, b * r);
}
//�ж��Ƿ���ͼ��ƽ���ϻ�������Բ���ġ�handle_p
bool MyEllipse::isOn(const Point& p)
{
    if (p.distanceTo(center_p) <= 5 || p.distanceTo(handle_p) <= 5 || isOnPlain(p))
        return true;
    for (Point mp : markPoints)
        if (mp.distanceTo(p) <= 5)
            return true;
    return false;
}
//�ж��Ƿ���ͼ��ƽ����
bool MyEllipse::isOnPlain(const Point& p)
{
    if (SimpleFigure::isOn(p)) //�ж��Ƿ�����Բ�ܳ���
        return true;
    if (!fillPoints.empty()) //�ж��Ƿ�����Բ�ڲ�
    {
        for (Point* pt : fillPoints)
            if (*pt == p)
                return true;
    }
    return false;
}
//���صڼ���ͼ��
int MyEllipse::isFigure()
{
    return 2;
}
//������Բ��Բ���ϵĵ㣬�����㷨
//bresenham method�������㷨
void MyEllipse::calculatePoints()
{
    if (a < 0 || b < 0)
        return;  //is not a legal ellipse
    long sqa = a * a;
    long sqb = b * b;
    //for the 1st area and k>-1
    int x = 0, y = b; //initial point is (0,b)
    long D = 2 * sqb - 2 * b * sqa + sqa; //��ʼ�жϱ��ʽ
    while (sqb * x < sqa * y)
    {
        if (D < 0)
        {
            D += 2 * sqb * (2 * x + 3);
        }
        else
        {
            D += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
            y--;
        }
        x++; //x position of next pixel
        //draw the known points in four quadrants
        //can be written a base function
        points.push_back(new Point(center_p.getX() + x, center_p.getY() + y)); //store all the points of the perimeter
        points.push_back(new Point(center_p.getX() + x, center_p.getY() - y));
        points.push_back(new Point(center_p.getX() - x, center_p.getY() - y));
        points.push_back(new Point(center_p.getX() - x, center_p.getY() + y));
    }
    //for the 2nd area and k<-1
    D = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while (y >= 0)
    {
        points.push_back(new Point(center_p.getX() + x, center_p.getY() + y)); //store all the points of the perimeter
        points.push_back(new Point(center_p.getX() + x, center_p.getY() - y));
        points.push_back(new Point(center_p.getX() - x, center_p.getY() - y));
        points.push_back(new Point(center_p.getX() - x, center_p.getY() + y));
        y--; //y position of next pixel
        if (D < 0)
        {
            x++;
            D += 2 * sqb * x + 2 * sqb - sqa - 2 * sqa * y;
        }
        else
            D = D - 2 * sqa * y - sqa;
    }
}
//ȷ��handle_p��λ�ã��루a,b)���������й�
const int MyEllipse::h = 30; //��ʼ��handle����
void MyEllipse::calculateHandle()
{
    if (a <= 0 || b <= 0)
    {
        handle_p.setPoint(center_p.getX(), center_p.getY() + h);
        return;
    }
    double temp = sqrt(a * a + b * b);
    handle_p.setPoint(center_p.getX() + int(h * a / temp + 0.5), center_p.getY() + int(h * b / temp + 0.5)); //����a,bȷ��handle_p��λ��
}
//���������㣬��������
void MyEllipse::calculateFillPoints()
{
    for (Point* p : points)
    {
        int x = p->getX();
        int y = p->getY();
        int distance = 2 * (center_p.getX() - x);
        int i = x;
        if (x < center_p.getX())
        {
            while (i < x + distance)
            {
                fillPoints.push_back(new Point(i++, y));
            }
        }
    }
}
//�����ɫ
void MyEllipse::fillColor()
{
    if (!fillPoints.empty())
        return;
    calculateFillPoints();
}
//��ͼ�α�������ʾ�����ɫ
void MyEllipse::draw()
{
    SimpleFigure::draw(); //����
    Area::fillColor(); //���
}
//���ͼ�κ������ɫ
void MyEllipse::clear()
{
    SimpleFigure::clear(); //����
    Area::clearColor();
}
