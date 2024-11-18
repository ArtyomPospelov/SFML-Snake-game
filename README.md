# SFML Snake game
SFML Snake game implementation. Flexibly customized to your taste
![Screenshot_2](https://github.com/user-attachments/assets/6e36c436-c49d-4955-afbd-5482b1473427)

## Motivation
To make a classic Snake game with support for user preferences settings. This way you can configure:
* The playing field;
* Timings. By doing this, you can adjust the difficulty of the game;
* Visual style. Full color palette + snake shape and its treats;
* A variant of the game;
* The layout of the control keys.

## How to build a game
You can build the game on any* C++ compiler. For development, I used the SFML library version 2.6.1.
The code also uses an ini file support header. I took it from the user [Rookfighter](https://github.com/Rookfighter). Thanks to him for developing this file for convenient ini file support.

*Provided that you use the MSVC compiler. There are _s functions there. There are not many of them. I'll get away from using them later.

## User's Guide
After compilation, place the exe file of the game in a directory convenient for you. It is better to go to a special separate room. The game requires a font file of any format that is supported by SFML, for example .ttf. Select the desired font, copy it to the game folder and rename it to "Font" (without extension.ttf). Later, I will implement that you can set the path to the font directly in the configuration file (about it below) without copying it to the folder with the game.

Actually, for the game, this is the minimum that is required for it to start. Of course, you can customize the game to your taste. Therefore, create an .ini file in the game directory (this is the time-tested simplest settings file that was originally developed by Microsoft to configure the first versions of Windows). Name it "config.ini". Here is a complete example of what can be configured in this file:
```
[Space]
GridWidth=20
GridHeight=20
CellSize=25

[Timing]
InitialFrameDelay=200
FrameDelayDecrement=10


[Style]
Background=10,15,27
SnakeBlock=108,212,69
SnakeHeadBlock=71,167,39
SnakeOutline=10,15,27
Meal=228,51,48
MealOutline=228,51,48
ScoreText=221,245,120
WelcomeText=108,212,69
GameOverText=228,51,48
MealShape=circle
SnakeShape=rectangle

[Mode]
WrapMode=true

[Control]
DirLeft=A
DirRight=D
DirUp=W
DirDown=S
Control=Space
```
Some explanation of the settings:
* All available numbers in the settings are non-negative decimal integers (and only);
* Colors are set in RGB recording format, where each color channel is separated by a comma;
* The values of the shape settings can be the following values: circle, rectangle, triangle. The case does not matter.
* Control key settings can have all available keyboard key mnemonics. I was sewing up the letters in the English code. The setting, which is referred to as "Control", is the key that will start the game, pause it.

Of course, some settings may not be in the file, but if you set the setting, then set the entire key section, because in the code I only check and read the settings by the presence of a section (if there is a section, but there is no expected key, then reading the settings stops, and an error is written in the vlog file).Later, I may make this process more flexible and less strict.

There are logs in the game. If the game does not start, then you can read "log.txt "and see what the reason is. Also, various information is written there with timestamps when what happened in general terms. The score of the game that the player managed to score is also recorded there.
