//
//  interface.cpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#include "interface.hpp"

bool Interface:: moveToCommand() {
    
    ProcessIP ip;
    Data tmp = ip.encapsulate("haha");
    cout << tmp.head << tmp.dataOfUpLayer << tmp.tail;
    
    return true;
}
