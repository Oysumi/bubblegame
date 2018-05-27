GAMEc=game.c
STUCTh=../headers/struct.h
INITh=../headers/init.h
CONSTh=../headers/const.h
BUBh=../headers/bubble.h
BIN=game
INSTL=../include
LIB=../lib

$(BIN): $(STUCTh) $(INITh) $(CONSTh) $(BUBh) $(GAMEc)
	gcc -Wall -g -std=c99 $(STUCTh) $(INITh) $(CONSTh) $(BUBh) $(GAMEc) `sdl-config --cflags --libs` \
	-I $(INSTL) \
    -L $(LIB) \
	-Wl,-rpath,$(LIB) \
	-o $(BIN) \
	-lm -lSDL_mixer \
    -lSDL \
    -lSDL_image \
    -lSDL_ttf
clean:
	rm -f $(BIN)