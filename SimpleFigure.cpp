#include "SimpleFigure.h"
#include <GL/glut.h>
using namespace std;
tuple<float, float, float> SimpleFigure::defaultColor(0.0, 0.0, 0.0); //��ʼ�����ɫΪ��ɫ
double SimpleFigure::defaultPointSize = 1.0;
SimpleFigure::SimpleFigure()
{
	color = make_tuple(-1.0, -1.0, -1.0);
	pointSize = defaultPointSize; //ȡ��ǰ�趨���߿�
}
SimpleFigure::~SimpleFigure()
{
	for (Point* p : points)
		delete p;
}
//�趨��ɫ
void SimpleFigure::setColor(tuple<float, float, float> newColor)
{
	defaultColor = newColor;
}
//�����趨��Ĵ�С�������ı����ͼ�ε��߿�
void SimpleFigure::setPSize(double newsize)
{
	defaultPointSize = newsize;
}
//���ص�ǰ���
double SimpleFigure::getPointSize()
{
	return pointSize;
}
//��������ͼ�εĵ㼯��
void SimpleFigure::draw()
{
	if (std::get<0>(color) < 0)
		color = defaultColor;
	glPointSize(pointSize);
	glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));
	//	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);     //�����ǵײ�Ļ�ͼ��������������ͼ�Ļ���
	for (auto it : points)  //pointsΪPoint���͵�ָ��
		it->draw();         //�����ú���glVertex2i(x, y)
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
