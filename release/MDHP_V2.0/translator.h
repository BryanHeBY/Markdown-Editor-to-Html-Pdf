#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

using namespace std;
QString translation(QString &text,int indent_num=0);

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


const QRegularExpression HR("^[\\*\\-_]{3}$");
const QRegularExpression fm[10]={
  QRegularExpression("\\$(.+?)\\$")
 ,QRegularExpression("[\\*]{3}(.+?)[\\*]{3}"),QRegularExpression("[\\*]{2}(.+?)[\\*]{2}"),QRegularExpression("[\\*](.+?)[\\*]"),QRegularExpression("~~(.+?)~~")
 ,QRegularExpression("!\\[(.+?)\\]\\((.+?)\\)"),QRegularExpression("\\[(.+?)\\]\\((.+?)\\)")
,QRegularExpression("`([^`]+?)`")};
const QString fmt[10]={
    QString("<img alt=\"\\1\" src=\"http://latex.codecogs.com/png.latex?\\1\">")
    ,QString("<strong><i>\\1</i></strong>"),QString("<strong>\\1</strong>"),QString("<i>\\1</i>"),QString("<s>\\1</s>")
   ,QString("<img alt=\"\\1\" src=\"\\2\" style=\"max-width:100%;\">"),QString("<a href=\"\\2\">\\1</a>")
    ,QString("<pre><code>\\1</code></pre>")};

const QRegularExpression h[6]={QRegularExpression("^#\\s+(.+)$"),QRegularExpression("^##\\s+(.+)$"),QRegularExpression("^###\\s+(.+)$"),
            QRegularExpression("^####\\s+(.+)$"),QRegularExpression("^#####\\s+(.+)$"),QRegularExpression("^######\\s+(.+)$")};
const QString ht[6]={QString("<h1>\\1</h1>"),QString("<h2>\\1</h2>"),QString("<h3>\\1</h3>"),QString("<h4>\\1</h4>"),QString("<h5>\\1</h5>"),QString("<h6>\\1</h6>")};

const QRegularExpression lst[4]={QRegularExpression("^[\\*+\\-]\\s+(.+)$"),QRegularExpression("^\\s{1}[\\*+\\-]\\s+(.+)$"),QRegularExpression("^\\s{2}[\\*+\\-]\\s+(.+)$"),QRegularExpression("^\\s{3}[\\*+\\-]\\s+(.+)$")};
const QRegularExpression olst[4]={QRegularExpression("^\\d+\\.\\s+(.+)$"),QRegularExpression("^\\s{1}\\d+\\.\\s+(.+)$"),QRegularExpression("^\\s{2}\\d+\\.\\s+(.+)$"),QRegularExpression("^\\s{3}\\d+\\.\\s+(.+)$")};
const QString lstt[4]={QString("\t<li>\\1</li>"),QString("\t\t<li>\\1</li>"),QString("\t\t\t<li>\\1</li>"),QString("\t\t\t\t<li>\\1</li>")};

const QRegularExpression highlight("^```(.*?)$");
const QRegularExpression lines_latex_begin("^\\$\\$(.*?)$"),lines_latex_end("^(.*?)\\$\\$$"),lines_latex_inner("^(.*?)$");
const QRegularExpression table("\\|((.+?)\\|)+"),td_left("^\\s*:-+\\s*$"),td_center("^\\s*:-+:\\s*$"),td_right("^\\s*-+:\\s*$");

QVector<QPair<QRegularExpression,QString>> UserDefineReplaceBlock;
QVector<QPair<QRegularExpression,QString>> UserDefineReplaceInline;
QRegularExpression user_define_block_sentence("^B:\\s+\"(.*)\"=>\"(.*)\";$");
QRegularExpression user_define_inline_sentence("^I:\\s+\"(.*)\"=>\"(.*)\";$");
void set_user_define(QString UserDefine){
    UserDefineReplaceBlock.clear();
    UserDefineReplaceInline.clear();
    QStringList lines=UserDefine.split(QRegularExpression("\\r?\\n"));
    QRegularExpressionMatch match;
    for(const QString &line:lines){
        match=user_define_block_sentence.match(line);
        if(match.hasMatch()){
            UserDefineReplaceBlock.push_back(qMakePair(QRegularExpression(match.captured(1)),match.captured(2)));
        }
        match=user_define_inline_sentence.match(line);
        if(match.hasMatch()){
            UserDefineReplaceInline.push_back(qMakePair(QRegularExpression(match.captured(1)),match.captured(2)));
        }
    }
}

