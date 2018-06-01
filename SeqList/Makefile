
.PHONY:clean

SeqList : SeqList.o
	gcc -g $^ -o $@

%.o: %.c
	gcc -c $^ -o $@

clean:
	rm *.o SeqList
