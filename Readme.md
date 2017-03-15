# SDL-Gaming
这是一份项目(project)仓库，用来创作一个基于SDL2图形库的游戏。

下面将介绍一些游戏源代码的基本要素，使得你能够更清晰地掌握这个project的构造。

**注意：随着代码的更新，这份README的说明可能会变得不准确。**

如有疑惑，请询问[@wch510719826](https://github.com/wch510719826)。

## Outline
这个游戏当前分为16个模块。
其中，11个模块各有一份头文件.h + 源文件.cpp：
- Camera
- Dice
- Inputor
- Main
- Player
- Projectile
- SoundLoader
- Sprite
- TextureLoader
- Tile
- World

有4个模块仅有一份头文件：
- Entity.h
- IDSheet.h
- Vector2D.h
- Object.h

以及main函数的入口：
- SDLGaming.cpp

一共**27**个文件。

随着开发的推进，会有更多的文件加入其中。因此，你需要时刻保持内容的同步，并**正确配置好project设置，以及project相关文件夹的结构布置**，才能正常工作。  
否则，build不过的绝望会把你逼疯的。

从这些模块的名称，可以明确地看到这个游戏的有机组成部分: 图像, 音频, 输入/输出, 等等。  
这份README将只说明这些模块**实现了什么功能**，并**提供了什么样的接口**，给予**指向如何实现的Github Wiki链接**，而尽量不涉及SDL的特性（实际上，你也只需要围绕着提供好的API来写就好了）。

如果你在SDL本身上有任何疑惑, 请自行查阅[SDL Wiki](http://wiki.libsdl.org/) (*就像SDL教程视频里做的那样*)。

### Why C++?

C++既是面向对象程序语言，又继承了C的高效运行特点，十分适合用来写游戏。

> -- Possible Question: 为什么不用Java？
>
> -- Answer: 相比Java,C#这些典型的面向对象语言，C++可以很好地使用一些它们没有（或者已经抛弃）的机制来更有效率地解决一些问题。这些机制包括指针、宏（预编译）、内存控制等等。不过，尽管如此，如果写的很烂的话，还是会比Java慢而且笨重的。

作者原话：

> "I'm such a chatterbox, u guys need to be careful to avoid these non-sense parts to get what is useful, okay?"  



**下面对各模块分别作一个简要介绍。**

----------
### SDLGaming.cpp ###
这个文件定义了游戏程序的入口,换言之,整个项目的main()函数。

更准确地来说，我们使用的是SDL的main()函数，因为我们使用了如下的宏指令：

```c++
#define main SDL_main
```

来重定向main()至SDL的main()。



这个文件并没有包含很多内容，因为几乎所有功能都被封装在各种**类**里面了。它所做的仅是：

* 调用了 **Main** 类来初始化游戏
* 用一个无限循环来安排游戏的所有内容（当玩家退出游戏时，才退出循环）
* 控制FPS



关于其工作方式的解释，请参阅[SDLGaming.cpp - Wiki](https://github.com/Vigilans-Yea/SDL-Gaming/wiki/SDLGaming.cpp)

----------

### Main/World ###

现在来看看最为基础的**Main**类与**World**类。最初，他们是同一个模块，现在则被区分开，分别行使如下的功能：

**Main**： 负责游戏的程序流程部分。比如启动、处理（*World*就是在“处理”函数中被调用的）、关闭、退出游戏。主要就是一些前置而底层，依托SDL架构的内容。

**World**：负责游戏系统与内容本身。比如初始化世界、更新世界、创造新物体等等，相当于游戏的GM。它也提供了一个不再依托于SDL的接口，也即**SDL在完成底层架构后，所有游戏的内容都将连接至*World*这个游戏系统**，我们只需要按照提供的接口实现游戏功能即可。



关于**World**布置了什么内容，请参阅[World & Main - Wiki](https://github.com/Vigilans-Yea/SDL-Gaming/wiki/World-&-Main)

----------

### TextureLoader/SoundLoader/Inputor/Camera ###

这些是当前使用Singleton模式的类。

各个类介绍如下：

* **TextureLoader** 加载材质（图片等等）
* **SoundLoader** 加载声音文件（音乐/特效等）

不管是用TextureLoader来制图，还是用SoundLoader来播放声音，它们都需要经历相同的流程，就像游戏是如何运行的一样：

1. 加载材质/音乐，即，将文件装载入*内存*中；
2. 使用*内存*中的材质/音乐。

由于它们都是单例类，只有一个对象，所以我们要在类中使用一个数组来存放各种不同的材质/音乐：

```c++
map<string, SDL_Texture*> textureMap;
```

```c++
map<string, Mix_Chunk*> sfxs;
map<string, Mix_Music*> musics;
```

我们使用Map作为关联数组，用ID字符串来检索对应的单位对象，这样更为方便。

关于如何使用它们来加载并使用材质/音乐，请移步[Load and use a file - Wiki](https://github.com/Vigilans-Yea/SDL-Gaming/wiki/Load-and-use-a-file)。

> 由于我们制作的是一个独立的小游戏，所以即使加载了所有音乐和材质，也不会占用过多的内存。因此，我们选择一开始就加载所有东西，暂时不考虑将它们从内存中移除的问题。



- **Inputor** 简单地封装了一些SDL函数，主要涉及键盘/鼠标的行为(event)，比如“是否按下某个键”、“获取鼠标指针位置”等等，方便我们调用。
- **Camera** 记录当前角色的坐标。它就像镜头一样始终对准着当前玩家所控制的角色，而除了角色外的所有东西的坐标，都将依托Camera存放的坐标来计算。它在**World::updating()**函数中被单独更新。
> Q:其实，项目中还有一个**Player**类，它代表每个玩家，并且也记录了玩家的坐标，那为什么还需要Camera呢？
>
> A:Camera的出现是为了避免**Player**不得不使用Singleton模式。未来这个游戏会扩展成多人版本，所以**Player**应该是需要多个对象的。这时候，我们就用Camera作为单例类来记录每个客户端的角色坐标。



以上类所提供的API，都可以在Repo的[Wiki](https://github.com/Vigilans-Yea/SDL-Gaming/wiki)中查到。

----------

### IDSheet/Vector2D/Object/Dice###

这是几个仅包含头文件，或内容很简单的类，简单介绍如下：

* **IDSheet.h** 这个头文件不包含类。它是一个ID表，预先定义了大量的符号常量，减少magic number的使用，随着游戏中的东西越来越多，它能使得我们便于检索与管理。

  符号常量的定义是用宏指令实现的，简单列举如下：

  ```c++
  #define WoodenSword 30410000
  #define WoodenSwordName "Wooden Sword"
  #define WoodenSwordFile "assets\\WoodenSword.png"
  #define PickupSound 40110010
  #define PickupSoundFile "sounds\\PickUpItem.mp3"
  ```

  因此，几乎每个类的实现文件，都会包含这个头文件。


* **Vector2D.h**  这个类用来表示一个平面上的点，或是一个二维向量。它预先封装好了一些简单的运算函数。如果你在某些功能如何实现上有不错的想法的话，你也可以为它写一个点乘或是叉乘的方法。
* **Object.h** 作为一个抽象的类，它可以保存游戏中每一个单位、物品或是其他任何东西的属性，比如ID，位置，大小等等。这个类实例化出来的对象就代表了游戏中的每一个具体的东西。这展现出了面向对象编程的特点与优势。


* **Dice.h** 随机数发生器。



关于*Object*类的进一步解释，请参阅[Object & Entity - Wiki](https://github.com/Vigilans-Yea/SDL-Gaming/wiki/Object-&-Entity)

----------

更多内容请查阅这个Repo的[Wiki](https://github.com/Vigilans-Yea/SDL-Gaming/wiki)，它们的内容同样重要。
