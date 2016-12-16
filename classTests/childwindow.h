#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <QWidget>

class ChildWindow : public QWidget
{
    Q_OBJECT
public:
    ChildWindow(QWidget *widget=0);
};

#endif // CHILDWINDOW_H
