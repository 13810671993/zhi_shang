#ifndef VIEW_MAIN_WIDGET_H
#define VIEW_MAIN_WIDGET_H

#include <QWidget>
#include "network/network_common.h"

namespace Ui {
class CMainWidget;
}

class CMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CMainWidget(CNetwork* pNetwork, QWidget *parent = 0);
    ~CMainWidget();

public slots:
    void DoShowRecvMessage(QString qstrMessage);
    void DoGetSendMessage();
    void DoCloseMainWidget();

private:
    void BindSignals();

private:
    Ui::CMainWidget *ui;
    CNetwork*	m_pNetwork;
};

#endif // VIEW_MAIN_WIDGET_H
