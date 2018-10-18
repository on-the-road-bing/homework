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
    QStringList stud;
} studData;
QDebug operator<<(QDebug d,const studData &data) {                      // 补全运算符重载函数，使其能直接输出studData结构
    for(int i=0;i<data.stud.size();i++)
//QDebug在输出QString等类型内容时，会自动添加双引号，这反而会让控制台的信息更密集，不便于分析结果。固使用该函数，修改此默认设置
        d.noquote().nospace()<<QString(data.stud.at(i))<<"\t" ;
    return d;
}
class myCmp {                                                             // 比较类，用于std::sort第三个参数
public:
    myCmp(int selectedColumn){                                            //构造函数
        this->currentColumn = selectedColumn;
    }
    bool operator() (const studData& d1,const studData& d2) const;
private:
    int currentColumn;
};
bool myCmp::operator()(const studData &d1, const studData& d2) const
{
    return d1.stud.at(currentColumn+1)>d2.stud.at(currentColumn+1) ;      //从大到小排序
}
class ScoreSorter
{
//private:
//    QVector<studData> st;
//    studData txttitle;  //文件第一行
//    QString filename;
//    void outfile(quint8 lie);
public:
    QVector<studData> st;
    studData txttitle;  //文件第一行
    QString filename;
    ScoreSorter(QString dataFile);
    void readFile(){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"文件打开失败";return;
        }
        QString title(file.readLine());
        txttitle.stud= title.split(" ", QString::SkipEmptyParts);

        studData s1;        //学生信息
        while(!file.atEnd()){
              QByteArray line = file.readLine();                             //按行读取
              QString str(line);
              s1.stud = str.split(" ", QString::SkipEmptyParts);

              if((s1.stud).last() == "\n") s1.stud.removeLast();
              if(s1.stud.size()==0) continue;
              st.append(s1);                                       //添加到st
        }
        file.close();
    }
    void doSort(){                                                 //排序函数
        for(int i=1;i<txttitle.stud.size();i++) {

                myCmp comp(i-1);    //初始化排序规则对象                                                //
                std::sort(st.begin(),st.end(),comp);
                qDebug()<<"当前排序第 "<< i+1 <<" 列：";
                qDebug()<< "    "<<txttitle;    //输出第一行
                for(int i=0;i<st.size();i++)
                    qDebug()<<st.at(i);
                qDebug()<<"----------------------------------\n";
                outfile(i+1);   //当前排序规则下的st输出到文件
        }
    }
    void outfile(quint8 lie)
    {
        QFile file("sort_"+filename);
        file.open(QIODevice::ReadWrite|QIODevice::Append);
        if(!file.open(QIODevice::ReadWrite | QIODevice::Append)){
            qDebug()<<"打开失败"; return;
            return;
        }
        QTextStream out(&file);
        out.setCodec("UTF-8");  //设置编码方式
        out<<QString("排序后输出，当前排序第 ")<<lie <<QString(" 列：")<<"\r\n";
        out<<"\t";
        for(int i=0;i<txttitle.stud.size();i++)
            out<<txttitle.stud.at(i)<<"\t";                    //输出第一行
        out<<"\r\n";
        for(int i=0;i<st.size();i++){
            for(int j=0;j<txttitle.stud.size();j++)
                    out<<st.at(i).stud.at(j)<<"\t";      //输出学生信息
            out<<"\r\n";
        }
        out<<"-----------------------------------------"<<"\r\n\r\n";
        file.close();
    }
};
ScoreSorter::ScoreSorter(QString dataFile){ //构造函数
    filename=dataFile;
}
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 自定义qDebug
    // 输出信息至文件中（读写、追加形式）
    QFile f("sorted_data.txt");
    f.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&f);
    stream << msg<<endl;
    f.flush();
    f.close();
    QTextStream ts(stdout);
    ts << msg<<endl;
}
int main()
{
    qInstallMessageHandler(myMessageOutput);
    QString datafile = "data.txt";
    QFile f("sorted_"+datafile);
    if (f.exists()){                        // 如果排序后文件已存在，则删除之
        f.remove();
    }
    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();
    return 0;
}
