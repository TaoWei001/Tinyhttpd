# Tinyhttpd
To analazy this project in detail. And this project is about http protocol.

https://github.com/EZLippi/Tinyhttpd

tinyhttpd是一个轻量级的http server

常见的web server有：
1.Apache
2.Lighttpd
3.Tomcat
4.IBM WebSphere
5.IIS
6.Nginx

HTTP的请求连接过程
前言
在浏览项目之前，需要先回顾一下计算机网络的相关知识，其实该问题也可以总结为一道面试题：
当我们在web浏览器的地址栏中输入：www.baidu.com，具体发生了什么？

概述
1. 对www.baidu.com这个网址进行DNS域名解析，得到对应的IP地址
2. 根据这个IP，找到对应的服务器，发起TCP的三次握手
3. 建立TCP连接后发起HTTP请求
4. 服务器响应HTTP请求，浏览器得到html代码
5. 浏览器解析html代码，并请求html代码中的资源（如js、css、图片等）（先得到html代码，才能去找这些资源）
6. 浏览器对页面进行渲染呈现给用户
7. 服务器关闭关闭TCP连接

上述的2.3.4步骤应该就是项目要核心介绍和实现的部分：HTTP的请求连接过程。

HTTP协议
众所周知，HTTP协议是建立在TCP网络连接协议基础之上的一种web通信协议，它有“四个基于”的特点：

请求与响应：客户端发送请求，服务器端响应数据

无状态的：协议对于事务处理没有记忆能力，客户端第一次与服务器建立连接发送请求时需要进行一系列的安全认证匹配等，因此增加页面等待时间，当客户端向服务器端发送请求，服务器端响应完毕后，两者断开连接，也不保存连接状态，颇有提上裤子不认人的意味，下一次客户端向同样的服务器发送请求时，由于他们之前已经遗忘了彼此，所以需要重新建立连接。

应用层：Http是属于应用层的协议，配合TCP/IP使用。

TCP/IP：Http使用TCP作为它的支撑运输协议。HTTP客户机发起一个与服务器的TCP连接，一旦连接建立，浏览器（客户机）和服务器进程就可以通过套接字接口访问TCP。










HTTP交互流程
 一般分为四个步骤(一次完整的请求)： 
步骤一: 客户端和服务器端建立连接 
步骤二：客户端发送请求数据到服务器端(HTTP 协议) 
步骤三：服务器端接收到请求后，进行处理，然后将 处理结果响应客户端(HTTP 协议) 
步骤四：关闭客户端和服务器端的连接(HTTP1.1 后不会立即关闭)
01-请求连接过程（三次握手）

02-Socket连接过程


03-客户端发起HTTP请求
http的请求格式
请求行：请求方式、请求的地址和 HTTP 协议版本 
请求头：消息报头，一般用来说明客户端要使用的一些附加信息 
空行： 位于请求行和请求数据之间，空行是必须的。 请求数据：非必须。
请求方法
GET	GET方法请求一个指定资源的表示形式，使用GET的请求应该只被用于获取数据。
HEAD	HEAD方法请求一个与GET请求的响应相同的响应，但没有响应体。
POST	POST方法用于将实体提交到指定的资源，通常导致在服务器上的状态变化或副作用。
PUT	PUT方法用请求有效载荷替换目标资源的所有当前表示。
DELETE	DELETE方法删除指定的资源。
CONNECT	CONNECT方法建立一个到由目标资源标识的服务器的隧道。
OPTIONS	OPTIONS方法用于描述目标资源的通信选项。
TRACE	TRACE方法沿着到目标资源的路径执行一个消息环回测试。
PATCH	PATCH方法用于对资源应用部分修改。
POST请求示例：
POST / HTTP1.1
Host:www.wrox.com
User-Agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022)
Content-Type:application/x-www-form-urlencoded
Content-Length:40
Connection: Keep-Alive

name=Professional%20Ajax&publisher=Wiley
04-服务器端响应客户端
http响应格式 
响应行(状态行)：HTTP 版本、状态码、状态消息 
响应头：消息报头，客户端使用的附加信息 
空行：响应头和响应实体之间的，必须的。 
响应实体：正文，服务器返回给浏览器的信息
http响应状态码
1xx：指示信息--表示请求已接收，继续处理
2xx：成功--表示请求已被成功接收、理解、接受
3xx：重定向--要完成请求必须进行更进一步的操作
4xx：客户端错误--请求有语法错误或请求无法实现
5xx：服务器端错误--服务器未能实现合法的请求

