## [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

I tried [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in **C** with [raylib](https://github.com/raysan5/raylib/). This may not follow best practices, but it might be the beginning of a C journey for me.

### try

Before compiling, ensure [raylib](https://github.com/raysan5/raylib/) is installed.

Build and run with [runner](https://github.com/mhs003/runner):

```bash
run build  # build
run run    # run the build
# or just,
run        # build and run
```

or build manually,

```bash
mkdir -p build/
cc -o build/main main.c -lraylib -Wall
```

then run

```bash
./build/main
```



## License

MIT (see [LICENSE](https://github.com/mhs003/game-of-life/blob/master/LICENSE) file)