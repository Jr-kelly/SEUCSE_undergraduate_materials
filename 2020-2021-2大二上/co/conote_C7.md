# co第七章

第七章里，最重要的是**I/O系统组成**和**程序直接控制I/O方式**，其次是**I/O接口**和**程序中断I/O方式**；

## I/O系统组成

### I/O系统的性能

响应时间 = 从I/O请求发出到I/O操作完成的时间；

吞吐率 = 单位时间内完成I/O操作的个数；

I/O所占CPU时间：I/O需要让CPU操作的时间/两次I/O的时间间隔；

### I/O系统的硬件

任务：实现I/O的设备连接；

外设，I/O接口，总线，传送控制部件；

### I/O系统的软件

任务：实现I/O的传送控制，何时传（工作协调），如何传（传送组织）；

实现：CPU执行I/O程序，或通道执行通道程序；

I/O程序包含多个程序段：初始化，传送控制，退出等；包含多个I/O指令；

I/O指令格式：操作码+地址码+命令码 = 操作码+I/O端口地址+信息内容；

命令码：传输的类型和内容 = 信息内容；地址码 = I/O端口地址；

### 外设与主机的连接

主机=CPU+内存 吧应该；

外设通过总线和I/O接口和CPU连接，I/O接口解决速度电平差异，暂存数据状态命令；

I/O的过程：

- 主机-接口：总线操作，接口用寄存器（大概就是端口？）暂存信息；
- 接口-外设：通信操作（是什么东西），外设就绪时接口自动实现；

操作码有InOut两种；

### 外设编址方式

#### 统一编址方式（存储器映像方式）

主存单元和外设共用一个地址空间；

无I/O指令，直接访存指令；总线控制信号也是访存控制信号MEMR#和MEMW#；（#表示取反）

I/O事务的识别：读写异或为1，地址∈外设地址范围；

省了指令，但是主存地址空间减小，并且地址译码复杂；

#### 独立编址方式

主存单元和I/O端口分别有一个地址空间；所有I/O端口共用一个地址空间；

需要I/O指令和IOR#IOW#了；

空间扩展容易，I/O地址译码简单；需增设2条机器指令和两个总线控制信号；

常被采用；

### 外设识别方法（总线操作的目标从设备识别）

I/O接口按地址主动识别；

#### I/O端口地址的组成：设备号+内部序号

设备ID被分配；表示I/O接口；

I/O接口一直监视总线状态，有I/O事务（读写异或为1）时比较地址和自己的ID；

### 外设的传送方式

#### 无条件传送方式

无需启动，随时传送；

字符设备，并行设备；

#### 条件传送方式

先启动设备，就绪后再传送；

字符/块，并行/串行；

### 外设的联络方式

联络：如何进行数据传送；

#### 无条件传送方式：立即响应方式

无需联络信号线；

#### 条件传送方式：异步联络方式

设置请求/应答线；

#### 条件传送方式：同步联络方式

设置时钟线；

### I/O的传送控制方式

目标：提高数据传输率，减少I/O所占CPU时间；

程序直接控制方式（程序查询 直接传送），程序中断方式，直接存储器访问方式（DMA），通道方式；

#### 程序直接控制方式

I/O功能：CPU-外设间，一个数据/次；

程序查询：条件传送设备；直接传送：无条件传送设备；

##### 程序查询也就是轮询：

传送控制原理：

- CPU启动设备后，不断查询设备状态；当设备准备就绪时，才进行数据传送；

CPU先发一个OUT指令说让外设启动；然后不停地执行IN指令获得外设状态；状态=就绪后执行IN/OUT来进行传送；

I/O所占CPU时间：m个指令周期（开始启动-传送完成的时延）/数据，CPU与外设串行工作；

##### 直接传送方式

控制原理：CPU随时进行数据传送；

I/O所占CPU时间：1指令周期/数据；

#### 程序中断I/O方式，中断驱动I/O方式

I/O功能：CPU-外设间，一个数据/次；

传送控制原理：

- CPU启动设备后，继续执行现行程序；
- 设备准备就绪时，向CPU提出请求；
- CPU响应请求，传送数据，返回现行程序；

I/O所占CPU时间：k指令周期（CPU中断响应+中断服务程序时延）/数据，CPU外设部分并行工作；

