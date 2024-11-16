# IJC-DU2
# Ronald Bednár <xbednar00>
# 25.4.2024, FIT - VUT

C_FLAGS = -g -std=c11 -pedantic -Wall -Wextra
CPP_FLAGS = -std=c++17 -pedantic -Wall

all: wordcount wordcount-dynamic tail

wordcount: wordcount.c io.o libhtab.a
	gcc $(C_FLAGS) -o $@ $^
	
wordcount-dynamic: wordcount.c io.o libhtab.so
	gcc $(C_FLAGS) -L. -lhtab -o $@ wordcount.c io.o

wordcount-: wordcount-.cc
	g++ $(CPP_FLAGS) -O2 -o $@ 
	
io.o: io.c io.h 
	gcc $(C_FLAGS) -c -o $@ $<

# static library
libhtab.a: htab_hash_function.o htab_init.o htab_free.o htab_clear.o htab_statistics.o htab_size.o htab_bucket_count.o htab_lookup_add.o htab_for_each.o
	ar -rcs $@ $^

htab_hash_function.o: htab_hash_function.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_init.o: htab_init.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_free.o: htab_free.c htab_private.h
	gcc $(C_FLAGS) -c $<   
htab_clear.o: htab_clear.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_statistics.o: htab_statistics.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_size.o: htab_size.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_bucket_count.o: htab_bucket_count.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_lookup_add.o: htab_lookup_add.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_for_each.o: htab_for_each.c htab_private.h
	gcc $(C_FLAGS) -c $<

# dynamic library
libhtab.so: htab_hash_function-dyn.o htab_init-dyn.o htab_free-dyn.o htab_clear-dyn.o htab_statistics-dyn.o htab_size-dyn.o htab_bucket_count-dyn.o htab_lookup_add-dyn.o htab_for_each-dyn.o
	gcc $(C_FLAGS) -shared -o $@ $^

htab_hash_function-dyn.o: htab_hash_function.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_init-dyn.o: htab_init.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_free-dyn.o: htab_free.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@  
htab_clear-dyn.o: htab_clear.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_statistics-dyn.o: htab_statistics.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_size-dyn.o: htab_size.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_bucket_count-dyn.o: htab_bucket_count.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_lookup_add-dyn.o: htab_lookup_add.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_for_each-dyn.o: htab_for_each.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@

run: 
	./wordcount
	export LD_LIBRARY_PATH="." ./wordcount-dynamic
clean:
	rm -f wordcount tail wordcount-dynamic wordcount- *.o *.a *.so
