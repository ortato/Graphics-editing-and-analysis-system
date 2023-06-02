#include "LineControl.h"
LineControl::LineControl()
{
	curLine = NULL;
}
LineControl::LineControl(std::vector<Figure*>* figures, std::vector<Figure*>* history)
	:FigureControl(figures, history)
{
	curLine = NULL;
}
LineControl::LineControl(int width, int height) : FigureControl(width, height)
{
	curLine = NULL;
}
LineControl::LineControl(std::vector<Figure*>* figures, int width, int height) : FigureControl(figures, width, height)
{
	curLine = NULL;
}
bool LineControl::setFocus(Figure* fg)
{
	for (Line* line : lines)
		if (line == fg)
		{
			curLine = line;
			return true;
		}
	return false;
}
void LineControl::onUndo()
{
}
void LineControl::onMousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (curLine != NULL)
		{
			Point curPoint(event->x(), height - event->y());
			if (curLine->getBeginPoint().distanceTo(curPoint) <= 5)    //�ı���ʼ��
			{
				setLP = SETBEGIN;
				pushForward(curLine);
				return;
			}
			else if (curLine->getEndPoint().distanceTo(curPoint) <= 5) //�ı��յ�
			{
				setLP = SETEND;
				pushForward(curLine);
				return;
			}
			else if (curLine->getCenterPoint().distanceTo(curPoint) <= 5)//�ı����ĵ�
			{
				setLP = SETCENTER;
				pushForward(curLine);
				return;
			}
			else if (curLine->getHandlePoint().distanceTo(curPoint) <= 5)//�ı���ֵ�
			{
				setLP = SETHANDLE;
				pushForward(curLine);
				return;
			}
			else if (curLine->isOn(curPoint))
			{
				pushForward(curLine);
				return;
			}
		}
		curLine = new Line(Point(event->x(), height - event->y()), Point(event->x(), height - event->y()));
		lines.push_back(curLine);
		allFigures->push_back(curLine);
		setLP = SETEND;
	}
}
void LineControl::onMouseMoveEvent(QMouseEvent* event)
{
	if (curLine == NULL)
		return;
	Point curPoint(event->x(), height - event->y());
	switch (setLP)
	{
	case SETBEGIN: curLine->setBeginPoint(curPoint); break;
	case SETEND: curLine->setEndPoint(curPoint); break;
	case SETCENTER: curLine->translate(curPoint - curLine->getCenterPoint()); break;
		//    case SETHANDLE: curLine->setHandlePointByRef(curPoint); break;    //�����
	default:;
	}
}
void LineControl::onDraw()
{
	for (Line* line : lines)
		line->draw();
}
void LineControl::onMarkDraw()
{
	if (curLine != NULL)
		curLine->markDraw();
}
void LineControl::onDelete() //ɾ��
{
	if (curLine == NULL)
		return;
	for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end(); it++)
	{
		if (curLine == *it)
		{
			allFigures->erase(it);
			break;
		}
	}
	//delete curLine;
	history->push_back(curLine);
	//historyLines.push(curLine);
	curLine = NULL;
}
void LineControl::onClear()  //���
{
	for (Line* line : lines)
	{
		for (vector<Figure*>::iterator it = allFigures->begin(); it != allFigures->end();)
		{
			if (line == *it)
				it = allFigures->erase(it);
			else
				it++;
		}
		delete line;
	}
	lines.clear();
	curLine = NULL;
}