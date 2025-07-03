#!/bin/bash

# Pulizia iniziale
rm -f input.txt output.txt expected.txt

echo "=== Test pipex (MANDATORY) ==="

# Test 1: semplice cat | wc -w
echo "ciao mondo" > input.txt
./pipex input.txt "cat" "wc -w" output.txt
< input.txt cat | wc -w > expected.txt
diff output.txt expected.txt && echo "Test 1 PASSED" || echo "Test 1 FAILED"

# Test 2: grep + wc
echo -e "ciao\nhello\nciao" > input.txt
./pipex input.txt "grep ciao" "wc -l" output.txt
< input.txt grep ciao | wc -l > expected.txt
diff output.txt expected.txt && echo "Test 2 PASSED" || echo "Test 2 FAILED"

# Test 3: comando inesistente
./pipex input.txt "noncomando" "wc" output.txt 2> /dev/null
if [ $? -ne 0 ]; then echo "Test 3 PASSED (errore atteso)"; else echo "Test 3 FAILED"; fi

rm -f input.txt output.txt expected.txt


