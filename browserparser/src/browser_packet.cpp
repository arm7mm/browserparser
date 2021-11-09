/**
\file
\bref Файл методов класса browser_packet.
*/

#include <cstdio>
#include "browser_packet.h"

using namespace std;

/**
\bref Коструктор.
\details Инициализация посредством вызова конструктора базового класса. 
\param[in] Буфер, где находится пакет.
\param[in] Смещение пакета в буфере.
*/
browser_packet::browser_packet(packet::buff_t &buffer, packet::pos_t position, packet::pos_t size_packet) 
    : packet::packet(buffer, position), size(size_packet) { 

}

/**
\bref Метод print_host_fields. 
\details Выводит данные полей пакета Host Announcement (0x01) на консоль.    
*/
void browser_packet::print_host_fields() const {

    printf(" command: Host Announcement (0x01)\n");
    printf(" host: %.16s\n", (*pbuff).data() + pos + host_pos);

    printf(" browser protocol major version: %u\n", (*pbuff)[pos + protocol_major_vers_pos]);
    printf(" browser protocol minor version: %u\n", (*pbuff)[pos + protocol_minor_vers_pos]);

    unalligned_ptr<uint16_t> psign((*pbuff).data() + pos + signature_pos);
    printf(" signature: 0x%04x\n", *psign);
}

/**
\bref Метод print_host_fields. 
\details Выводит данные полей пакета Domain/Workgroup Announcement (0x0c) на консоль.    
*/
void browser_packet::print_domain_workgroup_fields() const {

    printf(" command: Domain/Workgroup Announcement (0x0c)\n");
    printf(" domain/workgroup: %.16s\n", (*pbuff).data() + pos + domain_workgroup_pos);

    printf(" master browser server name: ");
    auto i = pos + master_browser_name_pos;
    auto pch = (*pbuff).data() + i;
    for (; i < (*pbuff).size() && *pch; ++ i) {
        printf("%c", *(pch ++) );
    }
    printf("\n");
}

/**
\bref Метод print_fields. 
\details Выводит данные полей пакета на консоль.    
*/
void browser_packet::print_fields() const {

    if (header_size < size &&
        pos + size <= (*pbuff).size()) {

        switch((*pbuff)[pos + command_pos]) {
            case host :
                print_host_fields();
                break;
            case domain_workgroup :
                print_domain_workgroup_fields();
                break;
            default :
                return;
        } 
        printf(" update count: %u\n", (*pbuff)[pos + update_count_pos]);    
        unalligned_ptr<uint32_t> pperiod((*pbuff).data() + pos + update_periodicity_pos);   
        printf(" update periodicity: %u millisec.\n", *pperiod);  

        printf(" OS major version: %u\n", (*pbuff)[pos + windows_major_vers_pos]);     
        printf(" OS minor version: %u\n", (*pbuff)[pos + windows_minor_vers_pos]); 

        unalligned_ptr<uint32_t> pserv_type((*pbuff).data() + pos + server_type_pos);   
        printf(" server type: 0x%08x\n", *pserv_type);     
    }
}

/**
\bref Метод get_next_level. 
\details Возвращает пакет следюущего уровня. 
\return Указатель на пакет следующего уровня.
*/
shared_ptr<packet> browser_packet::get_next_level() {

    return nullptr;
}


