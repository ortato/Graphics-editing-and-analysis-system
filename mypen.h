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
    void addPoint(Point* p); //�õ�һ���㣬�����뵽curPen�ĵ㼯����
    virtual void draw();      //����ͼ�α���
    virtual void markDraw();  //���Ƴ�draw����ı�ǣ���ǵ�(+���ο�)
    virtual void clear();     //���ͼ���еĵ㲢�ͷſռ�
    virtual void translate(const Point& offset); //ƽ��
    virtual void rotate(double angle);            //��ת
    virtual void scale(double s);                 //����
    virtual bool isOn(const Point& p);        //��p�Ƿ��ڱ�ͼ����(����ǵ㡢center��handle)
    virtual bool isOnPlain(const Point& p);   //��p�Ƿ���ͼ�α�����
private:
    double lineWidth;
    Point* lastPoint;  //��һ����
  //  Point endPoint;  //��ǰ�ĵ�
    tuple<float, float, float> penColor;
};
#endif // MYPEN_H