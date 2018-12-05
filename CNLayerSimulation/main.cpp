//
//  main.cpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#include <iostream>

#include "cnformat.h"
#include "interface.cpp"

int main(int argc, const char * argv[]) {
    Interface inter;
    Segment seg2(2, 2, 10, 10);
    while (1) {
        string cmd;
        cin >> cmd;
        if (cmd == "exit") {
            break;
        } else {
            inter.moveToCommand();
            printf("next:");
        }
    }
    return 0;
}
