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
    setMouseTracking(true); //������꣬���շǵ������ƶ��¼�
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
    BITMAPFILEHEADER bmfh;  //λͼ�ļ�ͷ
    BITMAPINFOHEADER bmih;  //λͼ��Ϣͷ
    bmfh.bfType = 'MB';       //ָ���ļ����ͣ�����.bmp�ļ���ͷ�����ֽڶ��ǡ�BM��
    bmfh.bfReserved1 = 0;     //�����֣����ÿ���
    bmfh.bfReserved2 = 0;     //�����֣����ÿ���
    bmfh.bfOffBits = 54;      //Ϊ���ļ�ͷ��ʵ�ʵ�λͼ���ݵ�ƫ���ֽ���
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
    bmih.biSize = 40;                 //�ṹ�ĳ���
    bmih.biWidth = viewPort[2];       //ָ��ͼ��Ŀ�ȣ���λ������
    bmih.biHeight = viewPort[3];      //ָ��ͼ��ĸ߶ȣ���λ������
    bmih.biPlanes = 1;                //������1�����ÿ���
    bmih.biBitCount = 24;             //ָ����ʾ��ɫʱҪ�õ���λ�������õ�ֵΪ1(�ڰ׶�ɫͼ), 4(16ɫͼ), 8(256ɫ), 24(���ɫͼ)
    bmih.biCompression = 0;           //ָ��λͼ�Ƿ�ѹ��
    bmih.biSizeImage = imageSize;     //ָ��ʵ�ʵ�λͼ����ռ�õ��ֽ���
    bmih.biXPelsPerMeter = 45089;     //ָ��Ŀ���豸��ˮƽ�ֱ���
    bmih.biYPelsPerMeter = 45089;     //ָ��Ŀ���豸�Ĵ�ֱ�ֱ���
    bmih.biClrUsed = 0;               //ָ����ͼ��ʵ���õ�����ɫ���������ֵΪ�㣬���õ�����ɫ��Ϊ2^biBitCount
    bmih.biClrImportant = 0;          //ָ����ͼ������Ҫ����ɫ���������ֵΪ�㣬����Ϊ���е���ɫ������Ҫ��
    fwrite(&bmfh, sizeof(bmfh), 1, file);
    fwrite(&bmih, sizeof(bmih), 1, file);
    fwrite(data, imageSize, 1, file);
    free(data);
    fclose(file);
}
void GLWidget::initializeGL()
{
    //����widget������ͳߴ�
    setGeometry(700, 400, 800, 500);//�丸���ھ�����Ļ
    //�������ʱ��ɫ
    glClearColor(1.0, 1.0, 1.0, 0);
}
void GLWidget::resizeGL(int w, int h)
{
    //ͶӰ�任
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)w, 0.0, (double)h);
    //��ͼ�任
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //����FigureControl
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
//��������
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
//ʵ�ʿ�ʼ��ͼ�����ϲ�
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);//����
    for (Figure* figure : allFigures)
        figure->draw();                     //���е�ͼ���ϵĵ㶼������
    figureControls[curCtrl]->onMarkDraw();  //���е�ͼ�α�ǵ㶼������
}
void GLWidget::mousePressEvent(QMouseEvent* event)
{
    //ͨ������������ĵ��λ�������õ�ǰ�۽���ͼ��
    setFocusByPoint(Point(event->x(), height() - event->y()));
    figureControls[curCtrl]->onMousePressEvent(event);//���þ۽���ͼ�εĿ��ƺ���
    updateGL(); //ʵ���ϵ����� paintGL()
}
void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)   //���1,��갴�����ƶ�
        figureControls[curCtrl]->onMouseMoveEvent(event);
    else                                    //���2,���������ƶ�
        figureControls[curCtrl]->onMousePassiveMoveEvent(event);
    updateGL();
}
//���ݵ����ж����ĸ�ͼ��
Figure* GLWidget::setFocusByPoint(const Point& p)
{
    for (int i = allFigures.size() - 1; i >= 0; i--)//�������е�ͼ��
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

