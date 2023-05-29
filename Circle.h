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
    vector<Point> getMarkPoints() const; //���ر�ǵ�
    Point getHandlePoint() const;
    void setRadius(int radius);
    void setHandlePointByRef(const Point& ref); //ref(�ο���)Ϊ��ǰ���λ�ã�ֻ������handle�㣬center����ref�㹲��
    void translate(const Point& offset); //ƽ��
    void rotate(double angle); //��ת
    void scale(double s); //����
    bool isOn(const Point& p);      //�����������Բ�ڼ��ɣ���û���������������
    bool isOnPlain(const Point& p); //������center��handle
    void draw();        //�������㣬������䣬��Ҳ������
    void markDraw();    //���Ƴ�draw����ı�ǣ����ο�+��ǵ�
    void clear();       //ɾ�������㣬������䣬Ҳɾ������
    void drawRect(const Point& a, const Point& b, const Point& c, const Point& d);//����������߿�
    void fillColor();
    int isFigure(); //����1
private:
    Point center;   //Բ��
    int radius;     //�뾶
    vector<Point> markPoints; //��ǵ�
    //�������Ϊhandle���
    Point handle; //handle��
    const static int h; //handle���ȣ���ʼ��Ϊ30
    void calculatePoints(); //����������λ��
    void calculateFillPoints(); //��������λ��
    void calculateHandle(); //����ת���������handle
};
#endif // CIRCLE_H
