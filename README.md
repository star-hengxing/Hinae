# Hinae

使用C++20编写的一个计算机图形学数学库

现在只能用这些= =
* Vector2
* Vector3
* Point2
* Point3
* Point4
* Matrix4
* Quaternion
* Ray3
* Bounds3
* RNG
* LCG
* 球坐标系互转/建立局部坐标系

**详细的使用方法可以看看test/test.cpp**

# Feature

没有选择使用模板<类型 长度>，而是直接把常用几何体都写一次

所以vector和point可以直接使用.x .y .z访问

matrix4则是使用了代理类，可以通过下标索引 m[0][0] 和 m[3][3] 来访问第一个和最后一个元素

* 纯模板，只需include
* 跨平台(Linux/Windows)，gcc/clang/msvc均可编译，mac平台没测试过

# Transform

point/vector/ray/bounds都可以乘矩阵进行transform

* scale
* translate
* rotate(x, y, z)
* 四元数to旋转矩阵
* look at摄像机矩阵(右手坐标系)
* 正交和透视投影矩阵

# Random number generator

## RNG

简单封装了一下`std::mt19937`，禁止了拷贝构造函数和拷贝复制函数，只能用clone函数新建一个

## Linear_congruential_generator

模仿标准库实现的一个线性同余伪随机数生成器，周期2^32

get输出范围
* 浮点数[0~1]
* 整数看类型字节大小
