# 42_pipex

## Test cases

### Mandatory part
```
./pipex infile.txt "ls -l" "wc -l" outfile.txt
./pipex infile.txt "cat Makefile" "wc -m" outfile.txt
./pipex infile.txt cat hostname outfile.txt
./pipex infile.txt wrong_command "cat Makefile" outfile.txt
```

***

input content:
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
./pipex infile.txt "grep Now" "head -2" outfile.txt
./pipex infile.txt "grep Now" "wc -w" outfile.txt
```

***

Delete input file:
```
./pipex infile.txt "cat Makefile" "wc -l" outfile.txt 
```

### Bonus part
```
./pipex_bonus infile.txt "ls -l" "wc -l" "ls" outfile.txt
./pipex_bonus infile.txt "cat Makefile" "head -n 5" "wc -m" outfile.txt
./pipex Makefile "head -10" "grep #" "sed s/#/holla/g" outfile.txt
```

***

Deletes "!" from the input, filters out lines that contain "Werld", replaces Hello with Salut:
```
./pipex infile.txt "tr -d !" "grep -v Werld" "sed s/Hello/Salut/g" outfile.txt
```

***

Deletes "!" from the input, filters out lines that contain "Werld", replaces Hello with Salut, selects only the rows containing Salut, counts number of rows:
```
./pipex infile.txt "tr -d !" "grep -v Werld" "sed s/Hello/Salut/g" "grep Salut" "wc -l" outfile.txt 
```

***

Lists the content of src directory, selects only the .c files, counts number of rows (files):
```
./pipex infile.txt "ls -l src/" "grep .c" "wc -l" outfile.txt 
```

### Valgrind
```
valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all 
```
