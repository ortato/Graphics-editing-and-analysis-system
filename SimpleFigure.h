#ifndef SIMPLEFIGURE_H
#define SIMPLEFIGURE_H
#include "Point.h"
#include "Figure.h"
#include <vector>
class SimpleFigure : public Figure
{
public:
	SimpleFigure();
	virtual ~SimpleFigure();    //����д������������
	//�����������������������
	static tuple<float, float, float> defaultColor;
	static double defaultPointSize;
	static void setColor(tuple<float, float, float> newColor);
	static void setPSize(double newsize);
	double getPointSize();
	virtual void draw();
	virtual void clear();
	virtual int isFigure(); // line=0,circle=1,ellipse=2,curve=3...
	virtual bool isOn(const Point& p); //�õ��Ƿ���������(�������е�ľ��뺯�����жϵ�p�Ƿ��ڱ�ֱ����)
	const std::vector<Point*>& getPoints() const;
protected:
	std::vector<Point*> points;
private:
	tuple<float, float, float> color;
	double pointSize;
};
#endif // SIMPLEFIGURE_H
