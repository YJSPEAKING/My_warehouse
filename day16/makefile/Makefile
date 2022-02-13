out:=main
SRCS:=$(wildcard *.c)#拿到当前目录下所有的c文件
OBJS:=$(patsubst %.c,%.o,$(SRCS))
#预定义变量
CC:=gcc
CFLAGS:=-g
$(out):$(OBJS)
	gcc -o $@ $^
rebuild:clean rebuild
clean:
	rm -rf $(OBJS) $(out)
