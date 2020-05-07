# RTOS Task Scheduler Simulator

This program is a scheduler simulation for Real Time Operating System (RTOS). It takes input as periodic, aperiodic and sporadic tasks and simulate using C Programming language.

## 1. File structure layout

    .
    ├── periodic_scheduler.c                   # Periodic Scheduler
    ├── periodic_scheduler.h  
    ├── sched_dynamicarray.c                   # Dynamic Array Implementation
    ├── sched_dynamicarray.h
    ├── sched_queue.c                          # Custom Queue to handle QNode, which consist of task_id and deadline
    ├── sched_queue.h
    ├── scheduler_driver.c                     # Main driver program which executes schedulers
    ├── scheduler_driver.h
    ├── sched_util.c                           # Contains utility functions
    ├── sched_util.h
    ├── util/stringencoders/modp_numtoa.c      # Used library for number to string conversion
    ├── input_periodic.txt                     # Sample Input file 
    └── README.md                              

## 2. How to Compile

Compilation can be done by running make command 

```bash
make
```
This will generate `scheduler.out` file

## 3. How to use

To read a periodic Tasks execute the following command

```bash
./scheduler.out input_periodic.txt
```
This will generate output file `scheduler_output.txt`

To read a aperiodic Tasks execute the following command

```bash
./scheduler.out input_aperiodic.txt
```
This will generate output file `scheduler_output.txt`

## 4. Project Status
Following Tasks has been acoomplished
- [x] Periodic Scheduler (Done, without tasksplit)
- [ ] Aperiodic Scheduler (Incomplete)
- [ ] Sporadic Scheduler (Incomplete)

## 5. Contributers
Contributers in this project
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
   <tr>
      <td align="center"><a href="https://ashishpatel.dev"><img src="https://avatars3.githubusercontent.com/u/652311?v=4" width="100px;" alt=""/><br /><sub><b>Ashish Patel</b></sub></a></td>
   </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://allcontributors.org) specification.
Contributions of any kind are welcome!



License
----

MIT