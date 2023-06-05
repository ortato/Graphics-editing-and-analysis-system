#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
QT_BEGIN_NAMESPACE
class Ui_MainWindow
{
public:
    QAction* actionNew;
    QAction* actionCurve;
    QAction* actionOpen;
    QAction* actionSave;
    QAction* actionCircle;
    QAction* actionEllipse;
    QAction* actionLine;
    QAction* actionColor;
    QAction* actionDelete;
    QAction* actionClear;
    QAction* actionFill;
    QAction* actionUndo;
    QAction* actionwidth_1;
    QAction* actionwidth_2;
    QAction* actionwidth_3;
    QAction* actionwidth_5;
    QAction* actionPen;
    QAction* actionRectangle;
    QWidget* centralwidget;
    QMdiArea* mdiArea;
    QMenuBar* menubar;
    QMenu* menuCurve;
    QMenu* menu;
    QStatusBar* statusbar;
    QToolBar* toolBar;
    void setupUi(QMainWindow* MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionCurve = new QAction(MainWindow);
        actionCurve->setObjectName(QStringLiteral("actionCurve"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionCircle = new QAction(MainWindow);
        actionCircle->setObjectName(QStringLiteral("actionCircle"));
        actionEllipse = new QAction(MainWindow);
        actionEllipse->setObjectName(QStringLiteral("actionEllipse"));
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QStringLiteral("actionLine"));
        actionColor = new QAction(MainWindow);
        actionColor->setObjectName(QStringLiteral("actionColor"));
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionFill = new QAction(MainWindow);
        actionFill->setObjectName(QStringLiteral("actionFill"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionwidth_1 = new QAction(MainWindow);
        actionwidth_1->setObjectName(QStringLiteral("actionwidth_1"));
        actionwidth_2 = new QAction(MainWindow);
        actionwidth_2->setObjectName(QStringLiteral("actionwidth_2"));
        actionwidth_3 = new QAction(MainWindow);
        actionwidth_3->setObjectName(QStringLiteral("actionwidth_3"));
        actionwidth_5 = new QAction(MainWindow);
        actionwidth_5->setObjectName(QStringLiteral("actionwidth_5"));
        actionPen = new QAction(MainWindow);
        actionPen->setObjectName(QStringLiteral("actionPen"));
        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QStringLiteral("actionRectangle"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setGeometry(QRect(280, 150, 245, 160));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuCurve = new QMenu(menubar);
        menuCurve->setObjectName(QStringLiteral("menuCurve"));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar->addAction(menuCurve->menuAction());
        menubar->addAction(menu->menuAction());
        menuCurve->addAction(actionNew);
        menuCurve->addAction(actionOpen);
        menuCurve->addAction(actionSave);
        menu->addAction(actionwidth_1);
        menu->addAction(actionwidth_2);
        menu->addAction(actionwidth_3);
        menu->addAction(actionwidth_5);
        toolBar->addSeparator();
        toolBar->addAction(actionLine);
        toolBar->addAction(actionRectangle);
        toolBar->addAction(actionCircle);
        toolBar->addAction(actionEllipse);
        toolBar->addAction(actionCurve);
        toolBar->addAction(actionPen);
        toolBar->addSeparator();
        toolBar->addAction(actionColor);
        toolBar->addSeparator();
        toolBar->addAction(actionDelete);
        toolBar->addAction(actionClear);
        toolBar->addAction(actionFill);
        toolBar->addAction(actionUndo);
        retranslateUi(MainWindow);
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi
    void retranslateUi(QMainWindow* MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionNew->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", Q_NULLPTR));
        actionCurve->setText(QApplication::translate("MainWindow", "\346\233\262\347\272\277", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCurve->setToolTip(QApplication::translate("MainWindow", "\346\233\262\347\272\277", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        actionCircle->setText(QApplication::translate("MainWindow", "\345\234\206", Q_NULLPTR));
        actionEllipse->setText(QApplication::translate("MainWindow", "\346\244\255\345\234\206", Q_NULLPTR));
        actionLine->setText(QApplication::translate("MainWindow", "\347\233\264\347\272\277", Q_NULLPTR));
        actionColor->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262", Q_NULLPTR));
        actionDelete->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\275\223\345\211\215\345\233\276\345\275\242", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionClear->setText(QApplication::translate("MainWindow", "\346\270\205\351\231\244", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionClear->setToolTip(QApplication::translate("MainWindow", "\346\270\205\351\231\244\346\211\200\346\234\211\345\233\276\345\275\242", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFill->setText(QApplication::translate("MainWindow", "\345\241\253\345\205\205", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionFill->setToolTip(QApplication::translate("MainWindow", "\344\270\272\345\233\276\345\275\242\345\241\253\345\205\205\351\242\234\350\211\262", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionUndo->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", Q_NULLPTR));
        actionwidth_1->setText(QApplication::translate("MainWindow", "width=1", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionwidth_1->setToolTip(QApplication::translate("MainWindow", "\345\256\275\345\272\246\344\270\2721", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionwidth_2->setText(QApplication::translate("MainWindow", "width=2", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionwidth_2->setToolTip(QApplication::translate("MainWindow", "\345\256\275\345\272\246\344\270\2722", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionwidth_3->setText(QApplication::translate("MainWindow", "width=3", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionwidth_3->setToolTip(QApplication::translate("MainWindow", "\345\256\275\345\272\246\344\270\2723", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionwidth_5->setText(QApplication::translate("MainWindow", "width=5", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionwidth_5->setToolTip(QApplication::translate("MainWindow", "\345\256\275\345\272\246\344\270\2725", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionPen->setText(QApplication::translate("MainWindow", "\347\224\273\347\254\224", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionPen->setToolTip(QApplication::translate("MainWindow", "\347\224\273\347\254\224\357\274\214\346\266\202\351\270\246\347\254\224", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionRectangle->setText(QApplication::translate("MainWindow", "\347\237\251\345\275\242", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRectangle->setToolTip(QApplication::translate("MainWindow", "\347\237\251\345\275\242", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        menuCurve->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\347\272\277\345\256\275", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi
};
namespace Ui {
    class MainWindow : public Ui_MainWindow {};
} // namespace Ui
QT_END_NAMESPACE
#endif // UI_MAINWINDOW_H