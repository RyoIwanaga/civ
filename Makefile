# $@ 	ターゲットファイル名
# $< 	最初の依存ファイル名
# $? 	ターゲットより新しい全ての依存ファイル名
# $^ 	全ての依存ファイル名
# $+ 	Makefileと同じ順番の依存ファイル名
# $* 	suffixを除いたターゲット名
# $% 	アーカイブだった時のターゲットメンバ名 

### Macro ###

CFLAGS=-Wall -O
CPP11=-std=c++11
CURSES=-lncurses

OBJS=

### Target ###

.PHONY: all
all:
#	${CC} ${CFLAGS} 
	${CXX} ${CPP11} ${CFLAGS} ${CURSES} main.cpp World.cpp # Console/Window.cpp
	./a.out

.PHONY: debug
debug:
	${CXX} ${CPP11} ${CFLAGS} ${CURSES} main.cpp World.cpp -g -O0
	lldb a.out

.PHONY: clean
clean:
	${RM}



