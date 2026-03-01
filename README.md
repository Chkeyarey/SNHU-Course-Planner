# SNHU-Course-Planner
Repository created for Module 8, CS-300
## Project Reflection: ABCU Advising Program
### The Problem
The goal of this project was to develop a software solution for academic advisors at ABCU to manage and display a large curriculum of computer science courses. The system needed to handle data loading from a CSV file, provide a way to search for specific courses and their prerequisites instantly, and generate an alphanumerically sorted list of all available courses to help students plan their schedules.

### My Approach
I approached this problem by first evaluating three core data structures: Vectors, Hash Tables, and Binary Search Trees. I conducted a Big O analysis of each to understand their performance trade-offs. I ultimately chose the Hash Table because of its O(1) average search time, which is critical for a high-traffic advising system where looking up individual course requirements is the most frequent task. Understanding data structures is vital because the choice of structure directly impacts the scalability and speed of the final product.

### Overcoming Roadblocks
One significant roadblock I encountered was a file-loading error where the program failed to read filenames containing spaces (like CS 300 ABCU_Advising_Program_Input.csv). Initially, my code used the *cin >> operator*, which stops at the first space. I overcame this by switching to getline(cin, fileName) and utilizing cin.ignore() to clear the input buffer.

### Expanding My Design Philosophy
Working on this project has fundamentally changed how I design software. I no longer just "jump into the code." I now prioritize the Design and Analysis phase—using pseudocode and Big O analysis to predict how a program will behave before a single line of C++ is written. This ensures that the architecture is efficient by design rather than by accident.

### Maintainability and Readability
This project evolved my coding style toward industry-standard best practices. I focused on making the program maintainable and readable by:

* Using meaningful naming conventions for variables and functions.

* Implementing modular logic, such as separating the Hash Table class from the file-parsing functions.

* Adding robust error handling to catch malformed data or invalid user input.

* Integrating memory management via destructors to prevent memory leaks, ensuring the program is adaptable for long-term use in larger systems.
