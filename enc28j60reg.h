#ifndef _ENC28J60REG_H_
#define _ENC28J60REG_H_

//SPI INSTRUCTION SET

#define ENC28j60_RCR 0x00
#define ENC28j60_RBM  0x3A
#define ENC28j60_WCR 0x40
#define ENC28j60_WBM 0x7A
#define ENC28j60_BFS  0x80
#define ENC28j60_BFC 0xA0
#define ENC28j60_SOFTRESET 0xFF

//Bank and reg type definition 
//The maximum size of the register ends with 0x1F therfore it's possible to use the last 3 bits to mask the
//bank and if the register is an ETH or (MII, MAC) register

#define ENC28j60_BANK0 0x00
#define ENC28j60_BANK1 0x20
#define ENC28j60_BANK2 0x40
#define ENC28j60_BANK3 0x60

#define ENC28j60_ETH 0x80

#define ENC28j60_NOREGEXTENSION 0x1F

// BANK 0

#define ENC28j60_ERDPTL ( 0x00 | ENC28j60_ETH )
#define ENC28j60_ERDPTH ( 0x01 | ENC28j60_ETH )

#define ENC28j60_EWRPTL ( 0x02 | ENC28j60_ETH )
#define ENC28j60_EWRPTH ( 0x03 | ENC28j60_ETH )

#define ENC28j60_ETXSTL ( 0x04 | ENC28j60_ETH )
#define ENC28j60_ETXSTH ( 0x05 | ENC28j60_ETH )

#define ENC28j60_ETXNDL ( 0x06 | ENC28j60_ETH )
#define ENC28j60_ETXNDH ( 0x07 | ENC28j60_ETH )

#define ENC28j60_ERXSTL ( 0x08 | ENC28j60_ETH )
#define ENC28j60_ERXSTH ( 0x09 | ENC28j60_ETH )

#define ENC28j60_ERXNDL ( 0x0A | ENC28j60_ETH )
#define ENC28j60_ERXNDH ( 0x0B | ENC28j60_ETH )

#define ENC28j60_ERXRDPTL ( 0x0C | ENC28j60_ETH )
#define ENC28j60_ERXRDPTH ( 0x0D | ENC28j60_ETH )

#define ENC28j60_ERXWRPTL ( 0x0E | ENC28j60_ETH )
#define ENC28j60_ERXWRPTH ( 0x0F | ENC28j60_ETH )

#define ENC28j60_EDMASTL ( 0x10 | ENC28j60_ETH )
#define ENC28j60_EDMASTH ( 0x11 | ENC28j60_ETH )

#define ENC28j60_EDMANDL ( 0x12 | ENC28j60_ETH )
#define ENC28j60_EDMANDH ( 0x13 | ENC28j60_ETH )

#define ENC28j60_EDMADSTL ( 0x14 | ENC28j60_ETH )
#define ENC28j60_EDMADSTH ( 0x15 | ENC28j60_ETH )

#define ENC28j60_EDMACSL ( 0x16 | ENC28j60_ETH )
#define ENC28j60_EDMACSH ( 0x17 | ENC28j60_ETH )


//ENC28j60_BANK1 

#define ENC28j60_EHT0 ( 0x00 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EHT1 ( 0x01 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EHT2 ( 0x02 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EHT3 ( 0x03 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EHT4 ( 0x04 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EHT5 ( 0x05 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EHT6 ( 0x06 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EHT7 ( 0x07 | ENC28j60_BANK1  | ENC28j60_ETH )

#define ENC28j60_EPMM0 ( 0x08 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMM1 ( 0x09 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMM2 ( 0x0A | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMM3 ( 0x0B | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMM4 ( 0x0C | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMM5 ( 0x0D | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMM6 ( 0x0E | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMM7 ( 0x0F | ENC28j60_BANK1  | ENC28j60_ETH )

#define ENC28j60_EPMCSL ( 0x10 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMCSH ( 0x11 | ENC28j60_BANK1  | ENC28j60_ETH )

#define ENC28j60_EPMOL ( 0x14 | ENC28j60_BANK1  | ENC28j60_ETH )
#define ENC28j60_EPMOH ( 0x15 | ENC28j60_BANK1  | ENC28j60_ETH )
 
