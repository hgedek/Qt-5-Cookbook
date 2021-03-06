#ifndef ORIENTABLETOOLBUTTON_H
#define ORIENTABLETOOLBUTTON_H

#include <QToolButton>

class OrientableToolButton : public QToolButton
{
   Q_OBJECT

public:
   explicit OrientableToolButton(const QIcon &icon = QIcon {},
                                 const QString &text = QString {},
                                 QWidget *parent = nullptr);

   QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
   void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
   void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // ORIENTABLETOOLBUTTON_H