响应头部
● 与请求头部类似，为响应报文添加了一些附加信息。常见响应头部如下：
  ○ Server：服务器应用程序软件的名称和版本
  ○ Content-Type：响应正文的类型（是图片还是二进制字符串）
  ○ Content-Length：响应正文长度
  ○ Content-Charset：响应正文使用的编码
  ○ Content-Encoding：响应正文使用的数据压缩格式
  ○ Content-Language：响应正文使用的语言
示例：

源码阅读
别人的阅读建议：https://www.codedump.info/post/20200605-how-to-read-code-v2020/
1.先跑起来
2.明确自己的目的
3.区分主线和支线剧情
4.纵向和横向
5.情景分析
6.利用好测试用例
7.理清核心数据结构直接的关系
8.多问自己几个问题
9.写自己的代码阅读笔记
（1）直接阅读
（2）带着问题去阅读
（3）带着解决方案去阅读

程序执行流程图

主要函数分析 
main
main函数通过startup函数来绑定和监听端口，accept一个客户端连接后创建一个线程调用accept_request函数来处理用户发来的HTTP请求报文。
sockaddr_in数据结构
sockaddr_in在头文件#include<netinet/in.h>或#include <arpa/inet.h>中定义，该结构体解决了sockaddr的缺陷，把port和addr 分开储存在两个变量中，如下：
struct sockaddr_in {
    short   sin_family;         //address family
    u_short sin_port;           //16 bit TCP/UDP port number
    struct  in_addr sin_addr;   //32 bit IP address
    char    sin_zero[8];        //not use, for align
};
sin_family 表示地址族，如AF_INET（IPv4）, AF_INET6（IPv6）
sin_port    表示16位TCP/UDP 端口号，例如：htons(3490)
在该结构体中提到的另一个结构体in_addr定义如下，它用来存放32 bit IP地址。
//
// IPv4 Internet address
// This is an 'on-wire' format structure.
//
typedef struct in_addr {
        union {
                struct { UCHAR s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { USHORT s_w1,s_w2; } S_un_w;
                ULONG S_addr;
        } S_un;
#define s_addr  S_un.S_addr /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_net   S_un.S_un_b.s_b1    // network
#define s_imp   S_un.S_un_w.s_w2    // imp
#define s_impno S_un.S_un_b.s_b4    // imp #
#define s_lh    S_un.S_un_b.s_b3    // logical host
} IN_ADDR, *PIN_ADDR, FAR *LPIN_ADDR;
sin_port和sin_addr都必须是网络字节序（NBO），一般可视化的数字都是主机字节序（HBO）
一般的用法为：
把类型、ip地址、端口填充sockaddr_in结构体，然后强制转换成sockaddr，作为参数传递给系统调用函数
//创建sockaddr_in结构体变量
struct sockaddr_in serv_addr;
memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
serv_addr.sin_family = AF_INET;  //使用IPv4地址
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
serv_addr.sin_port = htons(1234);  //端口号
htons()作用是将端口号由主机字节序转换为网络字节序的整数值。(host to net)
inet_addr()作用是将一个IP字符串转化为一个网络字节序的整数值，用于sockaddr_in.sin_addr.s_addr。
startup
启动server socket的函数。
1.创建socket：httpd = socket(PF_INET, SOCK_STREAM, 0);
2.初始化sockaddr_in数据：
memset(&name, 0, sizeof(name));
name.sin_family = AF_INET;
name.sin_port = htons(*port);
name.sin_addr.s_addr = htonl(INADDR_ANY);
3.bind绑定端口：bind(httpd, (struct sockaddr*)&name, sizeof(name))
4.listen监听端口：listen(httpd, 5);

pthread_create
在while循环中每使用accept成功连接一个客户端时，就创建一个新线程用于处理客户端请求
accept_request
用于读取并解析HTTP报文请求的函数
1. 提取 request 的类型（GET 或 POST）
2. 提取 url 信息
3. 如果是 GET 请求，提取 url 中的参数信息（?之后的内容）
4. 如果 url 结尾是 / 或者改地址对应一个目录，默认调用该目录下的 index.html
5. 如果不是 CGI，则调用 serve_file，将地址中的内容返回给客户端
6. 如果是 CGI，调用 execute_cgi，执行 CGI 脚本程序
7. 断开连接

通过getline按行处理HTTP请求
● 请求行
  ○ 将请求方法放在 method 中，只能处理 get 或者 post 方法，如果是 post 方法设置 cgi 处理标识。
  ○ 判断是何种 method（GET or POST）以及获取 url。对于 GET 方法，如果携带参数，设置 cgi 处理标识，截断 url，并将 query_string 指针指向 url 中 ? 后面的 GET 参数。
  ○ 将 htdocs 与 url 拼接为 path，如果 path 最后一个字符是‘/’，则继续拼接 index.html，即默认访问 path 下的 index.html 文件。
  ○ 如果 path 所指的文件不存在，读取并丢弃剩余请求首部，并向客户端返回 404 错误。
  ○ 如果 path 所指文件存在，是目录则拼接 index.html，是文件则根据是否可执行设置 cgi 标识。
  ○ 根据 cgi 标识决定执行 serve_file 还是 execute_cgi 。

getline 
该函数不管行原来是以 \n、\r 还是 \r\n 结束，均转化为以\n 再加\0 字符结束。

附：
换行、回车历史
这里主要介绍“回车”（carriage return \r）和 “换行”（line feed \n）这两个概念的来历和区别。

在计算机还没有出现之前，有一种叫做电传打字机（Teletype Model 33）的玩意，每秒钟可以打 10 个字符。但是它有一个问题，就是打完一行换行的时候，要用去 0.2 秒，正好可以打两个字符。要是在这 0.2 秒里面，又有新的字符传过来，那么这个字符将丢失。

于是，研制人员想了个办法解决这个问题，就是在每行后面加两个表示结束的字符。一个叫做 “回车”，告诉打字机把打印头定位在左边界；另一个叫做 “换行”，告诉打字机把纸向下移一行。这就是 “换行” 和 “回车” 的来历，从它们的英语名字上也可以看出一二。

后来，计算机发明了，这两个概念也就被般到了计算机上。那时，存储器很贵，一些科学家认为在每行结尾加两个字符太浪费了，加一个就可以。于是，就出现了分歧：Unix 系统里，每行结尾只有 “<换行>（\n）”；Windows 系统里面，每行结尾是 “<换行><回车>（\n\r）”，Mac 系统里，每行结尾是 “<回车>（\r）”。一个直接后果是，Unix/Mac 系统下的文件在 Windows 里打 开的话，所有文字会变成一行；而 Windows 里的文件在 Unix/Mac 下打开的话，在每行的结尾可能会多出一个 ^M 符号。

c 语言编程时(linux) \r 就是回到本行行首，这就会把这一行以前的输出覆盖掉。
#include <stdio.h>
int main(int argc, char *argv[])
{
    printf("hahahaha\rxixixi");
    return 0;
}
最后只显示 xixi，而 hahaha 被覆盖了。

\n 是回车＋换行，把光标先移到行首，然后换到下一行，也就是下一行的行首。
#include <stdio.h>
int main(int argc, char *argv[])
{
    printf("hahaha\nxixi\n");
    return 0;
}
execute_cgi
主要做的事情就是 fork 一个子进程执行可执行文件，然后通过管道将结果返回父进程，进而返回客户端。
1. 对 POST 请求，根据 Content-Length 提取 body 中的信息
2. 创建两个管道 cgi_input 和 cgi_output 用于进程间通信
3. 调用 fork 建立子进程
4. 子进程调用 dup2 将标准输入与标准输出分别重定向到对应管道的读端和写端
5. 在子进程中设置环境变量，并调用 execl，执行 CGI 脚本
6. 父进程通过管道向 CGI 脚本传入参数，并获取脚本的返回结果，再将结果传给客户端
7. 父进程等待子结束

● 如果是 get 方法，就读取并丢弃整个 http 首部。如果是 post 方法，还会从中 content_length 长度。
● 建立两个管道， cgi_input 和 cgi_output ，并 fork 一个进程（必须 fork 子进程，pipe 管道才有意义）。建立父子进程间的通信机制。
● 在子进程中，对其进程下的管道进行重定向，并设置对应的环境变量（method、 query_string 、 content_length ），这些环境变量都是为了给 cgi 脚本调用，接着用 execl 运行 cgi 脚本，可以看出 cgi 脚本的执行在子进程中进行，然后结果通过管道以及重定向返回给父进程。
● 父进程中，关闭管道一端，如果是 POST 方式，则把 POST 数据写入 cgi_intput ，已被重定向到 STDIN，读取 cgi_output 。 管道输出到客户端（浏览器输出），具体流程图参见上面的管道最终状态图。接着关闭所有管道，等待子进程结束。
● 关闭连接，完成一次 HTTP 请求与回应。

CGI
CGI 即 Common Gateway Interface，译作“通用网关接口”。
1. Common
通用，是一个显著特征。虽然我们听说过Java的Servlet，Python的WSGI。但其实Java、Python都是支持CGI的，不仅如此，其他我们所熟知的语言大都也都支持。理论上来说，所有支持标准输出，支持获取环境变量的编程语言都能用来编写CGI程序。

第一个版本的CGI由Perl语言编写的脚本，因此通常称之为“CGI脚本”。如今呢，上古巫术Perl早已淡出人们视野，CGI这技术虽然通用，但是实则真正仍在应用的恐怕只有C/C++了。
2. Gateway
网关，更形象的叫法是“协议翻译机”。CGI程序用于翻译网关的输入输出协议。

CGI程序通常部署到Web服务器（如Apache）上，Web服务器然后调用CGI程序，关于CGI程序到底如何从Web服务器中获得输入，请继续阅读下一节 Interface。请注意区分Web Server和后台Server。

3. Interface
接口，确切而言是“接口协议”，所谓协议，既是通信双方或多方都共识并遵守的一套规则。

输入，输出
CGI程序本质是OS上一个普通的可执行程序，它通过语言本身库函数来获取环境变量，从而获得数据输入。

除环境变量外，另外一个CGI程序获取数据的方式就是标准输入（stdin）。

而CGI如何构造出数据（比如HTML页面）返回给浏览器呢？其实CGI本身只要向标准输出（stdout）去写入数据即可。比如printf、cout，比如System.out.println，又比如print、echo等。因为Web服务器已经做了重定向，将标准输出重定向给Web服务器的与浏览器连接的socket。

4. 硬伤
每次HTTP请求CGI，Web服务器都有启动一个新的进程去执行这个CGI程序，即颇具Unix特色的fork-and-execute。当用户请求量大的时候，这个fork-and-execute的操作会严重拖慢Web服务器的性能。


时势造英雄，FastCGI（简称FCGI）技术应运而生。简单来说，其本质就是一个常驻内存的进程池技术，由调度器负责将传递过来的CGI请求发送给处理CGI的handler进程来处理。在一个请求处理完成之后，该处理进程不销毁，继续等待下一个请求的到来。

CGI脚本的结构
典型的CGI脚本做了如下的事情：
1. 读取用户提交表单的信息。
2. 处理这些信息（也就是实现业务）。
3. 输出，返回html响应（返回处理完的数据）。


编码
注释规范
1.文件注释
内容一般是:版权,作者,编写日期,功能描述
/**************************************************************************
Copyright:MyCompany
Author: Arwen
Date:2013-01-09
Description:Provide  functions  to connect Oracle
**************************************************************************/

2.类注释
一般是简单的说下这个类的功能,
// COleDataObject -- simple wrapper for IDataObject
class COleDataObject
{undefined

}
3.函数注释
函数声明处注释的一般内容：
（1）函数功能简介；
（2）函数参数说明；
（3）函数返回值说明；
/*
*Summary: connect the database
*Parameters:
*    connInfo:A class contains the connect info ,such as user name ,pwd,etc.*    
*    directConnect : use TNS name or use direct connection info
*Return : true is connect successfully.
*/

4.变量注释
一个变量如果代表的意思不容易从变量名看出来,而且又挺重要的话最好也加点注释.例
UINT m_nGrowBy;     // number of cache elements to grow by for new allocs

5.实现注释
在一些逻辑性很强,不容易理解的代码块前添加注释.特别是是像一些算法,

还有就是如果想针对函数的某些个参数做些注释,那最好把参数分几行写.
void MyFunction(string name, //This is my name
int age)
6.TODO注释
如果项目中存在功能代码有待修改和编写地方，建议使用TODO注释进行简略说明。TODO注释的作用类似于书签，便于开发者快速找到需要继续开发的位置和有待完成的功能，起到提醒标记的作用。
// TODO(kl@gmail.com): Use a "*" here for concatenation operator.
// TODO(Zeke): change this to use relations.
// TODO(bug 12345): remove the "Last visitors" feature
7.弃用注释
可以写上包含全大写的 DEPRECATED 的注释，以标记某接口为弃用状态。

弃用注释应当包涵简短而清晰的指引，以帮助其他人修复其调用点。
// DEPRECATED(dablelv):new interface changed to bool IsTableFull(const Table& t)
bool IsTableFull();

从编码角度上讲没有太多技巧和难点。要注意的有：
一是get_line函数，按行获取HTTP报文的处理方法。
二是注意函数的参数传递和返回。

问题
1.多线程编程
每接收一个客户端连接后，都会启动一个线程去处理新的连接，而在新线程处理请求的过程中，又使用fork函数创建了进程来执行CGI脚本。因此，在线程中创建进程是允许的吗？

答：
（1）首先要理清进程和线程的区别：
进程：进程的经典定义就是一个执行中的程序的实例。系统中的每个程序都是运行在某个进程的context中的。context是由程序正确运行所需的状态组成的，这个状态包括存放在存储器中的程序的代码和数据，它的栈、通用目的寄存器的内容、程序计数器（PC）、环境变量以及打开的文件描述符的集合。

进程主要提供给上层的应用程序两个抽象：
● 一个独立的逻辑控制流，它提供一个假象，好像我们程序独占的使用处理器。
● 一个私有的虚拟地址空间，它提供一个假象，好像我们的程序独占的使用存储器系统。
线程，就是运行在进程context中的逻辑流。线程由内核自动调度。每个线程都有它自己的线程context，包括一个唯一的整数线程ID、栈、栈指针、程序计数器（PC）、通用目的寄存器和条件码。每个线程和运行在同一进程内的其他线程一起共享进程context的剩余部分。这包括整个用户虚拟地址空间，它是由只读文本（代码）、读/写数据、堆以及所有的共享库代码和数据区域组成。线程也同样共享打开文件的集合。

即进程是资源管理的最小单位，而线程是程序执行的最小单位。
在linux系统中，posix线程可以“看做”为一种轻量级的进程，pthread_create创建线程和fork创建进程都是在内核中调用__clone函数创建的，只不过创建线程或进程的时候选项不同，比如是否共享虚拟地址空间、文件描述符等。

联系
一个进程至少拥有一个线程——主线程，也可以拥有多个线程；一个线程必须有一个父进程。多个进程可以并发执行；一个线程可以创建和撤销另一个线程；同一个进程中的多个线程之间可以并发执行。

与此同时，在Linux系统中创建进程有两种方式：一是由操作系统创建，二是由父进程创建进程（通常为子进程）。系统调用函数fork()是创建一个新进程的唯一方式，当然vfork()也可以创建进程，但是实际上其还是调用了fork()函数。

因此，进程是可以随时创建的，与是否在线程中创建并无关系。
扩展-多线程编程与fork
1.关于fork
当程序调用fork()函数并返回成功之后，程序就将变成两个进程，调用fork()者为父进程，后来生成者为子进程。这两个进程将执行相同的程序文本，但却各自拥有不同的栈段、数据段以及堆栈拷贝。子进程的栈、数据以及栈段开始时是父进程内存相应各部分的完全拷贝，因此它们互不影响。从性能方面考虑，父进程到子进程的数据拷贝并不是创建时就拷贝了的，而是采用了写时拷贝（copy-on -write）技术来处理。调用fork()之后，父进程与子进程的执行顺序是我们无法确定的（即调度进程使用CPU），

在Linux系统中，常常存在许多对文件的操作，fork()的执行将会对文件操作带来一些小麻烦。由于子进程会将父进程的大多数数据拷贝一份，这样在文件操作中就意味着子进程会获得父进程所有文件描述符的副本，这些副本的创建方式类似于dup()函数调用，因此父、子进程中对应的文件描述符均指向相同的打开的文件句柄，而且打开的文件句柄包含着当前文件的偏移量以及文件状态标志，所以在父子进程中处理文件时要考虑这种情况，以避免文件内容出现混乱或者别的问题。

2.关于多线程
多线程模式，指一个进程具有多个线程。
但是有一点需要注意的是，在Linux中，fork的时候只复制当前线程到子进程，在fork(2)-Linux Man Page中有着这样一段相关的描述：
The child process is created with a single thread--the one that called fork(). The entire virtual address space of the parent is replicated in the child, including the states of mutexes, condition variables, and other pthreads objects; the use of pthread_atfork(3) may be helpful for dealing with problems that this can cause.
也就是说除了调用fork的线程外，其他线程在子进程中“蒸发”了。这就是多线程中fork所带来的一切问题的根源所在了。

在多线程执行的情况下调用fork()函数，仅会将发起调用的线程复制到子进程中。（子进程中该线程的ID与父进程中发起fork()调用的线程ID是一样的，因此，线程ID相同的情况有时我们需要做特殊的处理。）也就是说不能同时创建出于父进程一样多线程的子进程。其他线程均在子进程中立即停止并消失，并且不会为这些线程调用清理函数以及针对线程局部存储变量的析构函数。造成如下问题：
（1）线程死锁
（2）内存泄漏

3.关于exec函数
因此，在多线程中调用fork的唯一情况是：其后立即调用exec()函数执行另一个程序，彻底隔断子进程与父进程的关系。由新的进程覆盖掉原有的内存，使得子进程中的所有pthreads对象消失。

其实即使这样做还是有一点不足。因为子进程会继承父进程中所有已打开的文件描述符，所以在执行exec之前子进程仍然可以读写父进程中的文件，但如果不希望子进程能读写父进程里的某个已打开的文件该怎么办？
或许fcntl设置文件属性是一种办法：

4.pthread_atfork
对于那些必须执行fork()，而其后又无exec()紧随其后的程序来说，pthreads API提供了一种机制：fork()处理函数。利用函数pthread_atfork()来创建fork()处理函数。



代码解释
关于execute_cgi
dup2函数
#include <unistd.h>
int dup(int oldfd);
int dup2(int oldfd, int newfd);
当调用dup函数时，内核在进程中创建一个新的文件描述符，此描述符是当前可用文件描述符的最小数值，这个文件描述符指向oldfd所拥有的文件表项。
	dup2和dup的区别就是可以用newfd参数指定新描述符的数值，如果newfd已经打开，则先将其关闭。如果newfd等于oldfd，则dup2返回newfd, 而不关闭它。dup2函数返回的新文件描述符同样与参数oldfd共享同一文件表项。
APUE用另外一个种方法说明了这个问题：
实际上，调用dup(oldfd)等效于，fcntl(oldfd, F_DUPFD, 0)
而调用dup2(oldfd, newfd)等效于，close(oldfd)；fcntl(oldfd, F_DUPFD, newfd)；
CGI中的dup2
dup2函数的作用是在CGI中进行文件描述符重定向
当浏览器使用post方法提交表单数据时，CGI读数据是从标准输入stdin，写数据是写到标准输出stdout(C语言利用printf函数)。按照我们正常的理解，printf的输出应该在终端显示，原来CGI程序使用dup2函数将STDOUT_FINLENO(这个宏在unitstd.h定义，为１)这个文件描述符重定向到了连接套接字：dup2(connfd, STDOUT_FILENO)。

一个进程默认的文件描述符１(STDOUT_FILENO)是和标准输出stdout相关联的，对于内核而言，所有打开的文件都通过文件描述符引用，而内核并不知道流的存在(比如stdin、stdout)，所以printf函数输出到stdout的数据最后都写到了文件描述符１里面。至于文件描述符0、１、2与标准输入、标准输出、标准错误输出相关联，这只是shell以及很多应用程序的惯例，而与内核无关。
 用下面的流图可以说明问题(ps: 虽然不是流图关系，但是还是有助于理解)：
 printf －> stdout －> STDOUT_FILENO(1) －> 终端(tty)
 printf最后的输出到了终端设备，文件描述符１指向当前的终端可以这么理解：
 STDOUT_FILENO = open(“/dev/tty”, O_RDWR);
 使用dup2之后STDOUT_FILENO不再指向终端设备，而是指向connfd, 所以printf的输出最后写到了connfd。是不是很优美？

如何在CGI程序的fork子进程中还原STDOUT_FILENO
STDOUT_FILENO被重定向到了connfd套接字，有时候我们可能想在CGI程序中调用后台脚本执行，而这些脚本中难免会有一些输入输出，我们知道fork之后，子进程继承了父进程的所有文件描述符，所以这些脚本的输入输出并不会如我们愿输出到终端设备，而是和connfd想关联了，这个显然会扰乱网页的输出。那么如何恢复STDOUT_FILENO和终端关联呢？
方法１：在dup2之前保存原有的文件描述符，然后恢复。
 代码实现如下：
 savefd = dup(STDOUT_FILENO); ／savefd此时指向终端/
 dup2(connfd, STDOUT_FILENO);
 …..
 dup2(savefd, STDOUT_FILENO);
 很遗憾CGI程序无法使用这种方法，因为dup2这些不是在CGI程序中完成的，而是在web server中实现的，修改web server并不是个好主意。
方法2: 追本溯源，打开当前终端恢复STDOUT_FILENO。
 分析第三节的流图，STDOUT_FILENO是如何和终端关联的？我们重头做一遍不就行了，代码实现如下：
 ttyfd = open(“/dev/tty”, O_RDWR);
 dup2(ttyfd, STDOUT_FILENO);
 close(ttyfd);
 /dev/tty是程序运行所在的终端，这个应该通过一种方法获得。实践证明这种方法是可行的，但是个人总感觉有些不妥，不知道为什么，可能一些潜在的问题还没出现。

pipe函数
管道(pipe)
管道可用于具有亲缘关系进程间的通信，有名管道克服了管道没有名字的限制，因此，除具有管道所具有的功能外，它还允许无亲缘关系进程间的通信；
父子进程通信过程解析
（1）父进程创建管道，得到两个文件描述符指向管道的两端；
● 该进程既可以往写入端描述符写入信息，也可以从读取端描述符读出信息。 可是一个进程管道，起不到任何通信的作用。这不是通信，而是自言自语。

（2）父进程fork出子进程，子进程也有两个文件描述符指向同一个管道。
● 此时，可以是父进程往管道里写，子进程从管道里面读；也可以是子进程往管道里写，父进程从管道里面读。这两条通路都是可选的，但是不能都选，原因如下。
● 管道里面是字节流，父子进程都写、都读，就会导致内容混在一起，对于读管道的一方，解析起来就比较困难

（3）父进程关闭fd[0]（读端）,子进程关闭fd[1]（写端），因为管道只支持单向通信。
● 父进程可以往管道写,子进程可以从管道读,管道是由环形队列实现的,

（4）父进程的两个子进程之间如何利用管道通信？
● 父进程再次创建一个子进程B，子进程B就持有管道写入端，这时候两个子进程之间就可以通过管道通信了。
● 父进程为了不干扰两个子进程通信，很自觉地关闭了自己的写入端。从此管道成为了两个子进程之间的单向的通信通道。

实现细节：
在 Linux 中，管道的实现并没有使用专门的数据结构，而是借助了文件系统的file结构和VFS的索引节点inode。通过将两个 file 结构指向同一个临时的 VFS 索引节点，而这个 VFS 索引节点又指向一个物理页面而实现的。如下图

有两个 file 数据结构，但它们定义文件操作例程地址是不同的，其中一个是向管道中写入数据的例程地址，而另一个是从管道中读出数据的例程地址。这样，用户程序的系统调用仍然是通常的文件操作，而内核却利用这种抽象机制实现了管道这一特殊操作。

关于管道的读写
管道实现的源代码在fs/pipe.c中，在pipe.c中有很多函数，其中有两个函数比较重要，即管道读函数pipe_read()和管道写函数pipe_wrtie()。管道写函数通过将字节复制到 VFS 索引节点指向的物理内存而写入数据，而管道读函数则通过复制物理内存中的字节而读出数据。当然，内核必须利用一定的机制同步对管道的访问，为此，内核使用了锁、等待队列和信号。

当写进程向管道中写入时，它利用标准的库函数write()，系统根据库函数传递的文件描述符，可找到该文件的 file 结构。file 结构中指定了用来进行写操作的函数（即写入函数）地址，于是，内核调用该函数完成写操作。写入函数在向内存中写入数据之前，必须首先检查 VFS 索引节点中的信息，同时满足如下条件时，才能进行实际的内存复制工作：
·内存中有足够的空间可容纳所有要写入的数据；
·内存没有被读程序锁定。

如果同时满足上述条件，写入函数首先锁定内存，然后从写进程的地址空间中复制数据到内存。否则，写入进程就休眠在 VFS 索引节点的等待队列中，接下来，内核将调用调度程序，而调度程序会选择其他进程运行。写入进程实际处于可中断的等待状态，当内存中有足够的空间可以容纳写入数据，或内存被解锁时，读取进程会唤醒写入进程，这时，写入进程将接收到信号。当数据写入内存之后，内存被解锁，而所有休眠在索引节点的读取进程会被唤醒。

管道的读取过程和写入过程类似。但是，进程可以在没有数据或内存被锁定时立即返回错误信息，而不是阻塞该进程，这依赖于文件或管道的打开模式。反之，进程可以休眠在索引节点的等待队列中等待写入进程写入数据。当所有的进程完成了管道操作之后，管道的索引节点被丢弃，而共享数据页也被释放。

Linux函数原型
#include <unistd.h> 
int pipe(int filedes[2]);
filedes[0]用于读出数据，读取时必须关闭写入端，即close(filedes[1]);
filedes[1]用于写入数据，写入时必须关闭读取端，即close(filedes[0])。

示例：
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int fds[2];
    if(pipe(fds) < 0){//创建一个管道，用于父子间进行通信
        perror("pipe");
        return 1;
    }
    char buf[1024];//临时数组，用于存放通信的消息
    
    printf("Please enter：");
    fflush(stdout);//对标准输出流的清理，但是它并不是把数据丢掉，而是及时地打印数据到屏幕上
    ssize_t s =  read(0,buf,sizeof(buf)-1);//0对应文件描述符
    if(s > 0){//判断读取的字节数
        buf[s] = 0;
    }
    
    pid_t pid = fork();//fork()子进程
    if(pid == 0){//子进程只写,关闭读端
        close(fds[0]);
        while(1){
            sleep(1);
            write(fds[1],buf,strlen(buf));//将buf的内容写入管道
        }
    }
    else{//父进程只读，关闭写端
        close(fds[1]);
        char buf1[1024];
        while(1){
            ssize_t s = read(fds[0],buf1,sizeof(buf1)-1);//从管道里读数据，放入buf
            if(s > 0){
                buf1[s-1] = 0;
                printf("client->farther：%s\n",buf1);
            }
        }
    }
}

