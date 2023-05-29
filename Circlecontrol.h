#ifndef CIRCLECONTROL_H
#define CIRCLECONTROL_H
#include "Circle.h"
#include "FigureControl.h"
#include <vector>
using namespace std;
class CircleControl :public FigureControl
{
public:
    CircleControl();
    CircleControl(std::vector<Figure*>* figures, std::vector<Figure*>* history); //���ͼ
    CircleControl(int width, int height);
    ~CircleControl();
    virtual bool setFocus(Figure* fg); //����Ϊ��ǰͼ
    virtual void onUndo(); //����ɾ�����Բ
    virtual void onMousePressEvent(QMouseEvent* event); //���press
    virtual void onMouseMoveEvent(QMouseEvent* event); //���press+move
    virtual void onDraw();           //��Բ
    virtual void onMarkDraw();       //����ǵ�
    virtual void onDelete(); //ɾ��
    virtual void onClear();  //���
    virtual void onFill();   //���
private:
    int setCV;  //��ǰ���ڸ��ĵĿ��Ƶ�������
                //-1��ʾѡ��markpoint,
                //-2��ʾѡ��center,
                //-3��ʾѡ����handle��
                //-4��ʾ�����µ�Բ��
    Circle* curCircle; //��ǰ�۽���Բ
    vector<Circle*> circles;
    //std::stack<Circle*> historyCircles;
};
#endif // !CIRCLECONTROL_H
