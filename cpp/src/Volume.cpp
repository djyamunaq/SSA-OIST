#include "Volume.hpp"          
#include "ReactionChannel.hpp" 
#include <cstdio>

Volume::Volume(const std::vector<ReactionChannel> &reactionChannelVector)
    : reactionChannelVector(reactionChannelVector) {}

Volume::Volume(const ReactionChannel &reactionChannel)
{
    this->reactionChannelVector.push_back(reactionChannel);
}
void Volume::addReactionChannel(ReactionChannel &reactionChannel)
{
    this->reactionChannelVector.push_back(reactionChannel);
}

void Volume::printVolume() const
{
    printf("--- Volume Details ---\n");
    printf("Total Reaction Channels: %zu\n", reactionChannelVector.size());

    for (size_t i = 0; i < reactionChannelVector.size(); ++i)
    {
        printf("Reaction %zu:\n", i + 1);
        reactionChannelVector[i].printReactionChannel();
        printf("----------------------\n");
    }
}

