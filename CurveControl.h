#ifndef CURVECONTROL_H
#define CURVECONTROL_H
#include "Curve.h"
#include "FigureControl.h"
class CurveControl :public FigureControl
{
public:
    CurveControl();
    CurveControl(std::vector<Figure*>* figures, std::vector<Figure*>* history);
    CurveControl(int width, int height);
    ~CurveControl();
    //����һ��ͼ�Ͽ����ж������ͼ��
    //ͨ��setFoucus()����ȷ�����ĸ�ͼ��
    bool setFocus(Figure* fg);
    void onUndo(); //����
    void onMousePressEvent(QMouseEvent* event); //��갴��
    void onMouseMoveEvent(QMouseEvent* event);  //����ƶ�
//	void onDraw();
    void onMarkDraw();
    void onDelete();  //ɾ����ǰ����
    void onClear();   //�����������
private:
    int setCV;  //��ǰ���ڸ��ĵĿ��Ƶ�������
                //-1��ʾ���ڻ��ƿ��Ƶ�,
                //-2��ʾѡ�������ĵ�,
                //-3��ʾѡ����handle��
    int curIdx;             //��ǰ�۽�����������������������ߵ�����
    vector<Point> curVtxs;  //��ǰ�۽��Ŀ��Ƶ�
    vector<Curve*> curves;  //�洢���е����ߣ����/ɾ����Ҫ��allFiguresͬ������
    //std::stack<Curve*> historyCurves;
    void deleteCurve(int idx); //ɾ���ض�������Curve
};
#endif // CURVECONTROL_H

