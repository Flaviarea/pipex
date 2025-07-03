#!/bin/bash

# Pulizia iniziale
rm -f input.txt output.txt expected.txt

echo "=== Test pipex (BONUS) ==="

# Verifica che pipex_bonus sia compilato
if [ ! -x ./pipex_bonus ]; then
    echo "Compilo pipex_bonus..."
    make bonus || { echo "Compilazione fallita"; exit 1; }
fi

# Test 1: cat | grep hello | wc -l
echo -e "hello\nciao\nhello" > input.txt
./pipex_bonus input.txt "cat" "grep hello" "wc -l" output.txt
< input.txt cat | grep hello | wc -l > expected.txt
diff output.txt expected.txt && echo "Test 1 PASSED" || echo "Test 1 FAILED"

# Test 2: tr + sort + uniq
echo -e "a\na\nb\nb\nc" > input.txt
./pipex_bonus input.txt "tr a-z A-Z" "sort" "uniq" output.txt
< input.txt tr a-z A-Z | sort | uniq > expected.txt
diff output.txt expected.txt && echo "Test 2 PASSED" || echo "Test 2 FAILED"

# Test 3: here_doc (solo se implementato)
./pipex_bonus here_doc LIMITER "echo prima" "echo seconda" output.txt
{ echo "prima"; echo "seconda"; } > expected.txt
diff output.txt expected.txt && echo "Test 3 PASSED (here_doc)" || echo "Test 3 FAILED (here_doc)"

rm -f input.txt output.txt expected.txt

