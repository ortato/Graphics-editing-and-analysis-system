#ifndef MYPEN_H
#define MYPEN_H
//#include <QDialog>
#include <QMouseEvent>
//#include <QPushButton>
#include "SimpleFigure.h"
#include "Point.h"
class Pen : public SimpleFigure
{
public:
    Pen();
    ~Pen();
    void addPoint(Point* p); //得到一个点，并加入到curPen的点集合中
    virtual void draw();      //绘制图形本身
    virtual void markDraw();  //绘制除draw以外的标记：标记点(+矩形框)
    virtual void clear();     //清除图形中的点并释放空间
    virtual void translate(const Point& offset); //平移
    virtual void rotate(double angle);            //旋转
    virtual void scale(double s);                 //缩放
    virtual bool isOn(const Point& p);        //点p是否在本图形上(含标记点、center、handle)
    virtual bool isOnPlain(const Point& p);   //点p是否在图形本身上
private:
    double lineWidth;
    Point* lastPoint;  //上一个点
  //  Point endPoint;  //当前的点
    tuple<float, float, float> penColor;
};
#endif // MYPEN_H