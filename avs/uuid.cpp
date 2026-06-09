#include "uuid.h"
#include <cstdlib>

#ifdef _WIN32
#include <rpc.h>
#elif defined __linux__
#include <uuid/uuid.h>
#endif

std::string uuid4() {
#ifdef _WIN32
    RPC_CSTR uuid_str;
    UUID uuid;
    UuidCreate(&uuid);
    UuidToString(&uuid, &uuid_str);
    std::string result((char*)uuid_str);
    RpcStringFree(&uuid_str);
    return result;
#elif defined __linux__
    char uuid_str[37];
    uuid_str[36] = '\0';
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    return uuid_str;
#else
    char buf[37]; const char* hex = "0123456789abcdef";
    for (int i = 0; i < 36; i++) { if (i==8||i==13||i==18||i==23){buf[i]='-';continue;} buf[i]=hex[arc4random_uniform(16)]; }
    buf[14]='4'; buf[19]=hex[8+arc4random_uniform(4)]; buf[36]='\0'; return buf;
#endif
}
