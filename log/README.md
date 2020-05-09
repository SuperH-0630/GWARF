# 关于LOG文件夹
## GWARF的LOG
GWARF在解释``.gwf``文件时，会生成日志并记录在``./log``文件夹下。
* debug.log 是词法解析器输出的日志
* status.log 是语法解析器输出的日志
* token.log 是语法解释器输出的日志，是token流(或称为token FILO)的详细日志
* tokenINFO.log 是token.log的简化日志
* tree.log 输出语法树