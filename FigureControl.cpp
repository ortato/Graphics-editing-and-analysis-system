#include "FigureControl.h"
FigureControl::FigureControl()
{
}
FigureControl::FigureControl(std::vector<Figure*>* figures, std::vector<Figure*>* history)
{
	allFigures = figures;
	this->history = history;
}
FigureControl::FigureControl(int width, int height)
{
	this->width = width;
	this->height = height;
}
FigureControl::FigureControl(std::vector<Figure*>* figures, int width, int height)
{
	allFigures = figures;
	this->width = width;
	this->height = height;
}
void FigureControl::resize(int width, int height)
{
	this->width = width;
	this->height = height;
}
void FigureControl::onUndo()
{
}
bool FigureControl::setFocus(Figure* fg)
{
	cout << "not finish!" << endl;
	return false;
}
void FigureControl::onMousePressEvent(QMouseEvent* event)
{
}
void FigureControl::onMouseMoveEvent(QMouseEvent* event)
{
}
void FigureControl::onMousePassiveMoveEvent(QMouseEvent* event)
{
}
void FigureControl::onDraw()
{
}
void FigureControl::onMarkDraw()
{
}
void FigureControl::onDelete()
{
}
void FigureControl::onClear()
{
}
void FigureControl::pushForward(Figure* figure)
{
	for (vector<Figure*>::iterator it = allFigures->begin();
		it != allFigures->end();
		it++)
	{
		if (*it == figure) //��������ͼ�Σ�����ǰѡ�е�ͼ��ɾ��
		{
			allFigures->erase(it);
			break;
		}
	}
	allFigures->push_back(figure);  //����ǰѡ�е�ͼ�η��������
}
void FigureControl::onFill()
{
}