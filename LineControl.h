#ifndef LINECONTROL_H
#define LINECONTROL_H
#include "Line.h"
#include "Point.h"
#include "FigureControl.h"
#include <vector>
using namespace std;
class LineControl :public FigureControl
{
public:
    LineControl();
    LineControl(std::vector<Figure*>* figures, std::vector<Figure*>* history);
    LineControl(int width, int height);
    LineControl(std::vector<Figure*>* figures, int width, int height);
    bool setFocus(Figure* fg);
    void onMousePressEvent(QMouseEvent* event);
    void onMouseMoveEvent(QMouseEvent* event);
    void onDraw();     //��ֱ��
    void onMarkDraw(); //����ǵ�
    virtual void onDelete(); //ɾ��
    virtual void onClear();  //���
    virtual void onUndo(); //����
    const vector<Line*>& getLines();
private:
    enum SetLP { SETBEGIN, SETEND, SETCENTER, SETHANDLE } setLP; //Ŀǰ���ĵ������/�յ�
    Line* curLine; //��ǰֱ��
    vector<Line*> lines;
    //std::stack<Line*> historyLines;
};
#endif // !LINECONTROL_H

