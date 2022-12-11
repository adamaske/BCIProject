#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdint.h>

#include <string>
#include <vector>

#include <unordered_map>

//networking, windows sockets, must include before windows.h, has redefiniton erros
#include <winsock2.h>

#include <Windows.h>
#include <Ws2tcpip.h>
#include "Logger/Logger.h"