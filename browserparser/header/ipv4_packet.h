/**
\file
\bref Заголовочный файл с описанием класса пакета протокола Internet Protocol Version 4.
*/

#ifndef IPV4_H 
#define IPV4_H

#include <cstdio>
#include <cstddef>
#include "packet.h"

/**
\bref Класс ipv4_packet.
\details Класс пакета протокола Internet Protocol Version 4, наследник класса packet.
         Объявлен final, так как пока наследование от него не планируется.
*/
class ipv4_packet final : public packet {
public:
    /**
    \bref Коструктор.
    \details Инициализация посредством вызова конструктора базового класса. 
    \param[in] Буфер, где находится пакет.
    \param[in] Смещение пакета в буфере.
    */
    ipv4_packet(packet::buff_t &, packet::pos_t );
    /**
    \bref Метод print_fields. 
    \details Выводит данные полей пакета на консоль.    
    */
    virtual void print_fields() const override;
    /**
    \bref Метод get_next_level. 
    \details Возвращает пакет следующего уровня. 
    \return  Указатель на пакет следующего уровня.
    */
    virtual std::shared_ptr<packet> get_next_level() override;
    /**
    \bref Деструктор.
    \details .
    */
    virtual ~ipv4_packet() noexcept = default;
private:
    struct header {
        uint8_t  vers_and_ihl;
        uint8_t  type_of_service;
        uint16_t total_length;
        uint16_t id;                      
        uint16_t flags_and_fragment_offset;        
        uint8_t  time_to_live;
        uint8_t  protocol;
        uint16_t checksum;              
        uint8_t  src_addr[4];
        uint8_t  dst_addr[4];
    };
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    ipv4_packet(const ipv4_packet &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    ipv4_packet(ipv4_packet &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    ipv4_packet& operator=(const ipv4_packet &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    ipv4_packet& operator=(ipv4_packet &&) = delete;
    /**
    \bref Размер заголовка пакета.
    \details .
    */
    packet::pos_t packet_header_size = 0;
    static const packet::pos_t addr_size       = sizeof(uint8_t[4]);          //4;
    static const packet::pos_t header_size_pos = offsetof(header, vers_and_ihl);//0;
    static const packet::pos_t protocol_pos    = offsetof(header, protocol);//9;
    static const packet::pos_t src_addr_pos    = offsetof(header, src_addr);//12;
    static const packet::pos_t dst_addr_pos    = offsetof(header, dst_addr);//16;

    static const uint8_t  udp  = 0x11;
};

#endif  /* IPV4_H */

