//
//  processTCP.cpp
//  NetworkLayerSimulation
//

#include "processTCP.hpp"

string HeadExamination(string head,string fromUpLayer) {
    string result(16, '0');
    vector <string> bytes;
    string temp;
    string A, B;
    if (fromUpLayer.size() % 16 == 0) {
        for (int i = 0; i <= head.size() - 16; i += 16) {
            temp.clear();
            temp = head.substr(i, 16);
            bytes.push_back(temp);
        }
        while (bytes.size() > 1) {
            A.clear();
            A = bytes[bytes.size() - 1];
            bytes.pop_back();
            B.clear();
            B = bytes[bytes.size() - 1];
            bytes.pop_back();
            temp.clear();
            temp = bmoc_calculation(A, B);
            bytes.push_back(temp);
        }
        result = bytes[0];
        for (int i = 0; i < 16; i++) {
            if (result[i] == '0') {
                result[i] = '1';
            }
            else {
                result[i] = '0';
            }
        }
    }
    else {
        head = head + transfer(0, 8);
        for (int i = 0; i <= head.size() - 16; i += 16) {
            temp.clear();
            temp = head.substr(i, 16);
            bytes.push_back(temp);
        }
        while (bytes.size() > 1) {
            A.clear();
            A = bytes[bytes.size() - 1];
            bytes.pop_back();
            B.clear();
            B = bytes[bytes.size() - 1];
            bytes.pop_back();
            temp.clear();
            temp = bmoc_calculation(A, B);
            bytes.push_back(temp);
        }
        result = bytes[0];
        for (int i = 0; i < 16; i++) {
            if (result[i] == '0') {
                result[i] = '1';
            }
            else {
                result[i] = '0';
            }
        }
    }
    return result;
}

Data ProcessTCP::encapsulate(string fromUpLayer) {
    Data result;
    result.layer = TCP;
    result.head = "";
    result.dataOfUpLayer = fromUpLayer;
    result.tail = "";
    
    port_src = transfer(basisInformation.srcPort, 16);//源端口
    port_des = transfer(basisInformation.desPort, 16); //目的端口
    serial_number = transfer(0,64) ;//序号
    confirm_number =transfer(0,64) ;//确认号
    data_offset = transfer(5,4);//数据偏移
    keep = transfer(0,6);//保留
    urg = transfer(0, 1);//紧急urg
    ack = transfer(1, 1);//确认ack
    psh = transfer(1, 1);//推送psh
    rst = transfer(0, 1);//复位rst
    syn = transfer(1, 1);//同步syn
    fin = transfer(0, 1);//终止fin
    window = transfer(0, 16);//窗口
    head_examination = transfer(0, 16);//首部检验和
    urgent_pointer = transfer(0, 16);//紧急指针
    option = transfer(0, 0);//选项
    sourceIP = "";
    destinationIP = "";
    for (int i = 0; i < NumOfIP; i++) {
        sourceIP.append(transfer(atoi(basisInformation.srcIP[i].c_str()), 8));
        destinationIP.append(transfer(atoi(basisInformation.desIP[i].c_str()), 8));
    }
    result.head.append(port_src);
    result.head.append(port_des);
    result.head.append(serial_number);
    result.head.append(confirm_number);
    result.head.append(data_offset);
    result.head.append(keep);
    result.head.append(urg);
    result.head.append(ack);
    result.head.append(psh);
    result.head.append(rst);
    result.head.append(syn);
    result.head.append(fin);
    result.head.append(window);
    result.head.append(head_examination);
    result.head.append(urgent_pointer);
    result.head.append(option);
    
    exam = sourceIP + destinationIP+transfer(0,8)+transfer(6,8) + transfer(static_cast<int>(fromUpLayer.length()) / 2, 16)+ result.head + fromUpLayer;
    head_examination = HeadExamination(exam,fromUpLayer);
    
    result.head = "";
    result.head.append(port_src);
    result.head.append(port_des);
    result.head.append(serial_number);
    result.head.append(confirm_number);
    result.head.append(data_offset);
    result.head.append(keep);
    result.head.append(urg);
    result.head.append(ack);
    result.head.append(psh);
    result.head.append(rst);
    result.head.append(syn);
    result.head.append(fin);
    result.head.append(window);
    result.head.append(head_examination);
    result.head.append(urgent_pointer);
    result.head.append(option);
    
    result.head = binToHex(result.head);
    return result;
}

