#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFile>

namespace SK {
enum SortKind{
    col01    =   0x00000001<<0,         //!< 第1列
    col02    =   0x00000001<<1,         //!< 第2列
    col03    =   0x00000001<<2,         //!< 第3列
    col04    =   0x00000001<<3,         //!< 第4列
    col05    =   0x00000001<<4,         //!< 第5列
    col06    =   0x00000001<<5,         //!< 第6列
    col07    =   0x00000001<<6,         //!< 第7列
    col08    =   0x00000001<<7,         //!< 第8列
    col09    =   0x00000001<<8,         //!< 第9列
    col10    =   0x00000001<<9,         //!< 第10列
    col11    =   0x00000001<<10,        //!< 第11列
    col12    =   0x00000001<<11,        //!< 第12列
    col13    =   0x00000001<<12,        //!< 第13列
    col14    =   0x00000001<<13,        //!< 第14列
    col15    =   0x00000001<<14,        //!< 第15列
    col16    =   0x00000001<<15,        //!< 第16列
    col17    =   0x00000001<<16,        //!< 第17列
    col18    =   0x00000001<<17,        //!< 第18列
    col19    =   0x00000001<<18,        //!< 第19列
    col20    =   0x00000001<<19,        //!< 第20列
    col21    =   0x00000001<<20,        //!< 第21列
    col22    =   0x00000001<<21,        //!< 第22列
    col23    =   0x00000001<<22,        //!< 第23列
    col24    =   0x00000001<<23,        //!< 第24列
    col25    =   0x00000001<<24,        //!< 第25列
    col26    =   0x00000001<<25,        //!< 第26列
    col27    =   0x00000001<<26,        //!< 第27列
    col28    =   0x00000001<<27,        //!< 第28列
    col29    =   0x00000001<<28,        //!< 第29列
    col30    =   0x00000001<<29,        //!< 第30列
    col31    =   0x00000001<<30,        //!< 第31列
    col32    =   0x00000001<<31,        //!< 第32列
};
}

typedef struct{                                                           // 请补全结构定义
    QString studNumber;
    QString studName;
    QVector<int> studScore;
} studData;

QDebug operator<< (QDebug d, const studData &data) {                      // 补全运算符重载函数，使其能直接输出studData结构
    QDebugStateSaver saver(d);
    d.noquote()<<data.studNumber<<data.studName<<data.studScore;//QDebug在输出QString和QByteArray等类型的内容时，会自动为其添加双引号。而有时，这反而会让控制台的信息更密集，不便于分析结果。所以，使用该函数，修改此默认设置
    return d;
}

class myCmp {                                                             // 比较类，用于std::sort第三个参数
public:
    myCmp(int selectedColumn){                                             //构造函数
        this->currentColumn = selectedColumn;
    }
    bool operator() (const studData& d1,const studData& d2);
private:
    int currentColumn;
};

bool myCmp::operator()(const studData &d1, const studData &d2)
{
    bool result = false;
    quint32 sortedColumn = 0x00000001<<currentColumn;
    switch (sortedColumn) {
    case SK::col01:
        result=(d1.studNumber>d2.studNumber);break;
    case SK::col02:
        result=d1.studName>d2.studName;break;
    default:
        result=d1.studScore.at(sortedColumn)>d2.studScore.at(sortedColumn);
    // ...
    // 请补全运算符重载函数
    // ...
    }
    return result;
}


class ScoreSorter

{
public:

    QString filename;
    ScoreSorter(QString dataFile);
    void readFile(){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"打开失败";
            return;
        }
        QTextStream in(&file);
        while( !file.atEnd()){
              QString line = file.readLine();
              qDebug()<<line;
          }
        file.close();
    }
    void doSort(){
//        QVector<studData> st;
//        myCmp comp;
//        std::sort(st.begin(),st.end();
    }
    // 请补全该类，使其实现上述要求

};

// 请补全
ScoreSorter::ScoreSorter(QString dataFile){ //构造函数
    filename=dataFile;
//    QFile file(filename);
//    filename=dataFile;
//    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
//        qDebug()<<"打开失败";
//        return;
//    }
//    QTextStream in(&file);
//    while( !file.atEnd()){
//          QString line = file.readLine();
//          qDebug()<<line;
//      }
}


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 自定义qDebug
    QByteArray localMsg = msg.toLocal8Bit();
         switch (type) {
         case QtDebugMsg:
             fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
             break;
         case QtInfoMsg:
             fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
             break;
         case QtWarningMsg:
             fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
             break;
         case QtCriticalMsg:
             fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
             break;
         case QtFatalMsg:
             fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
               abort();
         }
}

int main()
{
    qInstallMessageHandler(myMessageOutput);
    QString datafile = "D:/Project/3_16/data.txt";

    // 如果排序后文件已存在，则删除之
    QFile f("sorted_"+datafile);
    if (f.exists()){
        f.remove();
    }

    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();
    return 0;
}
