#ifndef POINT_H
#define POINT_H
#include <tuple>
#include <iostream>
using namespace std;
class Point
{
public:
	Point();
	Point(int x, int y);
	~Point();
	int getX() const;
	int getY() const;
	double distanceTo(const Point& p) const;
	void draw();                    //��Ҫ���glBegin()��glEnd()ʹ��
	void markDraw();                //��ǵ�
	void centerMarkDraw();          //���ĵ�
	void handleDraw(const Point& p);//���ֵ�
	void setPoint(int x, int y);
	void setHandlePoint(const Point& begin, const Point& end, int h); //����ֱ����ʼ�����ñ���Ϊֱ�ߵ�handle,(center,handle)��(center,begin)��ֱ������Ϊh
	void translate(const Point& offset);
	void rotate(const Point& ctr, double angle); //ctrΪ��ת���ģ�angleΪ�ȣ����ǻ���
	void scale(const Point& base, double sx, double sy); //baseΪ��׼�㣬sx��sy�ֱ�Ϊ�������������ϵ����0-1��ʾ��С��>1��ʾ�Ŵ�
	bool operator<(const Point& p) const;
	bool operator==(const Point& p) const;
	Point operator-(const Point& p) const;
	Point operator+(const Point& p) const;
	// Point operator=(const Point &p) const;
	friend ostream& operator<<(ostream& out, const Point& p); //���(x,y)����
private:
	int x; //gl��glut��������ͬ
	int y; //glY,��gl����ϵΪ׼��y��ԭ�������½�
};
#endif // !POINT_H