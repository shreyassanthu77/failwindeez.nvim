target=x86_64-linux-musl
cc=zig cc -target $(target)
cflags=-Wall -Werror -Wextra -std=c23
mode=debug
ifeq ($(mode), release)
	cflags+=-O3 -s
endif

builddir=build/$(mode)
objdir=$(builddir)/obj
bin=$(builddir)/failwindeez

.PHONY: mkdirs
mkdirs:
	@mkdir -p $(builddir) $(objdir)

$(objdir)/tree-sitter.o: mkdirs ./tree-sitter/src/lib.c
	$(cc) -std=c11 -c -o $@ ./tree-sitter/src/lib.c -I./tree-sitter/include -I./tree-sitter/src

tree-sitter-css-src=$(wildcard ./tree-sitter-css/*.c)
$(objdir)/tree-sitter-css.o: mkdirs $(tree-sitter-css-src)
	$(cc) -std=c11 -c -o $@ $(tree-sitter-css-src) \
		-I./tree-sitter-css/include -I./tree-sitter-css/include -I./tree-sitter/src

.PHONY: clean build run watch

src=$(wildcard *.c)
objs=$(objdir)/tree-sitter.o $(objdir)/tree-sitter-css.o
includes=-I./tree-sitter/include -I./tree-sitter-css/include -I./inc
$(bin): mkdirs $(src) $(objs)
	$(cc) $(cflags) -o $(bin) $(includes) $(src) $(objs) 

build: $(bin)

run: $(bin)
	@./$(bin)

watch: $(bin)
	ls $(src) | entr -cr make -s run -e mode=$(mode)

clean:
	rm -rf build