Git操作
項目文件保存在Ubuntu的一个文件夹中: /home/taowei/Project/Tinyhttpd

1.先在GitHub上创建一个仓库 Tinyhttpd

2.修改Tinyhttpd文件夹权限
chmod 777 Tinyhttpd

3.将该文件夹进行本地仓库初始化
git init

4.配置GitHub账户信息
git config --global user.name "TaoWei001"
git config --global user.email "1104148232@qq.com"

5.配置GitHub访问代理
使用http代理方式
git config --global http.proxy "http://127.0.0.1:1081"
git config --global https.proxy "http://127.0.0.1:1081"
端口号根据代理插件自己查看确定

6.配置token访问令牌
操作步骤：https://blog.csdn.net/qq_39045645/article/details/119833309
（1）在GitHub中生成token令牌，并复制令牌号码
（2）把token直接添加远程仓库链接中，这样就可以避免同一个仓库每次提交代码都要输入token了：
git remote set-url origin https://<your_token>@github.com/<USERNAME>/<REPO>.git

<your_token>：换成得到的token号码
<USERNAME>：换成自己github的用户名
<REPO>：换成自己的仓库名称



7.查看本地分支情况
git branch
发现Ubuntu20在进行本地仓库初始化之后，只有master分支，而现在GitHub都改成了main分支，所有要创建main分支
 
