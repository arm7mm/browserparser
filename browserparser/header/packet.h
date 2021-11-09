/**
\file
\bref Заголовочный файл с описанием абстрактного класса пакета.
*/

#ifndef PACKET_H 
#define PACKET_H

#include <vector>
#include <cstdint>
#include <memory>
#include <netinet/in.h>
#include "unalligned_ptr.h"

/**
\bref Класс packet.
\details Абстрактный класс.
*/
class packet {
public:

    typedef std::vector<uint8_t> buff_t;
    typedef std::vector<uint8_t>::size_type/*std::size_t*/ pos_t;

    /**
    \bref Коструктор.
    \details Инициализация. 
    \param[in] Буфер, где находится пакет.
    \param[in] Смещение пакета в буфере.
    */
    packet(buff_t &buffer, pos_t position) : pbuff(&buffer), pos (position) { };
    /**
    \bref Метод print_fields. 
    \details Выводит данные полей пакета на консоль.    
    */
    virtual void print_fields() const = 0;
    /**
    \bref Метод getNextLevel. 
    \details Возвращает пакет следюущего уровня. 
    \return При успехе значение success и соответствующее смещение в буфере,
            failure иначе.
    */
    virtual std::shared_ptr<packet> get_next_level() = 0;
    /**
    \bref Деструктор.
    \details .
    */
    virtual ~packet() noexcept = default;
protected:
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    packet(const packet &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    packet(packet &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    packet& operator=(const packet &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    packet& operator=(packet &&) = delete;
    /**
    \bref Указатель на паекет следующего уровня.
    \details .
    */
    std::shared_ptr<packet> next = nullptr;
    /**
    \bref Указатель буфера, где содержится пакет.
    \details .
    */
    buff_t *pbuff = nullptr;
    /**
    \bref Смещение пакета в буфере.
    \details .
    */
    pos_t pos;

};

#endif  /* PACKET_H */

