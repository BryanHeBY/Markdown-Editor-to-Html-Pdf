#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

using namespace std;
QString translation(const QString &text,int indent_num=0);

QString getHtml(QString text,QString title="",QString css=""){
    QString res=QString(
"<!Doctype html>\n\
<html>\n\
<head>\n\
<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\n\
\t<title>%1</title>\n\
%2\n\
</head>\n\
<body>\n\
%3\n\
</body>\n\
</html>").arg(title,css,translation(text,1));
     return res;
}


QString translation(const QString &text,int indent_num) {
    QString indent=QString("\t").repeated(indent_num);
    QRegularExpression fm[11]={
      QRegularExpression("^[\\*\\-_]{3}$"),QRegularExpression("\\$(.+?)\\$")
     ,QRegularExpression("[\\*]{3}(.+?)[\\*]{3}"),QRegularExpression("[\\*]{2}(.+?)[\\*]{2}"),QRegularExpression("[\\*](.+?)[\\*]"),QRegularExpression("~~(.+?)~~")
     ,QRegularExpression("#\\[[mM]\\]\\((.+?)\\)"),QRegularExpression("#\\[[rR]\\]\\((.+?)\\)")
     ,QRegularExpression("!\\[(.+?)\\]\\((.+?)\\)"),QRegularExpression("\\[(.+?)\\]\\((.+?)\\)")
    ,QRegularExpression("`([^`]+?)`")};
    QString fmt[11]={
        QString("<HR>"),QString("<img alt=\"\\1\" src=\"http://latex.codecogs.com/png.latex?\\1\">")
        ,QString("<strong><i>\\1</i></strong>"),QString("<strong>\\1</strong>"),QString("<i>\\1</i>"),QString("<s>\\1</s>")
        ,QString("<div style=\"text-align:center;\">\\1</div>"),QString("<div style=\"text-align:right;\">\\1</div>")
       ,QString("<img alt=\"\\1\" src=\"\\2\">"),QString("<a href=\"\\2\">\\1</a>")
        ,QString("<pre><code>\\1</code></pre>")};

    QRegularExpression h[6]={QRegularExpression("^#\\s+(.+)$"),QRegularExpression("^##\\s+(.+)$"),QRegularExpression("^###\\s+(.+)$"),
                QRegularExpression("^####\\s+(.+)$"),QRegularExpression("^#####\\s+(.+)$"),QRegularExpression("^######\\s+(.+)$")};
    QString ht[6]={QString("<h1>\\1</h1>"),QString("<h2>\\1</h2>"),QString("<h3>\\1</h3>"),QString("<h4>\\1</h4>"),QString("<h5>\\1</h5>"),QString("<h6>\\1</h6>")};

    QRegularExpression lst[4]={QRegularExpression("^[\\*+\\-]\\s+(.+)$"),QRegularExpression("^\\s{1}[\\*+\\-]\\s+(.+)$"),QRegularExpression("^\\s{2}[\\*+\\-]\\s+(.+)$"),QRegularExpression("^\\s{3}[\\*+\\-]\\s+(.+)$")};
    QRegularExpression olst[4]={QRegularExpression("^\\d+\\.\\s+(.+)$"),QRegularExpression("^\\s{1}\\d+\\.\\s+(.+)$"),QRegularExpression("^\\s{2}\\d+\\.\\s+(.+)$"),QRegularExpression("^\\s{3}\\d+\\.\\s+(.+)$")};
    QString lstt[4]={QString("\t<li>\\1</li>"),QString("\t\t<li>\\1</li>"),QString("\t\t\t<li>\\1</li>"),QString("\t\t\t\t<li>\\1</li>")};
    int now_lst_m=0;
    int lst_type[7]={0};

    QRegularExpression highlight("^```(.*?)$");
    QString highlight_code;
    bool has_highlight_left=0;

    QRegularExpression lines_latex_begin("^\\$\\$(.*?)$"),lines_latex_end("^(.*?)\\$\\$$"),lines_latex_inner("^(.*?)$");
    bool line_latex_mode=0;
    QString line_latex;

    QRegularExpression qblock("^>\\s(.+)$");
    QString inQblock;
    bool in_qblock_mode=0;

    QStringList lines=text.split(QRegularExpression("\\r?\\n"));
    QString res="";
    for(QString line:lines){
        if(highlight.match(line).hasMatch()){
            res+=has_highlight_left?"</code></pre>\n":indent+"<pre><code>",line="",has_highlight_left^=1;
            continue;
        }

        if(has_highlight_left){
            line.replace(QRegularExpression("&"),"&amp;");
            line.replace(QRegularExpression("<"),"&lt;"),line.replace(QRegularExpression(">"),"&gt;");
            res+=line+"\n";
            continue;
        }

        if(qblock.match(line).hasMatch()){
            in_qblock_mode=1;
            inQblock+=line.replace(qblock,"\\1\n");
            continue;
        }
        else{
            if(in_qblock_mode)res+=indent+"<div class=\"qblock\">\n"+translation(inQblock,indent_num+1)+indent+"</div>\n",inQblock="";
            in_qblock_mode=0;
        }

        if(lines_latex_begin.match(line).hasMatch()){
            line_latex+=line.replace(lines_latex_begin,"\\1");
            line_latex_mode=1;
            continue;
        }
        if(lines_latex_end.match(line).hasMatch()){
            line_latex+=line.replace(lines_latex_end,"\\1");
            res+=indent+QString("<img alt=\"%1\" src=\"http://latex.codecogs.com/png.latex?%2\">\n").arg(line_latex,line_latex);
            line_latex="";
            line_latex_mode=0;
            continue;
        }
        if(line_latex_mode){
            line_latex+=line.replace(lines_latex_inner,"\\1");
            continue;
        }

        for(int i=0;i<11;i++)line.replace(fm[i],fmt[i]);
        bool is_h=0;
        for(int i=0;i<6;i++)if(h[i].match(line).hasMatch()){
            line.replace(h[i],ht[i]);
            is_h=1;
            break;
        }
        int li_num=0;
        for(int i=0;i<4;i++)if(lst[i].match(line).hasMatch()){
            line.replace(lst[i],lstt[i]);
            li_num=i+1,lst_type[i+1]=0;
            break;
        }else if(olst[i].match(line).hasMatch()){
            line.replace(olst[i],lstt[i]);
            li_num=i+1,lst_type[i+1]=1;
            break;
        }

        for(int i=now_lst_m;i>li_num;i--)res+=indent+QString("\t").repeated(i-1)+(lst_type[i]==1?"</ol>\n":"</ul>\n");
        for(int i=now_lst_m+1;i<=li_num;i++)res+=indent+QString("\t").repeated(i-1)+(lst_type[i]==1?"<ol>\n":"<ul>\n");
        now_lst_m=li_num;
        if(!line.isEmpty()&&!is_h&&!li_num&&!has_highlight_left)line=QString("<p>%1</p>").arg(line);
        if(!line.isEmpty()||has_highlight_left)res+=indent+line+"\n";
    }
    for(int i=now_lst_m;i>0;i--)res+=indent+QString("\t").repeated(i-1)+(lst_type[i]==1?"</ol>\n":"</ul>\n");
    if(in_qblock_mode)res+=indent+"<div class=\"qblock\">\n"+translation(inQblock,indent_num+1)+indent+"</div>\n";
    return res;
}

#endif // TRANSLATOR_H
