#ifndef MYELLIPSE_H
#define MYELLIPSE_H
#include "Area.h"
#include "Point.h"
#include "SimpleFigure.h"
class MyEllipse :public SimpleFigure, public Area
{
public:
    MyEllipse();
    MyEllipse(const Point& begin, const Point& end);
    MyEllipse(const Point& center, int rx, int ry);
    ~MyEllipse();
    Point getCenter() const; //返回中心点
    vector<Point> getMarkPoints() const; //返回标记点，即外接矩形顶点
    Point getHandlePoint() const; //返回把手点
    void setEndPoint(const Point& end); //用于修改椭圆的第二个点
    void setTwoAxes(int a, int b); //设置长轴短轴
    void setHandlePointByRef(const Point& ref);
    void translate(const Point& offset); //平移
    void rotate(double angle); //旋转
    void scale(double s); //缩放
    bool isOn(const Point& p); //是否在椭圆上，包括圆周、标记点和把手点
    bool isOnPlain(const Point& p); //是否在椭圆圆周上
    int isFigure(); //返回2
    void markDraw();  //绘制除draw以外的标记：矩形框+标记点
    void fillColor(); //填充
    void draw();      //画轮廓点，若被填充，则也画填充点
    void clear();     //删除轮廓点，若被填充，也删除填充点
private:
    Point begin_p; //椭圆外接矩形起点
    Point end_p; //椭圆外接矩形终点
    Point center_p; //椭圆中心点
    int a, b;
    vector<Point> markPoints; //标记点，为椭圆的外接矩形四个顶点
    //下面参数为handle相关
    Point handle_p; //handle点
    const static int h; //handle长度，初始化为30
    void calculatePoints(); //计算各点位置
    void calculateHandle(); //非旋转操作后更新handle
    void calculateFillPoints(); //计算填充点位置
};
#endif // !ELLIPSE_H
