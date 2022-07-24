#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QLayout>
#include <QListWidget>
#define ERROR 0

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void resizeEvent(QResizeEvent *event) override;
public slots:
    void show_1();
    void show_4();
    void show_6();
    void show_9();
    void show_16();
private:
    Ui::Widget *ui;
    QList<QLayout*> list_layout ;
    QList<QWidget*> list_widget;
    QList<QListWidget*> list_CreateWidget;
    enum {
        ONE = 0x01,
        FOUR,
        SIX,
        NINE,
        SIXTEEN
    };
    int m_flag;
    QWidget* m_pWidget = nullptr;
};
#endif // WIDGET_H
