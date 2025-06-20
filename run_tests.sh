#!/bin/bash

# Test semplice per pipex

# Creo un file di input con contenuto di prova
echo "ciao mondo" > input.txt

# Eseguo il programma pipex con comandi di esempio
../pipex_bonus input.txt "cat" "wc -w" output.txt

# Eseguo il comando equivalente della shell
< input.txt cat | wc -w > expected.txt

# Confronto i risultati
if diff output.txt expected.txt > /dev/null; then
    echo "Test PASSED!"
else
    echo "Test FAILED!"
    echo "Differenze:"
    diff output.txt expected.txt
fi

# Pulisco i file temporanei
rm input.txt output.txt expected.txt

