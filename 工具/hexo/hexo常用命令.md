# hexo常用命令

## hexo init

**用于初始化本地文件夹为网站的根目录**

*   使用方式：hexo init  [目录名]
*   目录名是可选参数，如果未指定初始化目录，则默认为当前目录

## hexo new

**用于创建新的文件(文章)**

*   使用方法：hexo n [layout]  <title>
*   n是new的缩写
*   layout：可选参数，用于指定布局

>   hexo支持三种布局(layout) :  post(默认)、draft、page
>
>   若未指定，默认由配置文件中的default_layout选项决定

*   title：必填参数，用于指定生成的md文件名，如果文章名含有空格，文章名需要使用双引号包含

>   创建的文章位于source/_posts目录下
>
>   创建的md文件以Front-matter开头(其实就是该文章的一些变量，用于实现一些特定的功能)
>
>   ```
>   ---
>   title: xxx
>   author: xxx
>   date: xxx
>   tags: xxx
>   categories:xxx
>   ---
>   ```

*   如何自定义Front-matter布局

>   修改scaffolds/目录下的draft.md/page.md/post.md文件

*   草稿

>   使用hexo n draft xxx命令将在source目录下创建_drafts目录，并生成一个xxx.md文件
>
>   编辑完草稿后，可以使用hexo publish xxx 把文章推送到_posts目录下
>
>   使用hexo  --draft命令查看已有的草稿

## hexo clean

清除缓存文件db.json和已生成的静态文件public

*   博客网站显示异常时，可以尝试使用此命令

## hexo g

生成网站静态文件到默认设置的public文件夹

*   g是generate的缩写
*   使用该命令，便于查看网站生成的静态文件或者手动部署网站
*   如果使用自动部署，不需要先执行该命令

## hexo d

自动生成网站静态文件，并部署到设定的仓库

*   d是deploy的缩写
*   部署前需要修改_config.yml配置文件

## hexo s

启动本地服务器，用于预览主题 

*   s是server的缩写
*   运行服务器前需要安装hexo-server插件

```shell
$ npm install hexo-server --save
```

*   默认地址：http://localhost:4000/，如果要更改端口，使用hexo s -p 端口号
*   预览的同时可以修改文章内容或者主题代码，保存后刷新页面即可
*   对hexo根目录_config.yml的修改，需要重启本地服务器后才能生效

## hexo new page

用于生成博客页面

*   使用方式：hexo new page aboutme，新建一个aboutme的页面，默认链接地址为主页地址/aboutme/

## hexo --debug

用于调试模式，将详细消息记录到终端和debug.log文件中

