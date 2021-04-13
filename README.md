# M↓Editor&2&lt;H&gt;P V1.0 --- 用户手册
Authored by: H_Bryan
---

## 一、使用前环境配置说明
1. 程序打开方式: 
	- windows: 打开md_editor.exe
	- linux: 在终端中cd到程序文件夹下，输入`./md_editor`
2. 功能使用扩展依赖:
	- 离线转PDF功能: 需要 [wkhtmltopdf离线环境](https://wkhtmltopdf.org/)<br>安装方式:<br>Windows: 官网下载<br>Debian系: `sudo apt install wkhtmltopdf`<br>Red Hat/Centos: `sudo yum install wkhtmltopdf`

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
> 这是罗马国旗图片![这是罗马国旗](./Roman.jpeg)
> ```
> 效果
> 这是我的pastebin的超链接: [http://hbryan.ltd/pastebin](http://hbryan.ltd/pastebin)
> 这是罗马国旗图片![这是罗马国旗](./Roman.jpeg)
<br>

> ~~7.**表格**(暂不支持)~~
<br>

> 8.原生html代码以及语法混用
> ```
> <!--我是html原生的注释，下面是html的原生语法-->
> 换行<br><br><br><br><br>
> 空&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;格
> <div style="text-align:center;">我是 *html* 原生的**居中**div</div>
> <center><img alt="罗马国旗" src="./Roman.jpeg" style="width:300px;"></center>
> ```
> 效果
> <!--我是html原生的注释，下面是html的原生语法-->
> 换行<br><br><br><br><br>
> 空&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;格
> <div style="text-align:center;">我是 *html* 原生的**居中**div</div>
> <center><img alt="罗马国旗" src="./Roman.jpeg" style="width:300px;"></center>
<br>


> 9.**作者自创语法**~~(后期将加入用户自定义html替换语法功能)~~:
> ```
> #[m](这里可以**居中**)
> #[r](这里可以右**对齐**~)
> ```
> 效果
> #[m](这里可以**居中**)
> #[r](这里可以右**对齐**~)
<br>

> 10.**分割线**
> ```
> ---
> ```
> 效果
> ---

## 三、拓展功能
1. 输出html: 导出 -> 导出html
2. (本地)输出pdf: 导出 -> 导出pdf
3. ~~(未来上线)在线导出pdf: 导出 -> 在线导出pdf~~
4. ~~(未来上线)修改文本框字体字号背景~~
5. ~~(未来上线)切换主题: 计划推出: default, good_night(夜间模式), ancient_book, bright_blue 等主题~~
6. ~~(未来上线)自动缩进(自动添加区块">"符号)~~
7. ~~(未来上线)未保存文件时，关闭窗口自动提示~~
8. ~~(未来上线)更换程序名称，程序图标~~
9. ~~(未来上线)添加更多快捷键: 参照JetBrians套件, 等IDE的快捷键~~
10. ~~(未来上线)多标签页显示~~
11. ~~(未来上线)程序与markdown文件(.md,.markdown)关联~~

## 四、程序说明以及附录
1. 本说明文档的pdf版本以及html版本是由本程序生成 ~~允许套娃(x~~
2. 程序使用的外部扩展库
	- [highlight.js](https://highlightjs.org/) --- 语法高亮渲染库
	- [latex.codecogs](http://latex.codecogs.com/) --- 在线生成latex公式图片
	- [wkhtmltopdf](https://wkhtmltopdf.org/) --- html转pdf工具