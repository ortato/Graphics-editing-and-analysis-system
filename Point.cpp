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
//������ͨ��
void Point::draw()
{
	glVertex2i(x, y);
}
//���Ƶ�
void Point::markDraw()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	int n = 100; //����100����
	GLfloat R = 5.0f; //Բ�İ뾶
	GLfloat pi = 3.1415926536f;
	for (int i = 0; i < n; i++)
		glVertex2f(x + R * cos(2 * pi / n * i), y + R * sin(2 * pi / n * i));
	glEnd();
	glFlush();
}
//���Ʊ�־��
void Point::centerMarkDraw()
{
	//ѡ����ɫ
	glColor3f(1.0, 0.0, 0.0);
	//����ʮ��
	glBegin(GL_LINES);
	glVertex2i(x - 10, y);
	glVertex2i(x + 10, y);
	glVertex2i(x, y - 10);
	glVertex2i(x, y + 10);
	glEnd();
	//����Բ��
	glBegin(GL_POLYGON);
	int n = 100; //����100����
	GLfloat R = 5.0f; //Բ�İ뾶
	GLfloat pi = 3.1415926536f;
	for (int i = 0; i < n; i++)
		glVertex2f(x + R * cos(2 * pi / n * i), y + R * sin(2 * pi / n * i));
	glEnd();
	glFlush();
}
void Point::handleDraw(const Point& p)
{
	//ѡ����ɫ
	glColor3f(1.0, 0.65, 0.0);
	//��������
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(p.x, p.y);
	glEnd();
	//����Բ��
	glBegin(GL_POLYGON);
	int n = 100; //����100����
	GLfloat R = 5.0f; //Բ�İ뾶
	GLfloat pi = 3.1415926536f;
	for (int i = 0; i < n; i++)
		glVertex2f(x + R * cos(2 * pi / n * i), y + R * sin(2 * pi / n * i));
	glEnd();
	glFlush();
}
//�������õ�����
void Point::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Point::setHandlePoint(const Point& begin, const Point& end, int h)
{
	Point center((begin.getX() + end.getX()) / 2, (begin.getY() + end.getY()) / 2); //�����е�
	if (begin.getX() == end.getX())
		setPoint(center.getX(), center.getY() + h);//����غϵĻ���HandPoint�������Ϸ�
	else
	{
		double k = (double)(end.getY() - begin.getY()) / (double)(end.getX() - begin.getX());//б��
		setPoint(int(center.getX() - h * k / sqrt(k * k + 1) + 0.5), int(center.getY() + h / sqrt(k * k + 1) + 0.5));
	}
}
//���ƽ��
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
// ���ϵ��£�����������
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