//
//  processIP.cpp
//  NetworkLayerSimulation
//

#include "processIP.hpp"

string HeadExamination(string head){
    string result(16, '0');
    vector <string> bytes;
    string temp;
    string A,B;
    for(int i=0 ; i <= head.size()-16; i += 16){
        temp.clear();
        temp = head.substr(i,16);
        bytes.push_back(temp);
    }
    while(bytes.size() > 1){
        A.clear();
        A = bytes[bytes.size()-1];
        bytes.pop_back();
        B.clear();
        B = bytes[bytes.size()-1];
        bytes.pop_back();
        temp.clear();
        temp = bmoc_calculation(A,B);
        bytes.push_back(temp);
    }
    result = bytes[0];
    for(int i=0;i<16;i++){
        if(result[i] == '0'){
            result[i] = '1';
        }else{
            result[i] = '0';
        }
    }
    return result;
}

Data ProcessIP:: encapsulate(string fromUpLayer) {
    Data result;
    result.layer = IP;
    result.head = "";
    result.dataOfUpLayer = fromUpLayer;
    result.tail = "";
    version = transfer(4,4);
    head_length = transfer(5,4);
    differentiated_services = transfer(0,8); //Generally is not used
    total_length = transfer(static_cast<int>(20+fromUpLayer.length()/8), 16);
    identification = transfer(0,16);
    flag = transfer(0,3);
    offset = transfer(0,13);
    ttl = transfer(TTL,8);
    protocol = transfer(6,8);
    sourceIP = "";
    destinationIP = "";
    for(int i = 0;i < NumOfIP;i++){
        sourceIP.append(transfer(atoi(basisInformation.srcIP[i].c_str()),8));
        destinationIP.append(transfer(atoi(basisInformation.desIP[i].c_str()),8));
    }
    head_examination = transfer(0,16);
    result.head.append(version);
    result.head.append(head_length);
    result.head.append(differentiated_services);
    result.head.append(total_length);
    result.head.append(identification);
    result.head.append(flag);
    result.head.append(offset);
    result.head.append(ttl);
    result.head.append(protocol);
    result.head.append(head_examination);
    result.head.append(sourceIP);
    result.head.append(destinationIP);
    
    head_examination = HeadExamination(result.head);
    
    result.head = "";
    result.head.append(version);
    result.head.append(head_length);
    result.head.append(differentiated_services);
    result.head.append(total_length);
    result.head.append(identification);
    result.head.append(flag);
    result.head.append(offset);
    result.head.append(ttl);
    result.head.append(protocol);
    result.head.append(head_examination);
    result.head.append(sourceIP);
    result.head.append(destinationIP);
    
    return result;
}

Data ProcessIP:: disassemble(const string currentLayerData){
    Data result;
    result.layer = IP;
    result.head = currentLayerData.substr(0,40);
    result.dataOfUpLayer = currentLayerData.substr(40,currentLayerData.size()-40);
    result.tail = "";
    return result;
}


vector <DataFormat> ProcessIP:: interpret(const Data info){
    vector <DataFormat> result;
    string data_head;
    //data_head = hexToBin(info.head);
    data_head = info.head;
    DataFormat temp_info;
    temp_info.layer = IP;
    //version
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 0;
    temp_info.valueOfField = data_head.substr(0,4);
    temp_info.explainOfField = "IP_version";
    result.push_back(temp_info);
    //head_length
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 4;
    temp_info.valueOfField = data_head.substr(4,4);
    temp_info.explainOfField = "IP_head_length";
    result.push_back(temp_info);
    //differentiated_services
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 8;
    temp_info.valueOfField = data_head.substr(8,8);
    temp_info.explainOfField = "IP_differentiated_services";
    result.push_back(temp_info);
    //total_length
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 16;
    temp_info.valueOfField = data_head.substr(16,16);
    temp_info.explainOfField = "IP_total_length";
    result.push_back(temp_info);
    //identification
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 32;
    temp_info.valueOfField = data_head.substr(32,16);
    temp_info.explainOfField = "IP_identification";
    result.push_back(temp_info);
    //flag
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 48;
    temp_info.valueOfField = data_head.substr(48,3);
    temp_info.explainOfField = "IP_flag";
    result.push_back(temp_info);
    //offset
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 51;
    temp_info.valueOfField = data_head.substr(51,13);
    temp_info.explainOfField = "IP_offset";
    result.push_back(temp_info);
    //ttl
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 64;
    temp_info.valueOfField = data_head.substr(64,8);
    temp_info.explainOfField = "IP_TTL";
    result.push_back(temp_info);
    //protocol
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 72;
    temp_info.valueOfField = data_head.substr(72,8);
    temp_info.explainOfField = "IP_protocal";
    result.push_back(temp_info);
    //head_examination
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 80;
    temp_info.valueOfField = data_head.substr(80,16);
    temp_info.explainOfField = "IP_head_examination";
    result.push_back(temp_info);
    //sourceIP
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 96;
    temp_info.valueOfField = data_head.substr(96,32);
    temp_info.explainOfField = "IP_sourceIP";
    result.push_back(temp_info);
    //destinationIP
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 128;
    temp_info.valueOfField = data_head.substr(128,32);
    temp_info.explainOfField = "IP_destinationIP";
    result.push_back(temp_info);
    return result;
}
