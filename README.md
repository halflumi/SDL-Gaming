# SDL-Gaming
ok, so, yeah, this is um... a project, a game project, maybe not... well, just sorta like thtta way, a project that conducts making a game.

I wch of here, writing down some explanations of the most basic elements of the game itself so far, in case em... the chaotic codes of the game make u feel sick.

NOTICE: these illstrations can be inaccurate as the game being developed. This is only how it looks like when I first upload it onto Github.

The game has **27** source files for now:

- Camera.h
- Dice.cpp
- Dice.h
- Entity.h
- IDSheet.h
- Inputor.cpp
- Inputor.h
- Main.cpp
- Main.h
- Object.h
- Player.cpp
- Player.h
- Projectile.cpp
- Projectile.h
- SDLGaming.cpp
- Sound Loader.cpp
- SoundLoader.h
- Sprite.cpp
- Sprite.h
- TextureLoader.cpp
- TextureLoader.h
- Tile.cpp
- Tile.h
- Vector2D.h
- World.cpp
- World.h

S**t, that's a hell lot.
There's gonna be more of them as the game gets close to completion.
Note that ya'll need to download all of those to make it work, otherwise it won't compile which is gonna freak you out.

Actually lots of these are self-explanatory, what it gotta take to consist of a game is clear: graphic, audio, i/o, etc.
I'm only gonna illustrate how I implement these things, if u're having problems with SDL stuff, go searching on SDL wiki instead of holding a knife tracking me down through the network cables - it happens sometimes, right?

Okay, enough joking around.

The files consist of both .h and .cpp, where almost every .cpp has a parallel .h file. This is becasue:

the game is highly OOP featured
the way how C++ implements classes

Like player.h and player.cpp, the former is the definition (assignment) of class **Player** and the latter is implementation of that.

I just want to point this out since this is indispensible, especially this is the utmost difference of how OOP looks like between C++ and Java or C#

> -- Question: then why don't u use Java? It gotta be a lot more neat.
> 
> -- Answer: well, good idea, I guess I'm just gonna go ahead and delete all these and write them in... what the hell? Why it is so slow?
> 
> -- True Answer: I'm familiar with C++ more than Java, so...

I'm such a chatterbox, u guys need to be careful to avoid these non-sense parts to get what is useful, okay?
If u're having any troubles in C++, u can ask. I may have one way or two to make things clear.

"which language" should not be the topic here, but compared to pure OOP language like java or c#, c++ has the ability... or let's just say at least the potential to jump out from the loop of OOP. This enables us to find the methods that OOP has abandoned to solve some problems more efficiently and effectively.<br>
ofc, these methods , as a matter of fact, can only be found at some really limited situations. Most of time there are only organizational differences between languages. What a programming language can do is almost the same (espcially c++ and java). <br>
All in all, the persistence in c++ leads to two major results:

- Even lower lower limit
- Even higher upper limit

"Even lower lower limit" means the organization difficulty of c++ is higher than java. So if we don't do it gracefully, it'll mess up and ending up being even slower and heavier than java. On the contrary, "Even higher upper limit" means the visibility of programs of c++ is more than java. This includes pointers, macro (compiler), memory controls and so on. These featrues of c++ allow us to optimise our program at a larger scale.

The argue of "which language" won't end long as civilizations exist, but I guess I've talked enough of it already. Without further ado, let's jump into the project itself.

----------
### SDLGaming.cpp ###
Let's start with SDLGaming.cpp
If u have my VS project at hand, u'll notice this is also the name of the project.
This file defines the entrance of the game program, i.e. the main(), more precisely the main() of SDL.

This file doesn't do much, since almost everything is encapsulated into classed. It basically only calls **Main** class to initialize the game and organize everything into a forever running loop (ends when player wants to quit).

I guess there would be two questions u're gonna ask when looking at the code:

- how is **Main** initialized
- how is FPS controled here

　1. how is **Main** initialized?

Intuitively **Main** is initialized when Main::Inst() is called.
You might freak when there is not something like

    Main* mainClass;
    mainClass = new Main();

We shouldn"t do this with **Main** (and many other drivers) class here, since this implicate that **Main** is a repeatable and recreatable object, which is against its common sense.

What we want **Main** to be is:<br>
·　only one specific unique instance through out the whole process<br>
·　visible anywhere of the program

Well, these two features are easy to implement in java or c#. To be honest, when I first starts to write this game in c++, I also have a hard time looking for a way to implement these features in c++!<br>
Nonetheless, I finally find a magical (not entirely) technique to implement these two features at a time: **Singleton**.

Now Singleton is a very important technique that has been used through the whole program. It is something looks like this:

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

You can see that Singleton class like **Camera**,**TextureLoader**,**SoundLoader**,**Inputor** all have the identical structures like this.<br>

The implementation of Singleton in cpp mainly utilizes how "static" is treated in cpp. First we put constructor function "Main()" into "private" scale, this makes sure that the constructor cannot be called ousides the **Main**. So it ensures "one and unique" purpose.<br>
And the design of Inst() just gives us the access to get reference to **Main** publicly anywhere of the program, on the condition of returning the specific and unique instance of **Main**.

Um... I know these explanations have totally zero help with your understanding of how Singleton works. It's not a big problem if u don't know what happens on earth, since for us it is only a ready-to-use interface. but if u r interested in why to implement it like this or what happens inside these codes, u can simply go searching **Singleton** on the internet and there will be some more detailed interpretations.

Back to how **Main** is initialized.<br>
Since we implement **Main** using Singleton. The initialization process of **Main** is:<br>
·　Initialize the local variable **INSTANCE** of **Main** as **NULL** when compiling<br>
·　Inst() being called in main() when programs starts<br>
·　Inside Inst(), since **INSTANCE** is **NULL**, so create a **Main** instance and return it<br>
·　If Inst() is again called from elsewhere of the program, Inst() detects that **INSTANCE** is no longer **NULL**, so it returns the instance that was 　 created when the program starts.

　2. how is FPS controled

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

### Main.h　Main.cpp　　World.h　World.cpp###

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

### TextureLoad.h　TextureLoad.cpp　　SoundLoader.h　SoundLoader.cpp　　Inputor.h　Inputor.cpp ###

