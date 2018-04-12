# Assignment3

This is the source code repository that will be used as a starting point for Assignment 3. You should edit this file (README.md) in order to write your responses for Question 2.

## Question 2

ID: 260762008

### part one

- Check the number of input parameters. If the number is wrong, print error message and quit the program.
- Create an array of PREFERENCE\_INFO structures. Since argc is greater than 3, the length of this array is a positive number. This structure is defined in preferences.h. Then we create a new variable called target\_user of PREFERENCE\_INFO. We load its preferences by using load\_one\_preference function, which is defined in preferences.c. The input parameters are the adress of target\_user and the corresponding txt file.
- Next, we use pre-compiler to debug the program. If it doesn't compile, we will print the target\_user's preferences by using the print\_preferences function(which is defined in preferences.c). The input parameter is the address of target\_user, and it will loop through each field of PREFERENCE\_INFO and print each field. If it compiles, compute the min\_distance, best\_match and best\_fname by using compute\_difference\_numeric and compute\_difference\_alphabetic functions which are defined in distances.c. 
- Finally, print the first\_name and last\_name FIELDS of target\_user and favorite\_movie FIELD of best\_match.

### part two

LOAD\_FIELD creates an array of function-pointers (input\_fcn\_array). The size of the array is equal to the number of different fields in the PREFERENCE\_INFO. Each element in the array is a function that can load the corresponding information into the struct. Therefore, this function can handle various types of data.

### part three

In the field\_offsets, each element is corresponding to the size of each field in bytes. The number of bytes is computed by offsetof function, which is the offset from the beginning of an object of specified type to its specified member, including padding, in bytes. Therefore, the offset to each field in the struct can be computed accurately and stored in the field\_offsets array.

