#include <QCoreApplication>
#include <QDebug>
#include <QVector>
class Student
{
public:
    char Number[20];
    char Name[20];
    int class1_score,class2_score;
};
bool Com_Name(Student mm,Student nn){                                      //自定义按名字排序函数
    return (mm.Name>nn.Name);
}
bool Com_class1(Student mm,Student nn){                                    //自定义按课程1排序函数
    return (mm.class1_score>nn.class1_score);                              //按从大到小排序
}
bool Com_class2(Student mm,Student nn){                                    //自定义按课程2排序函数
    return (mm.class2_score>nn.class2_score);                              //按从大到小排序
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Student std1={"1403130209"," 鲁智深",80,72};
    Student std2={"1403140101"," 林冲 ",82,76};
    Student std3={"1403140102"," 宋江 ",76,85};
    Student std4={"1403140103"," 武松 ",88,80};
    QVector<Student> vector;                                                 //定义一个结构体数组
    vector<<std1<<std2<<std3<<std4;
    qDebug()<<"排序前---------------";
    qDebug()<<"   学号\t\t  "<<"姓名\t\t"<<"课程1\t"<<"课程2";
    foreach (Student st , vector) {
        qDebug()<<st.Number<<"\t"<<st.Name<<"\t"<<st.class1_score<<"\t"<<st.class2_score;
    }
    qDebug()<<"按姓名排序---------------";
    qDebug()<<"   学号\t\t  "<<"姓名\t\t"<<"课程1\t"<<"课程2";
    std::sort(vector.begin(),vector.end(),Com_Name);
    foreach (Student st , vector) {
        qDebug()<<st.Number<<"\t"<<st.Name<<"\t"<<st.class1_score<<"\t"<<st.class2_score;
    }
    qDebug()<<"按课程1排序---------------";
    qDebug()<<"   学号\t\t  "<<"姓名\t"<<"课程1\t"<<"课程2";
    std::sort(vector.begin(),vector.end(),Com_class1);
    foreach (Student st , vector) {
        qDebug()<<st.Number<<"\t"<<st.Name<<"\t"<<st.class1_score<<"\t"<<st.class2_score;
    }

    qDebug()<<"按课程2排序---------------";
    qDebug()<<"   学号\t\t  "<<"姓名\t\t"<<"课程1\t"<<"课程2";
    std::sort(vector.begin(),vector.end(),Com_class2);
    foreach (Student st , vector) {                                         //按顺序遍历容器中的对象，
        qDebug()<<st.Number<<"\t"<<st.Name<<"\t"<<st.class1_score<<"\t"<<st.class2_score;
    }
    return a.exec();
}
