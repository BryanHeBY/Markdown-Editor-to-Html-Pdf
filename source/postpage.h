#ifndef POSTPAGE_H
#define POSTPAGE_H

#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

namespace Ui {
class PostPage;
}

class PostPage : public QWidget
{
    Q_OBJECT

public:
    explicit PostPage(QWidget *parent,const QString &html);
    ~PostPage();
    void onBtnPushClicked();
public slots:
    void requestFinished(QNetworkReply* reply);
private:
    Ui::PostPage *ui;
    QString _html,_title;
};

#endif // POSTPAGE_H
