# EMOS
EMOS (Enhanced Multiplayer Online System) v0.1a

The Enhanced Multiplayer Online System or EMOS is built for making Online Games easier to create in Unreal Engine 4 projects. This
project is not intended to be a direct replacement to UnrealEngine 4's existing Network System, but instead as a compliment to the
existing system.

Some features include:

MongoDB. The connector is pre-built and the server files are included in the build, and ready to go when you are.
* The Database module only works on windows server, but in the future have the includes necessary built to support linux, and mac 
server varients.

Websockettpp. This is an additional Websockets module used to do websocket communications, No more trying to build Socket communication
protocols, Utilize the UnrealEngine 4 UStruct objects as communication messages.

Multiple 'GameType' Plugins will be included. Such as RPG, MOBA, FirstPersonShooter, and Platformer. These will be built along the way
to test the various systems included in EMOS. Each gametype plugin will be designed specifically around the multiplayer experience for
the specific game type and will most likely not work in a 'single player' envrionement.

EMOSRPG: The RPG Plugin to make Online RPG Related Games. Whether FirstPerson, ThirdPerson, or a Combination of the 2. This system is
designed with the most generic properties that all RPG's contain. This should be extended by your own project, but can be used
right out of the box

EMOSRPG Features
  * Patch Services
  * Account Services
  * Chat Services
  * In-game Mail Services
  * Consignment / AuctionHouse Services
  * Enchanting Services
  * Character Services
  * Crafting System
  * Storage Services (Account, Character, Inventory)
  * Social Services (Faction / Guilds / Parties)
  * Instance Area Services
  * Server Load Balancing
  * Combat Services
  * Quest and Dialog Services
  * Server2Server Communications
