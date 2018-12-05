//
//  processIP.cpp
//  NetworkLayerSimulation
//

#include "processIP.hpp"

Data ProcessIP:: encapsulate(string fromUpLayer) {
    Data result;
    result.layer = TCP;
    result.head = "Head";
    result.dataOfUpLayer = fromUpLayer;
    result.tail = "";
    return result;
}
