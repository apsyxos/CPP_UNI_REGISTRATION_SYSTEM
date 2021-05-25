# CPP_UNI_REGISTRATION_SYSTEM
This is a C++ example project to showcase various C++ concepts

This is a program that creates and updates a list of university members, of different types
and adding them to a txt file to be stored. Each member will have at least a name, surname, and id,
and afterward, extra information, depending on the category they belong to (Student, Professor, etc).

The categorization of the types of members was done with the help of classes and took advantage of all
the OOP concepts that C++ includes, like inheritance, abstraction, and encapsulation. Specifically,
the diamond inheritance problem was used in this example, since it is a nice way to demonstrate
possible issues that are seen in C++, like early binding.

For the program, the user follows the console commands, and uses the numerical values given to input
the necessary info. Then, the user is asked to confirm the input and when that happens,
the university member created is added to the text file, as well as added in a vector, 
that can be accessed in the console, where it can show all the members that were added while the program is active.