8.创建main分支
git branch main
git checkout main 

9.添加远程分支
git remote add origin git@github.com:username/repo_name.git

10.开始推送本地文件到远程仓库
git add .
git commit -m "commit descripiton"
git push -u origin main

但是出现以下报错：
To https://github.com/TaoWei001/Tinyhttpd.git
 ! [rejected]        main -> main (non-fast-forward)
error: 推送一些引用到 'https://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@github.com/TaoWei001/Tinyhttpd.git' 失败
提示：更新被拒绝，因为您当前分支的最新提交落后于其对应的远程分支。
提示：再次推送前，先与远程变更合并（如 'git pull ...'）。详见
提示：'git push --help' 中的 'Note about fast-forwards' 小节。
git官网上基于此提出的问题背景是：
Sometimes, Git can’t make your change to a remote repository without losing commits. When this happens, your push is refused.If another person has pushed to the same branch as you, Git won’t be able to push your changes.
即远端仓库有了比你本地分支更新的commit，不允许你的此次修改直接推送到远端分支。

网上搜索后找到解决方案：
https://blog.csdn.net/index20001/article/details/99764558
方案一：官网上给出的方法是
fix this by fetching and merging the changes made on the remote branch with the changes that you have made locally, or you can simply use git pull to perform both commands at once.
可以通过fetching and merging或者与其相同作用的pull解决，把远端已更新的项目拉回本地与你的本次修改合并，再push
注意pull前本次修改要提前commit到本地分支上；fetch merge pull的参数都要注意
$ git fetch origin
#Fetches updates made to an online repository
$ git merge origin YOUR_BRANCH_NAME
#Merges updates made online with your local work

$ git pull origin YOUR_BRANCH_NAME
#Grabs online updates and merges them with your local work
方案二：（本项目提交时采用此方案）
事实上，如果是两个不同的项目，可能会不允许简单地pull
$ git pull origin master --allow-unrelated-histories
#这条命令允许了不同项目的合并
接下来就可以进行push
$ git push origin master

最后推送成功！



















