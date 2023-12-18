#include "childwnd.h"
#include <QFileInfo>

ChildWnd::ChildWnd()
{
    // 子窗口关闭时销毁该类的实例对象
    setAttribute(Qt::WA_DeleteOnClose);

    m_bSaved = false;
}

void ChildWnd::newDoc()
{
    static int wndSeqNum = 1;
    m_CurDocPath = QString("WPS 文档 %1")
                       .arg(wndSeqNum++);

    // 设置窗体标题，文档改动后名称后加"*"号标识
    setWindowTitle(m_CurDocPath + "[*]" + "- MyWPS");
    connect(document(),SIGNAL(contentsChanged()),this,SLOT(docBeModified()));
}

QString ChildWnd::getCurDocName()
{
    return QFileInfo(m_CurDocPath).fileName();
}

void ChildWnd::docBeModified()
{
    setWindowModified(document()->isModified());
}
