/**
\file
\bref Файл методов класса ipv4_packet.
*/

#include "ipv4_packet.h"
#include "udp_packet.h"

using namespace std;

/**
\bref Коструктор.
\details Инициализация посредством вызова конструктора базового класса. 
\param[in] Буфер, где находится пакет.
\param[in] Смещение пакета в буфере.
*/
ipv4_packet::ipv4_packet(packet::buff_t &buffer, packet::pos_t position) 
    : packet::packet(buffer, position) { 

    if (pos + header_size_pos < (*pbuff).size()) {
        packet_header_size = ((*pbuff)[pos + header_size_pos] & 0xf) * 4;        /* размер заголовка */
    }
}


/**
\bref Метод print_fields. 
\details Выводит данные полей пакета на консоль.    
*/
void ipv4_packet::print_fields() const {

    if (pos + packet_header_size < (*pbuff).size()) {

        auto idx = pos + src_addr_pos;
        auto lim = idx + addr_size;
        printf(" src_ip: %hhu", (*pbuff)[idx]);
        for (packet::pos_t i = idx + 1; i < lim; ++ i) {
            printf(".%hhu", (*pbuff)[i]);
        }

        idx = pos + dst_addr_pos;
        lim = idx + addr_size;
        printf("\n dst_ip: %hhu", (*pbuff)[idx]);
        for (packet::pos_t i = idx + 1; i < lim; ++ i) {
            printf(".%hhu", (*pbuff)[i]);
        }
        printf("\n");  
    }    
}

/**
\bref Метод get_next_level. 
\details Возвращает пакет следюущего уровня. 
\return Указатель на пакет следующего уровня.
*/
shared_ptr<packet> ipv4_packet::get_next_level(){

    if (pos + packet_header_size < (*pbuff).size()) {

        if (next == nullptr && (*pbuff)[pos + protocol_pos] == udp) {
             next = make_shared<udp_packet>(*pbuff, pos + packet_header_size);
        }
        return next;
    }
    return nullptr;
}
