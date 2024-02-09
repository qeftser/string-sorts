## String sorts

A comparison of three way radix quicksort and radix counting sort for strings

### Use

To use:
```
 $ make
 $ make run
```
Make run will run the sort with gullivers-travels.txt. If you want to try the-hunting-of-the-snark.txt or 800-thousand-strings.txt you need  to call the program directly:
```
 $ ./bin/string-sorts "bin/the-hunting-of-the-snark.txt"
 $ ./bin/string-sorts "bin/gullivers-travels.txt" // Same as make run
 $ ./bin/string-sorts "bin/800-thousand-strings.txt"
```
On my computer 800-thousand-strings.txt was overflowing the stack memory so be warned that it might fail. If you know how to allocate more stack space it could work. 

### Results
I was getting 0.02 seconds average for radix counting sort and 0.07 seconds average for three way radix quicksort. This was for gullivers-travels.txt. For the-hunting-of-the-snark.txt I was averaging 0.0025 seconds for radix counting sort and 0.0035 seconds for three way radix quicksort

### Comments
A note about each algorithm: Three way radix quicksort will be better for strings than quicksort because it ignores string length. Quicksort will not sort as expected due to variable length strings. At least that was my experience. For radix counting sort it is important to note that these text files were ascii only. Using radix counting sort would not likely be a good idea for text that relies heavily on unicode, something like Chinese or Japanese.

### References
Three way radix quicksort: https://en.wikipedia.org/wiki/Multi-key_quicksort   
Three way quicksort partition: https://en.wikipedia.org/wiki/Quicksort#Repeated_elements   
Counting and radix counting sort: https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/   
