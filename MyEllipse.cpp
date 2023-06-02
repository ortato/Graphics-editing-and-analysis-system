#include "MyEllipse.h"
#include <cassert>
#include <cmath>
MyEllipse::MyEllipse()
{
    this->a = this->b = -1;
}
MyEllipse::MyEllipse(const Point& begin, const Point& end) //根据起点和终点来创建一个椭圆
{
    this->begin_p = begin;
    this->end_p = end;
    a = abs(end_p.getX() - begin_p.getX()) / 2;
    b = abs(end_p.getY() - end_p.getY()) / 2;
    center_p.setPoint((begin_p.getX() + end_p.getX()) / 2, (begin.getY() + end.getY()) / 2);
    calculatePoints(); //采用bressenham method来计算椭圆周长上的点
    calculateHandle(); //非旋转操作后更新handle，因为椭圆的参数改变了，handle也要随之改变
}
MyEllipse::MyEllipse(const Point& center, int rx, int ry)
{
    this->center_p = center;
    this->a = rx;
    this->b = ry;
    calculatePoints(); //生成新椭圆
    calculateHandle(); //更新handle
}
MyEllipse::~MyEllipse()
{
    for (Point* p : fillPoints)
        delete p;
    for (Point* p : points)
        delete p;
}
//把椭圆所有的标记点显示出来，包括外接矩形4个顶点、中心点和handle
void MyEllipse::markDraw()
{
    markPoints.erase(markPoints.begin(), markPoints.end());
    markPoints.push_back(Point(center_p.getX() - a, center_p.getY() - b)); //存入四个标记点
    markPoints.push_back(Point(center_p.getX() - a, center_p.getY() + b));
    markPoints.push_back(Point(center_p.getX() + a, center_p.getY() + b));
    markPoints.push_back(Point(center_p.getX() + a, center_p.getY() - b));
    Area::drawRect(markPoints[0], markPoints[1], markPoints[2], markPoints[3]); //得到椭圆的外接矩形的四个顶点
    for (Point p : markPoints) //把外接矩形四个点标记画出来
        p.markDraw();
    center_p.centerMarkDraw(); //标记中心点
    handle_p.handleDraw(center_p); //将中心点和handle_p连线
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
//重新定一个end_p，然后画一个新的椭圆
void MyEllipse::setEndPoint(const Point& end)
{
    clear();
    end_p = end;
    a = abs(end_p.getX() - begin_p.getX()) / 2;
    b = abs(end_p.getY() - begin_p.getY()) / 2;
    center_p.setPoint((begin_p.getX() + end_p.getX()) / 2, (begin_p.getY() + end_p.getY()) / 2);
    calculatePoints(); //画新的圆周
    calculateHandle(); //计算handle_p
}
//重新设定长半轴和短半轴，椭圆的中心不变
void MyEllipse::setTwoAxes(int ra, int rb)
{
    bool isFilled = !fillPoints.empty();
    clear();
    this->begin_p.setPoint(center_p.getX() - ra, center_p.getY() - rb); //begin为新外接矩形左下角
    this->end_p.setPoint(center_p.getX() + ra, center_p.getY() + rb); //end为新外接矩形右上角
    this->a = ra;
    this->b = rb;
    calculatePoints(); //画新的圆周
    calculateHandle();
    if (isFilled)
        fillColor();
}
//若拿着handle对椭圆进行旋转
void MyEllipse::setHandlePointByRef(const Point& ref)
{
    if (ref.getX() == center_p.getX() || ref.getY() == center_p.getY()) //若(center,ref)水平或垂直，则旋转90度
        setTwoAxes(b, a);
}
//整体沿着一个矢量 (0,0)->move_p 平移
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
//只是进行垂直旋转
void MyEllipse::rotate(double angle)
{
    int temp = abs((int)angle) % 180;
    if (temp >= 0 && temp < 90) //abs(angle%180)在[0,90)区间，则不变
        return;
    else //abs(angle%180)在[90,180)区间，旋转90度
        setTwoAxes(b, a);
}
//以r的比例放大或缩小
void MyEllipse::scale(double r)
{
    setTwoAxes(a * r, b * r);
}
//判断是否在图形平面上或者在椭圆中心、handle_p
bool MyEllipse::isOn(const Point& p)
{
    if (p.distanceTo(center_p) <= 5 || p.distanceTo(handle_p) <= 5 || isOnPlain(p))
        return true;
    for (Point mp : markPoints)
        if (mp.distanceTo(p) <= 5)
            return true;
    return false;
}
//判断是否在图形平面上
bool MyEllipse::isOnPlain(const Point& p)
{
    if (SimpleFigure::isOn(p)) //判断是否在椭圆周长上
        return true;
    if (!fillPoints.empty()) //判断是否在椭圆内部
    {
        for (Point* pt : fillPoints)
            if (*pt == p)
                return true;
    }
    return false;
}
//返回第几类图形
int MyEllipse::isFigure()
{
    return 2;
}
//计算椭圆的圆周上的点，近似算法
//bresenham method，整数算法
void MyEllipse::calculatePoints()
{
    if (a < 0 || b < 0)
        return;  //is not a legal ellipse
    long sqa = a * a;
    long sqb = b * b;
    //for the 1st area and k>-1
    int x = 0, y = b; //initial point is (0,b)
    long D = 2 * sqb - 2 * b * sqa + sqa; //初始判断表达式
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
//确定handle_p的位置，与（a,b)向量方向有关
const int MyEllipse::h = 30; //初始化handle长度
void MyEllipse::calculateHandle()
{
    if (a <= 0 || b <= 0)
    {
        handle_p.setPoint(center_p.getX(), center_p.getY() + h);
        return;
    }
    double temp = sqrt(a * a + b * b);
    handle_p.setPoint(center_p.getX() + int(h * a / temp + 0.5), center_p.getY() + int(h * b / temp + 0.5)); //根据a,b确定handle_p的位置
}
//遍历轮廓点，生成填充点
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
//填充颜色
void MyEllipse::fillColor()
{
    if (!fillPoints.empty())
        return;
    calculateFillPoints();
}
//画图形本身，并显示填充颜色
void MyEllipse::draw()
{
    SimpleFigure::draw(); //轮廓
    Area::fillColor(); //填充
}
//清除图形和填充颜色
void MyEllipse::clear()
{
    SimpleFigure::clear(); //轮廓
    Area::clearColor();
}
