#!/bin/bash

# Очищаем файл перед тестом
echo "{}" > test_data.json

echo "=== Тестирование массивов (M) ==="
./dbms --file test_data.json --query 'MCREATE arr1 5'
./dbms --file test_data.json --query 'MPUSH_END arr1 10'
./dbms --file test_data.json --query 'MPUSH_BY_INDEX arr1 0 20'
./dbms --file test_data.json --query 'MGET arr1'
./dbms --file test_data.json --query 'PRINT arr1'

echo -e "\n=== Тестирование односвязных списков (F) ==="
./dbms --file test_data.json --query 'FPUSH_HEAD flist value1'
./dbms --file test_data.json --query 'FPUSH_TAIL flist value2'
./dbms --file test_data.json --query 'FGET flist'
./dbms --file test_data.json --query 'PRINT flist'

echo -e "\n=== Тестирование двусвязных списков (L) ==="
./dbms --file test_data.json --query 'LPUSH_HEAD dlist data1'
./dbms --file test_data.json --query 'LPUSH_TAIL dlist data2'
./dbms --file test_data.json --query 'LGET dlist'
./dbms --file test_data.json --query 'PRINT dlist'

echo -e "\n=== Тестирование стеков (S) ==="
./dbms --file test_data.json --query 'SPUSH mystack item1'
./dbms --file test_data.json --query 'SPUSH mystack item2'
./dbms --file test_data.json --query 'SGET mystack'
./dbms --file test_data.json --query 'PRINT mystack'

echo -e "\n=== Тестирование очередей (Q) ==="
./dbms --file test_data.json --query 'QPUSH myqueue task1'
./dbms --file test_data.json --query 'QPUSH myqueue task2'
./dbms --file test_data.json --query 'QGET myqueue'
./dbms --file test_data.json --query 'PRINT myqueue'

echo -e "\n=== Тестирование деревьев (T) ==="
./dbms --file test_data.json --query 'TINSERT mytree 50'
./dbms --file test_data.json --query 'TINSERT mytree 30'
./dbms --file test_data.json --query 'TINSERT mytree 70'
./dbms --file test_data.json --query 'TGET mytree'
./dbms --file test_data.json --query 'PRINT mytree'

echo -e "\n=== Тестирование хэш-таблиц (H) ==="
./dbms --file test_data.json --query 'HINSERT htable key1 100'
./dbms --file test_data.json --query 'HINSERT htable key2 200'
./dbms --file test_data.json --query 'HGET htable'
./dbms --file test_data.json --query 'HSEARCH htable key1'
./dbms --file test_data.json --query 'HSEARCH htable key3'
./dbms --file test_data.json --query 'PRINT htable'

echo -e "\n=== Тестирование сохранения/загрузки ==="
echo "Создаем копию файла"
cp test_data.json test_data_copy.json
echo "Загружаем из копии и проверяем"
./dbms --file test_data_copy.json --query 'PRINT arr1'
./dbms --file test_data_copy.json --query 'PRINT flist'
./dbms --file test_data_copy.json --query 'PRINT htable'

echo -e "\n=== Тест завершен ==="
