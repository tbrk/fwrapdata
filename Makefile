
fwrapdata.o: fwrapdata.c fwrapdata.h
	$(CC) -c $< -o $@

test: fwrapdata.o test.c
	$(CC) -o $@ $^ -framework CoreFoundation

