/**
\file
\bref Заголовочный файл с описанием класса пакета протокола User Datagram Protocol.
*/

#ifndef UDP_H 
#define UDP_H

#include <cstdio>
#include "packet.h"

/**
\bref Класс udp_packet.
\details Класс пакета протокола User Datagram Protocol, наследник класса packet.
         Объявлен final, так как пока наследование от него не планируется.
*/
class udp_packet final : public packet {
public:
    /**
    \bref Коструктор.
    \details Инициализация посредством вызова конструктора базового класса. 
    \param[in] Буфер, где находится пакет.
    \param[in] Смещение пакета в буфере.
    */
    udp_packet(packet::buff_t &, packet::pos_t );
    /**
    \bref Метод print_fields. 
    \details Выводит данные полей пакета на консоль.    
    */
    virtual void print_fields() const override;
    /**
    \bref Метод get_next_level. 
    \details Возвращает пакет следюущего уровня. 
    \return  Указатель на пакет следующего уровня.
    */
    virtual std::shared_ptr<packet> get_next_level() override;
    /**
    \bref Деструктор.
    \details .
    */
    virtual ~udp_packet() noexcept = default;
private:
    struct header {
        uint16_t src_port;
        uint16_t dst_port;
        uint16_t length;
        uint16_t checksum;
    };
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    udp_packet(const udp_packet &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    udp_packet(udp_packet &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    udp_packet& operator=(const udp_packet &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    udp_packet& operator=(udp_packet &&) = delete;
    /**
    \bref Размер заголовка пакета.
    \details .
    */
    static const packet::pos_t packet_header_size = sizeof(header);//8;
    static const packet::pos_t src_port_pos       = offsetof(header, src_port);//0;
    static const packet::pos_t dst_port_pos       = offsetof(header, dst_port);//2;
    static const packet::pos_t packet_size_pos    = offsetof(header, length);//4;
    static const packet::pos_t msg_type_pos       = packet_header_size;
};

#endif  /* UDP_H */

