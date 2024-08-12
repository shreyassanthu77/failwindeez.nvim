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

.PHONY: clean build run watch

src=$(wildcard *.c)
$(bin): $(src)
	@mkdir -p $(builddir) $(objdir) 
	$(cc) $(cflags) -o $(bin) $(src)

build: $(bin)

run: $(bin)
	@./$(bin)

watch: $(bin)
	ls $(src) | entr -cr make -s run -e mode=$(mode)

clean:
	rm -rf build
