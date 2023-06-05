#ifndef RECTANGULARCONTROL_H
#define RECTANGULARCONTROL_H
#include "rectangular.h"
#include "FigureControl.h"
#include <vector>
using namespace std;
class RectangularControl :public FigureControl
{
public:
    RectangularControl();
    RectangularControl(std::vector<Figure*>* figures, std::vector<Figure*>* history);
    RectangularControl(int width, int height);
    virtual bool setFocus(Figure* fg);
    virtual void onUndo(); //����ɾ�����Բ
    //�������¼�
    virtual void onMousePressEvent(QMouseEvent* event); //�麯�����̳���figurecontrol���� �������
    virtual void onMouseMoveEvent(QMouseEvent* event);  //�麯���� �̳���figurecontrol���� �϶�
    virtual void onDraw(); //����ͼ�α���
    virtual void onMarkDraw(); //����ǰ������ӱ�ǣ������ζ��㡢���ĵ��handle
    virtual void onScale(double r); //���źͷŴ�
    virtual void onDelete(); //ɾ��
    virtual void onClear();  //���
    virtual void onFill();   //���
private:
    enum SetEP { ENDPOINT, MARKPOINT, CENTERPOINT, HANDLEPOINT }setEP; //��ǰ����ĵ�Ϊ�յ�/��ǵ�
    Rectangular* currectangular; //��ǰ���ڻ��Ƶ���Բ
    vector<Rectangular*> Allrectangular; //�������л��ƺõ���Բ
};
#endif // RECTANGULARCONTROL_H
