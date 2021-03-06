# Typora简易使用教程

### 生成目录方法

* 输入[toc]，然后回车，即可创建目录

### 生成标题

* #+空格+一级目录标题              		快捷键（Ctrl+1）

* ##+空格+二级目录标题        	        快捷键（Ctrl+2）

  .....

* ######+空格+六级目录标题          快捷键（Ctrl+6）

***

### 引用文字

* 单行引用

  > \>+空格+引用文字

* 多行引用

  > \~~~ +回车
  >
  > 如果多行引用代码，比如java代码则使用  ~~~java+回车

* 引用代码

  >使用反单引号来调用句子中的代码或命令
  >
  >Use `git status` to  all new or modified files that haven't yet been committed. 

### 加粗

> **加粗**      __加粗__             					快捷键 Ctrl+B  

### 斜体

> *斜体*     _斜体_     							  快捷键 Ctrl+I

### 删除线

>~~this was mistake text~~           		快捷键 Ctrl+U

### 高亮显示

>   ==文字==

### 上标下标

>   上标：x^2^
>
>   下标：H~2~O

### 注释

>   <!--这一段不要显示-->

### 内联公式

>   $公式$

### emoji 图标

>   语法：：+图标名称

***

### 无序列表

> * *+空格+列表名
> * ++空格+列表名
> * -+空格+列表名

### 有序列表

> 1. 有序列表1
> 2. 有序列表2
> 3. 有序列表3

### 任务列表

~~~
 格式：-+空格+[+空格+]+空格 列表项
 - [ ] 跑步
 - [ ] 骑车
 - [x] 吃饭
 - [ ] 睡觉
~~~

***

### 超链接

> 语法：           快捷键 Ctrl+K
>
> ```
>     [打开百度](http://www.baidu.com)
>     [打开百度](http://www.baidu.com "打开百度")
>     说明：[]里写链接名字，()里写链接地址
> ```

[打开百度](http://www.baidu.com)

### 自动连接

> 语法：
>
> ```
>  <http://www.baidu.com/>
>  说明：Markdown 支持以比较简短的自动链接形式来处理网址和电子邮件信箱，只要是用<>包起来
> ```

***

### 表格

> 语法：                      快捷键 Ctrl+T
>
> 使用竖杠下划线写法
>
> ```
>   |名字|性别|年龄|国籍|
>   |---|----|----|---|
> ```

| 名字 | 性别 | 年龄 | 国籍 |
| :--: | :--: | :--: | :--: |
|      |      |      |      |

### 插入图片

>语法：!+[+]+(+)
>
>说明：[]里写图片名字，()里写图片链接地址，可以是本地地址

### 流程图支持

>   说明：Flowchat、Sequence、Mermaid引擎，支持多种流程图、时序图、甘特图
>
>   使用方法：三个~ 语言框输入flow或者mermaid,即可打开流程图

***

### 分割线

在一空行输入***或者---然后按下回车

***

### 参考链接

>语法：正文中引用使用[+^+序号]
>
>参考附录：[+^+序号+]+:引用附录

***

### 附录

[Typora 编辑器 —— 书写即为美学](http://www.bilibili.com/video/BV1yW411s7og?from=search&seid=1847845888036815230)