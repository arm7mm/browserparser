/**
\file
\bref Файл точки входа программы (функции main()).
*/

#include <string>
#include <stdexcept>
#include <cstdio>
#include "parser.h"

using namespace std;

/**
\bref Точка входа программы. 
\details Создаёт объект класса Parser и вызывает его методы.
*/

int main(int argc, char ** argv) {

    try {
        if (argc == 2) {                                /* Проверка количества аргументов */
            string input;
            input.append(argv[1]);                      /* Аргумент - имя pcap файла */         
            parser prsr(input);                         /* Создание элемента класса Parser */
            prsr.parse();                               /* Разбор содержимого файла */
        } else {
            printf("Usage:   browserparser [name pcap file]\n");
        }
    } catch (exception & e) {
        perror(e.what());
        return 1;
    }
    return 0;
}
