# Opengl基础

1. GLSL语言，概念，工作原理,及如何传递数据的
参考learnopengl着色器
着色器(shader)是运行在GPU上的小程序，类似于C语言，构造一个着色器在其开头必须声明版本。本质上来说，着色器是一个把输入转化为输出的程序。
着色器定义了in和out等关键字实现数据的输入和输出，从而实现数据的交流。如果从一个着色器向另一个着色器发送数据，则必须在发送方声明一个输出，在接收方声明一个类似的输入。当类型和名字都相同的时候，便会自动链接在一起，实现数据传递。
另一种从cpu向gpu发送数据的方式是uniform。uniform是全局的，无需借助其他中介实现数据传递。在着色器程序中声明uniform变量，在主程序中通过glGetUniformLocation获得其地址，从而设置着色器中uniform变量的值。

2. CPU和GPU之间如何调度的
如1中所述，GLSL运行在GPU，其通过接口实现和CPU之间的数据转换。
opengl程序涉及到两种类型的处理单元--CPU和GPU。opengl主程序由CPU调度运行，图像处理部分通过GLSL交由GPU执行。CPU与GPU之间的数据传递分三个步骤：一，首先利用内置的OpenGL函数生成一个ID号码;二，根据需要对该ID号码进行内存类型的绑定;在经过上面两个步骤之后，GPU中用于接收系统内存中数据的“标识符”就准备好了，第三部对这部分内存进行初始化，初始化的内容来自于系统内存中，这一部分功能利用glBufferData函数完成。
数据提交到GPU专用的内存中之后，需要根据应用场景对这些数据进行适当的分配。比如，有的数据当做顶点，有的是作为颜色，有的用于控制光照等等
此外，由于GPU具有高并行结构(heighly parallel structure)，所以GPU在处理图形和复杂算法方面计算效率较高。CPU大部分面积为控制器和寄存器，而GPU拥有更多的ALU(Arithmetric Logic Unit,逻辑运算单云)用于数据处理，而非数据的高速缓存和流控制。

3. opengl中缓冲区的概念
[1] 帧缓冲(frame buffer)：帧缓冲是下面几种缓冲的合集。通过帧缓冲可以将你的场景渲染到一个不同的帧缓冲中，可以使我们能够在场景中创建镜子这样的效果，或者做出一些炫酷的特效，存放显示用的数据的。
[2] 颜色缓冲(color buffer)：存储所有片段的颜色：即视觉输出的效果。
[3] 深度缓冲(depth buffer)：根据缓冲的z值，确定哪些面片被遮挡。由GLFW自动生成。
[4] 模板缓冲(stencil buffer)：与深度测试类似，通过比较模板值和预设值，决定是否丢弃片段。
数据在opengl中处理顺序是： 顶点着色器 - 片段着色器 - 模板测试 - 深度测试
参考链接：http://blog.csdn.net/silangqu...

4. mipmap是怎么回事
Mipmap是多级渐远纹理,也是目前应用最为广泛的纹理映射(map)技术之一。简单来说，就是实现 “实物(图片)看起来近大远小，近处清晰远处模糊”的效果。它简单来说就是一系列的纹理图像，后一个纹理图像是前一个的二分之一。多级渐远纹理背后的理念很简单：距观察者的距离超过一定的阈值，OpenGL会使用不同的多级渐远纹理，即最适合物体的距离的那个。由于距离远，解析度不高也不会被用户注意到。同时，多级渐远纹理另一加分之处是它的性能非常好

5. opengl的常用坐标系
局部空间(local space):或称为 物体空间.指对象所在的坐标空间
世界空间(world space):指顶点相对于(游戏)世界的坐标。物体变换到的最终空间就是世界坐标系
观察空间(view space):观察空间(View Space)经常被人们称之OpenGL的摄像机(Camera)(所以有时也称为摄像机空间(Camera Space)或视觉空间(Eye Space))。观察空间就是将对象的世界空间的坐标转换为观察者视野前面的坐标。因此观察空间就是从摄像机的角度观察到的空间
裁剪空间(clip sapce):或称为视觉空间.在一个顶点着色器运行的最后，OpenGL期望所有的坐标都能落在一个给定的范围内，且任何在这个范围之外的点都应该被裁剪掉(Clipped)。被裁剪掉的坐标就被忽略了，所以剩下的坐标就将变为屏幕上可见的片段。这也就是裁剪空间(Clip Space)名字的由来。
屏幕空间(screen space):顾名思义，一般由glViewPort设置。
参考链接：http://learnopengl-cn.readthe...

6. opengl中的常用矩阵，各有什么作用
model:主要针对模型的平移、旋转、缩放、错切等功能，将模型由局部空间转换到世界空间
view：视图矩阵。摄像机/观察者的位置等信息（设置鼠标移动、滚轮等效果）,将所有世界坐标转换为观察坐标。
projection:投影矩阵。裁剪坐标 转换到屏幕上

