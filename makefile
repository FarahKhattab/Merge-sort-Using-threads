build: 
	gcc -pthread merge_sort.cpp -o merge_sort -lstdc++

clean:
	rm -f thread
