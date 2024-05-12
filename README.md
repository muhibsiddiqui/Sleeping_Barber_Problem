# Sleeping Barber Problem

## Introduction
The Sleeping Barber problem is a classic synchronization challenge in computer science, often used to illustrate concepts of concurrency and resource management. The scenario involves a barber who serves customers in a barbershop with a limited number of waiting chairs. Customers arrive at random intervals and either wait for a chair or leave if all chairs are occupied. The goal is to coordinate the behavior of the barber and customers efficiently to ensure fair service and optimal resource utilization.

## Implementation
This repository provides an implementation of the Sleeping Barber problem in C programming language. It utilizes POSIX threads (pthreads) for multi-threading and synchronization. The implementation includes separate threads for the barber and customers, along with synchronization mechanisms such as mutexes and semaphores to manage shared resources and coordinate interactions between threads.

## Features
- Configurable parameters such as the number of waiting chairs and customers.
- Realistic simulation of barber and customer behavior, including random arrival times.
- Statistics tracking, such as total time served by the barber.

## Objectives
- Implement a solution to the Sleeping Barber problem in C.
- Utilize POSIX threads for multi-threading and synchronization.
- Simulate realistic behavior of the barber and customers in the barbershop scenario.
- Track statistics to analyze performance and efficiency of the solution.

## Limitations
- Synchronization overhead may impact scalability and performance under high concurrency.
- Deadlocks and race conditions are possible in complex interaction scenarios.
- The fixed number of waiting chairs may not be suitable for all use cases.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Copyright
copyright © Muhammad Muhib Siddiqui 2024
