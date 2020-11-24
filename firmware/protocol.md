# ACNode Reader Protocol


## Goals

* Should be reliable, hard to corrupt
* Should be distinguishable from PN532 protocol, to allow detection of one or the other
* Should be implementable on a small, low power microcontroller

## Basic Protocol

### Framing


| Position| 0-1 | 2 | 3 | 4 - (n-1) | n |
| --- | --- | --- | --- | --- | --- | --- |
| Description | sync bytes | message type | length | payload | checksum |
| Example | 0xffdd | 0x04 | 0x12 | (dependent on message) | 0x42 |

#### Sync Bytes
*Name:* Sync bytes
*Count:* 2
*Description:* Two bytes, always 0xffdd to provide synchronisation and allow discarding of junk

*Name:* Message Type
*Count:* 1
*Description:* Type of message contained in the payload. See the table of messages below.

If the high bit (0x80) is set, the message is from the reader to the controller, otherwise it is from the controller to the reader.

*Name:* Length
*Count:* 1
*Description:* Number of bytes following, up to and including the checksum

*Name:* payload
*Count:* Variable
*Description:* Message data. See message descriptions for more details

*Name:* Checksum
*Count:* 1
*Description:* Value constructed such that bytes in the message including the checksum but excluding the sync bytes add to 0x00

### Ack/Nak

Any message sent or received should be ACKnowledged as received, or on error, NAK'd. This must occur before any other messages are sent.
If a message is not acknowledged as being received correctly, it should be resent.

The sequences are two bytes long and are as follows:

*ACK:* 0xfd02
*NAK:* 0xfd03

These sequences are chosen to allow them to be differentiated from messages, while also allowing framing to be established in case of spurious bytes

### Handling Unknown Messages
Valid but unknown messages should be ACKnowledged to avoid the other end resending them. A `Unknown Message` reply should be sent, in case the other end was expecting a response.

### Messages

| Message Code | Payload Length | Name | Direction |
| --- | --- | --- | --- |
| 0x01 | 0 | Query Reader Version | Host->Reader |
| 0x03 | 0 | Query Temperature | Host->Reader |
| 0x04 | 0 | Reset Reader | Host->Reader |
| 0x20 | 0 | Get Bootloader Status | Host->Reader |
| 0x21 | Varies | Write Firmware (Bootloader) | Host->Reader |
| 0x81 | Varies | Reader Version Response | Reader->Host |
| 0x82 | Varies | Log Message | Reader->Host |
| 0x83 | 2 | Temperature Response | Reader->Host |
| 0x7f | 1 | Unknown Message Reply | Host->Reader |
| 0xa0 | 1 | Bootloader Status Response | Reader->Host |
| 0xff | 1 | Unknown Message Reply | Reader->Host |

#### Query Reader Version (0x01)
*Description:* Get the version of the firmware running on the board
*Direction:* Host->Reader
*Payload:* None

#### Query Reader Version (0x03)
*Description:* Get the temperature of the board
*Direction:* Host->Reader
*Payload:* None

#### Reset Reader (0x04)
*Description:* Reset the reader CPU
*Direction:* Host->Reader
*Payload:* None

#### Query Bootloader Status (0x20)
*Description:* Get the status of the bootloader
*Direction:* Host->Reader
*Payload:* None

#### Write Firmware (Bootloader) (0x21)
*Description:* Write firmware when in bootloader mode
*Direction:* Host->Reader
*Payload:*

| 0-1 | 2-n |
| Address of first byte | up to 128 bytes of data |

The address of the first byte must be the boundary of a page

#### Reader Version Response (0x81)
*Description:* Response to `Query Reader Version`
*Direction:* Host->Reader
*Payload:* 

| 0 | 1 | 2 | 3-n | n+1 | n+1+m |
| --- | --- | --- | --- | --- | --- |
| Major Version | Minor Version | Build Date Length | Build Date String | Git Hash Length | Git Hash String |

#### Log Message (0x82)
*Description:* Log Message from Reader
*Direction:* Reader->Host
*Payload:* 

| 0 | 1 | 2-n | n+1 | n+1 - end |
| --- | --- | --- |
| Level | Context Length | Context | Message Length | MessageString |

| Numeric Level | Level Name |
| 0 | Error |
| 1 | Warning |
| 2 | Informational |
| 3 | Debug |

#### Temperature Response (0x83)
*Description:* Temperature Reading from Reader
*Direction:* Reader->Host
*Payload:*
| 0 | 1 |
| Integer Temperature | Fractional Temperature |

Temperature is given in celcius. The high bit is of the integer part is the sign bit. 

You can treat this as a 15 bit integer and divide by 256.

#### Bootloader Status Response (0xa0)
*Description:* Details of bootloader status from reader
*Direction:* Reader->Host
*Payload:*
| 0 |
| State (see below) |

| Numeric State | Description |
| 0 | Not in bootloader |
| 1 | Idle |
| 2 | Busy |

#### Unknown Message Reply (0x7f or 0xff)
*Description:* Reply to unknown message
*Direction:* Host->Reader or Reader->Host
*Payload:* 1 byte - message code of unknown message
