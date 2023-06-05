#include "rectangular.h"
#include <cassert>
#include <cmath>
Rectangular::Rectangular()
{
    this->length = this->width = -1;  //无参构造函数不生成矩形
}
Rectangular::Rectangular(const Point& begin, const Point& end) //根据起点和终点来创建一个椭圆
{
    this->begin = begin;
    this->end = end;
    length = abs(end.getX() - begin.getX()) / 2;
    width = abs(end.getY() - end.getY()) / 2;
    center.setPoint((begin.getX() + end.getX()) / 2, (begin.getY() + end.getY()) / 2);
    //    calculatePoints(); //计算矩形周上的点
    calculateHandle(); //非旋转操作后更新handle，因为矩形的参数改变了，handle也要随之改变
}
//把矩形的顶点，中心点和handle点显示出来
void Rectangular::markDraw()
{
    markPoints.erase(markPoints.begin(), markPoints.end()); //清除上一次的点
    markPoints.push_back(Point(center.getX() - 0.5 * length, center.getY() - 0.5 * width));
    markPoints.push_back(Point(center.getX() - 0.5 * length, center.getY() + 0.5 * width));
    markPoints.push_back(Point(center.getX() + 0.5 * length, center.getY() + 0.5 * width));
    markPoints.push_back(Point(center.getX() + 0.5 * length, center.getY() - 0.5 * width));
    for (Point p : markPoints) //把外接矩形四个点标记画出来
        p.markDraw();
    center.centerMarkDraw(); //标记中心点
    handle.handleDraw(center); //将中心点和handle_p连线
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
//整体沿着一个矢量 (0,0)->move_p 平移
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
    this->end = end; //矩形的第二个点赋值完毕
    length = abs(end.getX() - begin.getX());
    width = abs(end.getY() - begin.getY());
    center.setPoint((begin.getX() + end.getX()) / 2, (begin.getY() + end.getY()) / 2);
    calculatePoints();
    calculateHandle();
    if (isFilled)
        fillColor();
}
//以r的比例放大或缩小
//void Rectangular::scale(double r)
//{
 //     setTwoAxes(a*r, b*r);
//}
//判断是否在图形平面上或者在椭圆中心、handle_p
bool Rectangular::isOn(const Point& p)
{
    if (p.distanceTo(center) <= 5 || p.distanceTo(handle) <= 5 || isOnPlain(p))
        return true;
    for (Point mp : markPoints)
        if (mp.distanceTo(p) <= 5)
            return true;
    return false;
}
//判断是否在图形平面上
bool Rectangular::isOnPlain(const Point& p)
{
    if (SimpleFigure::isOn(p)) //判断是否在椭圆周长上
        return true;
    return false;
}
//确定handle_p的位置，与（a,b)向量方向有关
const int Rectangular::h = 30; //初始化handle长度
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
void Rectangular::calculatePoints()    //计算各点位置并存放到成员对象points里面
{
    if (width < 0 || length < 0)
        return;                 //is not a legal rectangluar
    //由于起始点和终止点相对位置不同，所以需要找到合适的参考点
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
    //正式计算矩形边上的点
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
//计算填充点
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
//清除矩形
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
    SimpleFigure::draw(); //轮廓
    Area::fillColor(); //填充
}
void Rectangular::rotate(double angle)
{
}
void Rectangular::scale(double s)
{
}