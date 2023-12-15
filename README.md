# 42_pipex

## Test cases

### Mandatory part
```
./pipex infile.txt "ls -l" "wc -l" outfile.txt
./pipex infile.txt "cat Makefile" "wc -m" outfile.txt
```

### Bonus part
```
./pipex_bonus infile.txt "ls -l" "wc -l" "ls" outfile.txt
./pipex_bonus infile.txt "cat Makefile" "head -n 5" "wc -m" outfile.txt
```

### Valgrind
```
valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all 
```
