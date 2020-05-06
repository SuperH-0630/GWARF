# GWARF基于C的编程语言
## 语法结构
### 保留关键词
```
import 'file' as xxx  导入模块并且明明为xxx
include 'file' 包含模块，等同于python的 from xxx import *

while  条件循环
for  循环
for i in xxx  遍历

if  条件分支

block  普通代码块

try  异常捕获
except  异常捕获
raise  诱发错误[抛出class时会转换为object, 需要指定[ErrorInfo]
throw  抛出错误

break n  跳出n层循环代码快[无视for循环第三表达式]
broken n  跳出n层代码块[无视for循环第三表达式]
continue n  重新执行循环代码快
continued n  重新执行代码块
restart n  重新执行循环代码块[无视条件]
restarted n  重新执行代码块[无视条件]
注意: 上述n不指定则默认为0

rego  if马上跳到下一个条件的代码块并执行[无视条件]
rewent  当前if代码块执行完成后跳到下一个代码块执行
注意: else层的rego和rewent需要可以遗传

default <var name> n,<var name> n  指定变量默认调用层级, 也可以把<var name> n写为[n]<var name>
global <var name>,<var name>...  指定变量为全局变量
nonlocal <var name>,<var name>...  指定变量为非本地变量

+ - * /  加减乘除运算符
** ^  指数运算
log  对数运算
sqrt  根试运算
=  赋值运算[左边为变量、索引(a[1])、和成员(a.name)]

True False bool值[本质为bool对象的实例]
None 空值[本质就是空值]
class  定义类
def  定义函数(函数本身就是function的实例)
return x n  函数返回值x，返回n层

'xxxx' "xxxx"  字符串
```

## GWARF 大事记
* GWARF立项和完成了基本结构。
* GWARF重写了PASER解析器。
* 修改了解析器中的status的成员的意义，修复了call back的bug[具体参见commit message]。
* 虚解包，允许语法：``a,b,\* = 1,2,3,4,5,6``。也支持形参表，但不支持实参表。
* 使用function定义静态方法(def)可以定义auto方法(如果是class内则定义为action方法，否则定义为def方法)。
* 优先级bug：调用类方法只能用``(xxx.zzz)()``的方式，为优先级错误[已经修复]。
* 使用cls来定义类方法，并且使用类调用对象方法的时候不会填入self。
* 使用点运算符读取成员的时候会越界访问外部变量。[已经修复]
* 设置了函数静态空间，允许对函数使用point运算符。
* 设置了setup函数，函数可以使用setup关键词进行初始化。
* 设置inline函数，函数执行的时候将不会产生单独的``var_list``，也不会记录``var_list``。
* 设置对None的point运算均为None
* 设置了变量访问权限：protect [受到保护的变量] 和public [公开变量]
* 设置了变量访问权限：private，根据对``var_list``的标签来判断
* 面向对象取出重复，``to_error``和``to_object``不用``find_var``，在global的时候就设定好
## 关于GWARF
最后更新时间 ： 2020年05月05日 广州
