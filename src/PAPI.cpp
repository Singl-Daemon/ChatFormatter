#include "Entry.h"
#include "Global.h"

std::string getDimensionName(Player* pl) {
    auto  dimName = ((GMLIB_Player*)pl)->getDimensionName();
    auto& nameMap = ChatFormatter::Entry::getInstance()->getConfig().DimensionNameMap;
    return nameMap.contains(dimName) ? nameMap[dimName] : dimName;
}

void registerPAPI() {
    GMLIB::Server::PlaceholderAPI::registerPlayerPlaceholder(
        "chatformatter_dimension",
        [](Player* pl) { return getDimensionName(pl); },
        "ChatFormatter"
    );
}

void unregisterPAPI() { GMLIB::Server::PlaceholderAPI::unregisterPlaceholder("chatformatter_dimension"); }
