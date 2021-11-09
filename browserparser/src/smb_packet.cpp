/**
\file
\bref Файл методов класса smb_packet.
*/

#include <cstdio>
#include "smb_packet.h"
#include "browser_packet.h"

using namespace std;

/**
\bref Коструктор.
\details Инициализация посредством вызова конструктора базового класса. 
\param[in] Буфер, где находится пакет.
\param[in] Смещение пакета в буфере.
*/
smb_packet::smb_packet(packet::buff_t &buffer, packet::pos_t position) 
    : packet::packet(buffer, position) { 

    auto offset = setup_count_pos + mailslot_name_offset;
    if (pos + offset < (*pbuff).size() &&
       (*pbuff)[pos + smb_command_pos] == smb_com_transaction) { 

        unalligned_ptr<uint16_t> data_cnt((*pbuff).data() + pos + data_count_pos); 
        data_count = *data_cnt;

        unalligned_ptr<uint16_t> data_ofst((*pbuff).data() + pos + data_offset_pos); 
        data_offset = *data_ofst; 

        mailslot_name_pos = offset + (*pbuff)[pos + setup_count_pos]*sizeof(uint16_t);
    }
}


/**
\bref Метод print_fields. 
\details Выводит данные полей пакета на консоль.    
*/
void smb_packet::print_fields() const {

}

/**
\bref Метод get_next_level. 
\details Возвращает пакет следующего уровня. 
\return Указатель на пакет следующего уровня.
*/
shared_ptr<packet> smb_packet::get_next_level() {

    auto name_pos = pos + mailslot_name_pos;
    auto data_pos = pos + data_offset;
    if (mailslot_name_pos > 0 &&
        name_pos + sizeof(mailslot_name) < (*pbuff).size() &&
        data_pos + data_count <= (*pbuff).size()) {

        if (next == nullptr &&
            memcmp((*pbuff).data() + name_pos, mailslot_name, sizeof(mailslot_name)) == 0) {
            next = make_shared<browser_packet>(*pbuff, data_pos, data_count);
        }
        return next;
   }
    return nullptr;
}


