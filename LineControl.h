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
    void onDraw();     //画直线
    void onMarkDraw(); //画标记点
    virtual void onDelete(); //删除
    virtual void onClear();  //清除
    virtual void onUndo(); //撤销
    const vector<Line*>& getLines();
private:
    enum SetLP { SETBEGIN, SETEND, SETCENTER, SETHANDLE } setLP; //目前更改的是起点/终点
    Line* curLine; //当前直线
    vector<Line*> lines;
    //std::stack<Line*> historyLines;
};
#endif // !LINECONTROL_H

