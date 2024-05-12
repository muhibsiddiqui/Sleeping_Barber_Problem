

##Introduction:
-The Sleeping Barber problem is a classic synchronization challenge in computer science, often used to illustrate concepts of concurrency and resource management. The scenario involves a barber who serves customers in a barbershop with a limited number of waiting chairs. Customers arrive at random intervals and either wait for a chair or leave if all chairs are occupied. The goal is to coordinate the behavior of the barber and customers efficiently to ensure fair service and optimal resource utilization.

##Implementation:
-This repository provides an implementation of the Sleeping Barber problem in C programming language. It utilizes POSIX threads (pthreads) for multi-threading and synchronization. The implementation includes separate threads for the barber and customers, along with synchronization mechanisms such as mutexes and semaphores to manage shared resources and coordinate interactions between threads.

## Features
- Configurable number of waiting chairs and customers.
- Realistic simulation of barber and customer behavior.
- Statistics tracking such as total time served by the barber.

## Limitations
- Synchronization overhead may impact scalability.
- Deadlocks and race conditions possible under complex interactions.
- Fixed number of waiting chairs may not suit all scenarios.

## Contribution
Contributions are welcome! Feel free to submit issues, feature requests, or pull requests.

## License
This project is licensed under the [MIT License](LICENSE).



