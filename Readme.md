# SDL-Gaming
这是一份项目(project)仓库，用来创作一个基于SDL2图形库的游戏。

下面将介绍一些游戏源代码的基本要素，使得你能够更清晰地掌握这个project的构造。

**注意：随着代码的更新，这份README的说明可能会变得不准确。**

如有疑惑，请询问[@wch510719826](https://github.com/wch510719826)。
##Outline
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

随着开发的推进，会有更多的文件加入其中。因此，你需要时刻保持内容的同步，并**正确配置好project设置，以及project相关文件夹的结构布置**，才能正常工作。否则，build不过的绝望会把你逼疯的。

从这些模块的名称，可以明确地看到这个游戏的有机组成部分: 图像, 音频, 输入/输出, 等等。这份README将只说明这些模块**实现了什么功能**，并**提供了什么样的接口**，给予**指向如何实现的Github Wiki链接**，而尽量不涉及SDL的特性（实际上，你也只需要围绕着提供好的API来写就好了）。

如果你在SDL本身上有任何疑惑, 请自行查阅[SDL Wiki](http://wiki.libsdl.org/) (*就像SDL教程视频里做的那样*)。

### Why C++?

C++既是面向对象程序语言，又继承了C的高效运行特点，十分适合用来写游戏。

> -- Possible Question: 为什么不用Java？
>
> -- Answer: 相比Java,C#这些典型的面向对象语言，C++可以很好地使用一些它们没有（或者已经抛弃）的机制来更有效率地解决一些问题。这些机制包括指针、宏（预编译）、内存控制等等。不过，尽管如此，如果写的很烂的话，还是会比Java慢而且笨重的。

作者原话：

> "I'm such a chatterbox, u guys need to be careful to avoid these non-sense parts to get what is useful, okay?"



***下面对各模块分别作一个简要介绍。***

----------
### SDLGaming.cpp ###
这个文件定义了游戏程序的入口,换言之,整个项目的main()函数。

更准确地来说，我们使用的是SDL的main()函数，因为我们使用了如下的宏指令：

```c++
#define main SDL_main
```

来重定向main()至SDL的main()。



这个文件并没有包含很多内容，因为几乎所有功能都被封装在各种***类***里面了。它所做的仅是：

* 调用了 ***Main*** 类来初始化游戏
* 用一个无限循环来安排游戏的所有内容（当玩家退出游戏时，才退出循环）
* 控制FPS




关于其工作方式的解释，请参阅SDLGaming.cpp - Wiki

#### 1.**Main** 是如何初始化的？

直观上，Main的实例(Instance)是在调用Main::Inst()函数后初始化的。

为什么要这么做，而不是直接用下面的方法实例化一个对象？

```c++
    Main* mainClass;
    mainClass = new Main();
```

这是因为我们对Main类有如下的期望：

* 整个程序运行期间，始终只有一个实例化的对象
* 在程序的任何地方都可见（即作用域为整个程序）



这在C#或Java中有对应的特性，但在C++中并不容易实现。这里，我们使用一种叫做***Singleton***（**单例模式**）的程序设计模式来达到上述目标。



Now Singleton is a very important technique that has been used through the whole program. 它的结构一般如下：

```c++
class Main
{
private:
	Main() {}
	~Main() {}
	Main(const Main&);
	static Main* INSTANCE;
public:
	static Main* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new Main();
			return INSTANCE;
		}

		return INSTANCE;
	}
}
Main* Main::INSTANCE = 0;
```

在那些与Main类一样，在仅需一个实例并且处处可见的类中，如**Camera**,**TextureLoader**,**SoundLoader**,**Inputor**等等，你能看到同样的结构。



The implementation of Singleton in cpp mainly utilizes how "static" is treated in cpp. First we put constructor function "Main()" into "private" scale, this makes sure that the constructor cannot be called ousides the **Main**. So it ensures "one and unique" purpose.<br>
And the design of Inst() just gives us the access to get reference to **Main** publicly anywhere of the program, on the condition of returning the specific and unique instance of **Main**.

Um... I know these explanations have totally zero help with your understanding of how Singleton works. It's not a big problem if u don't know what happens on earth, since for us it is only a ready-to-use interface. but if u r interested in why to implement it like this or what happens inside these codes, u can simply go searching **Singleton** on the internet and there will be some more detailed interpretations.

Back to how **Main** is initialized.<br>
Since we implement **Main** using Singleton. The initialization process of **Main** is:<br>
·　Initialize the local variable **INSTANCE** of **Main** as **NULL** when compiling<br>
·　Inst() being called in main() when programs starts<br>
·　Inside Inst(), since **INSTANCE** is **NULL**, so create a **Main** instance and return it<br>
·　If Inst() is again called from elsewhere of the program, Inst() detects that **INSTANCE** is no longer **NULL**, so it returns the instance that was 　 created when the program starts.

2.  how is FPS controled

    const int FPS = 60;
    const int DELAY_TIME = 1000.0f / FPS;

    int main(int argc, char **argv)
    {
    	Uint32 frameStart, frameTime;
    	...
    	...Create Main instance here
    	...
    	while (Main::Inst()->running())
    	{
    		frameStart = SDL_GetTicks();
    	
    		Main::Inst()->handleEvents();
    		Main::Inst()->updating();
    		Main::Inst()->rendering();
    	
    		frameTime = SDL_GetTicks() - frameStart;
    	
    		if (frameTime < DELAY_TIME)
    			SDL_Delay((int)(DELAY_TIME - frameTime));
    	}
    	...
    	...Close the game here
    	...
    	return 0;
    }
    Now we all know SDL_GetTicks() return the miliseconds the program has been running from the point the program starts.<br>
    Before the next frame of the game is going to be updated, we record the tick and restore it in **frameStart**, and then let the game run its stuff. Here is where the program starts to calculate everything of the game, and there is a lot of calculations.<br>
    Anyways, we record the tick when the game has done its jobs, then get the difference bewteen it and the   **frameStart** and restore it in **frameTime**.<br>
    This **frameTime** represents how long a frame of the game has actually taken.<br>
    It is a very small value when the game is not big and the computer has a strong performance. So in order to keep the game at a fixed 60 FPS, we give it a check to see whether the game freshes faster than 60 FPS.<br>
    If FPS > 60 then its fresh time gotta be lower than 1000/FPS.<br>
    This design of implementing FPS control is actually very smart (when I say smart, I mean it is not my idea). Since the game won't argue with 60 FPS all the time, like if the FPS is not 60 the program still intends to keep it at 60. This method avoids that.<br>

As u can see, when this **frametime** somehow is bigger than 1000/FPS, i.e. your computer takes longer to finish the calculation tasks, you will experience lags. It is weird to say this... but making a game lag in the right way is dramatically important in making a game. Although when we play a lagging game we are most likely crashing the keyboard and freaking out, the fact is that we just dunno the programmers also put no less efforts to make a game run right when lagging...

----------

### Main and World###

I seem to write too much trivial stuff... I'll try to grab essentials from now on.

Let's foncus on **Main** itself now.<br>
**Main** just like main(), it doesn't do much. it essentially just initalizes some SDL prerequisites, like video, the rendering suface of the video, and audio, etc. Once again if u r interested, u can refer to the SDL wiki and just type the function name u want to figure out then it'll quickly return you with the results.

What I want to say is the difference between **Main** and **World**.<br>
Hum... it is only yesterday I split them up, they are originally one united class.<br>
The reason why I seperate them is that I find it may be appropriate to draw a clear line between the program part (SDL hardware functions and program entrance) and the game system part.

After **World** class, there will be no more mentioning of any program initializations sutff, everything is related to the gaming system.<br>
As of **World**, I guess I'd better explain why I said the game is highly OOP featured.

What it takes to consist of a game?<br>

Well, I dunno how u guys  are thinking about this question.

Just form my personal perspective:

- A game has a world, it is a container that organizes everything of the game
- A world has a background (for a 2d game), and many other view elements like the white cloud floats in the sky and the soil on the ground
- A world has some other vivid views like the trees, the grass and the houses and blabla, you name it.
- A world has many entities, i.e. players, NPCs, and monsters.

If so, then the world is going to have a bunch of arrays (vectors) that store these objects respectively, hence the **World** class has (currently):

	enum LayerType
	{
		LAYER_SPRITE,
		LAYER_TILE,
		LAYER_ENTITY,
		LAYER_PROJECTILE,
		LAYER_PLAYER
	};
	
	vector<vector<Object*>> layers;
**layers** just represents five vectors, and every vector stores the responsive objects, so we can use a simple loop in the updating() of **World** to update everything in this game. There goes the most cheerful moment of OOP:

    void World::updating()
    {
    	int k, i;
    	int len;
    
    	for (k = 0; k < LAYERCOUNT; k++)
    	{
    		len = layers[k].size();
    		for (i = 0; i < len; i++)
    			layers[k][i]->update();
    	}
    }


And finally the **World** class should have a pile of "Creators" if I need to give it a name. For now I only add a "newProjectile" method, which is ofc used to create projectiles when necessary, like when players shooting arrows, bullets or magic missles. In the future I think there will be "newEnemy", "newNPC" or even "newTile". It depends.

Hum... yeah, nearly forgot, there is a relatively important technique I used in **World** class I gotta mention. It is a little bit clumsy though... since it is something I came up with.

The technique doesn't have a massive name like the **Singleton** bro does. It is used to scroll the map.

You see, a game map cannot only be as big as the window goes. That would be ridiculous. Like a map will be 3000 sized, where ATM a game window may only width 800. So the background will scroll as the player moving forward.

To implement this kind of effect, I calculated everything centered with the player, making the program only draw the things near the player, aka. drawing section = **(player.position.x - window.width/2, player.position.x + window.width/2)**.

Down the detailed implementations there will be several things to be cautioned, but now u just need to catch the idea then it is ok.

----------

#### TextureLoader　SoundLoader　Inputor　Camera####

这些是现在使用Singleton模式的类。

各个类的功能为：

* **TextureLoader** is used to load textures (pictures) 
* **SoundLoader** is used to load sound files (musics or sfxes). Nothing special.

The way Textureloader draws pictures onto the screen and Soundloader broadcasts sounds are just like how the game is being run - first to load, second to use. Everthing u want to use needs first to be loaded, more specifically loaded from file to the memories.

So it makes sense to put some arrays in **TextureLoader** and **SoundLoader**, they are respectively:

	map<string, SDL_Texture*> textureMap;

	map<string, Mix_Chunk*> sfxs;
	map<string, Mix_Music*> musics;

Hum... they are "maps" instead of "SDL_Texture*[]" or something likewise. This also makes sense because the textures or the sounds we'll be using won't be in a perfect liner list. We'll be using IDs instead, which is a way that is way more efficient and convenient.

So when we want to play a piece of music in the game, we need to call **Sound::Inst()->load("C:\\music.mp3, "examplemusic", SOUND_MUSIC)** first. The first param is the file path of the music file, the second param is the id of the particular music, and the third param is the type of the sound (is it music or sfx?). What this does is basically loading the music file from the disk and return a pointer of the music stored for the use.<br>
After this, we can use **Sound::Inst()->playMusic("examplemusic", -1)** to play the music anytime we want, and we simply need to pass the id the music. "-1" means loop endlessly.

I guess an indie game like our making won't be so huge that starts to lag most people's computers. A 200000-line-code and 20000-texture game still won't break a 4G-computer. So most likely we will be loading all the resources that the game is going to use or have potentials to use at the very beginning of the game.

Next class is the **Inputor**. Like the **TextureLoader** and **SoundLoader**, these classes are only some simple encapsulations of SDL functions that make it easier for us to call the functions.

**Inputor** simply encapsulates some keyboard and mouse events. Depending on future development, we can port the game to the mobile platforms like phones, ipads and consoles by adding according controller surpports.

For now I've implemented some basic functions like "iskeydown" , "getMouseButtonState" and "getMouseRelativePosition". In the future there should be more complicated controls like combination keyboard patterns and mouse wheel events.

I guess I need to wrtie a fuction sheet on the wiki which gives you guys a way to get all the API functions. If I were you, I would be already freaking out with this guy writing all these. God.

And we have **Camera**. This is a very simple class that records the position of player. You can regard it as a player-position recorder. Everything besides player use the position of **Camera** to calculate their drawing position (whether to draw or not). The **Camera** will be focusing on a player object and then being upadted in the **World::updating()** fuction exclusively.

In a way **Camera** is verbose here, since we have  the option to make **Player** a Singleton class to solve all these references problems.

The existence of class **Camera** merely refrain **Player** bring a Singleton class. I think the game in the future will definitely be a multiplayer game instead of singleplayer game. Singleplayer sucks sometimes. So **Player** class could not be Singleton. If there is 3 players then the vector of **Player** is gonna have 3 different elements.

----------

### IDSheet　Vector2D　Object　 Dice###

**IDSheet.h**, when our game have lots of... let's say thousands of different types of stuff, we'll need a effecient way to organize the IDs. We need to keep them easy to find, and precise to find. So we need a ID sheet like this.

The way how ID sheet is implemented in c++ is exactly the characteristic of c++, because in java u'll (only can) be using static class and final variables. In c++, however, we use macros.<br>
Hum... I guess Singleton'll do just fine here, but let's keep it thtta way.

**Vector2D.h**, this is a small class represents a point or a 2D vector in the 2D space. It implements a few most basic calculations and is ready to use.


**Object.h**, why Object exists is because everything in the game world will have ID, position, size and some other common properties. So we need to create an **Object** class to extract these abstract featrues and make everthing in our game inherit from the **Object** class. THIS IS THE POWER OF OOP!!!<br>
Long lives OOP forever!!!

(Don't tell others I'm learning Assembly recently, don't wanna be a paradox person)

**Dice.h**, it's a small random number generator. A game is bound to have lots of unstable factors.

----------


### 3/2/2017 22:03:20 ###

I guess that's all for now. There are a few files I don't cover them here, but they are only some base game classes inherit from the **Object** class, not much to explain. I have full faith in your being able to figure them out yourself.

I don't really want to write this readme since I'm a coder not a writer. Most of the time I will complicate things more than I can explain things. I hope I don't screw up your mind when trying to make things clear.

My code is hard to understand not because they are superior but merely due to the bad habit with my code writing. If you can understand my code naturely, you can.... well, you can do nothing and have absolutely ZERO amount of self-pround since it is useless...

**If have any question then ask.**