#define ENC28j60_EWOLIE ( 0x16 | ENC28j60_BANK1 | ENC28j60_ETH )
#define ENC28j60_EWOLIR ( 0x17 | ENC28j60_BANK1 | ENC28j60_ETH )

#define ENC28j60_ERXFCON ( 0x18 | ENC28j60_BANK1  | ENC28j60_ETH )

#define ENC28j60_EPKTCNT ( 0x19 | ENC28j60_BANK1  | ENC28j60_ETH )
 
//ENC28j60_BANK2

#define ENC28j60_MACON1 ( 0x00 | ENC28j60_BANK2 )
#define ENC28j60_MACON2 ( 0x01 | ENC28j60_BANK2 )
#define ENC28j60_MACON3 ( 0x02 | ENC28j60_BANK2 )
#define ENC28j60_MACON4 ( 0x03 | ENC28j60_BANK2 )

#define ENC28j60_MABBIPG ( 0x04 | ENC28j60_BANK2 )

#define ENC28j60_MAIPGL ( 0x06 | ENC28j60_BANK2 )
#define ENC28j60_MAIPGH ( 0x07 | ENC28j60_BANK2 )

#define ENC28j60_MACLCON1 ( 0x08 | ENC28j60_BANK2 )
#define ENC28j60_MACLCON2 ( 0x09 | ENC28j60_BANK2 )

#define ENC28j60_MAMXFLL ( 0x0A | ENC28j60_BANK2 )
#define ENC28j60_MAMXFLH ( 0x0B | ENC28j60_BANK2 )
 
#define ENC28j60_MAPHSUP ( 0x0D | ENC28j60_BANK2 )
 
#define ENC28j60_MICON ( 0x11 | ENC28j60_BANK2 )

#define ENC28j60_MICMD ( 0x12 | ENC28j60_BANK2 )

#define ENC28j60_MIREGADR ( 0x14 | ENC28j60_BANK2 )

#define ENC28j60_MIWRL ( 0x16 | ENC28j60_BANK2 )
#define ENC28j60_MIWRH ( 0x17 | ENC28j60_BANK2 )

#define ENC28j60_MIRDL ( 0x18 | ENC28j60_BANK2 )
#define ENC28j60_MIRDH ( 0x19 | ENC28j60_BANK2 )

//ENC28j60_BANK3

#define ENC28j60_MAADR1 ( 0x00 | ENC28j60_BANK3 )
#define ENC28j60_MAADR0 ( 0x01 | ENC28j60_BANK3 )
#define ENC28j60_MAADR3 ( 0x02 | ENC28j60_BANK3 )
#define ENC28j60_MAADR2 ( 0x03 | ENC28j60_BANK3 )
#define ENC28j60_MAADR5 ( 0x04 | ENC28j60_BANK3 )
#define ENC28j60_MAADR4 ( 0x05 | ENC28j60_BANK3 )

#define ENC28j60_EBSTSD ( 0x06 | ENC28j60_BANK3 | ENC28j60_ETH )

#define ENC28j60_EBSTCON ( 0x07 | ENC28j60_BANK3 | ENC28j60_ETH )

#define ENC28j60_EBSTCSL ( 0x08 | ENC28j60_BANK3 | ENC28j60_ETH )
#define ENC28j60_EBSTCSH ( 0x09 | ENC28j60_BANK3 | ENC28j60_ETH )

#define ENC28j60_MISTAT ( 0x0A | ENC28j60_BANK3 )

#define ENC28j60_EREVID ( 0x12 | ENC28j60_BANK3 | ENC28j60_ETH )

#define ENC28j60_ECOCON ( 0x15 | ENC28j60_BANK3 | ENC28j60_ETH )

#define ENC28j60_EFLOCON ( 0x17 | ENC28j60_BANK3 | ENC28j60_ETH )

#define ENC28j60_EPAUSL ( 0x18 | ENC28j60_BANK3 | ENC28j60_ETH )
#define ENC28j60_EPAUSH ( 0x19 | ENC28j60_BANK3 | ENC28j60_ETH )

#define ENC28j60_EIE ( 0x1B | ENC28j60_ETH )
#define ENC28j60_EIR ( 0x1C | ENC28j60_ETH )

#define ENC28j60_ESTAT ( 0x1D | ENC28j60_ETH )

