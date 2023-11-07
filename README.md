# 42_pipex

## Test cases

### Mandatory part
```
./pipex_bonus infile.txt "ls -l" "wc -l" outfile.txt
```

### Bonus part
```
./pipex_bonus infile.txt "ls -l" "wc -l" "ls" outfile.txt
```

### Valgrind
```
valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all 
```
