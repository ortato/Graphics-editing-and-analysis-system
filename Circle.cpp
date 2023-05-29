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
    calculatePoints(); //计算轮廓点
    calculateHandle(); //计算handle点
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
//返回标记点
vector<Point> Circle::getMarkPoints() const
{
    return markPoints;
}
//返回把手点
Point Circle::getHandlePoint() const
{
    return handle;
}
//set radius 后重新计算轮廓点和handle点
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
const int Circle::h = 30; //初始化handle相对长度
void Circle::setHandlePointByRef(const Point& ref)
{
    if (center == ref)
        return;
    //向量base->ref
    double c = ref.getX() - center.getX();
    double d = ref.getY() - center.getY();
    double rRef = center.distanceTo(ref); //center-ref向量的长度
    int x = int(center.getX() + h * c / rRef + 0.5);
    int y = int(center.getY() + h * d / rRef + 0.5);
    handle.setPoint(x, y);
}
//平移，通过平移特征点，再重新画圆
void Circle::translate(const Point& offset)
{
    center.translate(offset);
    for (Point* p : points)
        p->translate(offset);
    for (Point* p : fillPoints)
        p->translate(offset);
    calculateHandle();
}
//圆的旋转不需要
void Circle::rotate(double angle)
{
}
void Circle::scale(double s)
{
    setRadius(int(radius * s + 0.5));
    calculateHandle();
}
//判断是否在圆上
bool Circle::isOn(const Point& p) //在圆上，标记点，handle点上都可
{
    if (isOnPlain(p) || p.distanceTo(center) <= 5 || p.distanceTo(handle) <= 5) //圆内，圆心，handle点
        return true;
    for (Point mp : markPoints) //markpoint
        if (mp.distanceTo(p) <= 5)
            return true;
    return false;
}
//判断是否在圆周上
bool Circle::isOnPlain(const Point& p)
{
    if (SimpleFigure::isOn(p)) //在轮廓上
        return true;
    return false;
}
void Circle::draw()
{
    SimpleFigure::draw(); //画轮廓
    Area::fillColor(); //填充内部
}
void Circle::clear()
{
    SimpleFigure::clear(); //清除轮廓点
    Area::clearColor();
}
int Circle::isFigure()
{
    return 1;
}
//画出标记点，就是中心点、把手点和外接正方形顶点
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
    glLineWidth(1.0f); //宽度为1
    glEnable(GL_LINE_STIPPLE); //开启虚线绘制功能
    glLineStipple(1, 0x0f0f); //虚线
    glColor3f(0.0, 0.0, 1.0); //蓝色
    glBegin(GL_LINE_LOOP);
    glVertex2i(a.getX(), a.getY());
    glVertex2i(b.getX(), b.getY());
    glVertex2i(c.getX(), c.getY());
    glVertex2i(d.getX(), d.getY());
    glEnd();
    glFlush();
    glDisable(GL_LINE_STIPPLE); //关闭虚线绘制功能
}
void Circle::fillColor()
{
    if (radius <= 0 || !fillPoints.empty())
        return;
    calculateFillPoints();
}
//计算出圆周上的点，并存放
void Circle::calculatePoints() //生成轮廓点
{
    int x, y, d, r;
    x = 0;
    r = this->radius;
    if (r <= 0)
        return;
    y = r;
    d = 3 - 2 * r;
    //八分之一
    points.push_back(new Point(center.getX(), center.getY() + radius)); //最上
    points.push_back(new Point(center.getX() + radius, center.getY())); //最右
    points.push_back(new Point(center.getX(), center.getY() - radius)); //最下
    points.push_back(new Point(center.getX() - radius, center.getY())); //最左
    while (x < y)
    {
        if (d < 0) //取P1，d为下一个点的判别式
        {
            d = d + 4 * x + 6;
        }
        else //取P2，d为下一个点的判别式
        {
            d = d + 4 * (x - y) + 10;
            y--; //选P2后--
        }
        x++; //每次选了下一个点都要x++
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
void Circle::calculateFillPoints() //生成填充点
{
    for (Point* p : points) //遍历轮廓点
    {
        int x = p->getX();
        int y = p->getY();
        while (x < this->center.getX()) //生成与轮廓点一条线上的圆内的点
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