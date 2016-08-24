# GameDev-Framework
GameDev Framework (GDF) is a C++ / SFML modular framework for 2D game development.

It provides a small kernel to be used as a core-engine for any kind of application, due to its high flexibility achieved using GameObject/Component architecture, it can integrate any type of user-modules ( Components ), without changing the kernel code at all. 

In any case the GameLogic does not fit to your application-logic, it can be overridden (See. GameInfo class ) in order to implement your own game-logic. i.e: Your own way of __Intializing__,  __Updating__ and __Drawing__ stuffs. However, the architecture is preserved.


# Built-in modules
The framework does provide some (dedicated/specific) built-in modules to be directly used.  ( a Module is a set of several Components ), such as:
+ __Rendering__ : SpriteRenderer, TextRenderer, ShapeRenderer ...
+ __Animation__: State machine based Animation system, Multi-layered Animator. c.f Unity3d's Animator
+ __Audio__: Audio, Music, AudioListener, Filters ...
+ __Resource management__
+ __Cameras__ 
+ __Time management__
+ __Physics__: Rigidbodies, colliders, joints ...
+  etc .

# Everything is a *Component*
User-created components must inherit from Component class in order to be fully functioning. In consequence, depending on the type of the created component, we made the __Component__ class in a way that allows it to be most __versatile__ possible.

# Building & Compiling
The framework is built cross platform c++, extending the following labraires

#### __Requirements__
+ C++14
+ SFML 2.3.2
+ ~~Box2D 2.3.1~~
+ Qt 5.7.0 with GCC4.9


#### __Compiling__

+ Tested under Linux-Ubuntu 64bit GCC 5.4
+ Install the [Qt Library](https://www.qt.io/download/) to use __qmake__

__You can either compile__

* Using Qt-Creator, here is the pro-file [pro-file](./src/GameDevFramework.pro)
* Using command-line
In order to avoid some-problem with make path, ( like i had ), i create used qmake directly from its path.
```bash
QMAKE=/path_to_your_Qt/Qt5.7.0/5.7/gcc_64/bin/qmake
cd path_to_the_project/src/
$QMAKE -project "QT += serialport" "INCLUDEPATH += /path/to/sfml/include" "LIBS += -L/pat/to/sfml/lib -lsfml-system -lsfml-graphics -lsfml-window" "CONFIG += c++14" "TARGET GameDev-kernel"
$QMAKE
make
```

# Getting started
Here is a brief diagram showing your location within the framework.
![architecture](http://image.k-upload.com/view-img-norm_2016-08-24-1b5c50292gettingstart.png "Framework architecture")

To get started, you __must__ create you own game-logic and scenes, you can override both **GameInfo** & **Scene** class and redefine all **pure** methods.

* Note that each new (**different**) Scene you create, it must be done in a new class.

Just after that, you can start building you first component by overriding the __Component__ class.
 
 * c.f See [example](./example/) in kernel branch repo.
 
# Code samples
__Creating new GameObject__
```C++
gdf::kernel::GameObject* go = gdf::kernel::GameObject::instantiate<0>("g0"); 
// instantiate<0> must is static and must the scene target: 0 is a reference to a scene.
	
```

__Adding a Component to a GameObject__
```C++
Rigidbody2D* rb2d = go->addComponent<Rigidbody2D>()
// rb2d->set ...

go->addComponent<Chrono>()
```

__Destroying an Object__
```C++
gdf::kernel::GameObject::destroy( go );
// Automatically destroy all component within it
```

### Video Example ( Time Reversal )
<a href="https://www.youtube.com/watch?feature=player_embedded&v=EdxZK8fgfcg
" target="_blank"><img src="http://img.youtube.com/vi/EdxZK8fgfcg/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

# Contribution
The framework is designed to be fully open-source and community repo,

You are welcome to:

+ Suggest Code improvements ( as i'm writing very basic things right now to get a global architecture, then i'll refine every class ) 
+ Suggest modifications about the kernel or an existing module.
+ Suggest your own modules. even if there is an already existing one, 
There is no better code. but one can fit better than the other, depending on the problem+
+ Platform portability, ( as it is currently tested only under Ubuntu 16.04. )
But since Qt & SFML & Box2D are multi-platform, there should not be a problem.(not tested on other platforms )

# Links
Currently there is no available website or forum.

You can follow a topic on sfml forum which explain more things about the framework.
[GDF-Topic in SFML Forum](http://en.sfml-dev.org/forums/index.php?topic=20730.0)