Data ProcessTCP:: disassemble(const string currentLayerData) {
    Data result;
    result.layer = TCP;
    result.head = currentLayerData.substr(0, 40);
    result.dataOfUpLayer = currentLayerData.substr(40, currentLayerData.size() - 40);
    result.tail = "";
    return result;
}

vector <DataFormat> ProcessTCP:: interpret(const Data info) {
    vector <DataFormat> result;
    string tcp_head;
    tcp_head = hexToBin(info.head);
    DataFormat temp_info;
    temp_info.layer = TCP;
    //srcPort
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 0;
    temp_info.valueOfField = tcp_head.substr(0, 16);
    temp_info.explainOfField = "the valueoffiled of source Port is 16 bits(2 bytes),and it covers from 1 to 16 ";
    result.push_back(temp_info);
    //desPort
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 16;
    temp_info.valueOfField = tcp_head.substr(16, 16);
    temp_info.explainOfField = "the valueoffiled of destination Port is 16 bits(2 bytes),and it covers from 17 to 32 ";
    result.push_back(temp_info);
    //serial_number
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 32;
    temp_info.valueOfField = tcp_head.substr(32, 32);
    temp_info.explainOfField = "the valueoffiled of serial_number is 32 bits(4 bytes),and it covers from 33 to 64,every byte number according to the order ";
    result.push_back(temp_info);
    //confirm_number
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 64;
    temp_info.valueOfField = tcp_head.substr(64, 32);
    temp_info.explainOfField = "the valueoffiled of confirm_number is 32 bits(4 bytes),and it covers from 65 to 96,it is the  serial number of first data byte of next tcpdata ";
    result.push_back(temp_info);
    //dataoffset
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 96;
    temp_info.valueOfField = tcp_head.substr(96, 4);
    temp_info.explainOfField = "the valueoffiled of dataoffset is 4 bits,and it covers from 97 to 100,it is actually the length of head of tcpdata,so it sets 0101 ";
    result.push_back(temp_info);
    //keep
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 100;
    temp_info.valueOfField = tcp_head.substr(100, 6);
    temp_info.explainOfField = "the valueoffiled of keep is 6 bits,and it covers from 101 to 106,now it sets 000000 ";
    result.push_back(temp_info);
    //urg
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 106;
    temp_info.valueOfField = tcp_head.substr(106, 1);
    temp_info.explainOfField = "the valueoffiled of urg is 1 bit,and it cover 107,when it's urgrnt,it sets 1,now it sets 0 ";
    result.push_back(temp_info);
    //ack
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 107;
    temp_info.valueOfField = tcp_head.substr(107, 1);
    temp_info.explainOfField = "the valueoffiled of ack is 1 bit,and it cover 108,when establish connect,it sets 1";
    result.push_back(temp_info);
    //psh
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 108;
    temp_info.valueOfField = tcp_head.substr(108, 1);
    temp_info.explainOfField = "the valueoffiled of psh is 1 bit,and it cover 109,it sets 1";
    result.push_back(temp_info);
    //rst
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 109;
    temp_info.valueOfField = tcp_head.substr(109, 1);
    temp_info.explainOfField = "the valueoffiled of rst is 1 bit,and it cover 110,it sets 0";
    result.push_back(temp_info);
    //syn
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 110;
    temp_info.valueOfField = tcp_head.substr(110, 1);
    temp_info.explainOfField = "the valueoffiled of syn is 1 bit,and it cover 111,it sets 1";
    result.push_back(temp_info);
    //fin
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 111;
    temp_info.valueOfField = tcp_head.substr(111, 1);
    temp_info.explainOfField = "the valueoffiled of fin is 1 bit,and it cover 112,it sets 0";
    result.push_back(temp_info);
    //window
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 112;
    temp_info.valueOfField = tcp_head.substr(112, 16);
    temp_info.explainOfField = "the valueoffiled of window is 16 bits,and it covers from 113 to 128";
    result.push_back(temp_info);
    //head_examination
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 128;
    temp_info.valueOfField = tcp_head.substr(128, 16);
    temp_info.explainOfField = "the valueoffiled of head_examinatin is 16 bits,and it covers from 129 to 144";
    result.push_back(temp_info);
    //urgent pointer
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 144;
    temp_info.valueOfField = tcp_head.substr(144, 16);
    temp_info.explainOfField = "the valueoffiled of urgent_pointer is 16 bits,and it covers from 145 to 160";
    result.push_back(temp_info);
    //option
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 160;
    temp_info.valueOfField = tcp_head.substr(160, 0);
    temp_info.explainOfField = "the valueoffiled of option is 0 bit";
    result.push_back(temp_info);
    return result;
}
