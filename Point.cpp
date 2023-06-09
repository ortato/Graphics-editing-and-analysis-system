#include "Point.h"
#include <cmath>
#include <GL/glut.h>
#include <iostream>
using namespace std;
Point::Point()
{
}
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
Point::~Point()
{
}
int Point::getX() const
{
	return x;
}
int Point::getY() const
{
	return y;
}
double Point::distanceTo(const Point& p) const
{
	//return abs(this->x - p.x) + abs(this->y - p.y);
	return sqrt((this->x - p.x) * (this->x - p.x) + (this->y - p.y) * (this->y - p.y));
}
//绘制普通点
void Point::draw()
{
	glVertex2i(x, y);
}
//绘制点
void Point::markDraw()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	int n = 100; //绘制100个点
	GLfloat R = 5.0f; //圆的半径
	GLfloat pi = 3.1415926536f;
	for (int i = 0; i < n; i++)
		glVertex2f(x + R * cos(2 * pi / n * i), y + R * sin(2 * pi / n * i));
	glEnd();
	glFlush();
}
//绘制标志点
void Point::centerMarkDraw()
{
	//选择颜色
	glColor3f(1.0, 0.0, 0.0);
	//绘制十字
	glBegin(GL_LINES);
	glVertex2i(x - 10, y);
	glVertex2i(x + 10, y);
	glVertex2i(x, y - 10);
	glVertex2i(x, y + 10);
	glEnd();
	//绘制圆点
	glBegin(GL_POLYGON);
	int n = 100; //绘制100个点
	GLfloat R = 5.0f; //圆的半径
	GLfloat pi = 3.1415926536f;
	for (int i = 0; i < n; i++)
		glVertex2f(x + R * cos(2 * pi / n * i), y + R * sin(2 * pi / n * i));
	glEnd();
	glFlush();
}
void Point::handleDraw(const Point& p)
{
	//选择颜色
	glColor3f(1.0, 0.65, 0.0);
	//绘制连线
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(p.x, p.y);
	glEnd();
	//绘制圆点
	glBegin(GL_POLYGON);
	int n = 100; //绘制100个点
	GLfloat R = 5.0f; //圆的半径
	GLfloat pi = 3.1415926536f;
	for (int i = 0; i < n; i++)
		glVertex2f(x + R * cos(2 * pi / n * i), y + R * sin(2 * pi / n * i));
	glEnd();
	glFlush();
}
//重新设置点坐标
void Point::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Point::setHandlePoint(const Point& begin, const Point& end, int h)
{
	Point center((begin.getX() + end.getX()) / 2, (begin.getY() + end.getY()) / 2); //构造中点
	if (begin.getX() == end.getX())
		setPoint(center.getX(), center.getY() + h);//如果重合的话，HandPoint就在正上方
	else
	{
		double k = (double)(end.getY() - begin.getY()) / (double)(end.getX() - begin.getX());//斜率
		setPoint(int(center.getX() - h * k / sqrt(k * k + 1) + 0.5), int(center.getY() + h / sqrt(k * k + 1) + 0.5));
	}
}
//点的平移
void Point::translate(const Point& offset)
{
	this->x += offset.x;
	this->y += offset.y;
}
void Point::rotate(const Point& ctr, double angle)
{
	angle = angle * 3.14159265 / 180;
	int nx = int(ctr.x + (x - ctr.x) * cos(angle) - (y - ctr.y) * sin(angle) + 0.5);
	int ny = int(ctr.y + (x - ctr.x) * sin(angle) + (y - ctr.y) * cos(angle) + 0.5);
	x = nx, y = ny;
}
void Point::scale(const Point& base, double sx, double sy)
{
	x = x * sx + base.x * (1 - sx);
	y = y * sy + base.y * (1 - sy);
}
// 从上到下，从左到右增大
bool Point::operator<(const Point& p) const
{
	return this->y > p.y || (this->y == p.y && this->x < p.x);
}
bool Point::operator==(const Point& p) const
{
	return this->x == p.x && this->y == p.y;
}
Point Point::operator-(const Point& p) const
{
	return Point(x - p.x, y - p.y);
}
Point Point::operator+(const Point& p) const
{
	return Point(x + p.x, y + p.y);
}
/*
Point Point::operator=(const Point &p) const
{
	return Point(p.x,p.y);
}
*/
ostream& operator<<(ostream& out, const Point& p)
{
	out << '(' << p.getX() << ',' << p.getY() << ')';
	return out;
}