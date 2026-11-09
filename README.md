Smart Campus Navigation and Facility Analytics System
1. Project Purpose
The campus navigation and facility analytics system is an application that allows the user to search for facilities, explore campus buildings by its connection and find the shortest path by determining each building distance from the user location. Additionally, browse department hierarchy and search and explore campus facilities. 
2. Project Directory
Project2/
|-- include/      	campusGraph.h
|-- src/          	campusGraph.cpp, main.cpp
|-- data/         buildingNames.txt, connections.txt, facilitiesName.txt, departementsNames.txt 
|-- testdata/	buildingNamesTest.txt, connectionsTest.txt, facilitiesNameTest.txt, departementsNamesTest.txt     	
|-- README.txt
|-- CONTRIBUTIONS.txt
|-- design_document.txt
|-- test_results.txt
|-- .gitignore 
3. Data Structures
The Project display 3 different data structures, 
Hash Table:
Graph:
-Building are vertices, connections are edges, graph is undirected and unweighed. -Graph is represented with an adjacency list.
-Each newly added building would be inserted at the end to keep the BFS order correct, so we can find the shortest path.
-BFS uses a queue and a vector to note what has been visited, building is marked viseite when it been added to queue, shortest path is found using BFS
Tree:
4. How to Run Program
First Compile Files
G++ -I include srt/main.cpp src/campusGraph.cpp -o program
And execute ./program
5.GitHub
6. Additional Documentation
Group Contribution
 Group Contribution Report [https://docs.google.com/document/d/1gUp10woL3H9cnVbvGaLIpKB_KVPvBbfMH6PUzlwcuv8/edit?usp=sharing](https://docs.google.com/document/d/1qFEsmWzy6DayJnHQ4x-RyZ4CrF57N_DXrhIReCeMmeo/edit?usp=sharing)
Design Doc
Design Document https://docs.google.com/document/d/1_fVsl_vI7iaezZd-ou467czktSGIk_77zL9BcfWTdm0/edit?usp=sharing
Test Result
Test Result https://docs.google.com/document/d/1bgVE_p_rhF3W2Q0Ch_Xh2vBprhpvlCMx-fCa0DBOYI4/edit?usp=sharing


