/**
\file
\bref Заголовочный файл с описанием класса пакета протокола Microsoft Windows Browser Protocol.
*/

#ifndef BROWSER_H 
#define BROWSER_H

#include <cstdio>
#include "packet.h"

/**
\bref Класс browser_packet.
\details Класс пакета протокола Microsoft Windows Browser Protocol, наследник класса packet.
         Объявлен final, так как пока наследование от него не планируется.
*/
class browser_packet final : public packet {
public:
    /**
    \bref Коструктор.
    \details Инициализация посредством вызова конструктора базового класса. 
    \param[in] Буфер, где находится пакет.
    \param[in] Смещение пакета в буфере.
    */
    browser_packet(packet::buff_t &, packet::pos_t, packet::pos_t);
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
    virtual ~browser_packet() noexcept = default;
private:
    struct header {
        uint8_t  command;
        uint8_t  update_count;
        uint8_t  update_periodicity[4];           /* uint32_t */ 
        union name {
            uint8_t  host[16];                    /* Host Announcement (0x01) */
            uint8_t  domain_workgroup[16];        /* Domain/Workgroup Announcement (0x0c) */  
        } nm;                   
        uint8_t  windows_major_version;         
        uint8_t  windows_minor_version;
        uint8_t  server_type[4];                  /* uint32_t */ 
        union addition {
            struct host_addition {                /* Host Announcement (0x01) */
                uint8_t protocol_major_vers;
                uint8_t protocol_minor_vers;
                uint8_t signature[2];             /* uint16_t */
            } hst_addtn;
            struct domain_workgroup_addition {    /* Domain/Workgroup Announcement (0x0c) */
                uint8_t  reserv[4];        
            } dw_addtn;      
        } addtn;          
    };
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    browser_packet(const browser_packet &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    browser_packet(browser_packet &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    browser_packet& operator=(const browser_packet &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    browser_packet& operator=(browser_packet &&) = delete;
    /**
    \bref Метод print_host_fields. 
    \details Выводит данные полей пакета Host Announcement (0x01) на консоль.    
    */
    void print_host_fields() const;
    /**
    \bref Метод print_host_fields. 
    \details Выводит данные полей пакета Domain/Workgroup Announcement (0x0c) на консоль.    
    */
    void print_domain_workgroup_fields() const;
    /**
    \bref Размер пакета.
    \details инициализируется в конструкторе.
    */
    packet::pos_t size;

    enum command { host = 0x01, domain_workgroup = 0x0c };

    static const packet::pos_t header_size = sizeof(header)/*32*/;

    /* Host Announcement (0x01) и Domain/Workgroup Announcement (0x0c) */
    static const packet::pos_t command_pos             = offsetof(header, command)/*0*/;
    static const packet::pos_t update_count_pos        = offsetof(header, update_count)/*1*/;
    static const packet::pos_t update_periodicity_pos  = offsetof(header, update_periodicity)/*2*/;

    /* Host Announcement (0x01) */
    static const packet::pos_t host_pos                = offsetof(header, nm.host)/*6*/;
    static const packet::pos_t host_size               = 16;

    /* Domain/Workgroup Announcement (0x0c) */
    static const packet::pos_t domain_workgroup_pos    = offsetof(header, nm.domain_workgroup)/*6*/;
    static const packet::pos_t domain_workgroup_size   = 16;

    /* Host Announcement (0x01) и Domain/Workgroup Announcement (0x0c) */
    static const packet::pos_t windows_major_vers_pos  = offsetof(header, windows_major_version)/*22*/;
    static const packet::pos_t windows_minor_vers_pos  = offsetof(header, windows_minor_version)/*23*/;
    static const packet::pos_t server_type_pos         = offsetof(header, server_type)/*24*/;

    /* Host Announcement (0x01) */
    static const packet::pos_t protocol_major_vers_pos = offsetof(header, addtn.hst_addtn.protocol_major_vers)/*28*/;
    static const packet::pos_t protocol_minor_vers_pos = offsetof(header, addtn.hst_addtn.protocol_minor_vers)/*29*/;
    static const packet::pos_t signature_pos           = offsetof(header, addtn.hst_addtn.signature)/*30*/;
    static const packet::pos_t comment_pos             = header_size;

    /* Domain/Workgroup Announcement (0x0c) */
    static const packet::pos_t master_browser_name_pos = header_size;

};

#endif  /* BROWSER_H */

