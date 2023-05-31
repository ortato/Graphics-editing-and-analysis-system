#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "LineControl.h"
#include "circlecontrol.h"
#include "MyEllipseControl.h"
#include "CurveControl.h"
#include "FigureControl.h"
#include "mypen.h"
#include "mypencontrol.h"
#include "rectangular.h"
#include "rectangularcontrol.h"
#include <QtOpenGL/QtOpenGL>
#include <GL/glut.h>
#include <QMouseEvent>
#include <vector>
enum Mode { LINE = 0, CIRCLE, ELLIPSE, CURVE, PEN, RECTANGLE };     //��������
//enum Edit{DRAW=0, FILL, CUT};                 //��չ����
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget* parent, Mode m);
    ~GLWidget();
    virtual void setMode(Mode m);
    void onOpen();                  //���ļ�
    void onSave(string fileName);   //�����ļ�
    virtual void onDelete(); //ɾ����ǰ��ѡ�е�ͼ��
    virtual void onClear(); //��ջ���
    virtual void onFill();  //���
    virtual void undo();    //����
signals:
    void changeMode(Mode m); //���»�ͼ״̬
protected:
    //���ڻ�ͼ
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    //���ڽ���
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    int curCtrl; //��ǰFigureControl������
    vector<FigureControl*> figureControls;  //����ͼ�εĿ��ƣ�һ��ʼ�� push_bsck 5��ͼ�εĿ��ƺ���
    vector<Figure*> allFigures;             //�������е�����ͼ��
    vector<Figure*> history;                //����������ʷ��¼
    Figure* setFocusByPoint(const Point& p);//���ݵ���ĵ�������curCtrl�Ͷ�ӦFigureControl��curFigure
};
#endif // GLWIDGET_H
