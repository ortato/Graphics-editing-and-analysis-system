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
    CircleControl(std::vector<Figure*>* figures, std::vector<Figure*>* history); //多个图
    CircleControl(int width, int height);
    ~CircleControl();
    virtual bool setFocus(Figure* fg); //设置为当前图
    virtual void onUndo(); //撤销删除后的圆
    virtual void onMousePressEvent(QMouseEvent* event); //鼠标press
    virtual void onMouseMoveEvent(QMouseEvent* event); //鼠标press+move
    virtual void onDraw();           //画圆
    virtual void onMarkDraw();       //画标记点
    virtual void onDelete(); //删除
    virtual void onClear();  //清除
    virtual void onFill();   //填充
private:
    int setCV;  //当前正在更改的控制点索引；
                //-1表示选中markpoint,
                //-2表示选中center,
                //-3表示选中了handle点
                //-4表示创建新的圆心
    Circle* curCircle; //当前聚焦的圆
    vector<Circle*> circles;
    //std::stack<Circle*> historyCircles;
};
#endif // !CIRCLECONTROL_H
