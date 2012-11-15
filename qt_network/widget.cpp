#include "widget.h"
#include "ui_widget.h"
#include<QtNetwork>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    manager=new QNetworkAccessManager(this);
   // connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
   //manager->get(QNetworkRequest(QUrl("http://yafeilinux.com")));
    ui->progressBar->hide();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec=QTextCodec::codecForName("utf8");
    QString all=codec->toUnicode(reply->readAll());
    ui->textBrowser->setText("all");
    reply->deleteLater();
}

void Widget::on_pushButton_clicked()
{
    qDebug()<<"on_pushButton_clicked";
    QString urlString = ui->lineEdit->text();
    qDebug()<<"url string - > "<<urlString;
    url = urlString;//

    QFileInfo info(url.path());
    QString fileName(info.fileName());
    if(fileName.isEmpty())
        fileName="index.html";


    file=new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug()<<"open file error";
        return;
    }
    qDebug()<<"open file success and start tcp :"<<url.path() << fileName;


    ui->progressBar->setValue(0);
    ui->progressBar->show();
    startRequest(url);

}

void Widget::startRequest(QUrl url2)
{
//    QUrl t1("http://127.0.0.1/index.html");
//    qDebug()<<"request url -> "<<url2.path();
//    qDebug()<<"request url -> "<<t1.path();
//    qDebug()<<"request url -> "<<url2.host();
//    qDebug()<<"request url -> "<<t1.host();

    reply=manager->get(QNetworkRequest(url2));
    connect(reply,SIGNAL(finished()),this,SLOT(httpFinish()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(UpdateDataReadProgress(qint64,qint64)));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(httpError(QNetworkReply::NetworkError)));


}

void Widget::httpReadyRead()
{
    qDebug()<<"httpReadyRead";
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    //使用utf8编码，这样才可以显示中文
    QString all = codec->toUnicode(reply->readAll());
    qDebug()<<"http -> "<<all;
    if(file)
        file->write(all.toAscii());
    ui->textBrowser->append(all);
 //   ui->textBrowser->setHtml(all);
}

void Widget::UpdateDataReadProgress(qint64 totalBytes,qint64 bytesRead)
{
    qDebug()<<"UpdateDataReadProgress" <<totalBytes <<bytesRead;
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

void Widget::httpFinish()
{
 //   return;
    qDebug()<<"httpFinish";
    ui->progressBar->hide();

    file->flush();

    file->close();

    reply=0;
    delete file;
    file=0;

}
void Widget::httpError(QNetworkReply::NetworkError error){
    qDebug()<<"errorcode --> "<< error;
}
