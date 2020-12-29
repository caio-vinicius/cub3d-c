# Cub3D

> This project is inspired by the world-famous eponymous 90’s game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way

Inspired by [Wolfenstein3D](https://en.wikipedia.org/wiki/Wolfenstein_3D), the first FPS game to employ the technique of Raycasting and one of the first FPS games made, this project seeks to reproduce the same technique.

## Installation

This project was made on Ubuntu  (more specific: 5.3.0-45 18.04.1 Ubuntu), which I recommend to run. 

Requirements: [Clang v9](https://releases.llvm.org/9.0.0/tools/clang/docs/index.html), [GNU Make v4.1](https://www.gnu.org/software/make/) and [Minilibx](https://github.com/42Paris/minilibx-linux) library.

### Ubuntu

For Minilibx, you can get a guide to how install [here](https://gist.github.com/caio-vinicius/c082bf00b6b2d3c8aeb58f038af9b210).

Now, you can clone the repository:

```bash
$ git clone https://github.com/caio-vinicius/cub3d-c cub3d
$ cd cub3d
```
Then run:
```bash
$ make
```
Done! 

## Usage

To be able to use, you must execute the binary generated from the installation. On repository root:

```bash
$ ./cub3d cub3d.cub
```

That's it! Now a window must open.

### Controls

You can move with W, A, S and D. If you want exit the game, you can press ESC.

### Settings

You can modify some game settings in the `cub3d.cub` file. This file is available at the root of the project and changes some behaviors of the game such as: screen resolution, textures, colors and the map. For this, the configuration is identified with some directives:


| Directive | Param | Description    |
| -- | ------------ | -------------- |
| R  | width height | Resolution     |
| NO | path.xpm     | North texture  |
| SO | path.xpm     | South texture  |
| WE | path.xpm     | West texture   |
| EA | path.xpm     | East texture   |
| S  | path.xpm     | Sprite texture |
| C  | R, G, B      | Ceiling color  |
| F  | R, G, B      | Floor color    |

The last thing in the file is the map, which does not have a specific directive. It is defined by:

- 0: walkable space
- 1: not-walkable space i.e wall
- 2: sprite
- N, S, W, E: player start position with look direction i.e north, south, west and east

## Images

![Scene](https://github.com/caio-vinicius/cub3d-c/blob/media/1.png)
![Scene](https://github.com/caio-vinicius/cub3d-c/blob/media/2.png)
![Scene](https://github.com/caio-vinicius/cub3d-c/blob/media/3.png)
