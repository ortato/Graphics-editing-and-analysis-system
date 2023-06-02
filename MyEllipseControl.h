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
    virtual bool setFocus(Figure* fg); //把选中的椭圆设定为当前椭圆
    virtual void onUndo(); //撤销操作
    //鼠标操作事件
    virtual void onMousePressEvent(QMouseEvent* event); //单击左键
    virtual void onMouseMoveEvent(QMouseEvent* event); //拖动
    virtual void onDraw(); //绘制图形本身
    virtual void onMarkDraw(); //给当前椭圆添加标记，即外接矩形顶点、中心点和handle
    virtual void onScale(double r); //缩放和放大
    virtual void onDelete(); //删除
    virtual void onClear();  //清除
    virtual void onFill();   //填充
private:
    enum SetEP { ENDPOINT, MARKPOINT, CENTERPOINT, HANDLEPOINT }setEP; //当前点击的点为终点/标记点
    MyEllipse* curEllipse; //当前正在绘制的椭圆
    vector<MyEllipse*> Allellipses; //包括所有绘制好的椭圆
    //std::stack<MyEllipse*> historyEllipse;
};
#endif // !ELLIPSECONTROL_H

