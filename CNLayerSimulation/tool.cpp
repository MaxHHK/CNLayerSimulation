//
//  tool.cpp
//  CNLayerSimulation
//

#include "tool.hpp"

string Tools:: hexToBin(string hex) {
    vector<string> ans;
    string strBin;
    for (string::iterator it = hex.begin(); it < hex.end(); it++) {
        string tmp;
        switch (*it) {
            case '0':
                tmp = "0000";
                break;
            case '1':
                tmp = "0001";
                break;
            case '2':
                tmp = "0010";
                break;
            case '3':
                tmp = "0011";
                break;
            case '4':
                tmp = "0100";
                break;
            case '5':
                tmp = "0101";
                break;
            case '6':
                tmp = "0110";
                break;
            case '7':
                tmp = "0111";
                break;
            case '8':
                tmp = "1000";
                break;
            case '9':
                tmp = "1001";
                break;
            case 'A':
            case 'a':
                tmp = "1010";
                break;
            case 'B':
            case 'b':
                tmp = "1011";
                break;
            case 'C':
            case 'c':
                tmp = "1100";
                break;
            case 'D':
            case 'd':
                tmp = "1101";
                break;
            case 'E':
            case 'e':
                tmp = "1110";
                break;
            case 'F':
            case 'f':
                tmp = "1111";
                break;
            default:
                break;
        }
        ans.push_back(tmp);
    }
    strBin.clear();
    for (vector<string>:: iterator it = ans.begin(); it < ans.end(); it++) {
        strBin = strBin + *it;
    }
    return strBin;
}

string Tools:: hexToStr(string hex) {
    int hexLength = static_cast<int>( hex.length() );
    string str;
    int i;
    for( i = 0; i < hexLength; i += 2) {
        int units = hex[i + 1] <= '9' ? hex[i + 1] - '0' : hex[i + 1] - 55;
        int decade = hex[i] <= '9' ? hex[i] - '0' : hex[i] - 55;
        char temp = decade*16 + units;
        str.append(1, temp);
    }
    return str;
}

string Tools:: strToHex(string str) {
    int strLength = static_cast<int>( str.length() );
    string res;
    int i;
    for (i = 0; i < strLength; ++i) {
        int dec = (int)(str[i]);
        int remain = dec % 16;
        int factor = dec/16;
        remain = remain < 10? remain + '0': remain + 55;
        factor = factor < 10? factor + '0': factor + 55;
        // cout << (char) dec << ' ' <<  (char)remain << ' ' << (char)factor << endl;
        res.append(1, factor);
        res.append(1, remain);
    }
    return res;
}

string Tools:: binToHex(string bin) {
    string ans;
    int length = static_cast<int>( bin.length()/4 );
    for(int i = 0; i < length; ++i) {
        string sub = bin.substr(i*4, 4);
        if (sub == "0000") {
            ans += "0";
        } else if (sub == "0001") {
            ans += "1";
        } else if (sub == "0010") {
            ans += "2";
        } else if (sub == "0011") {
            ans += "3";
        } else if (sub == "0100") {
            ans += "4";
        } else if (sub == "0101") {
            ans += "5";
        } else if (sub == "0110") {
            ans += "6";
        } else if (sub == "0111") {
            ans += "7";
        } else if (sub == "1000") {
            ans += "8";
        } else if (sub == "1001") {
            ans += "9";
        } else if (sub == "1010") {
            ans += "A";
        } else if (sub == "1011") {
            ans += "B";
        } else if (sub == "1100") {
            ans += "C";
        } else if (sub == "1101") {
            ans += "D";
        } else if (sub == "1110") {
            ans += "E";
        } else if (sub == "1111") {
            ans += "F";
        }
    }
    return ans;
}

string Tools:: transfer(int x,int length) {
    string result(length, '0');
    int index = length-1;
    int r;
    while(x)
    {
        r=x%2;
        if(r == 0){
            result[index] = '0';
        }else{
            result[index] = '1';
        }
        index -= 1;
        x/=2;
    }
    return result;
}

string Tools:: bmoc_calculation(string A,string B) {
    string result(16, '0');
    int cx = 0;
    int a,b,sum;
    int index = 15;
    while(index > -1){
        a = A[index] - '0';
        b = B[index] - '0';
        sum = a+b+cx;
        cx = sum/2;
        sum = sum%2;
        if(sum){
            result[index] = '1';
        }else{
            result[index] = '0';
        }
        index -= 1;
    }
    return result;
}
