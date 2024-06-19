# Ice-Cream-Factory

## Description:

The Ice Cream Factory Problem is a simulation of an operating system problem implemented in C++. This project models a production line in an ice cream factory, where synchronization and inter-process communication are critical. The simulation uses threads to represent different stages of the production process, such as mixing, freezing, and packaging, ensuring that each stage operates efficiently and without conflict.

Key features include:

    Thread Synchronization: Utilizes mutexes and condition variables to manage synchronization between different production stages.
    Process Simulation: Each stage of the production line is simulated with threads, demonstrating inter-process communication and coordination.
    Concurrency Handling: The project addresses common concurrency issues such as deadlocks and race conditions, providing practical solutions.
    Performance Monitoring: Includes tools for monitoring the performance and efficiency of the production line, highlighting areas for optimization.

This project is a practical demonstration of operating system principles, particularly in the areas of concurrency, synchronization, and process management.

## To run the project:

1. Install SFML 2.6.1 + MinGW32 (add to path)
2. Place the SFML 'include' and 'lib' folders in a folder named 'src'
3. Place all the .dll files found in the bin folder into a folder named 'run'
4. Run the command 'make' from the command line (cmd, terminal, powershell)

## Group Members

Faizan Ali Abdulali (22i-2496)
Hamail Ur Rehman (22k-4443)
Jaswant Lal (22k-4473)
