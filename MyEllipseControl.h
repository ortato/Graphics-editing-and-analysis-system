#ifndef MYELLIPSECONTROL_H
#define MYELLIPSECONTROL_H
#include "MyEllipse.h"
#include "FigureControl.h"
#include <vector>
using namespace std;
class EllipseControl :public FigureControl
{
public:
    EllipseControl();
    EllipseControl(std::vector<Figure*>* figures, std::vector<Figure*>* history);
    EllipseControl(int width, int height);
    ~EllipseControl();
    virtual bool setFocus(Figure* fg); //��ѡ�е���Բ�趨Ϊ��ǰ��Բ
    virtual void onUndo(); //��������
    //�������¼�
    virtual void onMousePressEvent(QMouseEvent* event); //�������
    virtual void onMouseMoveEvent(QMouseEvent* event); //�϶�
    virtual void onDraw(); //����ͼ�α���
    virtual void onMarkDraw(); //����ǰ��Բ��ӱ�ǣ�����Ӿ��ζ��㡢���ĵ��handle
    virtual void onScale(double r); //���źͷŴ�
    virtual void onDelete(); //ɾ��
    virtual void onClear();  //���
    virtual void onFill();   //���
private:
    enum SetEP { ENDPOINT, MARKPOINT, CENTERPOINT, HANDLEPOINT }setEP; //��ǰ����ĵ�Ϊ�յ�/��ǵ�
    MyEllipse* curEllipse; //��ǰ���ڻ��Ƶ���Բ
    vector<MyEllipse*> Allellipses; //�������л��ƺõ���Բ
    //std::stack<MyEllipse*> historyEllipse;
};
#endif // !ELLIPSECONTROL_H

