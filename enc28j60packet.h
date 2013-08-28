/*
    This file is part of the enc28j60 driver project
    Copyright (C) 2013  Florian Menne (florianmenne@t-online.de)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see [http://www.gnu.org/licenses/].
*/

#ifndef _ENC28J60PACKET_H_
#define _ENC28J60PACKET_H_

//Some important Packet types

#define PACKET_IPV4 0x0800
#define PACKET_IPV6 0x86DD

#define PACKET_ARP 0x0806
#define PACKET_WOL 0x0842

#endif