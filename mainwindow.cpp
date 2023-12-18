#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "childwnd.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    // 初始化字号列表项
    QFontDatabase fontdb;
    foreach(int fontsize, fontdb.standardSizes())
    {
        ui->sizeComboBox->addItem(QString::number(fontsize));
    }

    QFont defFont;      // 当前应用程序默认的字体
    QString sFontSize;
    int defFontSize;   // 当前应用程序默认字体的字号
    int defFontindex;   // 当前字号在组合框中的索引好

    defFont = QApplication::font();
    defFontSize = defFont.pointSize();
    sFontSize = QString::number(defFontSize);
    defFontindex = ui->sizeComboBox->findText(sFontSize);

    ui->sizeComboBox->setCurrentIndex(defFontindex);
}

void MainWindow::docNew()
{
    ChildWnd *childwnd = new ChildWnd;
    ui->mdiArea->addSubWindow(childwnd);
    connect(childwnd,SIGNAL(copyAvailable(bool)),ui->cutAction,SLOT(setEnabled(bool)));
    connect(childwnd,SIGNAL(copyAvailable(bool)),ui->copyAction,SLOT(setEnabled(bool)));

    childwnd->newDoc();
    childwnd->show();
}

void MainWindow::formatEnabled()
{
    ui->boldAction->setEnabled(true);
    ui->italicAction->setEnabled(true);
    ui->underlineAction->setEnabled(true);
    ui->leftAlignAction->setEnabled(true);
    ui->centerAction->setEnabled(true);
    ui->rightAlignAction->setEnabled(true);
    ui->justifyAction->setEnabled(true);
    ui->colorAction->setEnabled(true);
}


void MainWindow::on_newAction_triggered()
{
    docNew();
}

