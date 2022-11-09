# Calculator with unlimited accuracy

## Task

My task will be to implement the calculator with unlimited accuracy. The calculator will be able to work with both integers and decimals, disabling basic operations: addition, subtraction, multiplication and division, but only for integers (it will take into account the rest). In addition, the calculator will be able not only to perform operations with numbers, but also to write the result into a variable and then use the variable in the calculation.

The user can at times use the calculator to use any of the proposed operator for the operations described above: `+`, `-`, `*`, `/`, `()`, parentheses can be nested in the expression.

In order for the calculator to be more useful, the user can save its state (for example, variables and history) in a file and, if necessary, reload it.

## Specification

In my imagination downloading will work so that the user can easily download all the operation, and those will be written to a separate file exact as it was written to the calculator(it will be written to the file at the same time when writing to the calculator, so that all these data were not stored in memory), then At the same time, when loading, the program writes variables to its objects in classes so that it can continue to work with them.

The Program will not use any graphical interface and all operations will be processed directly in the terminal. If the user wants to download the story of the calculator(for this he just needs to type the download command), I will make the program so that all downloaded files are stored in the "sourses" programs . On the contrary, if the user wants to load a story file, it will be enough just to write the saved file

The Program needs to parse the data to know what it needs to work with and with what classes it will call for further work. Since the user can type anything in the terminal, the program will have to detect and print an error if the syntax is not typed correctly. At the beginning of the program will be written what the user needs to write to the calculator work properly.

## Polymorphism

In my program I will assume to use jedmu hierarchies of classes that will satisfy the conditions for polymorphism. Specifically, some classes will work with numbers are quite large and others work with huge numbers.

### Fairly large numbers

In this class group, I will have a parent class (`CDataSize`) and two legacy classes (`CInteger` and `CFloat`) that will represent the type that the program will work with. Concretely, I will have two so-called types in the program: integers (presented using long long int), decimals (presented using two numbers long long int for frontal numbers and also long long int for numbers after the comma). This is not data types literally, but rather my own data type by which the classes will be named. In each inherited class, they will calculate the numbers in their own way, but in addition, the result after the operations will store its result in the variable parent class (for int and float respectively), so that it can be used further in the calculation. Numbers will be carried out with the help of operators`+`, `-`, `*`, `/`(only for integers), which will be virtual in the parent class and overwritten in the inherited classes. All this group can work only with limited numbers, if the type long long int allows. Larger numbers will require a vector long long int with multiple instacs/

### Huge numbers

The goal of this group is completely the same as the previous one, but it will work with numbers larger than long long int allows. For numbers of this size, I need to use a string (this will be a vector long long int) so that the program is shopped to represent very large numbers. The interface for this group of classes will be similar, but instead of operations with Operation numbers, they will be with strings (specifically in the vector long long int). The class hierarchy will look like this: parent class `CDataSize` and legacy classes: `CIntegerBig` and `CFloatBig`.
