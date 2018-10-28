#include "mainwindow.h"
#include <common.h>
#include <QToolBar>
#include <QColorDialog>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QToolButton>
#include <QDebug>
#include <QLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    centerFrame = new CenterFrame;   //新建CenterFrame对象
    setCentralWidget (centerFrame);  //新建的centerFrame->insideWidget()对象作为主窗口的中央窗口
    createToolBar ();                //创建一个工具栏
    setMinimumSize (600, 400);       //设置主窗体的最小尺寸
    setWindowTitle(tr("实验二 - 窗口、控件及基本绘图实验 "));

    penStyleChangged(styleComboBox->currentData().toInt());      //初始化线型，设置控件中当前值作为初始值

    centerFrame->setPenWidth (widthSpinBox->value ());           //设置初始线宽
    centerFrame->setPenColor (FOREGROUND_COLOR);                 //设置初始颜色
}

MainWindow::~MainWindow()
{
}

void MainWindow::createToolBar ()
{
    QToolBar *toolBar = addToolBar (tr("Tool"));   //为主窗口创建一个工具栏对象
    styleLabel = new QLabel(tr("线型"));
    styleComboBox = new QComboBox;// 线型选择下拉框
    styleComboBox->setToolTip(tr("选择画笔线型"));    //设置提示
    // 此处在下拉框的每个项目里，设置了一个item的userData，
    // 该用户数据作为用户选择的标志
    styleComboBox->addItem (tr("实线(SolidLine)"), static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem (tr("虚线(DashLine)"), static_cast<int>(Qt::DashLine));
    styleComboBox->addItem (tr("点线(DotLine)"), static_cast<int>(Qt::DotLine));
    styleComboBox->addItem (tr("点划线(DashDotLine)"), static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem (tr("连点划线(DashDotDotLine)"), static_cast<int>(Qt::DashDotDotLine));
    connect (styleComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
             this, &MainWindow::penStyleChangged);
    styleComboBox->setCurrentIndex(1);


    // 线宽选择框
    widthLabel = new QLabel(tr("线宽"));
    widthSpinBox = new QSpinBox;
    widthSpinBox->setToolTip(tr("选择画笔线宽"));
    widthSpinBox->setRange(1,50);        //线宽范围
    connect (widthSpinBox, static_cast<void(QSpinBox::*)(int )>(&QSpinBox::valueChanged),
             centerFrame, &CenterFrame::setPenWidth);
    widthSpinBox->setValue(1);//如果新值与旧值不同，则此属性保存旋转框的值

    // 颜色选择框
    colorBtn = new QToolButton;
    QPixmap pixmap(20, 20);
    pixmap.fill (FOREGROUND_COLOR);
    colorBtn->setIcon (QIcon(pixmap));     //设置图标icon
    colorBtn->setToolTip(tr("选择画笔颜色"));
    connect (colorBtn, &QToolButton::clicked, this, &MainWindow::penColorChangged);


    // 创建清除工具栏
    clearBtn = new QToolButton;
    clearBtn->setText (tr("清除"));
    clearBtn->setToolTip(tr("清除当前画板"));
    connect (clearBtn, &QToolButton::clicked, centerFrame, &CenterFrame::clearPaint);
    pictureBtn = new QToolButton;
//    QIcon icon;
//    icon.addFile(tr(":/pic/1.jpg"));
//    pictureBtn->setIcon(icon);
//    connect (pictureBtn, &QToolButton::clicked, centerFrame, &CenterFrame::draw);

    // 向工具栏上添加各个控件
    toolBar->addWidget (styleLabel);
    toolBar->addWidget (styleComboBox);
    toolBar->addWidget (widthLabel);
    toolBar->addWidget (widthSpinBox);
    toolBar->addWidget (colorBtn);
    toolBar->addSeparator();
    toolBar->addWidget (clearBtn);
    toolBar->addWidget(pictureBtn);

}

void MainWindow::penStyleChangged (int index)
{
    Q_UNUSED(index)   //向编译器指示具有指定名称的参数未在函数体中使用
    centerFrame->setPenStyle(styleComboBox->currentData().toInt ());
}

void MainWindow::penColorChangged ()
{/*弹出具有给定窗口标题的模态颜色对话框（如果没有指定，则弹出“选择颜色”），让用户选择颜色，
  然后返回该颜色。颜色最初设置为初始颜色*/
    QColor color = QColorDialog::getColor (static_cast<int>(FOREGROUND_COLOR),
                                           this,
                                           tr("选取画笔颜色"));

    //判断颜色是否有效,有效则设置钢笔颜色，并修改颜色按钮的图标
    if(color.isValid ())
    {
        centerFrame->setPenColor (color);
        QPixmap p(20, 20);
        p.fill (color);
        colorBtn->setIcon (QIcon(p));
    }
}

