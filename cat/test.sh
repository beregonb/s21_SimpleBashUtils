#!/bin/bash

echo "РАБОТА С ОДНИМ ФАЙЛОМ"
for file in test_case/test_1_cat.txt test_case/test_2_cat.txt test_case/test_3_cat.txt test_case/test_4_cat.txt 

do
    
    echo "Результат работы утилиты cat:"
    cat $file > result1.txt
    ./s21_cat $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -n:"
    cat -n $file > result1.txt
    ./s21_cat -n $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -b:"
    cat -b $file > result1.txt
    ./s21_cat -b $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -e:"
    cat -e $file > result1.txt
    ./s21_cat -e $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -s:"
    cat -s $file > result1.txt
    ./s21_cat -s $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -t:"
    cat -t $file > result1.txt
    ./s21_cat -t $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -v:"
    cat -v $file > result1.txt
    ./s21_cat -v $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

done

echo "РАБОТА С НЕСКОЛЬКИМИ ФАЙЛАМИ"
for file in test_case/test_1_cat.txt test_case/test_2_cat.txt test_case/test_3_cat.txt test_case/test_4_cat.txt 
do
    
    echo "Результат работы утилиты cat:"
    cat $file $file > result1.txt
    ./s21_cat $file $file> result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -n:"
    cat -n $file $file > result1.txt
    ./s21_cat -n $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -b:"
    cat -b $file $file > result1.txt
    ./s21_cat -b $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -e:"
    cat -e $file $file> result1.txt
    ./s21_cat -e $file $file> result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -s:"
    cat -s $file $file> result1.txt
    ./s21_cat -s $file $file> result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -t:"
    cat -t $file $file> result1.txt
    ./s21_cat -t $file $file> result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    echo "Результат работы утилиты cat -v:"
    cat -v $file $file> result1.txt
    ./s21_cat -v $file $file> result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

done