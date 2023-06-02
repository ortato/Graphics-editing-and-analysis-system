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
    Point getCenter() const; //�������ĵ�
    vector<Point> getMarkPoints() const; //���ر�ǵ㣬����Ӿ��ζ���
    Point getHandlePoint() const; //���ذ��ֵ�
    void setEndPoint(const Point& end); //�����޸���Բ�ĵڶ�����
    void setTwoAxes(int a, int b); //���ó������
    void setHandlePointByRef(const Point& ref);
    void translate(const Point& offset); //ƽ��
    void rotate(double angle); //��ת
    void scale(double s); //����
    bool isOn(const Point& p); //�Ƿ�����Բ�ϣ�����Բ�ܡ���ǵ�Ͱ��ֵ�
    bool isOnPlain(const Point& p); //�Ƿ�����ԲԲ����
    int isFigure(); //����2
    void markDraw();  //���Ƴ�draw����ı�ǣ����ο�+��ǵ�
    void fillColor(); //���
    void draw();      //�������㣬������䣬��Ҳ������
    void clear();     //ɾ�������㣬������䣬Ҳɾ������
private:
    Point begin_p; //��Բ��Ӿ������
    Point end_p; //��Բ��Ӿ����յ�
    Point center_p; //��Բ���ĵ�
    int a, b;
    vector<Point> markPoints; //��ǵ㣬Ϊ��Բ����Ӿ����ĸ�����
    //�������Ϊhandle���
    Point handle_p; //handle��
    const static int h; //handle���ȣ���ʼ��Ϊ30
    void calculatePoints(); //�������λ��
    void calculateHandle(); //����ת���������handle
    void calculateFillPoints(); //��������λ��
};
#endif // !ELLIPSE_H
