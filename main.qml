import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.0 //控制版本
import QtQuick.Layouts 1.0 //布局版本
import qt.an.colormaker 1.0 //倒入自定的C++类，这是其自定义的包名和主、次版本号

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML/C++混编")

    Text {
        id: timeLabel;
        anchors.top: parent.top;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.pixelSize: 40;
    }

    //在这里调用了C++类, 创建了一个介意供qml使用的C++对象
       ColorMaker {
           id: colorMaker;
       }

       //中间显示颜色变化的矩形
       Rectangle {
           id:colorRect;
           anchors.centerIn: parent;
           width: 300;
           height: 300;
           color: "Green";
       }

       //开始按钮
       Button {
           id: start;
           text: "start";
           anchors.left: parent.left;
           anchors.bottom: parent.bottom;
           anchors.leftMargin: 4;
           anchors.bottomMargin: 4;
           onClicked: {
               colorMaker.start();
           }
       }

       //结束按钮
       Button {
           id: stop;
           text: "stop";
           anchors.left: start.right;
           anchors.bottom: parent.bottom;
           anchors.leftMargin: 4;
           anchors.bottomMargin: 4;
           onClicked: {
               colorMaker.stop();
           }
       }

       //Javascript函数
       function changetAlgorithm(button, algorithm) {
           switch(algorithm)
           {
           case 0:
               button.text = "RGB";
               break;
           case 1:
               button.text = "Red";
               break;
           case 2:
               button.text = "Green";
               break;
           case 3:
               button.text = "Blue";
               break;
           default:
               button.text = "increase";
               break;
           }
       }

       //颜色算法按钮
       Button {
           id: colorAlgorithm;
           text: "RGB";
           anchors.left: stop.right;
           anchors.bottom: parent.bottom;
           anchors.leftMargin: 4;
           anchors.bottomMargin: 4;
           onClicked: {
               var algorithm = (colorMaker.algorithm() +1) % 5;
               changetAlgorithm(colorAlgorithm, algorithm);     //changetAlgorithm是后面的Javascript函数
               colorMaker.setAlgouthm(algorithm);
           }
       }

       //退出按钮
       Button {
           id: quit;
           text: "quit";
           anchors.left: colorAlgorithm.right;
           anchors.bottom: parent.bottom;
           anchors.leftMargin: 4;
           anchors.bottomMargin: 4;
           onClicked: {
               Qt.quit();
           }
       }

       //关联控件colorMaker 和 槽函数onCurrentTimer
       Connections {
           target: colorMaker;              //接收事件的对象
           onCurrentTimer: {                //收到事件时的处理函数
               timeLabel.text = strTime;    //strTime从currentTimer里发送过来的
               timeLabel.color = colorMaker.timeColor;
           }
       }

       Connections {
           target: colorMaker;
           onColorChanged: {
               colorRect.color = colorMaker.color;
           }
       }

}
