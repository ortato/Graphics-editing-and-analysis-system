#ifndef MYPENCONTROL_H
#define MYPENCONTROL_H
#include "mypen.h"
#include "Point.h"
#include "FigureControl.h"
#include <QPainter>
//#include <vector>
using namespace std;
class myPenControl :public FigureControl
{
public:
    myPenControl();
    myPenControl(std::vector<Figure*>* figures, std::vector<Figure*>* history);
    myPenControl(int width, int height);
    myPenControl(std::vector<Figure*>* figures, int width, int height);
    ~myPenControl();
    virtual bool setFocus(Figure* fg);
    virtual void onMousePressEvent(QMouseEvent* event);
    virtual void onMouseMoveEvent(QMouseEvent* event);
    virtual void onMousePassiveMoveEvent(QMouseEvent* event);
    virtual void onDraw();     //���ߣ��洢���в�׽���ĵ�
    virtual void onMarkDraw(); //����ǵ㣬������
    //virtual void onDelete(); //ɾ��
    virtual void onClear();  //���
private:
    //enum SetLP{SETBEGIN, SETEND, SETCENTER, SETHANDLE} setLP; //Ŀǰ���ĵ������/�յ�
   // vector<Line*> lines;
    Pen* curPen;
    vector<Pen*> Allpens; //�������л��ƺõĻ�����
};
#endif // MYPENCONTROL_H