# Project for the class : CS5300 (Database Systems)

GROUP :<br></br>
Yannis Fu<br></br>
Everett Yan<br></br>

# DISCLAIMER
Only 1NF - BCNF are currently working at the time of submission

# BEFORE RUNNING
The exampleInputTable.csv file should be where the csv should be input

The functioanlDependencies.txt file should be where all the functional dependencies should be input, it should be in the format of LHS->RHS NO spaces, if there are multivalued then they should be seperated by ',' with NO spaces 
I.E. "Course,Professor->CourseStart,CourseEnd,classRoom"

The Keys input is inside of the console, there should be NO spaces between each key, the only delimiter should be ',' 
I.E. "StudentID,Course"

# HOW TO RUN
```bash
g++ -std=c++17 main.cpp -o main
./main
```
