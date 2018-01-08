Voronoi Engine
==============

Advanced bullet hell engine.

Voronoi Engine aims to be a bullet hell engine with similar capabilities to
*Danmakufu Ph3*, but to also be better in several aspects:

- High speed, running at a stable ~60 FPS for many thousands of game objects.
- Extremely precise collision detection.
- Offer a better danmaku creation experience for scripters that allows
  high-level composition of sub-patterns.

Additionally, Voronoi Engine aims to have dual AI components: one that generates
nonspell or spell card stages, and one that plays arbitrary stages like a
player. The AI player's difficulty in playing the stage is then passed as
feedback to the stage-generating AI to allow many unique stages of a prescribed
difficulty to be generated. Additionally, the playing AI can be used to rank
user-generated stages.

The engine is currently in an early stage of development.

Obtaining
---------

This project requires CGAL and SDL2 stuff. Additionally, it relies upon a CMake
submodule, [sanitizers-cmake](https://github.com/arsenm/sanitizers-cmake). To
automatically get this submodule when cloning, run:

```sh
git clone --recurse-submodules https://github.com/jfjhh/voronoi-engine.git
```

Building
--------

To build with CMake:

```sh
cd voronoi-engine
mkdir build
cd build
cmake ..
make -j`nproc`
```

Running
-------

From the build directory, run `./voronoi`.

