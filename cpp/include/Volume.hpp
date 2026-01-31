#ifndef VOLUME_HPP
#define VOLUME_HPP

#include <map>
#include "Composition.hpp"

/**
 * Forward Declarations
 */
class ReactionChannel;

/**
 * \brief Volume Class
 */
class Volume
{
private:
    std::vector<ReactionChannel> reactionChannelVector; /**< Reaction Channel Vector */

public:

    Volume() = default;

    /**
     * \brief Constructor for Volume class
     * \param reactionChannelVector Vector of reaction channels
     */
    Volume(const std::vector<ReactionChannel> &reactionChannelVector);

    /**
     * \brief Constructor for Volume class
     * \param products Reaction channel
     */
    Volume(const ReactionChannel &reactionChannel);

    /**
     * \brief Get channels
     * \param reactionChannelVector Reaction channel vector
     */
    const std::vector<ReactionChannel> &getChannels() const { return reactionChannelVector; }

    void addReactionChannel(ReactionChannel &reactionChannel);
    /**
     * \brief Print the volume details: Print each reaction channel
     */
    void printVolume() const;
};

#endif