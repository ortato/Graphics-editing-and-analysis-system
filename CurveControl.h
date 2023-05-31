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
    //由于一个图上可能有多个该类图形
    //通过setFoucus()可以确定是哪个图形
    bool setFocus(Figure* fg);
    void onUndo(); //撤销
    void onMousePressEvent(QMouseEvent* event); //鼠标按下
    void onMouseMoveEvent(QMouseEvent* event);  //鼠标移动
//	void onDraw();
    void onMarkDraw();
    void onDelete();  //删除当前曲线
    void onClear();   //清除所有曲线
private:
    int setCV;  //当前正在更改的控制点索引；
                //-1表示正在绘制控制点,
                //-2表示选中了中心点,
                //-3表示选中了handle点
    int curIdx;             //当前聚焦的曲线索引，鼠标所在曲线的索引
    vector<Point> curVtxs;  //当前聚焦的控制点
    vector<Curve*> curves;  //存储所有的曲线，添加/删除都要在allFigures同步进行
    //std::stack<Curve*> historyCurves;
    void deleteCurve(int idx); //删除特定索引的Curve
};
#endif // CURVECONTROL_H

