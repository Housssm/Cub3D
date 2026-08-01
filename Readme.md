
*This project has been created as part of the 42 curriculum by mtodzzi and hoel-har.*

# Cub3d

## Description

This project aims to create a 3D game using raycasting, inspired by the first game of its kind: Wolfenstein 3D. The goal is to render a 3D perspective from a 2D map, simulating depth and movement through ray-casting techniques.

## Instructions

To play the game, simply run `make` to compile the project, then launch it with `./cub3D` followed by the path to the map file.

The map must follow specific rules to be valid:
- It must be entirely enclosed by walls (`1`)
- The player's starting position is represented by one of the following characters: `N`, `S`, `E`, or `W`, which indicate the initial facing direction (North, South, East, or West)
- The map must contain only valid characters and be properly formatted


Example usage:
```bash
make
./cub3D maps/map_valid.cub
```

## Ressources

Ray Casting Tutorial - YouTube - [Comprehensive video explanation of raycasting concepts](https://www.youtube.com/watch?v=NbSee-XM7WA)

Ray Casting in C - Medium Article - [Detailed technical article with code examples](https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13)

-Peer-learning and collaboration with fellow students
 