#define ENC28j60_ECON2 ( 0x1E | ENC28j60_ETH )
#define ENC28j60_ECON1 ( 0x1F | ENC28j60_ETH )
 
 //PHY
 
#define ENC28j60_PHCON1 0x00
#define ENC28j60_PHSTAT1 0x01

#define ENC28j60_PHID1 0x02
#define ENC28j60_PHID2 0x03

#define ENC28j60_PHCON2 0x10
#define ENC28j60_PHSTAT2 0x11

#define ENC28j60_PHIE 0x12
#define ENC28j60_PHIR 0x13

#define ENC28j60_PHLCON 0x14
 
 
//REGISTER PARAMETER

#define ENC28j60_EIE_INTIE 0x80
#define ENC28j60_EIE_PKTIE 0x40
#define ENC28j60_EIE_DMAIE 0x20
#define ENC28j60_EIE_LINKIE 0x10
#define ENC28j60_EIE_TXIE 0x08
#define ENC28j60_EIE_WOLIE 0x04
#define ENC28j60_EIE_TXERIE 0x02
#define ENC28j60_EIE_RXERIE 0x01

#define ENC28j60_EIR_PKTIF 0x40
#define ENC28j60_EIR_DMAIF 0x20
#define ENC28j60_EIR_LINKIF 0x10
#define ENC28j60_EIR_TXIF 0x08
#define ENC28j60_EIR_WOLIF 0x04
#define ENC28j60_EIR_TXERIF 0x02
#define ENC28j60_EIR_RXERIF 0x01

#define ENC28j60_ESTAT_INT 0x80
#define ENC28j60_ESTAT_LATECOL 0x10
#define ENC28j60_ESTAT_RXBUSY 0x04
#define ENC28j60_ESTAT_TXABRT 0x02
#define ENC28j60_ESTAT_CLKRDY 0x01

#define ENC28j60_ECON2_AUTOINC 0x80
#define ENC28j60_ECON2_PKTDEC 0x40
#define ENC28j60_ECON2_PWRSV 0x20
#define ENC28j60_ECON2_VRPS 0x08

#define ENC28j60_ECON1_TXRST 0x80
#define ENC28j60_ECON1_RXRST 0x40
#define ENC28j60_ECON1_DMAST 0x20
#define ENC28j60_ECON1_CSUMEN 0x10
#define ENC28j60_ECON1_TXRTS 0x08
#define ENC28j60_ECON1_RXEN 0x04
#define ENC28j60_ECON1_BSEL1 0x02
#define ENC28j60_ECON1_BSEL0 0x01

#define ENC28j60_EWOLIE_UCWOLIE 0x80
#define ENC28j60_EWOLIE_AWOLIE 0x40
#define ENC28j60_EWOLIE_PMWOLIE 0x10
#define ENC28j60_EWOLIE_MPWOLIE 0x08
#define ENC28j60_EWOLIE_HTWOLIE 0x04
#define ENC28j60_EWOLIE_MCWOLIE 0x02
#define ENC28j60_EWOLIE_BCWOLIE 0x01

#define ENC28j60_EWOLIR_UCWOLIF 0x80
#define ENC28j60_EWOLIR_AWOLIF 0x40
#define ENC28j60_EWOLIR_PMWOLIF 0x10
#define ENC28j60_EWOLIR_MPWOLIF 0x08
#define ENC28j60_EWOLIR_HTWOLIF 0x04
#define ENC28j60_EWOLIR_MCWOLIF 0x02
#define ENC28j60_EWOLIR_BCWOLIF 0x01

#define ENC28j60_ERXFCON_UCEN 0x80
#define ENC28j60_ERXFCON_ANDOR 0x40
#define ENC28j60_ERXFCON_CRCEN 0x20
#define ENC28j60_ERXFCON_PMEN 0x10
#define ENC28j60_RXFCON_MPEN 0x08
#define ENC28j60_ERXFCON_HTEN 0x04
#define ENC28j60_ERXFCON_MCEN 0x02
#define ENC28j60_ERXFCON_BCEN 0x01

#define ENC28j60_MACON1_LOOPBK 0x10
#define ENC28j60_MACON1_TXPAUS 0x08
#define ENC28j60_MACON1_RXPAUS 0x04
#define ENC28j60_MACON1_PASSALL 0x02
#define ENC28j60_MACON1_MARXEN 0x01

