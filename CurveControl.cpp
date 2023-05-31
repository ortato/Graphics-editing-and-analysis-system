#include "CurveControl.h"
#include <vector>
CurveControl::CurveControl()
{
	curIdx = -1;
}
CurveControl::CurveControl(std::vector<Figure *> *figures,std::vector<Figure*> *history)
    :FigureControl(figures,history)
{
	curIdx = -1;
}
CurveControl::CurveControl(int width, int height):FigureControl(width,height)
{
	curIdx = -1;
}
CurveControl::~CurveControl()
{
	for(Curve *curve:curves)
		delete curve;
}
bool CurveControl::setFocus(Figure *fg)
{
	for(int i=0;i<curves.size();i++)
		if(curves[i]==fg)
		{
			curIdx = i;
			return true;
		}
	return false;
}
void CurveControl::onUndo()
{
}
void CurveControl::onMousePressEvent(QMouseEvent *event)
{
    //�ж��Ƿ��¼�
	if(event->button()==Qt::LeftButton)
	{
        //��������3�����
        //1.�����еĵ�֮ǰ����1��Curve��û���꣬���Ըõ�Ҫ�н���һ����
        //2.�����еĵ����Ѿ�������ɵ�����1��������
        //3.�����еĵ���Ϊ�����ߵĵ�һ����
        //curPointΪ�����еĵ�ǰ��
		Point curPoint(event->x(), height-event->y());
        //��1�����
        if(!curVtxs.empty())
		{
			if(curVtxs.size()==3) //���һ����
			{
                //ѹ�����1����
				curVtxs.push_back(curPoint);
                //ѹ�뵱ǰ���Ƶ�����
				curves.push_back(new Curve(curVtxs));
				curIdx = curves.size()-1;
                //��allFiguresѹ�뵱ǰ����
				allFigures->push_back(curves.back());
				curVtxs.clear();
				return;
			}
			else if(curVtxs.size()<3)
			{
                //ѹ��ǰ3����
				curVtxs.push_back(curPoint);
				return;
			}
		}
        //��2�����
        else if(curVtxs.empty() && !curves.empty() && curIdx != -1 ) //ѡ�п��Ƶ�����߱����༭curves[curIdx]
		{
            //ѡ��4�����Ƶ��е�һ��
			vector<Point> vtxs = curves[curIdx]->getVertices();
            for(int i=0;i<vtxs.size();i++)
            {
				if(curPoint.distanceTo(vtxs[i])<=5)
				{
					setCV = i;
                    pushForward(curves[curIdx]);//����ǰ������Ϊ���
					return;
                }
            }
            //ѡ�����ĵ�
			if(curPoint.distanceTo(curves[curIdx]->getCenter())<=5)
			{
				setCV = -2;
                pushForward(curves[curIdx]);    //����ǰ������Ϊ���
				return;
			}
            //ѡ�а��ֵ�
			else if(curPoint.distanceTo(curves[curIdx]->getHandle())<=5)
			{
				setCV = -3;
                pushForward(curves[curIdx]);    //����ǰ������Ϊ���
				return;
			}
            //��
			else if(curves[curIdx]->isOn(curPoint))
			{
                pushForward(curves[curIdx]);    //����ǰ������Ϊ���
				return;
			}
		}
        //��3�����
        curVtxs.push_back(curPoint);
        setCV = -1;
	}
}
void CurveControl::onMouseMoveEvent(QMouseEvent *event)
{
	if(!curves.empty())
	{
        //curPointΪ�����еĵ�ǰ��
		Point curPoint(event->x(), height-event->y());
        //���������еĵ�(�ı�setCV)������һ������
        if(setCV>=0)        //�ı���״
			curves[curIdx]->setVertex(setCV, curPoint);
        else if(setCV==-2)  //ƽ��
			curves[curIdx]->translate(curPoint - curves[curIdx]->getCenter());
        else if(setCV==-3)  //��ת
			curves[curIdx]->setHandlePointByRef(curPoint);
	}
}
//��glwidget.cpp�У�ÿ������¼���ɺ�
//�������updateGL()�������Ӷ�����paitGL()����
//�Ӷ�����on
void CurveControl::onMarkDraw()
{
    if(!curVtxs.empty())        //4�����Ƶ㻹δ����
        for(Point &p:curVtxs)   //�����ǵ㣬������ǵ�
			p.markDraw();
                                //4�����Ƶ㻭����
    else if(curIdx>=0)          //���������ߣ�������ǵ�
		curves[curIdx]->markDraw();
}
void CurveControl::deleteCurve(int idx)
{
    Curve* curCurve = curves[idx];
   // for(vector<Curve*>::iterator it = curves.begin();it!=curves.end();it++)
   // {
    //    if(curCurve==*it)
    //    {
    //        curves.erase(it);
    //        break;
   //     }
   // }
    for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();it++)
    {
        if(curCurve==*it)
        {
            allFigures->erase(it);
            break;
        }
    }
    //delete curCurve;
    history->push_back(curCurve);
    //historyCurves.push(curCurve);
}
void CurveControl::onDelete()
{
    if(curIdx < 0)
        return;
    deleteCurve(curIdx);
    curIdx = -1;
}
//�����������
void CurveControl::onClear()
{
    for(Curve* curve : curves)
    {
        for(vector<Figure*>::iterator it=allFigures->begin();it!=allFigures->end();)
        {
            if(*it == curve)
                it = allFigures->erase(it);
            else
                it++;
        }
        delete curve;
    }
    curves.clear();
    curIdx = -1;
}
