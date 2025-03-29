# Практична робота №3
# Звіт по завданням
# Завдання 1
Використання команди --privileged ulimit

Звичайний запуск(без --privileged)
```bash
$ ulimit -n
1048576
$ ulimit -aS | grep "open files"
open files                          (-n) 1048576
$ ulimit -aH | grep "open files"
open files                          (-n) 1048576
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
open files                          (-n) 3000
$ ulimit -aH | grep "open files"
open files                          (-n) 3000
$ ulimit -n 3001
/bin/bash: line 1: ulimit: open files: cannot modify limit: Operation not permitted
$ ulimit -n 2000
$ ulimit -n
2000
$ ulimit -aS | grep "open files"
open files                          (-n) 2000
$ ulimit -aH | grep "open files"
open files                          (-n) 2000
$ ulimit -n 3000
/bin/bash: line 1: ulimit: open files: cannot modify limit: Operation not permitted
```
Запуск з --privileged
```bash
$ ulimit -n
1048576
$ ulimit -aS | grep "open files"
open files                          (-n) 1048576
$ ulimit -aH | grep "open files"
open files                          (-n) 1048576
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
open files                          (-n) 3000
$ ulimit -aH | grep "open files"
open files                          (-n) 3000
$ ulimit -n 3001
$ ulimit -n 2000
$ ulimit -n
2000
$ ulimit -aS | grep "open files"
open files                          (-n) 2000
$ ulimit -aH | grep "open files"
open files                          (-n) 2000
$ ulimit -n 3000
```

# Завдання 2
Проексперементовано з утилітою perf
```bash
$ perf --version
perf version 6.1.129
$ perf stat echo Hello World
Hello World!

 Performance counter stats for 'echo Hello World!':

              0.41 msec task-clock:u                     #    0.447 CPUs utilized
                 0      context-switches:u               #    0.000 /sec
                 0      cpu-migrations:u                 #    0.000 /sec
                53      page-faults:u                    #  129.743 K/sec
            480590      cycles:u                         #    1.176 GHz
             59949      stalled-cycles-frontend:u        #   12.47% frontend cycles idle   
             38599      stalled-cycles-backend:u         #    8.03% backend cycles idle    
            113567      instructions:u                   #    0.24  insn per cycle
                                                  #    0.53  stalled cycles per insn
             23891      branches:u                       #   58.485 M/sec
              2596      branch-misses:u                  #   10.87% of all branches

       0.000913754 seconds time elapsed

       0.000199000 seconds user
       0.000000000 seconds sys
```

# Завдання 3
Симуляція кидання шестигранного кубика з обмеженням на розмір файлу
Задано ліміт на розмір файлу за допомогою системного виклику setrlimit(RLIMIT_FSIZE, &lim) у коді перед записом у файл. При перевищенні ліміту запис припиняється, або за сигналом SIGXFSZ, або через перевірку поточного розміру файлу.
```
$ ./dice_roll
Current file size limit: soft = 1048576, hard = 1048576
Allocated file: dice_rolls.txt
Throw 1: 2
Throw 2: 5
Throw 3: 1
...
File size exceeded maximum limit. Stopping write operation.
```

# Завдання 4
Програма, що імітує лотерею
Встановлено ліміт та обробленно ситуації перевищення
```
$ ./lottery_simulation
Lottery Numbers (7 from 49):
42 17 3 28 6 45 13 
Bonus Numbers (6 from 36):
14 2 9 33 12 7
```
Додамо навантаження у вигляді бескінечного циклу перед printf
```
$ ./lottery_simulation
Lottery Numbers (7 from 49):
11 4 33 2 27 45 16 
CPU time limit exceeded. Stopping the lottery simulation.
```

# Завдання 5
Написано програму для копіювання одного іменованого файлу в інший
Встановлено ліміт програмно setrlimit та обробленно ситуації перевищення ліміту
```
$ ./file_copy input.txt source.txt
Reached file size limit
Contents of source.txt:
9
8
7
6
5
4
3
2
1
```

# Завдання 6
Написано програму, що демонструє використання обмеження - max stack segment size
```
$ prlimit --stack=100000:100000 ./stack_limit_demo
Stack size limit: 100000 bytes
Recursion depth: 1
Recursion depth: 2
Recursion depth: 3
Recursion depth: 4
Recursion depth: 5
Recursion depth: 6
Recursion depth: 7
Recursion depth: 8
Recursion depth: 9
```

# Завдання варіанту 6 
Дослідити вплив ulimit -l на фіксовану пам’ять 
Звичайний запуск 
```
mlock failed: Cannot allocate memory
```
Запуск з  ulimit -l 10240
```
Successfully locked 10 MB of memory.
mlock failed on second memory allocation: Cannot allocate memory
```

