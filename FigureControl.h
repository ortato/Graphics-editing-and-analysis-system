#ifndef FIGURECONTROL_H
#define FIGURECONTROL_H
#include "Figure.h"
#include <QMouseEvent>
#include <vector>
#include <stack>
class FigureControl
{
public:
    FigureControl();
    FigureControl(std::vector<Figure*>* figures, std::vector<Figure*>* history);
    FigureControl(int width, int height);
    FigureControl(std::vector<Figure*>* figures, int width, int height);
    void resize(int width, int height);
    //��fg��FigureControl�ڣ������þ۽�������true�����򷵻�false
    virtual void onUndo(); //����
    virtual bool setFocus(Figure* fg);
    virtual void onMousePressEvent(QMouseEvent* event);         //��갴��
    virtual void onMouseMoveEvent(QMouseEvent* event);          //��갴�����ƶ�
    virtual void onMousePassiveMoveEvent(QMouseEvent* event);   //���������ƶ�
    virtual void onDraw();      //��������ͼ�Σ�������ǣ�
    virtual void onMarkDraw();  //Ϊ��ǰͼ����ӱ��
    virtual void onDelete();    //ɾ��
    virtual void onClear();     //�������ͼ��
    virtual void onFill();      //���
protected:
    int width; //��ǰx�����ص���
    int height; //��ǰy�����ص���
    std::vector<Figure*>* allFigures; //ָ��ȫ�ֵ�Figure����
    std::vector<Figure*>* history;    //ָ��ȫ�ֵ�historyջ
    void pushForward(Figure* figure); //����ǰͼ�η������ͼ��
};
#endif // !FIGURECONTROL_H
