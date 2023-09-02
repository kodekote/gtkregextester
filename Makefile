
CC = gcc
CFLAGS =
PROGRAM_NAME = gtkregextester

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): 											\
		main.o												\
		grt_window.o										\
		grt_regex.o											\
		grt_target.o
	$(CC) $^ -o $@ $(CFLAGS)								\
		-l gtk-3											\
		-l gdk-3											\
		-l gio-2.0											\
		-l gobject-2.0										\
		-l glib-2.0											\
		-l cairo											\
		-l pango-1.0

main.o: main.c
	$(CC) main.c -c -o $@ $(CFLAGS)							\
		-I /usr/include/gtk-3.0/ 							\
		-I /usr/include/glib-2.0/							\
		-I /usr/lib/x86_64-linux-gnu/glib-2.0/include/ 		\
		-I /usr/include/pango-1.0/							\
		-I /usr/include/harfbuzz/						 	\
		-I /usr/include/cairo/ 								\
		-I /usr/include/gdk-pixbuf-2.0/ 					\
		-I /usr/include/atk-1.0/

grt_window.o: grt_window.c grt_window.h
	$(CC) grt_window.c -c -o $@ $(CFLAGS)					\
		-I /usr/include/gtk-3.0/ 							\
		-I /usr/include/glib-2.0/							\
		-I /usr/lib/x86_64-linux-gnu/glib-2.0/include/ 		\
		-I /usr/include/pango-1.0/							\
		-I /usr/include/harfbuzz/						 	\
		-I /usr/include/cairo/ 								\
		-I /usr/include/gdk-pixbuf-2.0/ 					\
		-I /usr/include/atk-1.0/

grt_regex.o: grt_regex.c grt_regex.h
	$(CC) grt_regex.c -c -o $@ $(CFLAGS)					\
		-I /usr/include/gtk-3.0/ 							\
		-I /usr/include/glib-2.0/							\
		-I /usr/lib/x86_64-linux-gnu/glib-2.0/include/ 		\
		-I /usr/include/pango-1.0/							\
		-I /usr/include/harfbuzz/						 	\
		-I /usr/include/cairo/ 								\
		-I /usr/include/gdk-pixbuf-2.0/ 					\
		-I /usr/include/atk-1.0/

grt_target.o: grt_target.c grt_target.h
	$(CC) grt_target.c -c -o $@ $(CFLAGS)					\
		-I /usr/include/gtk-3.0/ 							\
		-I /usr/include/glib-2.0/							\
		-I /usr/lib/x86_64-linux-gnu/glib-2.0/include/ 		\
		-I /usr/include/pango-1.0/							\
		-I /usr/include/harfbuzz/						 	\
		-I /usr/include/cairo/ 								\
		-I /usr/include/gdk-pixbuf-2.0/ 					\
		-I /usr/include/atk-1.0/

debug: CFLAGS += -g
debug: $(PROGRAM_NAME)

clean:
	rm -f *.o $(PROGRAM_NAME)
