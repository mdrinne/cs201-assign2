

OBJS = integer.o real.o string.o sll.o dll.o queue.o stack.o bst.o heap.o heapsort.o gst.o avl.o scanner.o trees.o
LOPTS = -Wall -Wextra -std=c99 -g
BEXTRA = sll.c queue.c integer.c real.c string.c
BOEXTRA = sll.o queue.o integer.o real.o string.o

all : test-sll test-dll test-stack test-queue test-bst test-gst test-avl trees

test-sll :
	gcc $(LOPTS) -c sll-0-0.c sll.c integer.c real.c string.c
	gcc $(LOPTS) sll-0-0.c integer.o real.o string.o sll.o  -o test-sll

test-dll :
	gcc $(LOPTS) -c dll-0-0.c dll.c integer.c real.c string.c
	gcc $(LOPTS) dll-0-0.c integer.o real.o string.o dll.o -o test-dll

test-stack :
	gcc $(LOPTS) -c stack-0-0.c stack.c integer.c real.c string.c dll.c
	gcc $(LOPTS) stack-0-0.c integer.o real.o string.o dll.o stack.o -o test-stack

test-queue :
	gcc $(LOPTS) -c queue-0-0.c queue.c integer.c real.c string.c sll.c
	gcc $(LOPTS) queue-0-0.c integer.o real.o string.o sll.o queue.o -o test-queue

test-bst :
	gcc $(LOPTS) -c bst-0-0.c bst.c $(BEXTRA)
	gcc $(LOPTS) bst-0-0.c $(BOEXTRA) bst.o -o test-bst

test-gst:
	gcc $(LOPTS) -c gst-0-0.c gst.c bst.c $(BEXTRA)
	gcc $(LOPTS) gst-0-0.c $(BOEXTRA) gst.o bst.o -o test-gst

test-avl:
	gcc $(LOPTS) -c avl-0-4.c avl.c bst.c $(BEXTRA)
	gcc $(LOPTS) avl-0-4.c $(BOEXTRA) avl.o bst.o -o test-avl

trees:
	gcc $(LOPTS) -c trees.c bst.c $(BEXTRA) gst.c avl.c scanner.c
	gcc $(LOPTS) trees.c $(BOEXTRA) bst.o gst.o avl.o scanner.o -o trees

valgrind: all
	valgrind ./test-sll
	valgrind ./test-dll
	valgrind ./test-stack
	valgrind ./test-queue
	valgrind ./test-bst
	valgrind ./test-gst
	valgrind ./test-avl

test :
	./test-sll
	./test-dll
	./test-stack
	./test-queue
	./test-bst
	./test-gst
	./test-avl
	./trees

clean :
	rm -f $(OBJS) queue-*.o stack-*.o dll-*.o test-stack test-queue test-sll test-dll test-bst test-gst test-avl trees gst-*.o avl-*.o sll-*.o bst-*.o
