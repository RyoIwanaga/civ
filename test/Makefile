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

OBJS=

### Target ###

.PHONY: all
all:
#	${CC} ${CFLAGS} 
	${CXX} ${CPP11} ${CFLAGS} HexTest.cpp
	./a.out

.PHONY: debug
debug:
	${CXX} ${CPP11} ${CFLAGS} ${CURSES} HexTest.cpp -g -O0
	lldb a.out

.PHONY: clean
clean:
	${RM}



