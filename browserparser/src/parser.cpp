/**
\file
\bref Файл методов класса parser.
*/

#include "parser.h"
#include "packet.h"
#include "ethernetII_packet.h"

using namespace std;

/**
\bref Коструктор класса parser.

\details Читает заголовок pcap файла и проверяет его.
\param[in] Имя pcap файла.
\details Файл открывается в бинарном режиме.
*/
parser::parser(string &input)
    : timestype(), in(input, ios::binary) {                      
                                  
    if (in.is_open() != true) {                                    /* Проверка доступности файла */
        throw runtime_error("Data file not available.");
    }

    pcap::header hdr;
    in.read(reinterpret_cast<char*>(&hdr), sizeof(pcap::header));
    if (in.gcount() != sizeof(pcap::header)) {
        throw runtime_error("Unexpected end of file.");
    }

    if (hdr.magic_number == pcap::magic1) {
        timestype = pcap::micro;
    } else if (hdr.magic_number == pcap::magic2) {
        timestype = pcap::nano;
    } else {
        throw runtime_error("The file format is not pcap.");
    }
    if (hdr.snap_len == 0) {
        throw runtime_error("The pcap file header SnapLen field is zero.");        
    }
}


/**
\bref Метод parse_frame_data. 
\details Проводит разбор фрейма по составляющим его пакетам.   
\param   Размер фрейма.   
*/
void parser::parse_frame_data(packet::pos_t frame_size) {

    if (frame_size != 0) {
        vector<uint8_t> frame_data(frame_size);
        in.read(reinterpret_cast<char*>(frame_data.data()), frame_data.size());
        if (in.gcount() != frame_data.size()) {
            throw runtime_error("Unexpected end of file.");
        }

        shared_ptr<packet> ptr_packet(new ethernetII_packet(frame_data, 0));                                /*  */
        while (ptr_packet != nullptr) {
            ptr_packet->print_fields();
            ptr_packet = ptr_packet->get_next_level();
        }
    } else {
        printf("Captured Frame Length field is zero.\n");
    }
}

/**
\bref Метод parse. 
\details Проводит разбор фреймов в pcap файле и выводит данные на консоль.    
*/
void parser::parse() {

    pcap::frame_header frame_hdr;
    streamsize cnt; 

    in.read(reinterpret_cast<char*>(&frame_hdr), sizeof(pcap::frame_header));
    while ((cnt = in.gcount()) == sizeof(pcap::frame_header)) {
        printf("======%u sec.  :  %u", frame_hdr.timestamp1, frame_hdr.timestamp2);
        printf((timestype == pcap::micro) ? " microsec. " : " nanosec. ");
        printf("======\n");
        parse_frame_data(frame_hdr.captured_frame_size);
        in.read(reinterpret_cast<char*>(&frame_hdr), sizeof(pcap::frame_header));
    };
    if (cnt != 0) {
        throw runtime_error("Unexpected end of file.");
    }
}

