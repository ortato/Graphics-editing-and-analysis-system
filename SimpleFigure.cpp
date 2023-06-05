#include "SimpleFigure.h"
#include <GL/glut.h>
using namespace std;
tuple<float, float, float> SimpleFigure::defaultColor(0.0, 0.0, 0.0); //初始化填充色为黑色
double SimpleFigure::defaultPointSize = 1.0;
SimpleFigure::SimpleFigure()
{
	color = make_tuple(-1.0, -1.0, -1.0);
	pointSize = defaultPointSize; //取当前设定的线宽
}
SimpleFigure::~SimpleFigure()
{
	for (Point* p : points)
		delete p;
}
//设定颜色
void SimpleFigure::setColor(tuple<float, float, float> newColor)
{
	defaultColor = newColor;
}
//重新设定点的大小，进而改变具体图形的线宽
void SimpleFigure::setPSize(double newsize)
{
	defaultPointSize = newsize;
}
//返回当前宽度
double SimpleFigure::getPointSize()
{
	return pointSize;
}
//画出基本图形的点集合
void SimpleFigure::draw()
{
	if (std::get<0>(color) < 0)
		color = defaultColor;
	glPointSize(pointSize);
	glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));
	//	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);     //这里是底层的绘图操作，是整个绘图的基础
	for (auto it : points)  //points为Point类型的指针
		it->draw();         //即调用函数glVertex2i(x, y)
	glEnd();
	glFlush();
}
void SimpleFigure::clear()
{
	for (auto it : points)
		delete it;
	points.erase(points.begin(), points.end());
}
bool SimpleFigure::isOn(const Point& p)
{
	for (Point* pt : points)
		if (pt->distanceTo(p) < 3)
			return true;
	return false;
}
int SimpleFigure::isFigure()
{
	return 0;
}
const vector<Point*>& SimpleFigure::getPoints() const
{
	return points;
}
