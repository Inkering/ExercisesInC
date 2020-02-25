trout: main.c trout.o util.o trout.h util.h
	gcc  $^ -o $@
%.o: %.c %.h
	gcc -c $< -o $@
clean:
	rm trout util.o trout.o
