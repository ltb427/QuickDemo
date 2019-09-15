#ifndef COLORMAKER_H
#define COLORMAKER_H

#include <QObject>
#include <QColor>
#include <QTimerEvent>

class ColorMaker : public QObject
{
    Q_OBJECT
    //  如果你要导出的类定义了想在 QML 中使用枚举类型，可以使用 Q_ENUMS 宏将该枚举注册到元对象系统中。
    Q_ENUMS(generate)
    //Q_PROPERTY 宏用来定义可通过元对象系统访问的属性，通过它定义的属性，可以在 QML 中访问、修改，也可以在属性变化时发射特定的信号。
    //READ   声明一个读取属性的函数，该函数一般没有参数，返回定义的属性。
    //WRITE  [可选]声明一个设定属性的函数。它指定的函数，只能有一个与属性类型匹配的参数，必须返回 void 。
    //NOTIFY [可选]给属性关联一个信号（该信号必须是已经在类中声明过的），当属性的值发生变化时就会触发该信号。信号的参数，一般就是你定义的属性。
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor timeColor READ timeColor )

public:
    explicit ColorMaker(QObject *parent = nullptr);

    //枚举该变量 （5中颜色的算法）
    enum generate{
        randomRGB,
        randomRed,
        randomGreen,
        randomBlue,
        increase  //（颜色变化算法为）直线增长模式
    };

    QColor color() const;
    void setColor(const QColor &color);
    QColor timeColor() const;

    //在定义一个类的成员函数时使用 Q_INVOKABLE 宏来修饰，就可以让该方法被元对象系统调用。这个宏必须放在返回类型前面。
    Q_INVOKABLE generate algorithm() const;              //返回类型为枚举类型GenerateAlgorithm;  这是一个算法函数
    Q_INVOKABLE void setAlgouthm(generate algorithm);    //设置为具体使用哪一个颜色的算法

signals:
    //定义colorChanged() / currentTime() 两个信号
    void colorChanged(const QColor &color);              //颜色改变的信号
    void currentTimer(const QString &strTime);           //当前时间的信号

public slots:
    //定义了 start() / stop() 两个槽
    void start();
    void stop();

protected:
    void timerEvent(QTimerEvent *event);                 //时间事件

private:
    generate myGenerate;   //具体使用的哪一种算法
    QColor myColor;        //现在的颜色
    int colorTimer;        //定时器的ID
};

#endif // COLORMAKER_H






