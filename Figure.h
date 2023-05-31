#ifndef FIGURE_H
#define FIGURE_H
#include "Point.h"
//FigureΪ����ͼ�εĻ��ֻ࣬�ṩ�ӿڣ����ṩʵ��
class Figure
{
public:
    virtual void draw() = 0;      //����ͼ�α���
    virtual void markDraw() = 0;  //���Ƴ�draw����ı�ǣ���ǵ�(+���ο�)
    virtual void clear() = 0;     //���ͼ���еĵ㲢�ͷſռ�
    virtual void translate(const Point& offset) = 0; //ƽ��
    virtual void rotate(double angle) = 0;            //��ת
    virtual void scale(double s) = 0;                 //����
    virtual bool isOn(const Point& p) = 0;        //��p�Ƿ��ڱ�ͼ����(����ǵ㡢center��handle)
    virtual bool isOnPlain(const Point& p) = 0;   //��p�Ƿ���ͼ�α�����
    virtual int isFigure() = 0;                  //����ͼ�δ���
};
#endif // !FIGURE_H
