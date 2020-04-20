# GWARF基于C的编程语言
## 语法结构
### 保留关键词
```
import 'file'  导入模块
import 'file' as xxx  导入模块并且明明为xxx
include 'file' 包含模块，等同于python的 from xxx import *

while  条件循环
for  循环
forin  遍历

if  条件分支

block  普通代码块

try  异常捕获
except  异常捕获
raise  诱发错误[抛出class时会转换为object, 需要指定ErrorInfo]
throw  抛出错误

as  引用[强引用]; 异常捕获
link  引用[弱引用]

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

default <var name> n  指定变量默认调用层级
global <var name>  指定变量为全局变量
nonlocal <var name>  指定变量为非本地变量

+ - * /  加减乘除运算符
** ^  指数运算
log  对书运算
~  sqrt  根试运算
=  赋值运算[左边仅能为变量、索引(a[1])、和成员(a.name)]

true True false False bool值[本质为bool对象的实例]
None NULL null  空值[本质就是空值]
class  定义类
def  定义函数
return n  函数返回值，返回n层

'xxxx' "xxxx"  字符串

同时支持：大括号语法和缩进语法
如：
def a()
{
...some to do...
}
和
def a()
    ....some to do...
等效
注意：不可以混用

def a()
{
    ....some to do....
}
等效于
def a()
{
{
.... some to do....
}
}

```
