/**
\file
\bref Файл методов класса ethernetII_packet.
*/

#include "ethernetII_packet.h"
#include "ipv4_packet.h"

using namespace std;

/**
\bref Коструктор.
\details Инициализация посредством вызова конструктора базового класса. 
\param[in] Буфер, где находится пакет.
\param[in] Смещение пакета в буфере.
*/
ethernetII_packet::ethernetII_packet(packet::buff_t &buffer, packet::pos_t position) 
    : packet::packet(buffer, position) {
}


/**
\bref Метод print_fields. 
\details Выводит данные полей пакета на консоль.    
*/
void ethernetII_packet::print_fields() const {

    if (pos + packet_header_size < (*pbuff).size()) {

        auto idx = pos + src_mac_pos;
        auto lim = idx + mac_size;
        printf(" src_mac:  %02hhx", (*pbuff)[idx]);
        for (packet::pos_t i = idx + 1; i < lim; ++ i) {
            printf(":%02hhx", (*pbuff)[i]);
        }

        idx = pos + dst_mac_pos;
        lim = idx + mac_size;
        printf("\n dst_mac:  %02hhx", (*pbuff)[idx]);
        for (packet::pos_t i = idx + 1; i < lim; ++ i) {
            printf(":%02hhx", (*pbuff)[i]);
        }
        printf("\n");  
    }    
}

/**
\bref Метод get_next_level. 
\details Возвращает пакет следюущего уровня. 
\return Указатель на пакет следующего уровня.
*/
shared_ptr<packet> ethernetII_packet::get_next_level(){

    if (pos + packet_header_size < (*pbuff).size()) {

        if (next == nullptr) {
            unalligned_ptr<uint16_t> ptype((*pbuff).data() + pos + type_pos);
            if (ntohs(*ptype) == ipv4) {
                next = make_shared<ipv4_packet>(*pbuff, pos + packet_header_size);
            }
        }
        return next;
    }
    return nullptr;
}
