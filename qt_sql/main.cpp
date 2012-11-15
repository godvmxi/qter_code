//#include <QtCore/QCoreApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QStringList>
#include <QString>
#include <QSqlDatabase>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"helloworld";
    qDebug() << "Available drivers:";

    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers)
    qDebug() << "\t" << driver;
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    qDebug()<<"open ";
    db.setDatabaseName(":memory:");
    if(!db.open()){
        qDebug()<<"open error";
        exit(1);
    }
    QSqlQuery query(db);
    query.exec("create table student(id int primary key ,name varchar(10)) ");
    query.exec("insert into student values(1,'pan')");
    query.exec("insert into student values(2,'shi')");
    query.exec("insert into student values(3,'li')");
    query.exec("select id,name from student where id<=2");
    while(query.next())
    {
        int ele0=query.value(0).toInt();
        QString ele1=query.value(1).toString();
        qDebug()<<ele0<<ele1;
        qDebug()<<"open next";
    }
    qDebug()<<"open over";
    return a.exec();
}
