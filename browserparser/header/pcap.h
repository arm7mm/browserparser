/**
\file
\bref Заголовочный файл с описанием формата pcap файла.
*/

#ifndef PCAP_H 
#define PCAP_H

#include <cstdint>

namespace pcap {

    const uint32_t magic1 = 0xA1B2C3D4; /* временные метки в пакетных записях находятся в секундах и микросекундах */
    const uint32_t magic2 = 0xA1B23C4D; /* временные метки в пакетных записях находятся в секундах и наносекундах */

    typedef enum { micro, nano } timestype_t;

    struct header {
        uint32_t magic_number;
        uint16_t major_version;         /* номер текущей основной версии формата */
        uint16_t minor_version;         /* номер текущей вспомогательной версии формата */
        uint32_t reserved1;
        uint32_t reserver2;
        uint32_t snap_len;              /* максимальное количество октетов, захваченных из каждого пакета (не должно быть равно нулю) */
        uint32_t link_type;
    };

    struct frame_header {
        uint32_t timestamp1;           /* секунды временной метки. */
        uint32_t timestamp2;           /* доли секундных значений временной метки. */
        uint32_t captured_frame_size;  /* количество октетов, захваченных из пакета */
        uint32_t original_frame_size;  /* фактическая длина пакета */
    };

}

#endif  /* PCAP_H */
