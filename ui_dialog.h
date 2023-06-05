#ifndef UI_DIALOG_H
#define UI_DIALOG_H
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
QT_BEGIN_NAMESPACE
class Ui_Dialog
{
public:
    QLabel* label;
    void setupUi(QDialog* Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(542, 387);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 491, 351));
        retranslateUi(Dialog);
        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi
    void retranslateUi(QDialog* Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "label", Q_NULLPTR));
    } // retranslateUi
};
namespace Ui {
    class Dialog : public Ui_Dialog {};
} // namespace Ui
QT_END_NAMESPACE
#endif // UI_DIALOG_H