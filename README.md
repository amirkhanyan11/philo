# Philosophers 🧑‍💻🍽️

Welcome to my implementation of the classic Philosophers Problem! This project delves into the fundamentals of concurrency and synchronization, two vital concepts in multi-threaded programming. Inspired by the work of the brilliant minds that first tackled this challenge, the Philosophers Problem explores the delicate balance of resource management in a dining scenario.

## 🌟 The Challenge

Imagine five philosophers seated around a table, each thinking and occasionally eating spaghetti 🍝. The catch? Each philosopher needs two chopsticks to eat. With only five chopsticks on the table, the philosophers must learn to share without getting into a deadlock 🕳️.

This project simulates that scenario using multi-threading and inter-process communication, where each philosopher is a thread. The goal is to manage these threads efficiently while preventing issues like deadlocks, race conditions, and starvation.

## 🧠 The Roots & History

The Philosophers Problem has deep roots in the study of computer science and is often used as an example to teach synchronization, mutual exclusion, and the dangers of race conditions. It has stood the test of time as a perfect representation of how threads can interact in an operating system.

Through this project, I had the opportunity to explore one of the most challenging and fundamental problems in modern computing. It also gave me hands-on experience with topics such as mutexes, condition variables, and thread management.

## 🚀 What I Learned

This project was a journey full of learning, debugging, and discovery. Here are a few key takeaways:

- **Concurrency Concepts**: I learned how to use pthread (POSIX threads) to handle multiple processes running simultaneously, managing their execution without interference.
  
- **Mutexes and Semaphores**: I gained a deep understanding of locking mechanisms such as mutexes, ensuring that only one philosopher can pick up a chopstick at a time to avoid race conditions.
  
- **Algorithm Optimization**: Through careful consideration, I implemented solutions to avoid deadlocks and starvation by introducing different strategies like timeouts and ordered resource acquisition.
  
- **Memory Management**: Handling dynamic memory allocation for multiple philosophers and ensuring no memory leaks were essential parts of the project.

## 🛠️ How It Works

1. **Philosophers as Threads**: Each philosopher is represented by a thread, which alternates between thinking and eating. They pick up two chopsticks (mutexes) to eat and then put them down once they're done. The challenge is to make sure no philosopher gets stuck waiting forever for chopsticks.
  
2. **Synchronization with Mutexes**: I used mutexes to lock the chopsticks, ensuring mutual exclusion and that no two philosophers could pick up the same chopstick at the same time.
  
3. **Avoiding Deadlocks**: One of the most important parts of this project was preventing deadlocks, where all philosophers are waiting for chopsticks indefinitely. I implemented a strategy to avoid this by introducing timeouts and forcing philosophers to relinquish chopsticks if they couldn’t pick them up in time.
  
4. **Time Tracking**: Philosophers have to eat within certain time constraints. The project tracks how long each philosopher spends eating and thinking, ensuring a fair distribution of time.

## ⚙️ Running the Project

To run the simulation, simply clone the repo and compile the source code using Makefile. Here's how you can get started:

1. Clone the repository:
   ```bash
   git clone https://github.com/amirkhanyan11/philo.git
   
