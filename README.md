<p align="center">
    <img src="https://user-images.githubusercontent.com/102881479/220914152-9fea3130-8edc-4f80-b936-be3c8c5e80e1.png">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/OS-Linux-blue" alt="OS">
    <img src="https://img.shields.io/badge/Language-C%20%7C%20C%2B%2B-blue.svg" alt="Language">
    <img src="https://img.shields.io/badge/Grade-125%2F100-brightgreen.svg" alt="Grade">
    <img src="https://img.shields.io/badge/Status-Completed-brightgreen.svg" alt="Status">
</p>

## Introduction

The ninth project of 42's curriculum asks students to solve the famous Dijkstra's synchronization problem called *The Dining Philosophers Problem*. This is a introduction to multithreads, multiprocesses, mutexes and semaphores. 

## How to compile and run the project

#### 1) Copy this repository to your local workstation

```html
git clone git@github.com:ygor-sena/42cursus-philosophers.git
```

#### 2) Choose the mandatory or bonus folder to compile the project

To compile the mandatory project, execute the following command in your terminal:

```html
cd philo/ && make
```

Otherwise, if you want to compile the bonus version, execute:

```html
cd philo_bonus/ && make
```

#### 3) Run the program

Both the mandatory and bonus program take at least 5 arguments. The last one is optional. Each of them stands for:

| #1 | #2 |  #3 | #4 | #5 | #6 (optional) |
|:----|:----|:----|:----|:----|:----|
|`./philo` or `./philo_bonus`| 5 | 800 | 200 | 200 | 5 |
| `path_to_binary` |  `number_of_philosophers` | `time_to_die` | `time_to_eat` | `time_to_sleep` | `number_of_times_each_must_eat` |

So, to start a dinning simulation where there are 5 philosophers that must eat 7 times each and the time to die, to eat and to sleep is 800, 200 and 200 respectively, we should execute the following command:

```html
./philo 5 800 200 200 7
```

#### 4) How to check for memory leaks and data race conditions

Run the program with the valgrind's flags below to check for memory leaks:

```
valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes
```

Also, run the program with valgrind's tools *DRD (Data Race Detector)* and *Helgrind* separately to search for data race conditions and typical syncronization problems such as deadlock:

```
valgrind --tool=drd 
```

```
valgrind --tool=helgrind 
```

## Known issues

There are cases where a philosopher can die because the scheduler priorized some threads/processes instead of giving all of them the same priority. To avoid this, it is necessary to implement a function that always will make the hungriest philosopher dinner first. It is possible to implement this in the mandatory project according the rules of the subject. For the bonus project, we would need shared memory to share information between the child processes, but its use is not allowed by the subject.

## References

- General references:
  - [Concorrência e Paralelismo (Parte 1) | Entendendo Back-End para Iniciantes ](https://www.youtube.com/watch?v=cx1ULv4wYxM) by [Fábio Akita](https://www.youtube.com/@Akitando).
  - [Ansel Sermersheim: “Multithreading is the answer. What is the question? (part 1 of 2)](https://www.youtube.com/watch?v=GNw3RXr-VJk) by CppCon 2017.
  - [Ansel Sermersheim: “Multithreading is the answer. What is the question? (part 2 of 2)](https://www.youtube.com/watch?v=sDLQWivf1-I) by CppCon 2017.
  - [Unix Threads in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) by [CodeVault](https://www.youtube.com/@CodeVault).

- About the Dining Philosophers Problem:
  - TANENBAUM, Andrew; BOS, Herbert. Modern Operating System. 4th edition. 2014.
  - [The Dining Philosophers Problem With Ron Swanson](https://www.adit.io/posts/2013-05-11-The-Dining-Philosophers-Problem-With-Ron-Swanson.html) by [Aditya Bhargava](https://www.adit.io/index.html).

- About threads and mutexes:
  - [MYERS, Ethan. An Application of Pthreads and Mutexes](https://files.kipr.org/gcer/2009/proceedings/Myers_ApplicationPthreads.pdf) by Cedar Brook Academy.
  - [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/) by [Lawrence Livermore National Laboratory](https://www.llnl.gov/).
  - [Introduction to Parallel Computing Tutorial](https://hpc.llnl.gov/documentation/tutorials/introduction-parallel-computing-tutorial##Overview) by [Lawrence Livermore National Laboratory](https://www.llnl.gov/).
  - [Race Condition vs. Data Race](https://blog.regehr.org/archives/490) by [Professor John Regehr](https://blog.regehr.org/).

- About Helgrind and DRD (Data Race Detector):
  - [Helgrind: a thread error detector](https://valgrind.org/docs/manual/hg-manual.html) by [Valgrind](https://valgrind.org/).
  - [DRD: a thread error detector](https://valgrind.org/docs/manual/drd-manual.html) by [Valgrind](https://valgrind.org/).
  
- Interesting contents by fellow 42's students:
  - [Web visualizer for Philosophers project](https://github.com/nafuka11/philosophers-visualizer) by [nafuka](https://github.com/nafuka11).
  - [Visual summary of the Philosophers project](https://miro.com/app/board/o9J_l0AjIkc=/) made with Miro.
  - [Acelera: Philosophers](https://rodsmade.notion.site/Acelera-Philosophers-a82a52edabe24ea4a382393fae6c4531) by [rodsmade](https://github.com/rodsmade).
  - [Summary of the concepts of Philosophers project](https://www.notion.so/Philosophers-2b872948598e4f0cba91c66d8b5ba821) made with Notion.

## Awknowledgements

I want to thank Marcelo Magalhães, also a student at [42SP](https://www.42sp.org.br/) for his support throughout the project when I needed. Please, check out his interesting projects at GitHub [here](https://github.com/magalhaesm).
