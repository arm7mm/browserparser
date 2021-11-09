/**
\file
\bref Заголовочный файл с описанием класса разбора pcap файла.
*/

#ifndef PARSER_H 
#define PARSER_H

#include <fstream>
#include <stdexcept>
#include <cstdio>
#include <string>
#include <vector>
#include "pcap.h"
#include "packet.h"

/**
\bref Класс parser разбора pcap файла.
      Объявлен final, так как пока наследование от него не планируется.
*/
class parser final {
public:
    /**
    \bref Коструктор.
    \details Читает заголовок pcap файла и проверяет его. 
    \param[in] Имя pcap файла.
    */
    explicit parser(std::string &);
    /**
    \bref Метод parse. 
    \details Проводит разбор пакетов в pcap файле и выводит данные на консоль.    
    */
    void parse();
    /**
    \bref Деструктор.
    \details .
    */
    ~parser() noexcept {};
private:
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    parser(const parser &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    parser(parser &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    parser& operator=(const parser &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    parser& operator=(parser &&) = delete;
    /**
    \bref Метод parse_frame_data. 
    \details Проводит разбор фрейма по составляющим его пакетам.   
    \param   Размер фрейма.   
    */
    void parse_frame_data(packet::pos_t frame_size);
    /**
    \bref . 
    \details .   
    */
    pcap::timestype_t timestype;
    /**
    \bref Класс потокового чтения из файла. 
    \details .   
    */
    std::ifstream in;
};

#endif  /* PARSER_H */

