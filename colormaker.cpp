#include "colormaker.h"
#include <QDateTime>
#include <QColor>

ColorMaker::ColorMaker(QObject *parent)
    : QObject(parent)
    , myGenerate(randomRGB)   //初始化一个随机的颜色算法
    , myColor(Qt::black)      //初始化赋值为黑色
    , colorTimer(0)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
}

//单纯的调用该函数, 确定设置颜色顺便会发射颜色改变的信号
QColor ColorMaker::color() const
{
    return myColor;
}

//颜色由当前时间作为参数来生成
void ColorMaker::setColor(const QColor &color)
{
    myColor = color;
    emit colorChanged(myColor);
}

//颜色由当前时间作为参数来生成
QColor ColorMaker::timeColor() const
{
    QTime time = QTime::currentTime();    //获取当前现在的时间
    int r = time.hour();
    int g = time.minute();
    int b = time.second();
    return QColor::fromRgb(r, g, b);
}

//传送出去一个（算法）的值 [确定是使用哪一种算法，RGB? Green? Red? Blue? ]
ColorMaker::generate ColorMaker::algorithm() const
{
    return myGenerate;
}

//赋值给类成员
void ColorMaker::setAlgouthm(ColorMaker::generate algorithm)
{
    myGenerate = algorithm;
}

//启动时间
void ColorMaker::start()
{
    if(colorTimer == 0)
    {
        colorTimer = startTimer(1000);
    }
}

//停止计时器的使用
void ColorMaker::stop()
{
    if(colorTimer > 0)
    {
        killTimer(colorTimer);    //终止计时器，销毁
        colorTimer = 0;
    }
}


//timerEvent事件消息
void ColorMaker::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == colorTimer)
    {
        switch (myGenerate) {
        case randomRGB:
            myColor.setRgb(qrand()%255, qrand()%255, qrand()%255);
            break;
        case randomRed:
            myColor.setRed(qrand()%255);
            break;
        case randomGreen:
            myColor.setGreen(qrand()%255);
            break;
        case randomBlue:
            myColor.setBlue(qrand()%255);
            break;
        default:
        {
            int r = myColor.red() + 10;
            int g = myColor.green() + 10;
            int b = myColor.blue() + 10;
            myColor.setRgb(r%255, g%255, b%255);
        }
            break;
        }

        //发射这两个信号
        emit colorChanged(myColor);
        emit currentTimer(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    else
    {
        timerEvent(event);
    }
}
