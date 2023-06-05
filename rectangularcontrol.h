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
    virtual void onUndo(); //撤销删除后的圆
    //鼠标操作事件
    virtual void onMousePressEvent(QMouseEvent* event); //虚函数，继承自figurecontrol基类 单击左键
    virtual void onMouseMoveEvent(QMouseEvent* event);  //虚函数， 继承自figurecontrol基类 拖动
    virtual void onDraw(); //绘制图形本身
    virtual void onMarkDraw(); //给当前矩形添加标记，即矩形顶点、中心点和handle
    virtual void onScale(double r); //缩放和放大
    virtual void onDelete(); //删除
    virtual void onClear();  //清除
    virtual void onFill();   //填充
private:
    enum SetEP { ENDPOINT, MARKPOINT, CENTERPOINT, HANDLEPOINT }setEP; //当前点击的点为终点/标记点
    Rectangular* currectangular; //当前正在绘制的椭圆
    vector<Rectangular*> Allrectangular; //包括所有绘制好的椭圆
};
#endif // RECTANGULARCONTROL_H
