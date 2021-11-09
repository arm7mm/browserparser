# browserparser                                Описание программы.

Содержимое /src :
main.cpp              - функция main().
parser.cpp            - методы класса разбора файла parser.
ethernetII_packet.cpp -+
ipv4_packet.cpp        | 
udp_packet.cpp         |  методы классов
netbios_packet.cpp     |  соответствеущих протоколов.
smb_packet.cpp         |
browser_packet.cpp   __|

Содержимое /header :
pcap.h                - описание заголовка и формата фреймов pcap файла.
packet.h              - актсрактный класс, служащий основой для 
                        описания классов пакетов различных протоколов.
unalligned_ptr.h      - класс для даступа к невыровненным данным.
ethernetII_packet.h -+
ipv4_packet.h        | 
udp_packet.h         |  описание классов
netbios_packet.h     |  соответствеущих протоколов.
smb_packet.h         |
browser_packet.h   __|

                                Сборка программы.

make COMP=<компилятор>
Например make COMP=g++ или make COMP=clang.
Запуск make без аргументов соответствует выбору g++.
                                Запуск
./broeserparser <имя pcap файла>
Например ./broeserparser browser.pcap
