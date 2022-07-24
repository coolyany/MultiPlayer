#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QSplitter>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QScopedPointer>
#include <QStatusBar>
#include <QGridLayout>
#include <QStackedWidget>
#include <QWidget>
#include <QMessageBox>
#include <QTextEdit>
#include <QList>
#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,m_flag(ERROR)
{
    ui->setupUi(this);
    this->setWindowTitle("Split_Screen");
    show_1();
}

Widget::~Widget()
{
    for(int i = 0;i<list_layout.size();i++)
        delete list_layout[i];
    for(int i =0;i<list_widget.size();i++)
        delete list_widget[i];
    list_layout.clear();
    list_widget.clear();
    list_CreateWidget.clear();
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    ui->widget->setGeometry(0,size().height()-40,size().width(),40);
}

void Widget::show_1()
{
    if(m_flag == Widget::ONE)
            return ;
    if(m_flag)
    {
        for(int i = 0;i<list_layout.size();i++)
        {
            delete list_layout[i];
            list_layout[i] = nullptr;
        }
        for(int i = 0;i<list_widget.size();i++)
        {
            delete list_widget[i];
            list_widget[i] = nullptr;
        }
        list_layout.clear();
        list_widget.clear();
         list_CreateWidget.clear();
    }
    m_flag = Widget::ONE;
    QListWidget* listWidget = new QListWidget;
    listWidget->addItems(QStringList() << "One" << "Four" << "Six" << "Nine" << "Sixteen");
    QWidget* son_widget = new QWidget(this);
    son_widget->setAttribute(Qt::WA_StyledBackground);
    son_widget->setStyleSheet("background-color : rgb(96,96,96)");
    QGridLayout* g_layout = new QGridLayout(son_widget);
    for(int i =0;i<1;i++)
    {
        QListWidget* pListWidget = new QListWidget(son_widget);
        list_CreateWidget.push_back(pListWidget);
    }
    int count = 0;
    for(int i = 0;i < 1;i++)
    {
        for(int j = 0;j < 1;j++)
        {
            g_layout->addWidget(list_CreateWidget[count++],i,j,1,1);
        }
    }
    g_layout->setContentsMargins(0,0,0,0);
    g_layout->setSpacing(0);
    QHBoxLayout* h_main_layout = new QHBoxLayout(this);
    h_main_layout->setContentsMargins(0,0,0,40);
    h_main_layout->setSpacing(10);
    h_main_layout->addWidget(listWidget);
    h_main_layout->addWidget(son_widget);
    h_main_layout->setStretchFactor(listWidget,1);
    h_main_layout->setStretchFactor(son_widget,5);
    list_widget.push_back(listWidget);
    list_widget.push_back(son_widget);
    list_layout.push_back(h_main_layout);
}

void Widget::show_4()
{
    if(m_flag == Widget::FOUR)
            return ;
    //first, delete heap_memory
    if(m_flag)
    {
        for(int i = 0;i<list_layout.size();i++)
        {
            delete list_layout[i];
            list_layout[i] = nullptr;
        }
        for(int i = 0;i<list_widget.size();i++)
        {
            delete list_widget[i];
            list_widget[i] = nullptr;
        }
        list_layout.clear();
        list_widget.clear();
        list_CreateWidget.clear();
    }
    //flag
    m_flag = Widget::FOUR;
    //1. listWidget
    QListWidget* listWidget = new QListWidget;
    listWidget->addItems(QStringList() << "One" << "Four" << "Six" << "Nine" << "Sixteen");
    //2. son widget
    QWidget* son_widget = new QWidget(this);
    son_widget->setAttribute(Qt::WA_StyledBackground);
    son_widget->setStyleSheet("background-color : rgb(96,96,96)");
        //(1)create gride_layout
    QGridLayout* g_layout = new QGridLayout(son_widget);
        //(2)create son_listWidget for gride_layout
    for(int i = 0;i < 4;i++)
    {
        QListWidget* pListWidget = new QListWidget(son_widget);
        list_CreateWidget.push_back(pListWidget);
    }
        //(3)put son_listWidget in gride_layout
    int count = 0;
    for(int i = 0;i < 2;i++)
    {
        for(int j = 0;j < 2;j++)
        {
            g_layout->addWidget(list_CreateWidget[count++],i,j,1,1);
        }
    }
        //(4)set inner son_control's  distance
    g_layout->setContentsMargins(0,0,0,0);
    g_layout->setSpacing(0);
    //3. create h_main_layout and sieris set(use h_main_layout to containe listWidget and son_widget)
    QHBoxLayout* h_main_layout = new QHBoxLayout(this);
    h_main_layout->setContentsMargins(0,0,0,40);
    h_main_layout->setSpacing(10);                      //control son_control's space
    h_main_layout->addWidget(listWidget);
    h_main_layout->addWidget(son_widget);
    h_main_layout->setStretchFactor(listWidget,1);      //set the proportion for son_control's
    h_main_layout->setStretchFactor(son_widget,5);
    //4. collect discard_pointer
    list_widget.push_back(listWidget);
    list_widget.push_back(son_widget);
    list_layout.push_back(h_main_layout);
}


