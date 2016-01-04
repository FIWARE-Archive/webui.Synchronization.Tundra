// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

// Login
const unsigned long cLoginMessage = 100;
const unsigned long cLoginReplyMessage = 101;
const unsigned long cClientJoinedMessage = 102;
const unsigned long cClientLeftMessage = 103;

// Interest management
/// @todo const unsigned long cSetObserverMessage = 104; // Server->client, tells what entity to use as the observer
/// The message would contain a scene ID and an entity reference (ID or name) of the desired observer entity.
/// This message would allow the server to tell what entity the client must use as the observer when the client joins the server.
/// The message could also be client->server and use to negotiate various observer settings (cutoff radius etc.)
/// @todo ObserverPosition message could be made server->client also to tell the initial position, or to force the position, of the observer.
const unsigned long cObserverPositionMessage = 105; // Client->server currently

// Scenesync
// NOTE 106-108 should be reserved for Scene messages (Create, EditProperties, Remove)
const unsigned long cEditEntityPropertiesMessage = 109;
const unsigned long cCreateEntityMessage = 110;
const unsigned long cCreateComponentsMessage = 111;
const unsigned long cCreateAttributesMessage = 112;
const unsigned long cEditAttributesMessage = 113;
const unsigned long cRemoveAttributesMessage = 114;
const unsigned long cRemoveComponentsMessage = 115;
const unsigned long cRemoveEntityMessage = 116;
const unsigned long cCreateEntityReplyMessage = 117; // Server->client only
const unsigned long cCreateComponentsReplyMessage = 118; // Server->client only
const unsigned long cRigidBodyUpdateMessage = 119;

// Entity action
const unsigned long cEntityActionMessage = 120;

// Assets
const unsigned long cAssetDiscoveryMessage = 121;
const unsigned long cAssetDeletedMessage = 122;

// Custom component types
const unsigned long cRegisterComponentTypeMessage = 123;

// Entity parenting
const unsigned long cSetEntityParentMessage = 124;

// In case of network message structs are regenerated and descriptions get deleted., saving their descriptions here.
// MsgAssetDeleted: Network message informing that asset has been deleted from storage.
// MsgAssetDiscovery: Network message informing that new asset has been discovered in storage.
// MsgClientJoined: Network message informing that client has joined the server.
// MsgClientLeft: Network message informing that client has left the server.
// MsgEntityAction: Network message for entity-action replication.
// MsgLogin: Network message for login request.
// MsgLoginReply: Network message for login reply.
