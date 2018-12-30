//
//  processMac.cpp
//  NetworkLayerSimulation
//

#include "processMac.hpp"

string ProcessMac:: getFCS(string M,string P) {
    string ans(32, '0');
    return ans;
    int lenM, lenP, i, j;
    lenM = static_cast<int>( M.size() );
    lenP = static_cast<int>( P.size() );
    string Y;
    string Z;
    string result;
    for(i=0;i<lenP;i++){
        Y[i] = M[i];
    }
    for(i=0;i<=lenM-lenP;i++){
        for(j=0;j<lenP-1;j++){
            if(M[i+j+1] == Y[j+1]){
                Z[j] = '0';
            }
            if(M[i+j+1] != Y[j+1]){
                Z[j] = '1';
            }
        }
        if(i<lenM-lenP){
            Z[lenP-1] = M[i+lenP];
        }
        for(j=0;j<lenP;j++){
            Y[j] = Z[j];
        }
    }
    for(i=0;i<lenP-1;i++){
        result[i] = Z[i];
    }
    return result;
}

Data ProcessMac:: encapsulate(string fromUpLayer) {
    Data result;
    string headndata;
    string divisor;
    result.layer = Mac;
    result.head = "";
    result.dataOfUpLayer = fromUpLayer;
    result.tail = "";
    sourceMac = "";
    destinationMac = "";
    for(int i = 0;i < NumOfMac;i++){
        sourceMac.append(transfer(atoi(basisInformation.srcMac[i].c_str()),8));
        destinationMac.append(transfer(atoi(basisInformation.desMac[i].c_str()),8));
    }
    
    
    type = transfer(4096,16);
    
    result.head.append(sourceMac);
    result.head.append(destinationMac);
    result.head.append(type);
    
    headndata = result.head;
    headndata.append(hexToBin(fromUpLayer));
    headndata.append(transfer(0,32));
    
    divisor = "10000010";
    divisor.append("01100000");
    divisor.append("10001110");
    divisor.append("110110110");
    
    result.tail = binToHex(getFCS(headndata,divisor));
    result.head = binToHex(result.head);

    return result;
}

Data ProcessMac:: disassemble(const string currentLayerData){
    Data result;
    result.layer = Mac;
    result.head = currentLayerData.substr(0,56);
    result.dataOfUpLayer = currentLayerData.substr(56,currentLayerData.size()-72);
    result.tail = currentLayerData.substr(currentLayerData.size()-16,16);
    return result;
}

vector <DataFormat> ProcessMac:: interpret(const Data info){
    vector <DataFormat> result;
    string data_head, data_tail;
    data_head = hexToBin(info.head);
    data_tail = hexToBin(info.tail);
    DataFormat temp_info;
    temp_info.layer = Mac;
    //sourceMac
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 0;
    temp_info.valueOfField = data_head.substr(0,48);
    temp_info.explainOfField = "sourceMac field covers 48 bits from 1 to 48. ";
    temp_info.explainOfField.append("This field is constructed by the sender's Mac address. ");
    result.push_back(temp_info);
    //destinationMac
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 48;
    temp_info.valueOfField = data_head.substr(48,48);
    temp_info.explainOfField = "destinationMac field covers 48 bits from 49 to 96.";
    temp_info.explainOfField.append("This field is constructed by the receiver's Mac address.");
    result.push_back(temp_info);
    //type
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 96;
    temp_info.valueOfField = data_head.substr(96,16);
    temp_info.explainOfField = "Type field covers 16 bits from 97 to 112. ";
    temp_info.explainOfField.append("This field explains what protocol the upper story uses. ");
    result.push_back(temp_info);
    //FCS
    temp_info.valueOfField.clear();
    temp_info.explainOfField.clear();
    temp_info.indexOfField = 16;
    temp_info.valueOfField = data_tail.substr(0,32);
    temp_info.explainOfField = "Total-Length field covers 32 bits from 1 to 32. ";
    temp_info.explainOfField.append("This field is used to correct whether the data is wrong or has been modificated. ");
    result.push_back(temp_info);
    return result;
}
