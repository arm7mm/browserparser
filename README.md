# browserparser                                 

Содержимое /src : 

main.cpp &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - функция main().  
parser.cpp &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- методы класса разбора файла.  
ethernetII_packet.cpp &nbsp;&nbsp;&nbsp;&nbsp;--+  
ipv4_packet.cpp        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|   
udp_packet.cpp         &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  методы классов  
netbios_packet.cpp     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  соответствующих протоколов.  
smb_packet.cpp         &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  
browser_packet.cpp   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;__|  
  
Содержимое /header :  

pcap.h               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - описание заголовка и формата фреймов pcap файла.  
packet.h             &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - абстрактный класс, служащий основой для описания классов пакетов различных протоколов.  
unalligned_ptr.h     &nbsp;&nbsp;- класс для доступа к невыровненным данным.  
ethernetII_packet.h&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--+  
ipv4_packet.h        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|   
udp_packet.h        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |  описание классов  
netbios_packet.h    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |  соответствующих протоколов.  
smb_packet.h         &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  
browser_packet.h   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;__|  
  
                                Сборка.

make COMP=<компилятор>  
Например make COMP=g++ или make COMP=clang.  
Запуск make без аргументов соответствует выбору g++. 

                                Запуск.
                                
./browserparser <имя pcap файла>  
Например ./browserparser browser.pcap  
