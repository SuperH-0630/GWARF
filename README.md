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
* GWARF去全局化，减少使用全局变量有利于为后期的多线程模式做铺垫
* 赋值语句会为``GWARF_value``的访问权限降低到``base``，除非是self=true(1)的模式。
* ``<==`` 和 ``==>``为非短路逻辑运算：蕴含
* ``<:=`` 和 ``=:>``为短路逻辑运算：蕴含
* ``<=>`` 为逻辑运算：同或门
* ``!==`` 为逻辑运算：异或门 ``and`` 和 ``or`` 为非短路逻辑运算符：与，或
* 处理``GWARF_result``
* 新增Exception, 修复了``to_object``会捕获异常的bug
* Div和Log运算检查数字类型
* 调整了运算优先级，修改了无法读取``5 ** -2``而可以读取``5 ** (-2)``的bug
* while和for循环新增else语句
* try...except增加了else和finally语句，并且允许``except``，``except as``，``else``，``finally``为可选语句
* 实现了slice赋None值(本质是依靠了虚解包)
* 修改了无法return的bug
* in 语句
* 可以捕捉import和include的代码语法异常
* 疑似bug：``a.__iter__.__next__``会出现内存错误, 已经修复，原因是: 内置函数无self属性
* ``a.__iter__().__next__()``会出现解析错误, 已经修复，调整了``.``运算符和``call_back``为同级优先级
* 解决了object的``__value__``无法调用的问题：原因是注册函数的时候使用了数字而不是枚举体[现在，使用``{__value__func, 1}``取代了数字``{3, 1}``]
* 可以生成语法树，输出文件到./log下
## GWARF计划
* 类型转换(list, str, int之间的转换)
* 魔法方法：``__eq__(用于特殊赋值)，__int__，__str__，__double__，__repo__，__list__，__tuple__，__dict__，__key__，__in__``
* 魔法属性：``__name__，__id__``
* 数据类型：``set()，link()，file()``
* 内置类：``range,exp(列表推导试)``
* 内置函数：``exit()[报出错误ExitException(Systemctl)], type(), isinherited()[A类是否继承B类], isinstance()[A object是否为B的实例(不检查继承关系)]``
* @装饰器语法
* 内存控制：控制``var``链表，控制``哈希表``，控制``var_list``
* 多重继承优化：``super().__init__()``
* 抽象类和接口类(纯抽象类)
* goto语句
* 宏定义
* yield生成器和列表推导试
* 模块化导入，读取``__init__.gwf``文件
* 优化错误输出[行号]
## 关于GWARF
最后更新时间 ： 2020年05月09日 广州
