#!/bin/bash
echo "=== Тест независимой работы ==="

echo "1. Тестируем JSON:"
rm -f test.json
./dbms --file test.json --query 'MCREATE arr 2'
./dbms --file test.json --query 'MPUSH_END arr hello'
./dbms --file test.json --query 'PRINT arr'
echo "Размер JSON: $(wc -c < test.json) байт"

echo -e "\n2. Тестируем бинарный:"
rm -f test.bin
./dbms --binary test.bin --query 'MCREATE arr 2'
./dbms --binary test.bin --query 'MPUSH_END arr hello'
./dbms --binary test.bin --query 'PRINT arr'
echo "Размер BIN: $(wc -c < test.bin) байт"

echo -e "\n3. Проверяем независимость:"
echo "Содержимое test.json:"
head -c 200 test.json
echo -e "\n\nСодержимое test.bin (hex):"
hexdump -C test.bin | head -5

echo "=== Готово ==="
