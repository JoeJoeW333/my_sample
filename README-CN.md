# my_sample

## 文件说明：

./test_sample:用于初步调试的项目工作区

buzzer_test：加入buzzer文件后，在九联Union Tiger开发环境中进行部分编译后，生成的无源蜂鸣器（ky-006）的烧录文件。

./buzzer:内部存放**./include**  和  **./src** 以及内层BUILD.gn，包括头文件的引用路径，编译文件目录，外部组件和模块名称等

./include:内部存放必要的头文件

./src:内部存放必要的.c文件

外层BUILD.gn：内部存放需编译的内层模块名称

bundle.json:增加子系统组件的修改



## 小组内部文件提交说明：

分为：Add、Modification、Remove

每次提交都应该说清楚提交次数、提交时修改的文件及相应的目录

好的例程：

```
Add:
第一次修改：增加XXX文件，路径为./XXX/XXX

Modification:
第二次修改：修改XXX文件为XXX文件，路径为./XXX/XXX

Remove：
第三次修改：由于测试不符合预期，删除./XXX/XXX文件
```



## 小组内部分工：

巫：编译环境搭建、代码框架编写、传感器运行调试

张：负责PWM控制蜂鸣器的代码修改和优化

杜：负责按键开关驱动的编写和优化

