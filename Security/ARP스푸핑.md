# ARP Spoofing
[ARP](https://github.com/SuhYC/Lesson/blob/main/Network/ARP.md)의 취약점을 이용해 네트워크 패킷의 목적지를 위장하여 패킷을 가로채는 공격방식.

가짜 ARP응답 메시지를 보내 네트워크 스위치 등의 장비에 공격대상의 IP를 공격자의 MAC주소로 저장하도록하여 공격한다. <br/>
이후 누군가 공격대상에게 패킷을 전달하려고하면,
공격대상의 IP가 공격자의 MAC주소로 변환되기 때문에 패킷이 공격자에게로 전송되게 된다.