void Widget::show_6()
{
    if(m_flag == Widget::SIX)
            return ;
    if(m_flag)
    {
        for(int i = 0;i<list_layout.size();i++)
        {
            delete list_layout[i];
            list_layout[i] = nullptr;
        }
        for(int i = 0;i<list_widget.size();i++)
        {
            delete list_widget[i];
            list_widget[i] = nullptr;
        }
        list_layout.clear();
        list_widget.clear();
         list_CreateWidget.clear();
    }
    m_flag = Widget::SIX;
    QListWidget* listWidget = new QListWidget;
    listWidget->addItems(QStringList() << "One" << "Four" << "Six" << "Nine" << "Sixteen");
    QWidget* son_widget = new QWidget(this);
    son_widget->setAttribute(Qt::WA_StyledBackground);
    son_widget->setStyleSheet("background-color : rgb(96,96,96)");
    QGridLayout* g_layout = new QGridLayout(son_widget);
    for(int i =0;i<6;i++)
    {
        QListWidget* pListWidget = new QListWidget(son_widget);
        list_CreateWidget.push_back(pListWidget);
    }
    int count = 0;
    for(int i = 0;i < 2;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            g_layout->addWidget(list_CreateWidget[count++],i,j,1,1);
        }
    }
    g_layout->setContentsMargins(0,0,0,0);
    g_layout->setSpacing(0);
    QHBoxLayout* h_main_layout = new QHBoxLayout(this);
    h_main_layout->setContentsMargins(0,0,0,40);
    h_main_layout->setSpacing(10);
    h_main_layout->addWidget(listWidget);
    h_main_layout->addWidget(son_widget);
    h_main_layout->setStretchFactor(listWidget,1);
    h_main_layout->setStretchFactor(son_widget,5);
    list_widget.push_back(listWidget);
    list_widget.push_back(son_widget);
    list_layout.push_back(h_main_layout);
}

void Widget::show_9()
{
    if(m_flag == Widget::NINE)
            return ;
    if(m_flag)
    {
        for(int i = 0;i<list_layout.size();i++)
        {
            delete list_layout[i];
            list_layout[i] = nullptr;
        }
        for(int i = 0;i<list_widget.size();i++)
        {
            delete list_widget[i];
            list_widget[i] = nullptr;
        }
        list_layout.clear();
        list_widget.clear();
        list_CreateWidget.clear();
    }
    m_flag = Widget::NINE;
    QListWidget* listWidget = new QListWidget;
    listWidget->addItems(QStringList() << "One" << "Four" << "Six" << "Nine" << "Sixteen");
    QWidget* son_widget = new QWidget(this);
    son_widget->setAttribute(Qt::WA_StyledBackground);
    son_widget->setStyleSheet("background-color : rgb(96,96,96)");
    QGridLayout* g_layout = new QGridLayout(son_widget);
    for(int i =0;i<9;i++)
    {
        QListWidget* pListWidget = new QListWidget(son_widget);
        list_CreateWidget.push_back(pListWidget);
    }
    int count = 0;
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            g_layout->addWidget(list_CreateWidget[count++],i,j,1,1);
        }
    }
    g_layout->setContentsMargins(0,0,0,0);
    g_layout->setSpacing(0);
    QHBoxLayout* h_main_layout = new QHBoxLayout(this);
    h_main_layout->setContentsMargins(0,0,0,40);
    h_main_layout->setSpacing(10);
    h_main_layout->addWidget(listWidget);
    h_main_layout->addWidget(son_widget);
    h_main_layout->setStretchFactor(listWidget,1);
    h_main_layout->setStretchFactor(son_widget,5);
    list_widget.push_back(listWidget);
    list_widget.push_back(son_widget);
    list_layout.push_back(h_main_layout);
}

void Widget::show_16()
{
    if(m_flag == Widget::SIXTEEN)
            return ;
    if(m_flag)
    {
        for(int i = 0;i<list_layout.size();i++)
        {
            delete list_layout[i];
             list_layout[i] = nullptr;
        }
        for(int i = 0;i<list_widget.size();i++)
        {
            delete list_widget[i];
             list_widget[i] = nullptr;
        }
        list_layout.clear();
        list_widget.clear();
        list_CreateWidget.clear();
    }
    m_flag = Widget::SIXTEEN;
    QListWidget* listWidget = new QListWidget;
    listWidget->addItems(QStringList() << "One" << "Four" << "Six" << "Nine" << "Sixteen");
    QWidget* son_widget = new QWidget(this);
    son_widget->setAttribute(Qt::WA_StyledBackground);
    son_widget->setStyleSheet("background-color : rgb(96,96,96)");
    QGridLayout* g_layout = new QGridLayout(son_widget);
    for(int i =0;i<16;i++)
    {
        QListWidget* pListWidget = new QListWidget(son_widget);
        list_CreateWidget.push_back(pListWidget);
    }
    int count = 0;
    for(int i = 0;i<4;i++)
    {
        for(int j = 0;j<4;j++)
        {
            g_layout->addWidget(list_CreateWidget[count++],i,j,1,1);
        }
    }
    g_layout->setContentsMargins(0,0,0,0);
    g_layout->setSpacing(0);
    //
    QHBoxLayout* h_main_layout = new QHBoxLayout(this);
    h_main_layout->setContentsMargins(0,0,0,40);
    h_main_layout->setSpacing(10);
    h_main_layout->addWidget(listWidget);
    h_main_layout->addWidget(son_widget);
    h_main_layout->setStretchFactor(listWidget,1);
    h_main_layout->setStretchFactor(son_widget,5);
    //
    list_widget.push_back(listWidget);
    list_widget.push_back(son_widget);
    list_layout.push_back(h_main_layout);
}