#### 直接存储器存取方式，DMA

传送的实现：DMA接口产生总线操作；

主存外设间，1批数据/次；适用块设备；

I/O所占CPU时间：n指令周期（传送准备+结束处理+中断响应）时延/批数据，并行；

## 外部设备

### 辅存性能指标

存储密度：不知道什么意思；会给出磁道密度（径向算）和位密度（一圈算）；

存储容量

寻址时间=寻道+等待；寻道给出，平均等待是 一转的时间/2；

数据传输率=**磁道容量*磁盘转速**；rpm：revolusions per minute；

题中给出的 外径内径什么的 是直径哦！！

==磁盘中啊，M是10^6！不是二进制那一套！==听说只有主存是二进制那一套；

==笔记最后有关于十进制二进制的讨论！！==

磁盘访问时间=寻道+等待+读写，读写远小于等待；

磁盘地址：磁道号+盘面号+扇区号；

读写：一转的时间/扇区数量；

### 关于ppt7 43页题

一次I/O所占CPU时间TINT＝(6中断响应＋10中断服务程序指令数\*5CPI)/(50\*10^6CPU主频，即乘上CPU周期长度)＝1.12μs

I/O占CPU时间% = 一次I/O所占CPU时间/2次中断请求间隔！

磁盘的数据传输率 = 磁道容量\*磁盘转速；

## I/O接口

I/O接口的功能：

- 数据缓冲：暂存数据；
- 操作中转：暂存命令；
- 状态监测：监视外设工作状态并存在寄存器内；
- 通信控制：与主机和外设通信；
- 信号转换：格式/电平/时序；

### I/O接口组成

总线缓冲器，I/O端口，设备选择，控制逻辑；

![image-20210115204019736](.\..\..\typora-user-images\image-20210115204019736.png)

#### I/O端口：

与**数据总线**交换信息的寄存器，数据口/控制口/状态口；

信息中转的实现原理：二段式，主机-端口，端口-外设；

### I/O接口分类

按数据传送方式：

- 并行接口：接口-外设间同时传送n位数据；
- 串行接口：接口-外设间1位；

按功能的选择方式：

- 可编程接口：功能通过软件选择
- 不可编程接口

按传送的控制方式：

- 查询接口：CPU控制传送，接口记录状态；字符设备；
- 中断接口：CPU控制传送，接口报告状态；字符设备；
- DMA接口：接口控制传送，报告状态；块设备；

串行接口可连接无条件传送设备？否，无条件传送设备传送1个数据/次、无联络信号线，串行传输时不同位间须进行定时，有联络信号，无法连接；

查询接口必有控制口？是，所连设备为条件传送设备，而启动设备的命令需暂存在控制口中；

### CPU访问I/O接口

执行机器指令，产生总线事务，I/O接口响应，访问一个**端口**；

## 程序直接控制I/O方式！

基本思想：CPU启动设备后，不断查询设备状态；当设备准备就绪时，才进行数据传送；

I/O所占CPU时间：开始启动/查询-数据传送完成的所有时间；

### 程序查询方式类型：

- 独占查询，启动后一直查；
- 定时查询，过一会再查；

U盘接口：串行接口。貌似上课讲过；

### I/O接口组织

条件传送方式都需要控制口，包含启动位；

==笔记最后有关于启动位的讨论==；

设置状态口，包含就绪位；

支持操作：

- 启动设备
- 查询状态
- 传送数据

直接传送方式只有数据口一个口，无控制口和状态口；

## 程序中断I/O方式

中断类型：

- 可屏蔽 不可屏蔽；
- 向量 非向量；
- 单重 多重；响应单重，处理可以多重；多重：保存现场+屏蔽字，置新屏蔽字；

### 中断接口的组织

功能：基于查询接口，产生/撤销中断请求；

端口含中断允许位EI，中断请求位INT；

EI Enable Interrupt 为1时中断，为0时查询；

EI=1&&设备就绪，INT=1；中断响应后，INT复位；大概这样，我也不知道；

### 中断源识别的组织

中断请求连接方式：共用请求式，独立请求式；

识别方法：

