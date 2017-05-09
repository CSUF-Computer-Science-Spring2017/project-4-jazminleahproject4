CSUF CPSC 131, Spring 2017
Project 4

Group members:
Jazmin Esqueda jazminesqueda@csu.fullerton.edu
Leah Smith leahsmith@csu.fullerton.edu

Our fourth and final project takes a list of related friends (similar to a Facebook setup) and recommends new connections from mutual friends. We used an adjacency matrix to show if two users are friends. For our friend recommendation function we created a queue containing all friends of a person. By iterating through the queue of friends we populated a second queue of possible friends from the existing friends. That queue is then used to populate a map with those same names to ensure there are no duplicates. We added error checking that searches for and eliminates the starting person and pre-esisting friends from the map of new friend reccomendations. 