QString get_td_align(const QVector<QString> &td_align,int td_num){
    if(td_num>=td_align.size())return QString();
    return td_align[td_num];
}

QString translation(QString &text,int indent_num) {
    QString indent=QString("\t").repeated(indent_num);

    text.replace(QRegularExpression("<br>\\n[ \\t]*"),"<br>");

    int now_lst_m=0;
    int lst_type[7]={0};


    QString highlight_code;
    bool has_highlight_left=0;


    bool line_latex_mode=0;
    QString line_latex;

    QRegularExpression qblock("^>\\s(.+)$");
    QString inQblock;
    bool in_qblock_mode=0;


    QVector<QString> td_align;
    int table_state=0;

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
            line.replace("\\`","`");
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

        if(HR.match(line).hasMatch()){res+=indent+"<HR>\n";continue;}
        for(const auto &i:UserDefineReplaceInline)line.replace(i.first,i.second);
        for(int i=0;i<8;i++)line.replace(fm[i],fmt[i]);

        if(table.match(line).hasMatch()){
            if(table_state==0){
                res+=indent+"<table>\n";
                res+=indent+"\t<thead>\n";
                res+=indent+"\t\t<tr>\n";
                QStringList tds=line.split("|");

                res+=indent+"\t\t\t";
                for(auto td=tds.cbegin()+1;td+1!=tds.cend();td++)res+=QString("<th>%1</th>").arg(*td);
                res+="\n";

                res+=indent+"\t\t</tr>\n";
                res+=indent+"\t</thead>\n";
                res+=indent+"\t<tbody>\n";
                table_state=1;
            }else if(table_state==1){
                QStringList tds=line.split("|");
                for(auto td=tds.cbegin()+1;td+1!=tds.cend();td++){
                    QString now_align;
                    if(td_left.match(*td).hasMatch())now_align="left";
                    if(td_center.match(*td).hasMatch())now_align="center";
                    if(td_right.match(*td).hasMatch())now_align="right";
                    td_align.push_back(now_align);
                }
                table_state=2;
            }
            else if(table_state==2){
                res+=indent+"\t\t<tr>\n";
                QStringList tds=line.split("|");

                res+=indent+"\t\t\t";
                int now_index=0;
                for(auto td=tds.cbegin()+1;td+1!=tds.cend();td++)res+=QString("<td align=\"%1\">%2</td>").arg(get_td_align(td_align,now_index),*td),now_index++;
                res+="\n";

                res+=indent+"\t\t</tr>\n";
            }
            continue;
        }
        else{
            if(table_state){
                res+=indent+"\t</tbody>\n";
                res+=indent+"</table>\n";
                td_align.clear();
                table_state=0;
            }
        }

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
        bool has_user_define_block=0;
        for(const auto &i:UserDefineReplaceBlock){
            if(i.first.match(line).hasMatch()){
                line.replace(i.first,i.second);
                res+=indent+line+"\n";
                has_user_define_block=1;
                break;
            }
        }
        if(has_user_define_block)continue;
        now_lst_m=li_num;
        if(!line.isEmpty()&&!is_h&&!li_num&&!has_highlight_left)line=QString("<div class=\"para\">%1</div>").arg(line);
        if(!line.isEmpty()||has_highlight_left)res+=indent+line+"\n";
    }
    for(int i=now_lst_m;i>0;i--)res+=indent+QString("\t").repeated(i-1)+(lst_type[i]==1?"</ol>\n":"</ul>\n");
    if(in_qblock_mode)res+=indent+"<div class=\"qblock\">\n"+translation(inQblock,indent_num+1)+indent+"</div>\n";
    if(table_state){
        res+=indent+"\t</tbody>\n";
        res+=indent+"</table>\n";
        td_align.clear();
        table_state=0;
    }
    return res;
}

#endif // TRANSLATOR_H