- 软件判优；接口无需响应电路，CALL指令直接轮询INTR线；
- 串行判优方式：共用请求式连接，硬件轮询，中断源给出类型号，需响应电路；
- 并行判优方式：独立请求式连接，中断机构产生类型号，无响应电路；

串行判优：共用请求，需响应电路；并行判优：独立请求，无需主设备；

共用请求（可扩展性），并行判优（快）；因此增设中断控制器；

然后就没讲吧。。。？我不会。





## 关于 I/O接口的组织 和 神奇启动位 的讨论

**条件传送方式**都需要控制口，包含启动位；

任老大：

条件传送设备都要先启动，等待就绪后才可以传送数据。启动信息保存在接口的什么地方？

我：

老师我不太明白这个启动信息是什么，是告诉外设如何启动吗？那是不是放在指令最后信息内容那个字段里？

任老大：

你需搞清楚的问题是：

1、条件传送设备的工作特性是什么（先启动、后等待、再传送）；   ←这是你致命的地方，问题的鼻祖

2、设备通过I/O接口连接主机时， I/O接口负责中转各种信息，通过数据总线中转的信息有哪些类型（命令、状态、数据）；

3、I/O接口中转的这些信息放在I/O接口内的什么地方（I/O端口中）；

4、I/O指令的源/目标部件是什么（GPRs和I/O端口）；

5、启动信息的传输方向是什么（GPRs→I/O端口），启动信息是一条指令，还是指令中的一个地址码所指向！

我：

1、条件传送设备的工作特性：先启动，就绪后传送；

2、通过数据总线中转的信息类型：命令（读还是写），数据（写入内容），状态（把外设状态告诉CPU）；

3、命令放**控制**端口，数据放数据端口，状态放状态端口；

4、I/O指令的源/目标部件是什么（GPRs和I/O端口）；

5、启动信息是一条指令，还是指令中的一个地址码所指向？启动信息到底是什么。。。

任老大：

条件传送设备示例：

【一个失效的图片】

磁盘操作过程：

①寻址，主机接口(I/O接口)通过数据线、命令/数据线(=1)、REQ发送寻址命令；

②等待，磁盘收到命令后，使BUSY=1、ACK=0，磁盘完成寻址时（时延较大）ACK=1；

③传送，主机接口通过数据线、命令/数据线(=0)收/发数据

我：

哦哦…启动信息是第一条指令吗？就是让外设先转到可以直接读/写的状态，再告诉CPU自己就绪？

我的思考：

以前光知道条件传送设备是先启动后传送，但是启动的过程是为了什么？只是像什么 仪器预热10min 吗？

不是的。是像磁盘一样转到直接读/写的状态。

任老大：

无语！

1、启动信息是第一条指令中的内容，不是指令本身！！！！！

2、外设怎么告诉CPU？是CPU去查！

指令字和指令字中的操作数分不清？！

我：

启动信息是第一条指令中的内容，如操作码（读/写）和操作数（地址，如要读磁盘的哪一部分）。

磁盘启动起来，转到可以直接读/写那个地址的地方，此时就绪。

如果直接控制，那么CPU不断地查；如果程序中断，那么I/O接口发起中断请求。

因此，需要控制口存放启动内容，磁盘转的时候与启动内容中的地址比较，一转到就就绪。请问是这样吗？

## 关于十进制和二进制的讨论

我：打印机每秒打印10KB数据好像指的是10240B诶，这个也是主存吗？

任老大：

有关K=1024、K=1000的问题，讲过若干遍了：

有关**时间、速度、距离**的计量单位，都是1000，1s=1000ms，1km/s=1000m/s，1km=1000m，100Kbps=100\*1000bps；

有关**容量**的计量单位，**与二进制译码相关**（如RAM）的都是1024，1K\*4b SRAM的容量=1024个\*4bit/个，其余的都是1000，如100MB U盘的容量=100*10^6B=100MiB。

不及时搞懂，耽误了一学期时间，一个问题变成一堆问题，学习态度决定学习成绩；


$$
但是我不接受他的预言。我希望拿到不错的成绩。\\
虽然这两天感觉复习了个寂寞，人家做思考题做真题我还什么都没做，\\
但是，但是，\\
在这种完全没时间复习的情况下，就是自己跟自己博弈了啊。\\
加油加油冲冲冲。20210121
$$















