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
    //若fg在FigureControl内，则设置聚焦并返回true，否则返回false
    virtual void onUndo(); //撤销
    virtual bool setFocus(Figure* fg);
    virtual void onMousePressEvent(QMouseEvent* event);         //鼠标按下
    virtual void onMouseMoveEvent(QMouseEvent* event);          //鼠标按下且移动
    virtual void onMousePassiveMoveEvent(QMouseEvent* event);   //鼠标仅仅是移动
    virtual void onDraw();      //绘制所有图形（不带标记）
    virtual void onMarkDraw();  //为当前图形添加标记
    virtual void onDelete();    //删除
    virtual void onClear();     //清除所有图形
    virtual void onFill();      //填充
protected:
    int width; //当前x轴像素点数
    int height; //当前y轴像素点数
    std::vector<Figure*>* allFigures; //指向全局的Figure数组
    std::vector<Figure*>* history;    //指向全局的history栈
    void pushForward(Figure* figure); //将当前图形放在最高图层
};
#endif // !FIGURECONTROL_H
