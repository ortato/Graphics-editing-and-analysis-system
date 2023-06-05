#ifndef RECTANGULAR_H
#define RECTANGULAR_H
#include "Point.h"
#include "SimpleFigure.h"
#include "Area.h"
#include <vector>
class Rectangular :public SimpleFigure, public Area
{
public:
    Rectangular();
    Rectangular(const Point& begin, const Point& end);
    Point getCenter() const;
    vector<Point> getMarkPoints() const;
    Point getHandlePoint() const;
    void setEndPoint(const Point& end);
    void setHandlePointByRef(const Point& ref);
    void translate(const Point& offset);
    void rotate(double angle);
    void scale(double s);
    bool isOn(const Point& p);
    bool isOnPlain(const Point& p);
    void markDraw(); //绘制除draw以外的标记：矩形框+标记点
    void clear();       //删除轮廓点，若被填充，也删除填充点
    void fillColor();
    void draw();        //画轮廓点，若被填充，则也画填充点
private:
    Point begin;  //两个点可以确定矩形
    Point end;
    Point center;
    int length, width;       // 记录矩形的长度宽度。
    vector<Point> markPoints; //标记点，为矩形的外接四个顶点
//下面参数为handle相关
    Point handle; //handle点
    const static int h; // 静态常量成员变量  handle长度，初始化为30
    void calculatePoints(); //计算各点位置
    void calculateHandle(); //非旋转操作后更新handle
    void calculateFillPoints(); //计算填充点位置
};
#endif // RECTANGULAR_H
