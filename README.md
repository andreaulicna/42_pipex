# 42_pipex

## Test cases

### Mandatory part
```
./pipex infile.txt "ls -l" "wc -l" outfile.txt
< input ls -l | wc -l > output
./pipex infile.txt "cat Makefile" "wc -m" outfile.txt
< input cat Makefile | wc -m > output
./pipex infile.txt cat hostname outfile.txt
< input cat | hostname > output
./pipex infile.txt wrong_command "cat Makefile" outfile.txt
< infile.txt wrong_command | cat Makefile > output
./pipex infile.txt cat wrong_command outfile.txt 
< input cat | wrong_command > output
```

***

Input file content:
```
Hello World!
Hello World!
Hello Werld!
Hello World!
Hello World!
Now or never
Now
only Now
Now or tomorrow
```

```
./pipex infile.txt "grep Now" "head -2" outfile.txt
< input grep Now | head -2 > output
./pipex infile.txt "grep Now" "wc -w" outfile.txt
< input grep Now | wc -w > output 
```

***

Non-existent input file:
```
./pipex jou "cat Makefile" "wc -l" outfile.txt 
< jou cat Makefile | wc -l > output
```

***

Change permissions to 000 for input and output file:
```
./pipex infile.txt "grep Now" "wc -w" outfile.txt
< input grep Now | wc -w > output 
./pipex infile.txt "grep Now" "wc -w" outfile.txt
< input grep Now | wc -w > output 
```

***

### Bonus part
```
./pipex_bonus infile.txt "ls -l" "wc -l" "ls" outfile.txt
< input ls -l | wc -l | ls > output
./pipex_bonus infile.txt "cat Makefile" "head -n 5" "wc -m" outfile.txt
< input cat Makefile | head -n 5 | wc -m > output
./pipex_bonus Makefile "head -10" "grep #" "sed s/#/holla/g" outfile.txt
< Makefile head -n 10 | grep '#' | sed s/#/holla/g > output
```

***

Deletes "!" from the input, filters out lines that contain "Werld", replaces Hello with Salut:
```
./pipex_bonus infile.txt "tr -d !" "grep -v Werld" "sed s/Hello/Salut/g" outfile.txt
< infile.txt tr -d ! | grep -v Werld | sed s/Hello/Salut/g > output
```

***

Deletes "!" from the input, filters out lines that contain "Werld", replaces Hello with Salut, selects only the rows containing Salut, counts number of rows:
```
./pipex_bonus infile.txt "tr -d !" "grep -v Werld" "sed s/Hello/Salut/g" "grep Salut" "wc -l" outfile.txt 
```

***

Lists the content of src directory, selects only the .c files, counts number of rows (files):
```
./pipex_bonus infile.txt "ls -l src/" "grep .c" "wc -l" outfile.txt 
```

***

### Valgrind
```
valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all 
```
