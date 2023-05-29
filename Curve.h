#ifndef CURVE_H
#define CURVE_H
#include "Point.h"
#include "SimpleFigure.h"
class Curve : public SimpleFigure
{
public:
    Curve();
    Curve(const vector<Point>& vertices);
    ~Curve();
    //��ȡ
    vector<Point> getVertices() const;  //��ȡ4�����Ƶ�
    Point getCenter() const;            //��ȡ���ĵ�
    Point getHandle() const;            //��ȡ���ֵ�
    //����
    void setVertex(int idx, const Point& p);    //��������Ϊidx�Ķ���λ��
    void setHandlePointByRef(const Point& ref); //ref(�ο���)Ϊ��ǰ���λ�ã�ֻ������handle�㣬center����ref�㹲�߼���
    void translate(const Point& offset);    //ƽ��
    void rotate(double angle);              //��ת
    void scale(double s);                   //����
    bool isOn(const Point& p);
    bool isOnPlain(const Point& p);
    int isFigure(); //����3
    void draw();
    void markDraw();
    void clear(); //ֻ��������ϵĵ㣬��������Ƶ�
private:
    vector<Point> vertices; //4�����Ƶ�:begin,*,*,end
    Point center;           //���ģ�������������ʱ��calculatePoints()����õ�
    Point handle;           //����ת֮����calculatePoints()֮��õ�����תʱֱ�Ӽ���
    const static int h;     //handle���ȣ���ʼ��Ϊ30
    void calculatePoints(); //���ݿ��Ƶ���������ϸ����center
    void calculateCenter(); //���ݿ��Ƶ����center
};
#endif // CURVE_H