7.为什么说opengl是一个状态机
首先简单了解一下什么是"状态机"，比如我们使用的电脑，接受各种输入(鼠标，键盘，摄像头等)，然后改变自己当前的状态，但却并不知道状态的改变是如何实现的。opengl类似，接受各种参数，然后参数的改变引起当前状态的改变，达到一种新的状态(如：颜色改变，纹理变化，光照强弱变化)。
opengl状态机

8. 光照
冯式光照模型：环境光照(Ambient)、漫反射(Diffuse)、镜面(Specular)
光源：点光、定向光、手电筒（聚光灯）

9. 显示器是二维的，三维数据如何在二维屏幕上显示的。
主要是通过图形渲染管线（管线：实际上是指一堆原始图像数据途径一个输送管道，期间经过经过各种变换处理，最终输出在屏幕上的过程）管理的，其被划分为两个过程：1. 把3D坐标转换为2D坐标。 2. 把2D坐标转换为实际有颜色的像素。
2D坐标和像素是不同的，2D坐标精确表示一个点在空间的位置，而2D像素（好像都是整数）是这个点的近似值，2D像素受到个人屏幕/窗口 分辨率的限制。

10. 坐标系
局部空间(local space):或称为 物体空间.指对象所在的坐标空间 世界空间(world space):指顶点相对于(游戏)世界的坐标。物体变换到的最终空间就是世界坐标系 观察空间(view space):观察空间(View Space)经常被人们称之OpenGL的摄像机(Camera)(所以有时也称为摄像机空间(Camera Space)或视觉空间(Eye Space))。观察空间就是将对象的世界空间的坐标转换为观察者视野前面的坐标。因此观察空间就是从摄像机的角度观察到的空间 裁剪空间(clip sapce):或称为视觉空间.在一个顶点着色器运行的最后，OpenGL期望所有的坐标都能落在一个给定的范围内，且任何在这个范围之外的点都应该被裁剪掉(Clipped)。被裁剪掉的坐标就被忽略了，所以剩下的坐标就将变为屏幕上可见的片段。这也就是裁剪空间(Clip Space)名字的由来。 屏幕空间(screen space):顾名思义，一般由glViewPort设置。

11. 常用矩阵
model:主要针对模型的平移、旋转、缩放、错切等功能，将模型由局部空间转换到世界空间 view：视图矩阵。摄像机/观察者的位置等信息（设置鼠标移动、滚轮等效果）,将所有世界坐标转换为观察坐标。 projection:投影矩阵。裁剪坐标 转换到屏幕上

12. 为什么说opengl是一个状态机
首先简单了解一下什么是"状态机"，比如我们使用的电脑，接受各种输入(鼠标，键盘，摄像头等)，然后改变自己当前的状态，但却并不知道状态的改变是如何实现的。
opengl类似，接受各种参数，然后参数的改变引起当前状态的改变，达到一种新的状态(如：颜色改变，纹理变化，光照强弱变化)。

13. 光照
冯式光照模型：环境光照(Ambient)、漫反射(Diffuse)、镜面(Specular)
光源：点光、定向光、手电筒（聚光灯）

14. 显示器是二维的，三维数据如何在二维屏幕上显示的
主要是通过图形渲染管线（管线：实际上是指一堆原始图像数据途径一个输送管道，期间经过经过各种变换处理，最终输出在屏幕上的过程）管理的，
其被划分为两个过程：1. 把3D坐标转换为2D坐标。 2. 把2D坐标转换为实际有颜色的像素。 2D坐标和像素是不同的，2D坐标精确表示一个点在空间的位置，
而2D像素（好像都是整数）是这个点的近似值，2D像素受到个人屏幕/窗口 分辨率的限制。

15. 渲染流水线
    首先，发送**顶点数据**到**顶点着色器(Vertex Shader)**，顶点着色器主要的目的是把3D坐标转为另一种3D坐标（后面会解释），
同时顶点着色器允许我们对顶点属性进行一些基本处理。
    然后进入图元装配(Primitive Assembly)阶段将顶点着色器输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），并所有的点装配成指定图元的形状。

图元装配阶段的输出会传递给几何着色器(Geometry Shader)。它可以通过产生新顶点构造出新的（或是其它的）图元来生成其他形状。

光栅化阶段(Rasterization Stage)，这里它会把图元映射为最终屏幕上相应的像素，生成片段(Fragment)。在片段着色器运行之前会执行裁切(Clipping)。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。

**片段着色器(Fragment Shader)**计算一个像素的最终颜色。通常，片段着色器包含3D场景的数据（比如光照、阴影、光的颜色等等），这些数据可以被用来计算最终像素的颜色。

最终传到Alpha测试和混合(Blending)阶段。这个阶段检测片段的对应的深度和模板值，用它们来判断这个像素是其它物体的前面还是后面，决定是否应该丢弃。这个阶段也会检查alpha值（alpha值定义了一个物体的透明度）并对物体进行混合(Blend)。

几何着色器的输出会被传入光栅化阶段(Rasterization Stage)，这里它会把图元映射为最终屏幕上相应的像素，生成供片段着色器(Fragment Shader)使用的片段(Fragment)。在片段着色器运行之前会执行裁切(Clipping)。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。

16. gldrawArrays glDrawElement
glDrawElement基于索引绘制，需要配置EBO
