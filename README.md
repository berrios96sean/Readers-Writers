# Readers and Writers 

This project uses readers and writers to do the following: 

The readers should read the variable value and print the current value of the variable. 
Each reader should print the variables twice. 
The writers should write their ids in the variable. 
The writer should write in one go and then verify that the correct Id is written into the variable.
Readers and writers do not run in infinite loop, but reader reads twice while writer writes and then again verifies.
The reader yields after one read and then finishes after the second read.

On the first read the reader prints:
Printf(“\n This is the %d th reader reading value i = %d for the first time \n”, readerID, i );

On the second read the reader prints:
Printf(“\n This is the %d th reader reading value i = %d for the second time \n”, readerID, i );

The writer yields after the first write and then exits after the verification step.
On the first write the writer prints:
Printf(“\n This is the %d th writer writing value i = %d \n”, writerID, i );

On the verification loop the writer should print:
Printf(“\n This is the %d th writer verifying value i = %d \n”, writerID, i );

# Test Case

The test case will be in the following format:
2,2
1
-1
2
-2

The first line will have number of readers and number of writers consecutively, followed by R+W numbers showing the ready Q. The positive numbers are readers, the negative numbers are writers. Always have the initial scratch pad variable i = 0;
In this case the output will be
This is the 1 th reader reading value i = 0 for the first time

 This is the 1 th reader reading value i = 0 for the second time

 This is the 1 th writer writing value i = 1

 This is the 1 th writer verifying value i = 1

 This is the 2 th reader reading value i = 1 for the first time

 This is the 2 th reader reading value i = 1 for the second time

 This is the 2 th writer writing value i = 2

 This is the 2 th writer verifying value i = 2
