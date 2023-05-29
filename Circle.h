#ifndef CIRCLE_H
#define CIRCLE_H
#include "Point.h"
#include "Area.h"
#include "SimpleFigure.h"
#include <vector>
using namespace std;
class Circle : public SimpleFigure, public Area
{
public:
    Circle();
    Circle(Point center, int radius);
    ~Circle();
    Point getCenter() const;
    vector<Point> getMarkPoints() const; //返回标记点
    Point getHandlePoint() const;
    void setRadius(int radius);
    void setHandlePointByRef(const Point& ref); //ref(参考点)为当前鼠标位置，只需设置handle点，center点与ref点共线
    void translate(const Point& offset); //平移
    void rotate(double angle); //旋转
    void scale(double s); //缩放
    bool isOn(const Point& p);      //若已填充则在圆内即可；若没有填充需在轮廓上
    bool isOnPlain(const Point& p); //不包括center和handle
    void draw();        //画轮廓点，若被填充，则也画填充点
    void markDraw();    //绘制除draw以外的标记：矩形框+标记点
    void clear();       //删除轮廓点，若被填充，也删除填充点
    void drawRect(const Point& a, const Point& b, const Point& c, const Point& d);//画外面的虚线框
    void fillColor();
    int isFigure(); //返回1
private:
    Point center;   //圆心
    int radius;     //半径
    vector<Point> markPoints; //标记点
    //下面参数为handle相关
    Point handle; //handle点
    const static int h; //handle长度，初始化为30
    void calculatePoints(); //计算轮廓点位置
    void calculateFillPoints(); //计算填充点位置
    void calculateHandle(); //非旋转操作后更新handle
};
#endif // CIRCLE_H
