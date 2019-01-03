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
string Tools::readFile(const char* path, char* buff, int start, int length) {
    int fd = open(path, O_RDONLY);
    lseek(fd, start, SEEK_CUR);
    char temp[3096];
    
    read(fd, temp, length);
    string ba64res = Tools::base64_encode((const unsigned char*) temp, length);
    ba64res.copy(buff, ba64res.length(), 0);
    
    string ret(path);
    return ret;
}


static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

static string Tools::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    
    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        
        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];
        
        while((i++ < 3))
            ret += '=';
        
    }
    
    return ret;
    
}

static string Tools::base64_decode(string const& encoded_string) {
    int in_len = static_cast<int>(encoded_string.size());
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    string ret;
    
    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        
        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);
        
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    
    return ret;
    
}