#define ENC28j60_MACON2_MARST 0x80
#define ENC28j60_MACON2_RNDRST 0x40
#define ENC28j60_MACON2_MARXRST 0x08
#define ENC28j60_MACON2_RFUNRST 0x04
#define ENC28j60_MACON2_MATXRST 0x02
#define ENC28j60_MACON2_TFUNRST 0x01

#define ENC28j60_MACON3_PADCFG2 0x80
#define ENC28j60_MACON3_PADCFG1 0x40
#define ENC28j60_MACON3_PADCFG0 0x20
#define ENC28j60_MACON3_TXCRCEN 0x10
#define ENC28j60_MACON3_PHDRLEN 0x08
#define ENC28j60_MACON3_HFRMEN 0x04
#define ENC28j60_MACON3_FRMLNEN 0x02
#define ENC28j60_MACON3_FULDPX 0x01

#define ENC28j60_MACON4_DEFER 0x40
#define ENC28j60_MACON4_BPEN 0x20
#define ENC28j60_MACON4_NOBKOFF 0x10
#define ENC28j60_MACON4_LONGPRE 0x02
#define ENC28j60_MACON4_PUREPRE 0x01

#define ENC28j60_MAPHSUP_RSTINTFC 0x80
#define ENC28j60_MAPHSUP_RSTRMII 0x08

#define ENC28j60_MICON_RSTMII 0x80

#define ENC28j60_MICMD_MIISCAN 0x02
#define ENC28j60_MICMD_MIIRD 0x01
 
#define ENC28j60_EBSTCON_PSV2 0x80
#define ENC28j60_EBSTCON_PSV1 0x40
#define ENC28j60_EBSTCON_PSV0 0x20
#define ENC28j60_EBSTCON_PSEL 0x10
#define ENC28j60_EBSTCON_TMSEL1 0x08
#define ENC28j60_EBSTCON_TMSEL0 0x04
#define ENC28j60_EBSTCON_TME 0x02
#define ENC28j60_EBSTCON_BISTST 0x01

#define ENC28j60_MISTAT_NVALID 0x04
#define ENC28j60_MISTAT_SCAN 0x02
#define ENC28j60_MISTAT_BUSY 0x01

#define ENC28j60_ECOCON_COCON2 0x04
#define ENC28j60_ECOCON_COCON1 0x02
#define ENC28j60_ECOCON_COCON0 0x01

#define ENC28j60_EFLOCON_FULDPXS 0x04
#define ENC28j60_EFLOCON_FCEN1 0x02
#define ENC28j60_EFLOCON_FCEN0 0x01

//PHY Parameters

#define ENC28j60_PHCON1_PRST 0x8000
#define ENC28j60_PHCON1_PLOOPBK 0x4000
#define ENC28j60_PHCON1_PPWRSV 0x0800
#define ENC28j60_PHCON1_PDPXMD 0x0100

#define ENC28j60_PHSTAT1_PFDPX 0x1000
#define ENC28j60_PHSTAT1_PHDPX 0x0800
#define ENC28j60_PHSTAT1_LLSTAT 0x0004
#define ENC28j60_PHSTAT1_JBSTAT 0x0002

#define ENC28j60_PHCON2_FRCLNK 0x4000
#define ENC28j60_PHCON2_TXDIS 0x2000
#define ENC28j60_PHCON2_JABBER 0x0400
#define ENC28j60_PHCON2_HDLDIS 0x0100

#define ENC28j60_PHSTAT2_TXSTAT 0x2000
#define ENC28j60_PHSTAT2_RXSTAT 0x1000
#define ENC28j60_PHSTAT2_COLSTAT 0x0800
#define ENC28j60_PHSTAT2_LSTAT 0x0400
#define ENC28j60_PHSTAT2_DPXSTAT 0x0200
#define ENC28j60_PHSTAT2_PLRITY 0x0010

#define ENC28j60_PHIE_PLNKIE 0x0010
#define ENC28j60_PHIE_PGEIE 0x0002

#define ENC28j60_PHIR_PLNKIF 0x0010
#define ENC28j60_PHIR_PGIF 0x0004

#endif