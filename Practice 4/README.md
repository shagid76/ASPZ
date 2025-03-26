# Практична робота №4 
# Звіт
# Завдання 1
 Максимальний обсяг пам’яті, який можна виділити за один виклик malloc(), обмежений максимальним значенням типу size_t, оскільки саме цей тип використовується як параметр функції.  У 64-бітній системі size_t займає 8 байтів, тобто теоретично можна передати до malloc() значення до 2^64 - 1 байт. Проте на практиці архітектура x86_64 використовує лише 48 біт віртуальної адресації, тому реальна межа — 256 ТБ. 
# Вивід програми
``` bash
yarik@tv-32:~/ASPZ/Practice 4 $./task1
Searching for maxi mum allocatable memory block...
Maxi mum allocatable block with malloc(): 70368744177664 bytes ( 65536.00 GB)
```

# Завдання 2
 Якщо malloc() передати від’ємне значення, воно буде перетворене в дуже велике беззнакове число, і malloc() поверне NULL. У випадку переповнення при множенні знакових чисел результат стане від’ємним, що також призведе до помилкового запиту пам’яті й повернення NULL.
# Вивід програми
``` bash
num = 1410065408
mal loc succeeded:
num ( overf lowed) = - 4
malloc failed after overflow
allocated 1410065408 bytes
```

# Завдання 3
 Виклик malloc(0) є допустимим, але його поведінка залежить від реалізації бібліотеки: функція може повернути NULL або допустимий, але некорисний вказівник, який можна передати у free() без помилок.
# Вивід програми
``` bash
Calling malloc(0) ...
mal loc(0) returned non- NULL pointer: 0x1e9a6e408008
Pointer freed successfully
```

# Завдання 4
 Проблема цього коду полягає в тому, що після виклику free(ptr) вказівник ptr все ще містить адресу звільненої пам’яті, і на наступній ітерації цикл може спробувати її використати, що призведе до невизначеної поведінки. Щоб уникнути цього, слід або звільнити пам’ять після завершення циклу, або встановлювати ptr = NULL наприкінці кожної ітерації.
# Вивід програм
``` bash
ptr: hello
ptr: hello
ptr: hello
```

# Завдання 5
 Якщо realloc() не зможе виділити пам’ять, вона поверне NULL, а початковий вказівник залишиться дійсним і не буде звільнений. Тому завжди потрібно зберігати результат realloc() у тимчасову змінну, щоб уникнути втрати даних.

# Завдання 6
Якщо realloc() викликається з NULL, вона працює як malloc() і виділяє новий блок пам’яті. Якщо розмір дорівнює 0, то поведінка залежить від реалізації: або повертається NULL, або виділяється мінімальний блок, який можна безпечно передати в free().
``` bash
Calling realloc ( NULL, 100) ...
realloc ( NULL, 100) succeeded, ptr = 0x352774413000
Calling realloc(ptr, o) ...
realloc(ptr, o) returned non- NULL pointer: 0x352774408008 (still must free)
```

# Завдання 7
# Вивід програми (з reallocarray())
``` bash
yarik@tv-32:~/ASPZ/Practice4 $ gcc task7.1.c -o task7.1
yarik@tv-32:~/ASPZ/Practice4 $ ./task7.1
ID: 42, Name: original

```
# Вивід ltrace
``` bash
yarik@tv-32:~/ASPZ/Practice4 $ ltrace ./task7.2
calloc(1000, 36)                            = 0x55ae946e8000
strcpy(0x55ae946e8000, "original")          = 0x55ae946e8000
reallocarray(0x55ae946e8000, 500, 36)       = 0x55ae946e9000
puts("ID: 42, Name: original")             = ID: 42, Name: original
free(0x55ae946e9000)                        = <void>
+++ exited (status 0) +++
```

# Завдання 8(варіант 6)
Написано код, який досліджує поведінку malloc під час високого навантаження
``` bash
Allocated 1 GB
Allocated 2 GB
Allocated 3 GB
Allocated 4 GB
Allocated 5 GB
Allocated 6 GB
Allocated 7 GB
Allocated 8 GB
Allocated 9 GB
Allocated 10 GB
Allocated 11 GB
Allocated 12 GB
Allocated 13 GB
Allocated 14 GB
Killed
```
