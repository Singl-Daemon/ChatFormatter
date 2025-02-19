#include "Config.h"
#include "Entry.h"
#include "Global.h"

#include <mc/network/ServerNetworkHandler.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/level/Level.h>

#include <GMLIB/Event/Packet/TextPacketEvent.h>
#include <GMLIB/Server/PlaceholderAPI.h>

#include <ll/api/event/EventBus.h>
#include <ll/api/service/Bedrock.h>

namespace ChatFormatter {

std::string formatMessage(const std::string_view author, const std::string_view message, Player* pl) {
    const auto& config = ChatFormatter::Entry::getInstance().getConfig();
    std::string result = config.ChatFormat;
    GMLIB::Server::PlaceholderAPI::translate(result, pl);
    ll::utils::string_utils::replaceAll(result, "{player}", author);
    ll::utils::string_utils::replaceAll(result, "{message}", message);
    return result;
}

void listenEvent() {
    auto& eventBus = ll::event::EventBus::getInstance();
    eventBus.emplaceListener<GMLIB::Event::PacketEvent::TextPacketWriteBeforeEvent>(
        [](const GMLIB::Event::PacketEvent::TextPacketWriteBeforeEvent& ev) {
            auto& pkt = ev.getPacket();
            if (pkt.mType == TextPacketType::Chat) {
                const auto& config = ChatFormatter::Entry::getInstance().getConfig();
                const auto  pl     = ll::service::getLevel()->getPlayer(pkt.mAuthor);
                pkt.mMessage       = formatMessage(pkt.mAuthor, pkt.mMessage, pl);
                pkt.mAuthor.clear();
                if (config.ChatLogger.Enabled && pl) {
                    chatLogger->info(pkt.mMessage);
                }
            }
        }
    );
}

} // namespace ChatFormatter