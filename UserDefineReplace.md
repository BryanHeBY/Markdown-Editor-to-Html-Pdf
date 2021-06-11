默认扩展语法源代码
```
# 这里你可以自由地添加自己需要的替换语法，支持正则表达式分组替换
# 替换语句语法格式如下(字符不需要转义)
# 块级元素: 
# B: "from"=>"to";
# 行内元素: 
# I: "from"=>"to";

//居中和右对齐
I: "#[cC]\((.*?)\)"=>"<div style="text-align:center;">\1</div>";
I: "#[rR]\((.*?)\)"=>"<div style="text-align:right;">\1</div>";

//下划线
I: "#[uU]\((.*?)\)"=>"<u>\1</u>";

//Markdown扩展可设置大小图片
I: "#[pP]\[(.*),(.*)\]\((.*)\)"=>"<img alt="\1" src="\3" width="\2">";

//手动设置字体大小(单位:px)
I: "#[fF]\[(.*)\]\((.*)\)"=>"<span style="font-size:\1px">\2</span>";

//手动设置字体格式
I: "#[tT]\[(.*)\]\((.*)\)"=>"<span style="\1">\2</span>";

//块级元素居中弹性盒
B: "<[cC]>"=>"<div style="display:flex; flex-direction:column; align-items:center;">";
B: "</[cC]>"=>"</div>";

//分栏
B: "<((cols)|(COLS))>"=>"<div style="display:flex; flex-direction:row; padding:10px">";
B: "</((cols)|(COLS))>"=>"</div>";
B: "<((col)|(COL))>"=>"<div style="width:100%; margin:10px;">";
B: "</((col)|(COL))>"=>"</div>";


```
---
#C(我是居中)
#R(我是右对齐)
#U(我是下划线)

我是可调整大小图片
#P[NJU,400px](https://bkimg.cdn.bcebos.com/pic/2fdda3cc7cd98d103d73086f2c3fb80e7aec90cc?x-bce-process=image/watermark,image_d2F0ZXIvYmFpa2UyNzI=,g_7,xp_5,yp_5/format,f_auto)
#P[NJU,30%](https://bkimg.cdn.bcebos.com/pic/2fdda3cc7cd98d103d73086f2c3fb80e7aec90cc?x-bce-process=image/watermark,image_d2F0ZXIvYmFpa2UyNzI=,g_7,xp_5,yp_5/format,f_auto)

#F[80](*80px* 的字体)
#T[font-size:60px;color:blue;background:linear-gradient(to bottom,transparent,yellow)](我是可设置css的文本)

---

# 我是一个居中容器
---
<C>

**居中**

- 1
- 2
	1. 1
	1. 2

|一|二|三|
|:-:|:-:|:-:|
|1|2|3|
|4|5|6|
|7|8|9|

</C>
---

# 分栏
---
<COLS>
<col>

## 第一栏
|一|二|三|
|:-:|:-:|:-:|
|1|2|3|
|4|5|6|
|7|8|9|

</col>
<col>

## 第二栏
> 区块
> 2
> > 区块嵌套

</col>
<col>

## 第三栏
分隔栏
---
1. 1
	- 1.1
	- 1.2

</col>
</COLS>
---


