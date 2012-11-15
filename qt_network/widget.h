#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QDebug>
#include <QtNetwork>
#include <QEvent>
#include <QFile>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    void startRequest(QUrl url);

    ~Widget();
//protected:


private slots:
    void replyFinished(QNetworkReply *);
    void on_pushButton_clicked();
    void httpFinish();
    void httpReadyRead();
    void httpError(QNetworkReply::NetworkError error);
    void UpdateDataReadProgress(qint64,qint64);

private:
    Ui::Widget *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
    QFile *file;

//    changeEvent(QEvent *e);

};

#endif // WIDGET_H
