# 关于GWARF的demo
## .gwf文件
``.gwf``是gwarf的程序源文件的扩展名
## 1.gwf和6.gwf
关于计算的``demo``，使用``print``输出计算结果
## 2.gwf
关于分支结构的demo。注意：``if``分支的demo已经移动到了``7.gwf``
## 3.gwf
关于函数定义和函数调用的demo。
## 4.gwf
关于变量空间的demo。解释``[1]a``实际访问的是倒数第一层的变量``a``。  
if里面是倒数低0层变量空间，再外一层就是倒数第一层。赋值的时候，默认给倒数第0层赋值，取值默认从倒数第0层开始寻找变量。
## 5.gwf和test.gwf
关于``impor``t的demo。
## 7.gwf
关于``if``分支的demo。解释``rego``和``rewent``语句可以让``if``分支变成``switch``的功能(向下执行)。
## 8.gwf
关于``input``和``print``t的demo。
## 9.gwf
关于内置函数``isinherited，isinstance，isinstance，isbelong，type``的测试