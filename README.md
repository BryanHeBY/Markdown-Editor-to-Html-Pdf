# #C(<img src="./MDHP.png" width="70px">&nbsp;M↓Editor&amp;2&lt;H&gt;P V1.0 --- 用户手册)
# #R(Authored by: H_Bryan)
---
 
## 一、使用前环境配置说明
1. 程序打开方式: 
 - windows: 打开MDHP.exe
 - linux: 在终端中cd到程序文件夹下，输入`./MDHP`
2. 功能使用扩展依赖:
 - 离线转PDF功能: 需要 [wkhtmltopdf离线环境](https://wkhtmltopdf.org/)<br>
	安装方式:<br>
	Windows: 程序自带<br>
	Debian系: `sudo apt install wkhtmltopdf`<br>
	Red Hat/Centos: `sudo yum install wkhtmltopdf`

## 二、支持语法功能
 
> 1.**标题**
> ```
> # 一号标题
> ## 二号标题
> ### 三号标题
> #### 四号标题
> ##### 五号标题
> ###### 六号标题
> ```
> 效果:
> # 一号标题
> ## 二号标题
> ### 三号标题
> #### 四号标题
> ##### 五号标题
> ###### 六号标题
<br>
 
> 2.**字体**
> ```
> *斜体* **加粗** ***斜体加粗*** ~~删除~~
> ```
> 效果：
> *斜体* **加粗** ***斜体加粗*** ~~删除~~
<br>
 
> 3.**列表及列表嵌套**
> ```
> * 第一层列表
>  - 第二层列表
>   1. 第一个
>   2. 第二个
> * 第一层列表的第二个
> ```
> 效果:
> * 第一层列表
>  - 第二层列表
>   1. 第一个
>   2. 第二个
> * 第一层列表的第二个
<br>
 
> 3.**区块**
> ```
> > 区块
> > 区块二
> > - 支持区块链表嵌套 
> >  1. 第一项
> >  2. 第二项
> >  区块二末尾
> > >  区块三
> ```
> 效果:
> > 区块
> > 区块二
> > - 支持区块链表嵌套 
> >  1. 第一项
> >  2. 第二项
> >  区块二末尾
> > >  区块三
> 提示：多个区块连在一起需要用单行换行符&lt;br&gt;分割
<br>
 
> 4.**代码块**
> ```
> 这里是`pip install numpy`的代码块
> 下面是c++代码块
> \```
> #include<iostream>
> using namespace std;
> int main(){
>    int n;
>    cin>>n;
>    return 0;
> }
> \```
> ```
> 效果:
> 这里是`pip install numpy`的代码块
> 下面是c++代码块
> ```
> #include<iostream>
> using namespace std;
> int main(){
>    int n;
>    cin>>n;
>    return 0;
> }
> ```
<br>
 
> 5.**Latex公式**
> ```
> 这是单行数学公式: $\sum_{i=0}^N\int_{a}^{b}g(t,i)\text{d}t$
> 行内公式:  $x$的取值范围为 $1 \leq x \leq 10^5$
> 下面是多行数学公式
> $$\begin{bmatrix}
> {a_{11}}&{a_{12}}&{\cdots}&{a_{1n}}\\
> {a_{21}}&{a_{22}}&{\cdots}&{a_{2n}}\\
> {\vdots}&{\vdots}&{\ddots}&{\vdots}\\
> {a_{m1}}&{a_{m2}}&{\cdots}&{a_{mn}}\\
> \end{bmatrix}$$
> ```
> 效果:
> 这是单行数学公式: $\sum_{i=0}^N\int_{a}^{b}g(t,i)\text{d}t$
> 行内公式:  $x$的取值范围为 $1 \leq x \leq 10^5$
> 下面是多行数学公式
> $$\begin{bmatrix}
> {a_{11}}&{a_{12}}&{\cdots}&{a_{1n}}\\
> {a_{21}}&{a_{22}}&{\cdots}&{a_{2n}}\\
> {\vdots}&{\vdots}&{\ddots}&{\vdots}\\
> {a_{m1}}&{a_{m2}}&{\cdots}&{a_{mn}}\\
> \end{bmatrix}$$
<br>
 
> 6.**超链接与图片**
> ```
> 这是我的pastebin的超链接: [http://hbryan.ltd/pastebin](http://hbryan.ltd/pastebin)
> 这是NJU校徽![NJU](https://bkimg.cdn.bcebos.com/pic/2fdda3cc7cd98d103d73086f2c3fb80e7aec90cc?x-bce-process=image/watermark,image_d2F0ZXIvYmFpa2UyNzI=,g_7,xp_5,yp_5/format,f_auto)
> ```
> 效果
> 这是我的pastebin的超链接: [http://hbryan.ltd/pastebin](http://hbryan.ltd/pastebin)
> 这是NJU校徽![NJU](https://bkimg.cdn.bcebos.com/pic/2fdda3cc7cd98d103d73086f2c3fb80e7aec90cc?x-bce-process=image/watermark,image_d2F0ZXIvYmFpa2UyNzI=,g_7,xp_5,yp_5/format,f_auto)
<br>
 
> 7.**表格**
> ```
> |表头1|表头2|表头3|
> |------:|:----:|:----|
> |1|2|3|
> |4|5|6|
> |7|8|9|
> |10|11|12|
> |13|14|15|
> ```
> |表头1|表头2|表头3|
> |------:|:----:|:----|
> |1|2|3|
> |4|5|6|
> |7|8|9|
> |10|11|12|
> |13|14|15|
<br>
 
> 8.原生html代码以及语法混用
> ```
> <!--我是html原生的注释，下面是html的原生语法-->
> 换行<br><br><br><br><br> 
> 空     格
> <div style="text-align:center;">我是 *html* 原生的**居中**div</div>
> <center><img alt="NJU" src="https://bkimg.cdn.bcebos.com/pic/2fdda3cc7cd98d103d73086f2c3fb80e7aec90cc?x-bce-process=image/watermark,image_d2F0ZXIvYmFpa2UyNzI=,g_7,xp_5,yp_5/format,f_auto" style="width:300px;"></center>
> ```
> 效果
> <!--我是html原生的注释，下面是html的原生语法-->
> 换行<br><br><br><br><br> 
> 空     格
> <div style="text-align:center;">我是 *html* 原生的**居中**div</div>
> <center><img alt="NJU" src="https://bkimg.cdn.bcebos.com/pic/2fdda3cc7cd98d103d73086f2c3fb80e7aec90cc?x-bce-process=image/watermark,image_d2F0ZXIvYmFpa2UyNzI=,g_7,xp_5,yp_5/format,f_auto" style="width:300px;"></center>
<br>
 

> 9.**分割线**
> ```
> ---
> ```
> 效果
> ---
<br>
 
> 10.**用户自定义替换语法，为高级用户提供语法拓展功能**
>  详情请打开用户自定义语法展示文件，查看程序自带拓展语法
<br>
 

 
## 三、程序功能
1. 文件操作(F)
	- 新建文件（有当前文件未保存提醒）
	- 打开文件（有当前文件未保存提醒）
	- 保存文件
	- 另存为
	- 最近使用文件列表，快速打开markdown文件
		- 可清空最近文件列表
	- 退出（有当前文件未保存提醒）
2. 编辑(E)
	- 撤销\重做
	- 提供markdown文本框字体与大小调整功能
3. 主题(T)
	- 主题更换，现在提供如下主题
		- 默认主题 default.theme
		- 小古书主题 ancient-book.theme
4. 导出(O)
	- 导出html (导出的html是单文件(除了图片资源) )
	- 导出pdf
	- 导出可分享的在线链接
		- 链接可点击复制、分享查看
5. 预览(V) 
	- 回车自动刷新预览
	- ctrl+H手动刷新预览
	- 调整编辑框和预览框大小比例(提供快捷键)
		- 提供以下编辑:预览比例: 1:1 1:0 0:1 2:1 3:1
6. 工具(M)
	- 修改自定义替换语法 (修改窗口关闭自动保存并自动导入，带有正则合法性检查)
	- 重新载入自定义语法
7. 帮助(M)
	- 打开帮助文档
8. 打开(*.md)文件
	- linux: 可在终端命令后加上文件路径，即可打开文件
	- windows: 直接用**MDPH.exe**程序打开，或拖动文件到MDPH.exe程序上
 
## 四、程序说明以及附录
1. 程序使用的外部扩展库
	- [highlight.js](https://highlightjs.org/) --- 语法高亮渲染库
	- [latex.codecogs](http://latex.codecogs.com/) --- 在线生成latex公式图片
	- [wkhtmltopdf](https://wkhtmltopdf.org/) --- html转pdf工具

## 五、更多信息请关注github本项目网站
链接: [https://github.com/BryanHeBY/Markdown-Editor-to-Html-Pdf](https://github.com/BryanHeBY/Markdown-Editor-to-Html-Pdf)