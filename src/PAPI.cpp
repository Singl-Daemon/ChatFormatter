#include "Entry.h"

#include <GMLIB/Server/PlaceholderAPI.h>
#include <GMLIB/Server/PlayerAPI.h>
#include <mc/world/actor/player/Player.h>

namespace ChatFormatter {

std::string getDimensionName(Player* pl) {
    auto  dimName = static_cast<GMLIB_Player*>(pl)->getDimensionName();
    auto& nameMap = ChatFormatter::Entry::getInstance().getConfig().DimensionNameMap;
    return nameMap.contains(dimName) ? std::string(nameMap.at(dimName)) : std::string(dimName);
}

void registerPAPI() {
    GMLIB::Server::PlaceholderAPI::registerPlayerPlaceholder(
        "chatformatter_dimension",
        [](Player* pl) { return getDimensionName(pl); },
        "ChatFormatter"
    );
}

void unregisterPAPI() { GMLIB::Server::PlaceholderAPI::unregisterPlaceholder("chatformatter_dimension"); }

} // namespace ChatFormatter