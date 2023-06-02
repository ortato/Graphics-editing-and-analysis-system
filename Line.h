#ifndef LINE_H
#define LINE_H
#include "Point.h"
#include "SimpleFigure.h"
class Line : public SimpleFigure
{
public:
	Line();
	Line(const Point& begin, const Point& end);
	Point getBeginPoint() const;
	Point getEndPoint() const;
	Point getDownPoint() const;
	Point getUpPoint() const;
	Point getCenterPoint() const;
	Point getHandlePoint() const;
	Point intersectWithX(int x) const; //��Ҫ��֤��ֱ�߲�ƽ����x�ᣬ�������
	Point intersectWithY(int y) const; //��Ҫ��֤��ֱ�߲�ƽ����y�ᣬ�������
	void setBeginPoint(const Point& p);
	void setEndPoint(const Point& p);
	void setLine(const Point& begin, const Point& end);
	void setHandlePointByRef(const Point& ref); //�����
	void translate(const Point& offset); //ƽ��
	void rotate(double angle); //���е���ת
	void scale(double s); //���е�Ϊ��׼���з���
	bool isOn(const Point& p); //isOn������SimpleFigure��
	bool isOnPlain(const Point& p); //������center��handle
	bool cut(const Point& leftDown, int width, int height); //���ݾ��δ��ڲü��������ڴ������򷵻�false
	int isFigure(); //����0
	void markDraw(); //ֻ�������draw����ı�ǣ�������ֱ�߱���
	void plainMarkDraw(); //����center��Ǻ�handle���
private:
	Point begin;
	Point end;
	Point* left;
	Point* right;
	Point* up;
	Point* down;
	//�������ֻ���ڽ����л��õ�������Ϊֱ�ߵĹؼ���Ϣ����calculateRelatedPoints()�����и���
	Point center; //�е�
	Point handle; //handle��
	double length; //ֱ�߳��ȣ�����ת���õ�
	const static int h; //handle���ȣ���ʼ��Ϊ30
	void updateParameters();
	void calculateRelatedPoints(); //ÿ�η���ת����֮�����center��handle���Լ�length
	void calculatePoints(); //����begin��end����ֱ�����е�
	void bresenham01(int dx, int dy);
	void bresenham_10(int dx, int dy);
	void bresenham1inf(int dx, int dy);
	void bresenham_inf_1(int dx, int dy);
};
#endif // !LINE_H
