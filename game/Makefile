GAMEc=game.c
STUCTh=../headers/struct.h
INITh=../headers/init.h
CONSTh=../headers/const.h
BUBh=../headers/bubble.h
BIN=game

$(BIN): $(STUCTh) $(INITh) $(CONSTh) $(BUBh) $(GAMEc)
	gcc -Wall -g -std=c99 $(STUCTh) $(INITh) $(CONSTh) $(BUBh) $(GAMEc) `sdl-config --cflags --libs` \
	-I $$HOME/Install/include \
    -L $$HOME/Install/lib \
	-Wl,-rpath,$$HOME/Install/lib \
	-o $(BIN) \
	-lm -lSDL_mixer

clean:
	rm -f $(BIN)