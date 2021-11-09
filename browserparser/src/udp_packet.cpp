/**
\file
\bref Файл методов класса udp_packet.
*/

#include "udp_packet.h"
#include "netbios_packet.h"

using namespace std;

/**
\bref Коструктор.
\details Инициализация посредством вызова конструктора базового класса. 
\param[in] Буфер, где находится пакет.
\param[in] Смещение пакета в буфере.
*/
udp_packet::udp_packet(packet::buff_t &buffer, packet::pos_t position) 
    : packet::packet(buffer, position) { 
}


/**
\bref Метод print_fields. 
\details Выводит данные полей пакета на консоль.    
*/
void udp_packet::print_fields() const {

    if (pos + packet_header_size < (*pbuff).size()) {

        unalligned_ptr<uint16_t> psrc_port((*pbuff).data() + pos + src_port_pos);
        printf(" src_port: %hu\n", ntohs(*psrc_port));

        unalligned_ptr<uint16_t> pdst_port((*pbuff).data() + pos + dst_port_pos);
        printf(" dst_port: %hu\n", ntohs(*pdst_port));  
    }    
}

/**
\bref Метод get_next_level. 
\details Возвращает пакет следюущего уровня. 
\return Указатель на пакет следующего уровня.
*/
shared_ptr<packet> udp_packet::get_next_level(){

    if (pos + msg_type_pos < (*pbuff).size()) {

        if (next == nullptr) {
            unalligned_ptr<uint16_t> ppacket_size((*pbuff).data() + pos + packet_size_pos);
            if (ntohs(*ppacket_size) > packet_header_size &&
                (*pbuff)[pos + msg_type_pos] == netbios_packet::direct_group_datagram) {
                next = make_shared<netbios_packet>(*pbuff, pos + packet_header_size);
            }
        }
        return next;
    }
    return nullptr;
}
