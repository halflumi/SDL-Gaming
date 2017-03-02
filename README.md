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

Like player.h and player.cpp, the former is the definition (assignment) of class "player" and the latter is implementation of that.

I just want to point this out since this is indispensible, especially this is the utmost difference of how OOP looks like between C++ and Java or C#

> -- Question: then why don't u use Java? It gotta be a lot more neat.
> 
> -- Answer: well, good idea, I guess I'm just gonna go ahead and delete all these and write them in... what the hell? Why it is so slow?
> 
> -- True Answer: I'm familiar with C++ more than Java, so...

I'm such a chatterbox, u guys need to be careful to avoid these non-sense parts to get what is useful, okay?
If u're having any troubles in C++, u can ask. I may have one way or two to make things clear.

----------
#### SDLGaming.cpp ####
Let's start with SDLGaming.cpp
If u have my VS project at hand, u'll notice this is also the name of the project.
This file defines the entrance of the game program, i.e. the main(), more precisely the main() of SDL.

This file doesn't do much, since almost everything is encapsulated into classed. It basically only calls "Main" class to initialize the game and organize everything into a forever running loop (ends when player wants to quit).

I guess there would be two questions u're gonna ask when looking at the code:

1. how is "Main" initialized
2. how is FPS controled here

First: how is "Main" initialized?

Intuitively "Main" is initialized when Main::Inst() is called.
You might freak when there is not something like

    Main* mainClass;
    mainClass = new Main();

We shouldn"t do this with "Main" (and many other drivers) class here, since this implicate that "Main" is a repeatable and recreatable object, which is against its common sense.

What we want "Main" to be is:
