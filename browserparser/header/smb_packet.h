/**
\file
\bref Заголовочный файл с описанием класса пакета протокола SMB (Server Message Block Protocol).
*/

#ifndef SMB_H 
#define SMB_H

#include <string>
#include <cstdio>
#include "packet.h"

/**
\bref Класс smb_packet.
\details Класс пакета протокола SMB, наследник класса packet.
         Объявлен final, так как пока наследование от него не планируется.
*/
class smb_packet final : public packet {
public:
    /**
    \bref Коструктор.
    \details Инициализация посредством вызова конструктора базового класса. 
    \param[in] Буфер, где находится пакет.
    \param[in] Смещение пакета в буфере.
    */
    smb_packet(packet::buff_t &, packet::pos_t );
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
    virtual ~smb_packet() noexcept = default;
private:
    struct header {
        uint8_t  server_component[4];
        uint8_t  smb_command;
        uint8_t  error_class;
        uint8_t  reserv1;                      
        uint8_t  error_code[2];            /* uint16_t */   
        uint8_t  flags;
        uint8_t  flags2[2];                /* uint16_t */
        uint8_t  process_id_hight[2];      /* uint16_t */              
        uint8_t  signature[8];        
        uint8_t  reserv2[2];               /* uint16_t */
        uint8_t  tree_id[2];               /* uint16_t */
        uint8_t  process_id[2];            /* uint16_t */
        uint8_t  user_id[2];               /* uint16_t */
        uint8_t  multiplex_id[2];          /* uint16_t */
    };
    struct trans_request {
        uint8_t  wct;
        uint8_t total_parameter_count[2]; /* uint16_t */
        uint8_t total_data_count[2];      /* uint16_t */
        uint8_t max_parameter_count[2];   /* uint16_t */                  
        uint8_t max_data_count[2];        /* uint16_t */   
        uint8_t max_setup_count;
        uint8_t reserv;           
        uint8_t flags[2];                 /* uint16_t */              
        uint8_t timeout[4];               /* uint32_t */
        uint8_t reserv2[2];               /* uint16_t */
        uint8_t parameter_count[2];       /* uint16_t */
        uint8_t parameter_ffset[2];       /* uint16_t */
        uint8_t data_count[2];            /* uint16_t */
        uint8_t data_offset[2];           /* uint16_t */
        uint8_t setup_count;     
        uint8_t reserv3; 
        uint8_t setup[1];  
        uint8_t size[2];                  /* uint16_t */
        uint8_t name[1];
    };  
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    smb_packet(const smb_packet &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    smb_packet(smb_packet &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    smb_packet& operator=(const smb_packet &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    smb_packet& operator=(smb_packet &&) = delete;

    uint16_t data_count  = 0;
    uint16_t data_offset = 0;
    packet::pos_t mailslot_name_pos = 0;

    static const packet::pos_t packet_header_size    = sizeof(header); /* 32 */
    static const packet::pos_t smb_command_pos       = offsetof(header, smb_command); /* 4 */
    static const uint8_t smb_com_transaction         = 0x25;

    static const packet::pos_t data_count_pos  = packet_header_size + offsetof(trans_request, data_count)/* 23 */;
    static const packet::pos_t data_offset_pos = packet_header_size + offsetof(trans_request, data_offset)/* 25 */;
    static const packet::pos_t setup_count_pos = packet_header_size + offsetof(trans_request, setup_count)/* 27 */;
    static const packet::pos_t mailslot_name_offset = sizeof(uint16_t) + sizeof(uint16_t) /* 4 */;   /* Размеры полей trans_request.reserv3 и trans_request.size */

    static constexpr uint8_t mailslot_name[] = "\\MAILSLOT\\BROWSE";
};

#endif  /* SMB_H */

