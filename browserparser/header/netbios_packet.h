/**
\file
\bref Заголовочный файл с описанием класса пакета протокола NetBIOS.
*/

#ifndef NETBIOS_H 
#define NETBIOS_H

#include <string>
#include <cstring>
#include <cstdio>
#include "packet.h"

/**
\bref Класс netbios_packet.
\details Класс пакета протокола NetBIOS, наследник класса packet.
         Объявлен final, так как пока наследование от него не планируется.
*/
class netbios_packet final : public packet {
public:
    static const uint8_t  direct_group_datagram = 0x11;
    /**
    \bref Коструктор.
    \details Инициализация посредством вызова конструктора базового класса. 
    \param[in] Буфер, где находится пакет.
    \param[in] Смещение пакета в буфере.
    */
    netbios_packet(packet::buff_t &, packet::pos_t );
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
    virtual ~netbios_packet() noexcept = default;
private:
    struct header {
        uint8_t  msg_type;
        uint8_t  flags;
        uint16_t datagram_id;
        uint8_t  src_ip[4];                      
        uint16_t src_port;        
        uint16_t datagram_len;
        uint16_t packet_offset;
        uint8_t  src_name[34];              
        uint8_t  dst_name[34];
    };
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    netbios_packet(const netbios_packet &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    netbios_packet(netbios_packet &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    netbios_packet& operator=(const netbios_packet &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    netbios_packet& operator=(netbios_packet &&) = delete;
    /**
    \bref Метод push_char. 
    \details . 
    \return  .
    */
    void push_char(std::string &, uint8_t, uint8_t) const;
    /**
    \bref Метод push_code. 
    \details . 
    \return  .
    */
    void push_code(std::string &, uint8_t, uint8_t) const;
    /**
    \bref Метод decode_name. 
    \details . 
    \return  .
    */
    std::string decode_name(packet::pos_t) const;
    /**
    \bref Размер заголовка пакета.
    \details .
    */
    static const packet::pos_t packet_header_size    = sizeof(header);//82;
    static const packet::pos_t src_name_pos          = offsetof(header, src_name);//14;
    static const packet::pos_t dst_name_pos          = offsetof(header, dst_name);//48;
    static const packet::pos_t netbios_name_size     = 32;
    static const packet::pos_t server_component_pos  = packet_header_size;
    static const packet::pos_t server_component_size = 4;
    static constexpr const uint8_t smb[4] = { 0xFF, 'S', 'M', 'B' };

};

#endif  /* NETBIOS_H */

