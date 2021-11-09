/**
\file
\bref Файл методов класса netbios_packet.
*/

#include "netbios_packet.h"
#include "smb_packet.h"

using namespace std;

/**
\bref Коструктор.
\details Инициализация посредством вызова конструктора базового класса. 
\param[in] Буфер, где находится пакет.
\param[in] Смещение пакета в буфере.
*/
netbios_packet::netbios_packet(packet::buff_t &buffer, packet::pos_t position)
    : packet::packet(buffer, position) { 
}


/**
\bref Метод print_fields. 
\details Выводит данные полей пакета на консоль.    
*/
void netbios_packet::print_fields() const {

    if (pos + packet_header_size < (*pbuff).size()) {
        printf(" source name: %s\n", decode_name(src_name_pos).c_str());
        printf(" destination name: %s\n", decode_name(dst_name_pos).c_str()); 
    }    
}

/**
\bref Метод get_next_level. 
\details Возвращает пакет следюущего уровня. 
\return Указатель на пакет следующего уровня.
*/
shared_ptr<packet> netbios_packet::get_next_level(){

    auto srv_comp_pos = pos + server_component_pos;
    if (srv_comp_pos + server_component_size < (*pbuff).size()) {

       if (next == nullptr && 
           memcmp((*pbuff).data() + srv_comp_pos, smb, server_component_size) == 0) {
           next = make_shared<smb_packet>(*pbuff, pos + packet_header_size);
       }
       return next;
   }
    return nullptr;
}

/**
\bref Метод push_char. 
\details . 
\return  .
*/
void netbios_packet::push_char(string &str, uint8_t first, uint8_t second) const {

    str.push_back(static_cast<char>(((first - 'A')*16) | (second - 'A')));
}

/**
\bref Метод push_code. 
\details . 
\return  .
*/
void netbios_packet::push_code(string &str, uint8_t first, uint8_t second) const {

    str.push_back('<');
    str.push_back(static_cast<char>(first  - 'A' + 0x30));
    str.push_back(static_cast<char>(second <= 'J' ? second - 'A' + 0x30 : second - 'A' + 0x57));
    str.push_back('>');
}

/**
\bref Метод decode_name. 
\details . 
\return  .
*/
string netbios_packet::decode_name(packet::pos_t position) const {

    string str = "";
    auto idx = pos + position + 1;
    auto i = idx;
    for (; i < idx + netbios_name_size - 2;) {
        auto first  = (*pbuff)[i ++];
        auto second = (*pbuff)[i ++];
        if (first != 'C' || second != 'A') {            
            (first >= 'C') ? push_char(str, first, second) : push_code(str, first, second);
        }
    }
    auto first  = (*pbuff)[i];
    auto second = (*pbuff)[++ i];
    (first > 'C'|| (first == 'C' && second != 'A')) ? push_char(str, first, second) : push_code(str, first, second);

    return str;
}


