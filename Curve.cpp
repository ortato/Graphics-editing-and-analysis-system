#include "Curve.h"
#include <GL/glut.h>
#include <cmath>
Curve::Curve()
{
}
Curve::Curve(const vector<Point>& vertices)
{
	this->vertices = vertices;
	calculatePoints();
	calculateCenter();
	handle.setHandlePoint(center - Point(-1, 0), center - Point(1, 0), h);
}
Curve::~Curve()
{
}
vector<Point> Curve::getVertices() const
{
	return vertices;
}
Point Curve::getCenter() const
{
	return center;
}
Point Curve::getHandle() const
{
	return handle;
}
void Curve::setVertex(int idx, const Point& p)
{
	if (idx >= vertices.size())
		return;
	vertices[idx] = p;
	clear();            //���֮ǰ���Ѿ����ĵ�
	calculatePoints();  //�������������еĵ�
	calculateCenter();  //�������ĵ�
						//������ֵ�
	handle.setHandlePoint(center - Point(-1, 0), center - Point(1, 0), h);
}
void Curve::setHandlePointByRef(const Point& ref)
{
	double a = handle.getX() - center.getX(), b = handle.getY() - center.getY();
	double c = ref.getX() - center.getX(), d = ref.getY() - center.getY();
	double angle = 180 / 3.14159265 * acos((a * c + b * d) / sqrt((a * a + b * b) * (c * c + d * d)));
	if (b * c > a * d) //��ʱ����ת���Ƕ�ȡ��
		angle = -angle;
	handle.rotate(center, angle);
	for (Point& v : vertices)
		v.rotate(center, angle);
	clear();
	calculatePoints();
}
void Curve::draw()
{
	SimpleFigure::draw();
}
void Curve::markDraw()
{
	for (Point p : vertices)       //����4�����Ƶ�
		p.markDraw();
	center.centerMarkDraw();    //�������ĵ�
	handle.handleDraw(center);  //��������
								//�������ߵķ�Χ
	glLineWidth(1.0f);          //���Ϊ1
	glEnable(GL_LINE_STIPPLE);  //�������߻��ƹ���
	glLineStipple(1, 0x0f0f);   //����
	glColor3f(0.0, 0.0, 1.0);   //��ɫ
	glBegin(GL_LINES);
	for (int i = 0; i + 1 < (int)vertices.size(); i++)
	{
		glVertex2i(vertices[i].getX(), vertices[i].getY());
		glVertex2i(vertices[i + 1].getX(), vertices[i + 1].getY());
	}
	glEnd();
	glFlush();
	glDisable(GL_LINE_STIPPLE); //�ر����߻��ƹ���	
}
void Curve::clear()
{
	SimpleFigure::clear();
}
int Curve::isFigure()
{
	return 3;
}
void Curve::translate(const Point& offset)
{
	center.translate(offset);   //ƽ�����ĵ�
	handle.translate(offset);   //ƽ�ư��ֵ�
	for (Point& v : vertices)      //ƽ��4�����Ƶ�
		v.translate(offset);
	for (Point* p : points)        //ƽ�������ϵ����е�
		p->translate(offset);
}
void Curve::rotate(double angle)
{
	handle.rotate(center, angle);   //��ת���ֵ�
	for (Point& v : vertices)          //��ת4�����Ƶ�
		v.rotate(center, angle);
	clear();
	calculatePoints();
}
void Curve::scale(double s)
{
	for (Point& v : vertices)
		v.scale(center, s, s);
	clear();
	calculatePoints();
}
bool Curve::isOn(const Point& p)
{
	//�������� || �����ĵ��� || �ڰ��ֵ���
	if (isOnPlain(p) || p.distanceTo(center) <= 5 || p.distanceTo(handle) <= 5)
		return true;
	//��4�����Ƶ���
	for (Point& v : vertices)
		if (p.distanceTo(v) <= 5)
			return true;
	return false;
}
bool Curve::isOnPlain(const Point& p)
{
	return SimpleFigure::isOn(p);
}
const int Curve::h = 30; //handle����
void Curve::calculatePoints()
{
	if (vertices.size() < 4)
		return;
	//����verticesǰ4����������߸���
	for (double u = 0; u <= 1; u += 0.001)
	{
		double a = pow(1 - u, 3);
		double b = 3 * u * pow(1 - u, 2);
		double c = 3 * pow(u, 2) * (1 - u);
		double d = pow(u, 3);
		//ÿ����1���㣬�ͽ���ѹ��points������
		points.push_back(new Point(a * vertices[0].getX() + b * vertices[1].getX() + c * vertices[2].getX() + d * vertices[3].getX() + 0.5,
			a * vertices[0].getY() + b * vertices[1].getY() + c * vertices[2].getY() + d * vertices[3].getY() + 0.5));
	}
}
void Curve::calculateCenter()
{
	//����vertices����center
	int minX = vertices[0].getX();
	int maxX = vertices[0].getX();
	int minY = vertices[0].getY();
	int maxY = vertices[0].getY();
	for (Point v : vertices)
	{
		minX = min(minX, v.getX());
		maxX = max(maxX, v.getX());
		minY = min(minY, v.getY());
		maxY = max(maxY, v.getY());
	}
	center.setPoint((minX + maxX) / 2, (minY + maxY) / 2);
}