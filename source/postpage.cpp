#include "postpage.h"
#include "ui_postpage.h"
#include <QMessageBox>
#include <QClipboard>

PostPage::PostPage(QWidget *parent,const QString &html) :
    QWidget(parent),
    ui(new Ui::PostPage),
    _html(html)
{
    ui->setupUi(this);
    ui->link->setText("http://hbryan.ltd/pastebin/show/raw.php?id=MDPH");
    connect(ui->postBtn,&QPushButton::clicked,this,&PostPage::onBtnPushClicked);
    connect(ui->copylink,&QPushButton::clicked,this,[=](){
        QClipboard *clip = QApplication::clipboard();
        clip->setText(ui->link->toPlainText());
        QMessageBox::information(this,"Successfully!","Copy successfully!");
    });
}

PostPage::~PostPage()
{
    delete ui;
}


void PostPage::onBtnPushClicked()
{
    _title=ui->page_title->toPlainText();
    if(_title==""){
        QMessageBox::warning(this,tr("Error"), "Title can't be empty.");
        return;
    }
    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    request.setUrl(QUrl("http://hbryan.ltd/pastebin/post.php"));
    request.setRawHeader("Content-Type","multipart/form-data; boundary=---------------------------413250491427529503671899464513");

    QString testData = QString("-----------------------------413250491427529503671899464513\n"
            "Content-Disposition: form-data; name=\"id\"\n"
            "\n"
            "%1\n"
            "-----------------------------413250491427529503671899464513\n"
            "Content-Disposition: form-data; name=\"code\"\n"
            "\n"
            "%2\n"
            "-----------------------------413250491427529503671899464513--\n"
            "").arg(_title,_html);
    QNetworkReply* reply = naManager->post(request, testData.toUtf8());
}

void PostPage::requestFinished(QNetworkReply *reply)
{
    // 获取http状态码
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(statusCode.isValid())
            qDebug() << "status code=" << statusCode.toInt();

        QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        if(reason.isValid())
            qDebug() << "reason=" << reason.toString();

        QNetworkReply::NetworkError err = reply->error();
        if(err != QNetworkReply::NoError) {
            QMessageBox::warning(this,tr("Error"), "Failed: " + reply->errorString());
        }
        else {
            ui->link->setText("http://hbryan.ltd/pastebin/show/raw.php?id="+_title);
            QMessageBox::information(this,"Successfully!","Post successfully!");
            qDebug() << reply->readAll();
        }
}
