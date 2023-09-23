# uniq
Implemented the 'uniq' command in xv6, a Linux utility that detects and removes adjacent duplicate lines from a file. This command filters out repeated lines in an input file and writes the filtered data to an output file.
The uniq command in Linux is a command-line utility that reports or filters out the repeated lines in a file. In simple words, uniq is the tool that helps to detect the adjacent duplicate lines and also deletes the duplicate lines. uniq filters out the adjacent matching lines from the input file(that is required as an argument) and writes the filtered data to the output file. For instance, look at the simple file OS611 example.txt. Cat will print out all the contents from the file and uniq removes duplicates from the adjacent line.

Example: By running the cat command, 
$cat OS example.txt

I understand Operating system.

I understand Operating system.

I understand Operating system.

I love to work on OS.

I love to work on OS.

Thanks xv6.

$uniq OS example.txt

I understand Operating system.

I love to work on OS.

Thanks xv6.

For the given solutio1.c and solution1.txt file, the outputs for different commands should work as demonstrated below.

1. For the uniq-c command, the output will give us the number of times each line is repeated.

   $solutio1 -c solution1.txt

   Output:

   3 I understand Operating system

   2 I love to work on OS

   1 Thanks xv6

   1 hello

   1 hi

   1 hiii

2. For the uniq-i command, all the duplicates are removed and the rest are shown in the output console.

   $solutio1 -i solution1.txt

   Output:

   I understand Operating system

   I love to work on OS

   Thanks xv6

   hello

   hi

   hiii

3. For the uniq-d command, all the lines that have duplicates are shown in the output console.

   $solutio1 -d solution1.txt

   Output:
   
   I understand Operating system

   I love to work on OS
