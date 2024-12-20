# co第一章

## 冯诺依曼计算机

存储单元长度：编址单位；

程序空间=MEM空间；

### 工作方式（重中之重）

- 程序和数据预先存放在存储器中；
- 机器工作时，自动、逐条地取出指令并执行；

程序的执行过程：循环的指令执行过程，取指译码执行产生下条指令地址；

## 现代计算机

以存储器为中心（运算与I/O并行，缓冲+DMA），多种存储器共存（cache，主存，辅存）；

额，**显卡是I/O接口**。

基本结构，部件组成，部件互连；

程序局部性原理。

## 计算机性能指标

机器字长：CPU一次处理整数的二进制位数；决定ALU、数据REGs、数据通路的位数；

CPU主频：CPU内部主时钟脉冲的频率，最基本原子操作时延；

存储容量：主存地址空间（主存决定），CPU可寻址空间（CPU地址引脚）；

响应时间：从提交到完成；

CPU时间：I_N\*CPI\*T_CPU；

吞吐率：n个任务总工作量/n个任务总时间；

MIPS(Million instructions per secend，每秒百万条10^6指令)；

## 做ppt例题的感想

G是10的9次方诶；

# co第二章

## 数据的编码

十进制数转R进制数：除R取余；

### 原码

+0 -0表示不同，n位原码只表示2^n-1个数；

小数原码：+0.01，-0.01->1.01；

### 补码

无冗余编码；补数，第一位是符号位，剩下位是真值或正补数；

小数补码负数：1 (1-|x|)，第一位符号位，剩下是1的补数；

### 反码

负数：[x]补=[x]反+1；

### 移码

真值连续时，机器数也连续；

对补码的符号位取反，剩下都一样；

十进制数：8421码了、；

字符编码：交换码，内码，输入码，字模码；

## 校验码

### 冗余检验思想

码距：任二合法编码 相异字符 个数最小值；

用待发数据M生成校验信息P，M和P一起发送；

接受M‘P'，用M'形成P'’，然后看P'P'‘一不一样；、

校验码 = 数据位+校验位；

校验码∈合法码字？

### 奇偶校验码

使校验码中1的个数为奇/偶；

故障字S=P'异或P’‘；0无错，1有错；

### 海明码

数据分为多个有重叠的组，多重奇偶校验；

数据n位，校验位p位，故障字是p'异或p'’，应表示n+p+1（对）中情况；

校验位错：0001 0010 0100 1000；

错误位置=S值；全0全对；

![image-20210120213921915](.\..\..\typora-user-images\image-20210120213921915.png)

## 数据的表示

### 整数表示

截断、位扩展（0扩展，符号扩展）；内部电路：n-1到0输出，2n-1到n=op&n-1，op=0零扩展1符号扩展；

### 浮点数表示

阶码+尾数码；尾数*阶的基数^阶码；

浮点数规格化：（补码）最高数组位与符号位相反；（原码）最高数值位=1；

IEEE754貌似不考，战略放弃；

### 非数值数据的运算规则 实现方法

小端方式存放：数据按字节顺序存放，地址最小的单元存放最低有效字节；

如：数据B3B2B1B0放在40#～43#单元时，40#单元存放B0；

假设我们的内存单元是40-43一行一行往下写的，大端是直接搬过去，小端是“地址最小的单元存放最低有效字节”；

## 定点数浮点数运算

### 加减

[A-B]补=[A]补+[-B]补；

若减法，C-1=1，把输入的B取异或再送进加法器；

#### 溢出条件！

同号相加异号相减，结果与第一个opd异号；即 (An-1同或Bn-1\*op#+An-1异或Bn-1\*op)*(Sn-1异或An-1)；

无符号进位借位：CF=Cn-1异或C-1；

### 移位

![image-20210121094724471](.\..\..\typora-user-images\image-20210121094724471.png)

### 补码加减

对阶（都化成大阶），尾数加减，尾数规格化，溢出判断；

## ALU组成（组合逻辑）

**运算器**还要配REGs，存放数据/地址；还包括状态寄存器PSR；这里说的是运算器！



















