#ifndef VIEW_HOME_WIDGET_H
#define VIEW_HOME_WIDGET_H

#include <QWidget>

namespace Ui {
class CHomeWidget;
}

class CHomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CHomeWidget(QWidget *parent = 0);
    ~CHomeWidget();

private:
    Ui::CHomeWidget *ui;
};

#endif // VIEW_HOME_WIDGET_H
