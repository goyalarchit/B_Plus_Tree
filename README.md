# B+ Tree 
Implementation of B+ tree, which is extensively used in the SQL range queries.The implementation supports queries like INSERT,FIND,COUNT and RANGE.

## Types Of Queries
### Query Syntax
1. INSERT X - insert X into the B+ tree 
2. FIND X - print YES if X is already inserted, else NO
3. COUNT X - print number of occurrences of X in B+tree
4. RANGE X Y - print number of elements in range x to y (both x and y included)
5. PRINT - Pretty Print B+ Tree

### Constraints:
1. -10^9 <= X <= 10^9, -10^9 <= Y <= 10^9
2. The number of queries will be less than 10^6.


## How to Build
### Using Makefile and make
1. Open terminal in your machine.
2. Type ```make``` and press enter.
3. Now you should see an a.out file in the current directory.

### Using manual build
1. Open terminal in your machine.
2. Type ``` g++ -g BPTree.h BPTree.cpp PrettyPrint.h PrettyPrint.cpp main.cpp ``` and press enter.
3. Now you should see an a.out file in the current directory.


## How to Execute
1. Type ```./a.out <file_name>``` and press enter.

#### Note 
```<file_name>``` : Can be a path too, or just file_name if it is present in current directory.


## Input:
1. The input argument consists of a file name.
2. Each line in the file consists of one of the above-mentioned queries.
## Output:
Write outputs of the corresponding queries in command-line.

## How to Test
### Running Test Cases
1. Type ```./test.sh``` and press enter.
2. If there is no line after the Comparision Line for each test Case then that test case is passed.
3. Else output will correspond to the output format of ```diff```.

### Generating New Test Cases
1. Inside the Director test_data, there are two programs, ```test_input_generator.py``` and ```test_out_generator.cpp```. 
2. First run ```python3 test_input_generator.py``` and a new file called input.txt will be generated/overwritten in the pwd.
3. Now compile ```g++ -g test_out_generator.cpp ```, followed by ```./a.out input.txt > out.txt```. Now you will have the correct output corresponding to your newly generated input.txt.
4. Now you can use this input.txt with the test.sh, and see if it passes it. 

#### Note
1. There will be no PRINT test queries, as it is just for making code easier to write during developement.

2. Also PRINT does not support more than 10 level in B+ Tree.As it will not be pretty printable on terminal.
 
## Basic Implementation Details
### Directory Structure
1. PrettyPrint.h - Declares a class called ```BPTreePrinter``` which gives a print function which pretty prints the tree. 
2. PrettyPrint.cpp - Implements the class ```BPTreePrinter```.
3. PrettyPrint.h - Declares classes called ```Node, BPTree``` which defines a B+ Tree node and B+ Tree.
4. PrettyPrint.cpp - Implements the class ```Node, BPTree```.
5. main.cpp - The Driver Program. 
6. test_data/ - Director Containing Test input files and Test Case Generators.

### Overview Of B+ Tree
#### B + Tree Node
1. Keeps track of Keys, Child Pointers, Number of Keys, Parent Pointer, Leaf Status.
2. Common class which acts as both a Leaf as well as a Internal Node.
3. Has a special function called ```sterlizeNode()``` which sterlizes the node i.e. removes the garbage values from the node after Node splitting.
4. It is a friend of ```BPTreePrinter``` class

#### B+ Tree
1. Keeps track of the root Node.
2. Implements functions like insert(), search(), count(), and range() etc.
3. It is a friend of ```BPTreePrinter``` class

### Implementation of B+ Tree Operations
#### ```insert(int x)```
1. First it checks if the tree is empty, if it is then it creates a leaf node and returns it as root.
2. Else Search for the leaf Node where the node should be inserted.
3. If the found leaf node has space then add the value, and finish.
4. Else split the node using Right Bias, and add the smallest key of new formed leaf to the parent. And again follow insertion process steps 2,3,4 till the overflow condition becomes false, and the tree becomes stable.

#### ```search(int x)```
1. Uses an private utility Function called ```findLeafNode(int x)``` which returns potential leaf node with the value.
2. Check the node if value exists then print "YES" else "NO".

#### ```range(int x,int y)```
1. Uses an private utility Function called ```findLeafNode(int x)``` which returns potential leaf node with the value. But here we call it on x-1, to ensure we get keys from first occurence of x.
2. Traverse the values in the node and increase count.
3. If the values in current leaf node are traversed and no key > y is found we go to next adjacent leaf node and continue counting.
4. If any key > y is found , print the value of count.

#### ```count(int x)```
1. Uses the same Range function internally, by calling ```range(x,x)```.
2. We get the required count.