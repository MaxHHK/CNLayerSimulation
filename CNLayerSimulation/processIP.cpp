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
    total_length = transfer(20 + static_cast<int>(fromUpLayer.length())/2,16);
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
    
    result.head = binToHex(result.head);
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
    data_head = hexToBin(info.head);
    DataFormat temp_info;
    temp_info.layer = IP;
    //version
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 0;
    temp_info.valueOfField = data_head.substr(0,4);
    temp_info.explainOfField = "Version field covers 4 bits from 1 to 4. ";
    temp_info.explainOfField.append("This field refers to the version of IP protocol. ");
    temp_info.explainOfField.append("Because this computer uses IPv4, the value of this field is 4.");
    result.push_back(temp_info);
    //head_length
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 4;
    temp_info.valueOfField = data_head.substr(4,4);
    temp_info.explainOfField = "Header-Length field covers 4 bits from 5 to 8 with a meaning of total length of the header of the IP message. ";
    temp_info.explainOfField.append("The unit of this field is 32 bits and the maximum value and minimum value of this fields are 15 and 5 respectively. ");
    temp_info.explainOfField.append("With the aid of complementing field, the header length can be devided exactly by 4. ");
    temp_info.explainOfField.append("Because this IP message only have a fixed header, the value of this field is 5.");
    result.push_back(temp_info);
    //differentiated_services
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 8;
    temp_info.valueOfField = data_head.substr(8,8);
    temp_info.explainOfField = "Differentiated-Services field covers 8 bits from 9 to 16. ";
    temp_info.explainOfField.append("This field was set hoping to obtain better service, however, it was never used before. ");
    temp_info.explainOfField.append("In 1998, IETF renamed this field as differentiated services.");
    temp_info.explainOfField.append("It only works when differentiated services are served. ");
    temp_info.explainOfField.append("In this IP message, not using the differentiated restrict that the value should be 0.");
    result.push_back(temp_info);
    //total_length
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 16;
    temp_info.valueOfField = data_head.substr(16,16);
    temp_info.explainOfField = "Total-Length field covers 16 bits from 17 to 32. ";
    temp_info.explainOfField.append("It refers to the total length of both the header and the data area. ");
    temp_info.explainOfField.append("There are 16 bits in this field, thus the maximum length of an IP message is 65535 bytes. ");
    temp_info.explainOfField.append("The value of this field is a dynamic number depending on the real length of the massage.");
    result.push_back(temp_info);
    //identification
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 32;
    temp_info.valueOfField = data_head.substr(32,16);
    temp_info.explainOfField = "Identification field covers 16 bits from 33 to 48. ";
    temp_info.explainOfField.append("Each IP application maintains an counter to autoincrease after one more IP message is generated. ");
    temp_info.explainOfField.append("The value of the counter will then be assigned to the identification field of the newly generated IP message.");
    temp_info.explainOfField.append("Apart from that, we should keep in mind that identification is not a sequence. It has nothing to do with order. ");
    temp_info.explainOfField.append("For an extremely long message, after being segmented, all of the segments will have the same identification. ");
    temp_info.explainOfField.append("And these identical identification values can help the segments to combine successfully. ");
    temp_info.explainOfField.append("Since we are just sitimulating the process, the value of this field was assigned to 0 by us. ");
    result.push_back(temp_info);
    //flag
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 48;
    temp_info.valueOfField = data_head.substr(48,3);
    temp_info.explainOfField = "Flag field covers 3 bits from 49 to 51 but only two of them are significant. ";
    temp_info.explainOfField.append("The lowest bit are called MF, short for more fragment, and MF = 1 means there are more segments behind. M = 0 means this is the last segment of all. ");
    temp_info.explainOfField.append("The middle bit refers to DF, short for Don't Fragment. It means segmenting is forbidden and only if DF = 1, the message can be segmented. ");
    temp_info.explainOfField.append("Since our message is not segmented although it's allowed, the value of this field is 0.");
    result.push_back(temp_info);
    //offset
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 51;
    temp_info.valueOfField = data_head.substr(51,13);
    temp_info.explainOfField = "Offset field covers 13 bits from 52 to 64. ";
    temp_info.explainOfField.append("This field makes the relative index of a specific segment clear after the message is segmented. ");
    temp_info.explainOfField.append("Since our message is not segmented, the value of this field is 0.");
    
    result.push_back(temp_info);
    //ttl
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 64;
    temp_info.valueOfField = data_head.substr(64,8);
    temp_info.explainOfField = "TTL field, the abbreviation of Time To Live, covers 8 bits from 65 to 72. ";
    temp_info.explainOfField.append("It refers to the lifetime of a segment, and the value is initialized by the source port. ");
    temp_info.explainOfField.append("This field was set in order to avoid going around in circles. ");
    temp_info.explainOfField.append("Passing through one router makes its value decline by 1. ");
    temp_info.explainOfField.append("In our message, the value of this field is set to 255, the maximum value it can represent.");
    result.push_back(temp_info);
    //protocol
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 72;
    temp_info.valueOfField = data_head.substr(72,8);
    temp_info.explainOfField = "Protocol field covers 8 bits from 73 to 80. ";
    temp_info.explainOfField.append("This field describes which protocol this message is using, making it easier for IP layer to tranport the message to the right protocol of the TCP layer. ");
    temp_info.explainOfField.append("Since our message is using TCP protocol, the value of this field is 6.");
    result.push_back(temp_info);
    //sourceIP
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 96;
    temp_info.valueOfField = data_head.substr(96,32);
    temp_info.explainOfField = "SourceIP field covers 32 bits from 97 to 128. ";
    temp_info.explainOfField.append("This field is constructed by the sender's IP address.");
    result.push_back(temp_info);
    //destinationIP
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 128;
    temp_info.valueOfField = data_head.substr(128,32);
    temp_info.explainOfField = "DestinationIP field covers 32 bits from 129 to 160. ";
    temp_info.explainOfField.append("This field is constructed by the receiver's IP address.");
    result.push_back(temp_info);
    //head_examination
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 80;
    temp_info.valueOfField = data_head.substr(80,16);
    temp_info.explainOfField = "Head-Examination field covers 16 bits from 81 to 96. ";
    temp_info.explainOfField.append("This field only check the header of a data message rather than the data area, ");
    temp_info.explainOfField.append("the reason of which is because it can reduce the burden of calculation. ");
    temp_info.explainOfField.append("The header will be divided to dozens of sequences consisting of 16 bits in each of them. ");
    temp_info.explainOfField.append("And the head examination field is set to 0 at first. After raidx-minus-one complement calculation, we can get the correct value of this field.");
    temp_info.explainOfField.append("The value of this field is calculated as follows.");
    result.push_back(temp_info);
    return result;
}
