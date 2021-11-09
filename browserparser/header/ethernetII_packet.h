/**
\file
\bref Заголовочный файл с описанием класса ethernet II пакета.
*/

#ifndef ETHERNET_II_H 
#define ETHERNET_II_H

#include <cstdio>
#include <cstddef>
#include "packet.h"

/**
\bref Класс ethernetII_packet.
\details Класса ethernet II пакета, наследник класса packet.
         Объявлен final, так как пока наследование от него не планируется.
*/
class ethernetII_packet final : public packet {
public:
    /**
    \bref Коструктор.
    \details Инициализация посредством вызова конструктора базового класса. 
    \param[in] Буфер, где находится пакет.
    \param[in] Смещение пакета в буфере.
    */
    ethernetII_packet(packet::buff_t &, packet::pos_t );
    /**
    \bref Метод print_fields. 
    \details Выводит данные полей пакета на консоль.    
    */
    virtual void print_fields() const override;
    /**
    \bref Метод get_next_level. 
    \details Возвращает пакет следующего уровня. 
    \return Указатель на пакет следующего уровня.
    */
    virtual std::shared_ptr<packet> get_next_level() override;
    /**
    \bref Деструктор.
    \details .
    */
    virtual ~ethernetII_packet() noexcept = default;
private:
    struct header {
        uint8_t  dst_mac[6];
        uint8_t  src_mac[6];
        uint16_t type;
    };
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    ethernetII_packet(const ethernetII_packet &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    ethernetII_packet(ethernetII_packet &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    ethernetII_packet& operator=(const ethernetII_packet &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    ethernetII_packet& operator=(ethernetII_packet &&) = delete;
    /**
    \bref Размер заголовка пакета.
    \details .
    */
    static const packet::pos_t packet_header_size = sizeof(header);//14;
    static const packet::pos_t mac_size    = 6;
    static const packet::pos_t dst_mac_pos = offsetof(header, dst_mac);//0;
    static const packet::pos_t src_mac_pos = offsetof(header, src_mac);//6;
    static const packet::pos_t type_pos    = offsetof(header, type);//12;

    static const uint16_t ipv4 = 0x800;
};

#endif  /* ETHERNET_II_H */

