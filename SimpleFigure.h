#ifndef SIMPLEFIGURE_H
#define SIMPLEFIGURE_H
#include "Point.h"
#include "Figure.h"
#include <vector>
class SimpleFigure : public Figure
{
public:
	SimpleFigure();
	virtual ~SimpleFigure();    //必须写成虚析构函数
	//存在于整个对象的生命周期
	static tuple<float, float, float> defaultColor;
	static double defaultPointSize;
	static void setColor(tuple<float, float, float> newColor);
	static void setPSize(double newsize);
	double getPointSize();
	virtual void draw();
	virtual void clear();
	virtual int isFigure(); // line=0,circle=1,ellipse=2,curve=3...
	virtual bool isOn(const Point& p); //该点是否在轮廓上(调用所有点的距离函数来判断点p是否在本直线上)
	const std::vector<Point*>& getPoints() const;
protected:
	std::vector<Point*> points;
private:
	tuple<float, float, float> color;
	double pointSize;
};
#endif // SIMPLEFIGURE_H
