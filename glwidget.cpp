#include "glwidget.h"
GLWidget::GLWidget(QWidget* parent, Mode m) :QGLWidget(parent)
{
    figureControls.push_back(new LineControl(&allFigures, &history));
    figureControls.push_back(new CircleControl(&allFigures, &history));
    figureControls.push_back(new EllipseControl(&allFigures, &history));
    figureControls.push_back(new CurveControl(&allFigures, &history));
    figureControls.push_back(new myPenControl(&allFigures, &history));
    figureControls.push_back(new RectangularControl(&allFigures, &history));
    setMode(m);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true); //跟踪鼠标，接收非点击鼠标移动事件
}
GLWidget::~GLWidget()
{
}
void GLWidget::setMode(Mode m)
{
    curCtrl = m;
    updateGL();
}
void GLWidget::onOpen()
{
}
void GLWidget::onSave(string fileName)
{
    FILE* file;
    unsigned long imageSize;
    GLbyte* data = NULL;
    GLint viewPort[4];
    GLenum lastBuffer;
    BITMAPFILEHEADER bmfh;  //位图文件头
    BITMAPINFOHEADER bmih;  //位图信息头
    bmfh.bfType = 'MB';       //指定文件类型，所有.bmp文件的头两个字节都是“BM”
    bmfh.bfReserved1 = 0;     //保留字，不用考虑
    bmfh.bfReserved2 = 0;     //保留字，不用考虑
    bmfh.bfOffBits = 54;      //为从文件头到实际的位图数据的偏移字节数
    glGetIntegerv(GL_VIEWPORT, viewPort);
    imageSize = ((viewPort[2] + ((4 - (viewPort[2] % 4)) % 4)) * viewPort[3] * 3) + 2;
    bmfh.bfSize = imageSize + sizeof(bmfh) + sizeof(bmih);
    data = (GLbyte*)malloc(imageSize);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_PACK_SWAP_BYTES, 1);
    glGetIntegerv(GL_READ_BUFFER, (GLint*)&lastBuffer);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, viewPort[2], viewPort[3], GL_BGR, GL_UNSIGNED_BYTE, data);
    data[imageSize - 1] = 0;
    data[imageSize - 2] = 0;
    glReadBuffer(lastBuffer);
    file = fopen(fileName.c_str(), "wb");
    bmih.biSize = 40;                 //结构的长度
    bmih.biWidth = viewPort[2];       //指定图象的宽度，单位是象素
    bmih.biHeight = viewPort[3];      //指定图象的高度，单位是象素
    bmih.biPlanes = 1;                //必须是1，不用考虑
    bmih.biBitCount = 24;             //指定表示颜色时要用到的位数，常用的值为1(黑白二色图), 4(16色图), 8(256色), 24(真彩色图)
    bmih.biCompression = 0;           //指定位图是否压缩
    bmih.biSizeImage = imageSize;     //指定实际的位图数据占用的字节数
    bmih.biXPelsPerMeter = 45089;     //指定目标设备的水平分辨率
    bmih.biYPelsPerMeter = 45089;     //指定目标设备的垂直分辨率
    bmih.biClrUsed = 0;               //指定本图象实际用到的颜色数，如果该值为零，则用到的颜色数为2^biBitCount
    bmih.biClrImportant = 0;          //指定本图象中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的
    fwrite(&bmfh, sizeof(bmfh), 1, file);
    fwrite(&bmih, sizeof(bmih), 1, file);
    fwrite(data, imageSize, 1, file);
    free(data);
    fclose(file);
}
void GLWidget::initializeGL()
{
    //设置widget的坐标和尺寸
    setGeometry(700, 400, 800, 500);//其父窗口就是屏幕
    //设置清除时颜色
    glClearColor(1.0, 1.0, 1.0, 0);
}
void GLWidget::resizeGL(int w, int h)
{
    //投影变换
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)w, 0.0, (double)h);
    //视图变换
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //设置FigureControl
    for (FigureControl* figureControl : figureControls)
        figureControl->resize(w, h);
}
void GLWidget::onDelete()
{
    figureControls[curCtrl]->onDelete();
    updateGL();
}
void GLWidget::onClear()
{
    figureControls[LINE]->onClear();
    figureControls[CIRCLE]->onClear();
    figureControls[ELLIPSE]->onClear();
    figureControls[CURVE]->onClear();
    figureControls[PEN]->onClear();
    figureControls[RECTANGLE]->onClear();
    // allFigures.clear();
    updateGL();
}
void GLWidget::onFill()
{
    figureControls[curCtrl]->onFill();
    updateGL();
}
//撤销操作
void GLWidget::undo()
{
    if (!history.empty())
    {
        allFigures.push_back(history.back());
        history.pop_back();
        updateGL();
        return;
    }
}
//实际开始画图，最上层
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);//清屏
    for (Figure* figure : allFigures)
        figure->draw();                     //所有的图形上的点都画出来
    figureControls[curCtrl]->onMarkDraw();  //所有的图形标记点都画出来
}
void GLWidget::mousePressEvent(QMouseEvent* event)
{
    //通过点击鼠标产生的点的位置来设置当前聚焦的图形
    setFocusByPoint(Point(event->x(), height() - event->y()));
    figureControls[curCtrl]->onMousePressEvent(event);//调用聚焦的图形的控制函数
    updateGL(); //实际上调用了 paintGL()
}
void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)   //情况1,鼠标按下且移动
        figureControls[curCtrl]->onMouseMoveEvent(event);
    else                                    //情况2,鼠标仅仅是移动
        figureControls[curCtrl]->onMousePassiveMoveEvent(event);
    updateGL();
}
//根据点来判断是哪个图形
Figure* GLWidget::setFocusByPoint(const Point& p)
{
    for (int i = allFigures.size() - 1; i >= 0; i--)//遍历所有的图形
    {
        if ((i == allFigures.size() - 1) ? (allFigures[i]->isOn(p)) : (allFigures[i]->isOnPlain(p)))
        {
            for (int j = 0; j < figureControls.size(); j++)
            {
                if (figureControls[j]->setFocus(allFigures[i]))
                {
                    curCtrl = j;
                    emit changeMode(Mode(curCtrl));
                    break;
                }
            }
            return allFigures[i];
        }
    }
    return NULL;
}

