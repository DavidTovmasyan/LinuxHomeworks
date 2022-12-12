run: task1 task2
	./task1 333333333 333333333 333333333 binF
	./task2 33 1 binF
task1 : task1.c
	gcc task1.c -o task1 -pthread
task2 : task2.c
        gcc task2.c -o task2 -pthread
clean:
	rm -f task1 task2 binF
