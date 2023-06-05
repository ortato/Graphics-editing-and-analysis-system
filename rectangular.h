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
    void markDraw(); //���Ƴ�draw����ı�ǣ����ο�+��ǵ�
    void clear();       //ɾ�������㣬������䣬Ҳɾ������
    void fillColor();
    void draw();        //�������㣬������䣬��Ҳ������
private:
    Point begin;  //���������ȷ������
    Point end;
    Point center;
    int length, width;       // ��¼���εĳ��ȿ�ȡ�
    vector<Point> markPoints; //��ǵ㣬Ϊ���ε�����ĸ�����
//�������Ϊhandle���
    Point handle; //handle��
    const static int h; // ��̬������Ա����  handle���ȣ���ʼ��Ϊ30
    void calculatePoints(); //�������λ��
    void calculateHandle(); //����ת���������handle
    void calculateFillPoints(); //��������λ��
};
#endif // RECTANGULAR_H
