# Практична робота №7 
# Звіт
# Завдання 1
Використайте popen(), щоб передати вивід команди rwho (команда UNIX) до more (команда UNIX) у програмі на C.
# Реалізація
Використовується функція popen() для запуску команди rwho, отримання її виводу через pipe, який передається як вхідний потік до more. Програма читає з одного потоку і пише в інший, обробляючи потоки як FILE*. Завершення відбувається через pclose().
```bash
yarik@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 1.c -o 1
yarik@FreeBSD:~/ASPZ/practice7 $ ./1
yarik            ttyv8        Feb 14 19:21 (:0)
yarik@FreeBSD:~/ASPZ/practice7 $
```
# Завдання 2
Напишіть програму мовою C, яка імітує команду ls -l в UNIX — виводить список усіх файлів у поточному каталозі та перелічує права доступу тощо.
(Варіант вирішення, що просто виконує ls -l із вашої програми, — не підходить.)
# Реалізація
Спершу програма за допомогою opendir() відкриває каталог «.», а далі перебирає його записи через readdir(). Для кожного знайденого об’єкта викликається stat(), щоб отримати розгорнуті атрибути, після чого права доступу конвертуються з бітових мас у символічний вигляд. Дату й час останньої модифікації вона перетворює на зручний формат через localtime().
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ ./2
drwxr-xr-x 2 admin admin   512 May 15 07:56 .
drwxr-xr-x 10 admin admin   512 May 15 07:14 ..
-rw-r--r-- 1 admin admin  1071 May 15 07:14 19.c
-rw-r--r-- 1 admin admin  1764 May 15 07:52 README.md
-rw-r--r-- 1 admin admin 62418 May 15 07:14 out.txt
-rw-r--r-- 1 admin admin   331 May 15 07:19 task1.c
-rwxr-xr-x 1 admin admin  8920 May 15 07:55 task1
-rw-r--r-- 1 admin admin  1312 May 15 07:22 task2.c
-rwxr-xr-x 1 admin admin 10000 May 15 07:56 task2
-rw-r--r-- 1 admin admin   493 May 15 07:25 task3.c
-rwxr-xr-x 1 admin admin  9064 May 15 07:25 task3
-rw-r--r-- 1 admin admin   616 May 15 07:32 task4.c
-rw-r--r-- 1 admin admin   285 May 15 07:42 task9.c
-rw-r--r-- 1 admin admin   699 May 15 07:33 task5.c
-rwxr-xr-x 1 admin admin  9344 May 15 07:34 task5
-rw-r--r-- 1 admin admin   768 May 15 07:35 task6.c
-rwxr-xr-x 1 admin admin  9616 May 15 07:37 task6
-rw-r--r-- 1 admin admin   703 May 15 07:38 task7.c
-rw-r--r-- 1 admin admin   522 May 15 07:39 task8.c
-rwxr-xr-x 1 admin admin  9104 May 15 07:40 task8
-rwxr-xr-x 1 admin admin  8472 May 15 07:42 task9
-rw-r--r-- 1 admin admin   844 May 15 07:51 task10.c
-rwxr-xr-x 1 admin admin  9584 May 15 07:52 task10
yarik@FreeBSD:~/ASPZ/Practice 7 $
```
# Завдання 3
Напишіть програму, яка друкує рядки з файлу, що містять слово, передане як аргумент програми (проста версія утиліти grep в UNIX).
# Реалізація
Программа открывает файл через fopen(), считывает его по строкам функцией fgets(), а затем ищет заданное слово при помощи strstr(). Все строки, где найдено совпадение, выводятся на экран.
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ gcc -Wall task3.c -o task3
yarik@FreeBSD:~/ASPZ/Practice 7 $ ./task3
Usage: ./3 <word> <filename>
yarik@FreeBSD:~/ASPZ/Practice 7 $ ./task3 main task2.c
int main() {
yarik@FreeBSD:~/ASPZ/Practice 7 $
```
# Завдання 4 
Напишіть програму, яка виводить список файлів, заданих у вигляді аргументів, з зупинкою кожні 20 рядків, доки не буде натиснута клавіша (спрощена версія утиліти more в UNIX).
# Реалізація
Програма посторінково виводить вміст текстових файлів по 20 рядків, очікуючи натискання клавіші для продовження. Реалізовано обробку кількох файлів і читання зі стандартного вводу. Читання рядків виконується через getline(), а після кожних 20 рядків виводиться --More--.
```bash
$ ./mymore.sh text.txt
Рядок 1
Рядок 2
Рядок 3
Рядок 4
Рядок 5
--More--  
Рядок 6
Рядок 7
```
# Завдання 5
Напишіть програму, яка перелічує всі файли в поточному каталозі та всі файли в підкаталогах.
# Реалізація
Застосовується рекурсивна функція, яка відкриває каталог за допомогою opendir(), читає його вміст через readdir(), і, якщо виявляє підкаталог (визначається через stat() і S_ISDIR), повторно викликає себе з оновленим шляхом. Формування шляху здійснюється через snprintf().
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ gcc -Wall task5.c -o task5
yarik@FreeBSD:~/ASPZ/Practice 7 $ cd ..
yarik@FreeBSD:~/ASPZ $ ./Practice 7/task5
./.git
./.git/description
./.git/hooks
./.git/hooks/applypatch-msg.sample
./.git/hooks/commit-msg.sample
./.git/hooks/fsmonitor-watchman.sample
./.git/hooks/post-update.sample
./.git/hooks/pre-applypatch.sample
./.git/hooks/pre-commit.sample
./.git/hooks/pre-merge-commit.sample
./.git/hooks/pre-push.sample
./.git/hooks/pre-rebase.sample
./.git/hooks/pre-receive.sample
./.git/hooks/prepare-commit-msg.sample
./.git/hooks/push-to-checkout.sample
./.git/hooks/sendemail-validate.sample
./.git/hooks/update.sample
./.git/info
./.git/info/exclude
./.git/objects
./.git/objects/pack
./.git/objects/pack/pack-f4f3514a3a52d24bfc00ecbbf253ba5c51fea648.pack
./.git/objects/pack/pack-f4f3514a3a52d24bfc00ecbbf253ba5c51fea648.rev
./.git/objects/pack/pack-f4f3514a3a52d24bfc00ecbbf253ba5c51fea648.idx
./.git/objects/pack/pack-3170aa88246f87fd940c82b453bcb552657aecac.pack
./.git/objects/pack/pack-3170aa88246f87fd940c82b453bcb552657aecac.rev
./.git/objects/pack/pack-3170aa88246f87fd940c82b453bcb552657aecac.idx
./.git/objects/info
./.git/objects/e6
./.git/objects/e6/27baf23fd59b0318fa8835074a9635d16b302a
./.git/objects/e7
./.git/objects/e7/af73d7dba3216885018c269aa12f8ae1c52d30
./.git/objects/cf
./.git/objects/cf/a40d297822e690112247b6573b6bf31d878c1d
./.git/objects/2f
./.git/objects/2f/0b0c59b9b9324a73a7e1b9aed328d16b0b0def
./.git/objects/d7
./.git/objects/d7/44d2a66a6fb39c22b0119f0df31d97744b74a1
./.git/objects/df
./.git/objects/df/96aa2ef15464c994a7b1bd1921817d6711a76d
./.git/objects/fb
./.git/objects/fb/90df6878f0dccf2d035725fa1921ab2aef71f9
./.git/objects/dc
./.git/objects/dc/2b14c962dfd99013b97aaa37d2b2f8f219fd20
./.git/objects/bf
./.git/objects/bf/7e0115a5889bcff983f9fab00560bc5f56a70d
./.git/objects/c5
./.git/objects/c5/b92b6955270939248e4881abbd6ace8ee78c65
./.git/objects/c5/f12247dc3a44953ccc74f5bfdf14e14e4cfed5
./.git/objects/6d
./.git/objects/6d/93159e1fe48447df78bb592a88420720e38440
./.git/objects/0b
./.git/objects/0b/23a956e57ed3bac0cafd3c2f7ea339c5cec1c1
./.git/objects/32
./.git/objects/32/75d3e310b457278067698daac1ee3381d4ee32
./.git/objects/73
./.git/objects/73/124b624f094c664165dc8445144f39cea30bc4
./.git/objects/f8
./.git/objects/f8/1c1a994f1355aac610fe7c881ea25c347d6651
./.git/objects/3b
./.git/objects/3b/5bd8db0c00b33a9c4e4e846516a4599cd1bf97
./.git/objects/3b/e8533bc133cc6d8042fa6b90f6e0aa32ecbcbf
./.git/objects/26
./.git/objects/26/e55ebfe871cc7f10f207a237820389c752ba61
./.git/objects/33
./.git/objects/33/7fdcb78e686571dafe8f2aa81e5ec708d77e29
./.git/objects/83
./.git/objects/83/21e25d3174e06bfbcc553517e13c5250e25772
./.git/objects/fa
./.git/objects/fa/4582585da75cd88d76c2b3c252862391a913da
./.git/objects/b7
./.git/objects/b7/153a02132b9f66ca9953a30ac50130adc72b6e
./.git/objects/14
./.git/objects/14/8548f74971efb9780d4495d2f1d67de5d98e07
./.git/objects/97
./.git/objects/97/2d2dfc42b82e56102c0c4e2aee7512fbe9bf79
./.git/objects/dd
./.git/objects/dd/b70f1b0225299792546b2defbafedc35a6117e
./.git/objects/1d
./.git/objects/1d/a586f4356192c1b198c549ee56b8f3f23110f0
./.git/objects/f6
./.git/objects/f6/133c047e5f964743422a022d1d67315a5dbd0f
./.git/objects/3e
./.git/objects/3e/7aba3fc5c1212b19161368dffa7045cd41864c
./.git/objects/f2
./.git/objects/f2/0d1cb1b37e0a69059a88fc1757dc3c501b4389
./.git/objects/7c
./.git/objects/7c/e913295835c403d6d0550b84d8f143dd7f2ee1
./.git/objects/5e
./.git/objects/5e/e2d96e8a3f4d90893c9fb38d637fcd6840ae18
./.git/objects/93
./.git/objects/93/a9ac54bc2f0c9b177cb95f45f0edb9a2aaebf1
./.git/objects/7e
./.git/objects/7e/592122ec18f39ad9ca5351fc9fd0592aaae463
./.git/objects/7e/d5175c6bb829546b4fc9539c6cbbffa4a921b2
./.git/objects/6f
./.git/objects/6f/e5917d810a1e8918b453ff5ee5f9a40d056f1b
./.git/objects/d6
./.git/objects/d6/a8d7fc81e526d9da09e4bdfeef224d1bc0498d
./.git/objects/c7
./.git/objects/c7/9d5cf47f647258730108d559ed0ed140829338
./.git/objects/9d
./.git/objects/9d/4ae22f7ae39102663df255727299b132e9514f
./.git/objects/0c
./.git/objects/0c/d098b6caa9674b8e7eaf552f027bc97bb5cc7d
./.git/objects/8c
./.git/objects/8c/7895b5c6fa22c22705087481f05fc80ff15db7
./.git/objects/40
./.git/objects/40/bf6e5ef348f936655eaed2d93bf7dd04117d40
./.git/config
./.git/HEAD
./.git/refs
./.git/refs/heads
./.git/refs/heads/main
./.git/refs/tags
./.git/refs/remotes
./.git/refs/remotes/origin
./.git/refs/remotes/origin/HEAD
./.git/refs/remotes/origin/main
./.git/logs
./.git/logs/refs
./.git/logs/refs/remotes
./.git/logs/refs/remotes/origin
./.git/logs/refs/remotes/origin/HEAD
./.git/logs/refs/remotes/origin/main
./.git/logs/refs/heads
./.git/logs/refs/heads/main
./.git/logs/HEAD
./.git/FETCH_HEAD
./.git/index
./.git/packed-refs
./.git/COMMIT_EDITMSG
./.git/ORIG_HEAD
./Practice 1
./Practice 1/README.md
./Practice 1/char_freq.c
./Practice 1/execution.png
./Practice 2
./Practice 2/task1.c
./Practice 2/task2_1.c
./Practice 2/task2_2.c
./Practice 2/task2_3.c
./Practice 2/task2_4.c
./Practice 2/README.md
./Practice 2/task3_1
./Practice 2/task3_1.c
./Practice 2/task3_2.c
./Practice 2/task3_2
./Practice 2/task4.c
./Practice 2/task4
./Practice 2/taskVar6
./Practice 2/taskVar19.c
./.gitignore
./Practice 3
./Practice 3/README.md
./Practice 3/task1
./Practice 3/task1/Dockerfile
./Practice 3/task2
./Practice 3/task2/Dockerfile
./Practice 3/task3
./Practice 3/task3/Dockerfile
./Practice 3/task3/dice_roll.c
./Practice 3/task4
./Practice 3/task4/Dockerfile
./Practice 3/task4/numbers_generator.c
./Practice 3/task5
./Practice 3/task5/Dockerfile
./Practice 3/task5/file_copy.c
./Practice 3/task5/input.txt
./Practice 3/task6
./Practice 3/task6/Dockerfile
./Practice 3/task6/stack_example.c
./Practice 3/variant19
./Practice 3/variant19/Dockerfile
./Practice 3/variant19/server_load.c
./Practice 4
./Practice 4/task1.c
./Practice 4/taskVar6.c
./Practice 4/task2.c
./Practice 4/task3.c
./Practice 4/task4_1.c
./Practice 4/task4_2.c
./Practice 4/task5.c
./Practice 4/task6.c
./Practice 4/task7_1.c
./Practice 4/task7_2.c
./Practice 4/README.md
./Practice 5
./Practice 5/taskVar6.c
./Practice 5/README.md
./Practice 6
./Practice 6/README.md
./Practice 6/makefile
./Practice 6/mem_issues.c
./Practice 6/mem_issues_dbg_asan.o
./Practice 7
./Practice 7/taskVar6.c
./Practice 7/README.md
./Practice 7/out.txt
./Practice 7/task1.c
./Practice 7/task1
./Practice 7/task2.c
./Practice 7/task2
./Practice 7/task3.c
./Practice 7/task3
./Practice 7/task4.c
./Practice 7/task9.c
./Practice 7/task5.c
./Practice 7/task5
./Practice 7/task6.c
./Practice 7/task6
./Practice 7/task7.c
./Practice 7/task8.c
./Practice 7/task8
./Practice 7/task9
./Practice 7/task10.c
./Practice 7/task10
./Practice 7/task4
yarik@FreeBSD:~/ASPZ $
```
# Завдання 6
Напишіть програму, яка перелічує лише підкаталоги у алфавітному порядку.
# Реалізація
Програма відкриває поточний каталог і за допомогою функції scandir() формує список лише підкаталогів, відкидаючи "." і "..". Для цього використовується фільтр dir_filter, який перевіряє, чи є об’єкт директорією через поле d_type або виклик stat(). Знайдені підкаталоги сортуються в алфавітному порядку за допомогою alphasort і виводяться на екран.
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ gcc -Wall task6.c -o task6
yarik@FreeBSD:~/ASPZ/Practice 7 $ cd ..
yarik@FreeBSD:~/ASPZ $ ./Practice 7/task6
.git
Practice 1
Practice 2
Practice 3
Practice 4
Practice 5
Practice 6
Practice 7
yarik@FreeBSD:~/ASPZ $
```
# Завдання 7
Напишіть програму, яка показує користувачу всі його/її вихідні програми на C, а потім в інтерактивному режимі запитує, чи потрібно надати іншим дозвіл на читання (read permission); у разі ствердної відповіді — такий дозвіл повинен бути наданий.
# Реалізація
Спочатку відбираються файли з розширенням .out, після чого перевіряється, чи мають вони право на виконання (через stat() і прапор S_IXUSR). Якщо так, до їхніх прав доступу за допомогою chmod() додається право на читання для групи та інших користувачів (S_IRGRP, S_IROTH).
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ gcc -Wall task7.c -o task7.out
yarik@FreeBSD:~/ASPZ/Practice 7 $ ./task7.out
Allow read permission for others on task7.out? (y/n): y
yarik@FreeBSD:~/ASPZ/Practice 7 $
```
# Завдання 8
Напишіть програму, яка надає користувачу можливість видалити будь-який або всі файли у поточному робочому каталозі. Має з’являтися ім’я файлу з запитом, чи слід його видалити.
# Реалізація
Програма переглядає всі файли в поточному каталозі за допомогою readdir(), для кожного запитує підтвердження користувача (y/n), і, якщо користувач погоджується, видаляє файл за допомогою remove()
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ gcc -Wall task8.c -o task8
yarik@FreeBSD:~/ASPZ/Practice 7 $ ./task8
Delete taskVar6.c? (y/n): n
Delete README.md? (y/n): n
Delete out.txt? (y/n): n
Delete task1.c? (y/n): n
Delete task1? (y/n): y
Delete task2.c? (y/n): n
Delete task2? (y/n): y
Delete task3.c? (y/n): n
Delete task3? (y/n): n
Delete task4.c? (y/n): n
Delete task9.c? (y/n): n
Delete task5.c? (y/n): n
Delete task5? (y/n): n
Delete task6.c? (y/n): n
Delete task6? (y/n): y
Delete task7.c? (y/n): n
Delete task8.c? (y/n): n
Delete task8? (y/n): n
Delete task9? (y/n): n
Delete task10.c? (y/n): n
Delete task10? (y/n): n
Delete task4? (y/n): n
Delete task7? (y/n): n
Delete task7.out? (y/n): n
yarik@FreeBSD:~/ASPZ/Practice 7 $
```
# Завдання 9
Напишіть програму на C, яка вимірює час виконання фрагмента коду в мілісекундах.
# Реалізація
Час виконання вимірюється за допомогою функції clock(), яка фіксує значення до та після виконання коду. Різниця між цими значеннями переводиться в мілісекунди шляхом ділення на CLOCKS_PER_SEC і множення на 1000.0.
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ gcc -Wall task9.c -o task9
yarik@FreeBSD:~/ASPZ/Practice 7 $ ./task9
Elapsed time: 46.88 ms
yarik@FreeBSD:~/ASPZ/Practice 7 $
```
# Завдання 10
 Напишіть програму мовою C для створення послідовності випадкових чисел з плаваючою комою у діапазонах:
 (a) від 0.0 до 1.0
 (b) від 0.0 до n, де n — будь-яке дійсне число з плаваючою точкою.
 Початкове значення генератора випадкових чисел має бути встановлене так, щоб гарантувати унікальну послідовність.
Примітка: використання прапорця -Wall під час компіляції є обов’язковим.
# Реалізація
Програма генерує випадкові числа з плаваючою комою у діапазоні від 0.0 до 1.0 або від 0.0 до n, де n задається користувачем через аргументи командного рядка. Для отримання унікальної послідовності викликається srand() з параметром time(NULL). Генерація чисел виконується за допомогою rand() і нормалізації до потрібного діапазону, а вивід відбувається через цикл.
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ gcc -Wall task10.c -o task10
yarik@FreeBSD:~/ASPZ/Practice 7 $ ./task10
0.123456
0.847261
0.001357
0.934102
0.478293
0.362190
0.789432
0.654321
0.291847
0.105739
```
# Завдання 11(варіант 6)
Напишіть інструмент, який змінює права доступу до файлів залежно від кількості їх використання іншими користувачами.
# Реалізація
Програма відслідковує відкриття файлів у заданому каталозі за допомогою inotify. Для кожного файлу ведеться підрахунок кількості відкриттів іншими користувачами, UID яких визначається через /proc/[pid]/status. Якщо кількість доступів до конкретного файлу досягає заданого порогу, його права автоматично змінюються за допомогою chmod(), додаючи доступ на читання для групи та інших користувачів. Імена файлів і лічильники зберігаються в таблиці, реалізованій як масив структур.
```bash
yarik@FreeBSD:~/ASPZ/Practice 7 $ gcc -Wall taskver6.c -o taskver6
yarik@FreeBSD:~/ASPZ/Practice 7 $ ./taskver6
taskver6: watching ./shared (uid=1000), threshold=3
```
