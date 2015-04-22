# Server to Client #

## When Communication will occur ##

When the client-side lobby is opened.

At the beginning of the match.

20 times per second as long as the game is running.

At the end of a match.

## What Communication will occur ##

Lobby Info: players connected/disconnected

Player info: Health, Money, and what is unlocked.

Tower info: Only when needed upon creation, firing, upgrading.

Unit info: As long as it is alive at least position. If it is not communicated delete it.

Bullet info: As long as it exists position. If it is not communicated delete it.

## Suggested vectors on Client ##

several vectors of beginning stats so they can be displayed

### Players: Not Clickable ###

"static" vector

only change when told by server, delete only at end of game

### Towers: Clickable ###

"static" vector

only change when told by server

### Units: Clickable ###

"dynamic" vector

update from communication string - delete if not present in communication string

### Shots: Not Clickable ###

"dynamic" vector

update from communication string - delete if not present in communication string

## Information Strings ##

### Key ###

COMMANDTYPE = special number denoting entity affected as well as the information sent about it

_TILES = int - number of tiles in on_axis

TEAM = int - 1 or 2(0 for none)

HEALTH = int - current health in percent

MONEY = int - current money(-1 if infinity)

DIRECTION = int - north(1), east(2), south(3), west(4)

XCOORD = int

YCOORD = int

ID = int associated with the unit

TYPE = int standing for the type of object: 1\_x - building, 2\_x - unit; x = specifictype\_lvl

example:building - 1 basic - 1, lvl - 3 -> 1\_1\_3

UNLOCK = comma delimited list of TYPE's unlocked, or to be unlocked

BUILDABLE = 0 for not, 1 for

### Initial Information Strings ###

COMMANDTYPE = 0x

Types: 4

**Type 00: Team Set**

The server will tell the client what team its on

Structure: COMMANDTYPE TEAM

**Type 01: Tile Set**

The server will tell the client what the tile sizes and positions are and whether they are buildable or not

Structure: COMMANDTYPE XTILES YTILES WIDTH HEIGHT

followed by

Structure: COMMANDTYPE XCOORD YCOORD BUILDABLE TEAM
(as many times as needed)

**Type 02: Tower Set**

The Lvl 1 stats for all towers will be sent

Structure: COMMANDTYPE TYPE ATTACK SPEED RANGE PRODUCTION COST UNLOCK
(as many times as needed)

**Type 03: Unit Set**

The Lvl 1-5 stats for all units will be sent

Structure: COMMANDTYPE TYPE HEALTH SPEED DAMAGE COST
(as many times as needed)

### Player Information Strings ###

COMMANDTYPE = 1x

Types: 4

**Type 11: Creation**

Structure: COMMANDTYPE TEAM HEALTH MONEY UNLOCK

**Type 14: Health Change**

Structure: COMMANDTYPE TEAM HEALTH

**Type 16: Money Change**

Structure: COMMANDTYPE TEAM MONEY

### Tower Information Strings ###

COMMANDTYPE = 2x

Types: 3

**Type 21: Creation**

Structure: COMMANDTYPE XCOORD YCOORD TYPE TEAM NEXTLVLATTACK NEXTLVLSPEED NEXTLVLRANGE NEXTLVLPRODUCTION NEXTLVLCOST NEXTLVLUNLOCK

**Type 28: Upgrade**

Structure: COMMANDTYPE XCOORD YCOORD NEXTLVLATTACK NEXTLVLSPEED NEXTLVLRANGE NEXTLVLPRODUCTION NEXTLVLCOST NEXTLVLUNLOCK

**Type 20: Death**

Structure: COMMANDTYPE XCOORD YCOORD

### Unit Information Strings ###

COMMANDTYPE = 3x

Types: 6

**Type 31: Creation**

Structure: COMMANDTYPE ID TYPE XCOORD YCOORD DIRECTION

**Type 32: Position Change**

Structure: COMMANDTYPE ID XCOORD YCOORD

**Type 33: Position and Direction Change**

Structure: COMMANDTYPE ID XCOORD YCOORD DIRECTION

**Type 34: Health Change**

Structure: COMMANDTYPE ID HEALTH

**Type 30: Death**

Structure: COMMANDTYPE ID

### Shot Information Strings ###

COMMANDTYPE = 4

Types: 1

Structure: COMMANDTYPE XCOORD YCOORD

### Pause ###

COMMANDTYPE = 5

# Client to Server #

## When Communication will occur ##

Send information only when a button is clicked.

## Communication Strings ##

### Start Game ###

COMMANDTYPE = 2

Structure: COMMANDTYPE

### Buy Tower Button ###

COMMANDTYPE = 1

Structure: COMMANDTYPE TYPE XCOORD YCOORD

### Buy Unit Button ###

COMMANDTYPE = 3

Structure: COMMANDTYPE TYPE TEAM

### Upgrade Button ###

COMMANDTYPE = 8

Structure: COMMANDTYPE XCOORD YCOORD

### Destroy Button ###

COMMANDTYPE = 0

Structure: COMMANDTYPE XCOORD YCOORD

### Pause Button ###

COMMANDTYPE = 5

Structure: COMMANDTYPE

### Save Button ###

COMMANDTYPE = 6

Structure: COMMANDTYPE FILENAME

### Load Button ###

COMMANDTYPE = 7

Structure: COMMANDTYPE FILENAME

### I'm Dying ###

COMMANDTYPE = 9

Structure: COMMANDTYPE TEAM