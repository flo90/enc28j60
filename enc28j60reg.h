#ifndef _ENC28J60REG_H_
#define _ENC28J60REG_H_

//SPI INSTRUCTION SET

#define RCR 0x00
#define RBM  0x3A
#define WCR 0x40
#define WBM 0x7A
#define BFS  0x80
#define BFC 0xA0
#define SOFTRESET 0xFF

//Bank and reg type definition 
//The maximum size of the register ends with 0x1F therfore it's possible to use the last 3 bits to mask the
//bank and if the register is an ETH or (MII, MAC) register

#define BANK0 0x00
#define BANK1 0x20
#define BANK2 0x40
#define BANK3 0x60

#define ETH 0x80

#define NOREGEXTENSION 0x1F

// BANK 0

#define ERDPTL ( 0x00 | ETH )
#define ERDPTH ( 0x01 | ETH )

#define EWRPTL ( 0x02 | ETH )
#define EWRPTH ( 0x03 | ETH )

#define ETXSTL ( 0x04 | ETH )
#define ETXSTH ( 0x05 | ETH )

#define ETXNDL ( 0x06 | ETH )
#define ETXNDH ( 0x07 | ETH )

#define ERXSTL ( 0x08 | ETH )
#define ERXSTH ( 0x09 | ETH )

#define ERXNDL ( 0x0A | ETH )
#define ERXNDH ( 0x0B | ETH )

#define ERXRDPTL ( 0x0C | ETH )
#define ERXRDPTH ( 0x0D | ETH )

#define ERXWRPTL ( 0x0E | ETH )
#define ERXWRPTH ( 0x0F | ETH )

#define EDMASTL ( 0x10 | ETH )
#define EDMASTH ( 0x11 | ETH )

#define EDMANDL ( 0x12 | ETH )
#define EDMANDH ( 0x13 | ETH )

#define EDMADSTL ( 0x14 | ETH )
#define EDMADSTH ( 0x15 | ETH )

#define EDMACSL ( 0x16 | ETH )
#define EDMACSH ( 0x17 | ETH )


//BANK1 

#define EHT0 ( 0x00 | BANK1  | ETH )
#define EHT1 ( 0x01 | BANK1  | ETH )
#define EHT2 ( 0x02 | BANK1  | ETH )
#define EHT3 ( 0x03 | BANK1  | ETH )
#define EHT4 ( 0x04 | BANK1  | ETH )
#define EHT5 ( 0x05 | BANK1  | ETH )
#define EHT6 ( 0x06 | BANK1  | ETH )
#define EHT7 ( 0x07 | BANK1  | ETH )

#define EPMM0 ( 0x08 | BANK1  | ETH )
#define EPMM1 ( 0x09 | BANK1  | ETH )
#define EPMM2 ( 0x0A | BANK1  | ETH )
#define EPMM3 ( 0x0B | BANK1  | ETH )
#define EPMM4 ( 0x0C | BANK1  | ETH )
#define EPMM5 ( 0x0D | BANK1  | ETH )
#define EPMM6 ( 0x0E | BANK1  | ETH )
#define EPMM7 ( 0x0F | BANK1  | ETH )

#define EPMCSL ( 0x10 | BANK1  | ETH )
#define EPMCSH ( 0x11 | BANK1  | ETH )

#define EPMOL ( 0x14 | BANK1  | ETH )
#define EPMOH ( 0x15 | BANK1  | ETH )
 
#define EWOLIE ( 0x16 | BANK1 | ETH )
#define EWOLIR ( 0x17 | BANK1 | ETH )

#define ERXFCON ( 0x18 | BANK1  | ETH )

#define EPKTCNT ( 0x19 | BANK1  | ETH )
 
//BANK2

#define MACON1 ( 0x00 | BANK2 )
#define MACON2 ( 0x01 | BANK2 )
#define MACON3 ( 0x02 | BANK2 )
#define MACON4 ( 0x03 | BANK2 )

#define MABBIPG ( 0x04 | BANK2 )

#define MAIPGL ( 0x06 | BANK2 )
#define MAIPGH ( 0x07 | BANK2 )

#define MACLCON1 ( 0x08 | BANK2 )
#define MACLCON2 ( 0x09 | BANK2 )

#define MAMXFLL ( 0x0A | BANK2 )
#define MAMXFLH ( 0x0B | BANK2 )
 
#define MAPHSUP ( 0x0D | BANK2 )
 
#define MICON ( 0x11 | BANK2 )

#define MICMD ( 0x12 | BANK2 )

#define MIREGADR ( 0x14 | BANK2 )

#define MIWRL ( 0x16 | BANK2 )
#define MIWRH ( 0x17 | BANK2 )

#define MIRDL ( 0x18 | BANK2 )
#define MIRDH ( 0x19 | BANK2 )

//BANK3

#define MAADR1 ( 0x00 | BANK3 )
#define MAADR0 ( 0x01 | BANK3 )
#define MAADR3 ( 0x02 | BANK3 )
#define MAADR2 ( 0x03 | BANK3 )
#define MAADR5 ( 0x04 | BANK3 )
#define MAADR4 ( 0x05 | BANK3 )

#define EBSTSD ( 0x06 | BANK3 | ETH )

#define EBSTCON ( 0x07 | BANK3 | ETH )

#define EBSTCSL ( 0x08 | BANK3 | ETH )
#define EBSTCSH ( 0x09 | BANK3 | ETH )

#define MISTAT ( 0x0A | BANK3 )

#define EREVID ( 0x12 | BANK3 | ETH )

#define ECOCON ( 0x15 | BANK3 | ETH )

#define EFLOCON ( 0x17 | BANK3 | ETH )

#define EPAUSL ( 0x18 | BANK3 | ETH )
#define EPAUSH ( 0x19 | BANK3 | ETH )

#define EIE ( 0x1B | ETH )
#define EIR ( 0x1C | ETH )

#define ESTAT ( 0x1D | ETH )

#define ECON2 ( 0x1E | ETH )
#define ECON1 ( 0x1F | ETH )
 
 //PHY
 
#define PHCON1 0x00
#define PHSTAT1 0x01

#define PHID1 0x02
#define PHID2 0x03

#define PHCON2 0x10
#define PHSTAT2 0x11

#define PHIE 0x12
#define PHIR 0x13

#define PHLCON 0x14
 
 
//REGISTER PARAMETER

#define EIE_INTIE 0x80
#define EIE_PKTIE 0x40
#define EIE_DMAIE 0x20
#define EIE_LINKIE 0x10
#define EIE_TXIE 0x08
#define EIE_WOLIE 0x04
#define EIE_TXERIE 0x02
#define EIE_RXERIE 0x01

#define EIR_PKTIF 0x40
#define EIR_DMAIF 0x20
#define EIR_LINKIF 0x10
#define EIR_TXIF 0x08
#define EIR_WOLIF 0x04
#define EIR_TXERIF 0x02
#define EIR_RXERIF 0x01

#define ESTAT_INT 0x80
#define ESTAT_LATECOL 0x10
#define ESTAT_RXBUSY 0x04
#define ESTAT_TXABRT 0x02
#define ESTAT_CLKRDY 0x01

#define ECON2_AUTOINC 0x80
#define ECON2_PKTDEC 0x40
#define ECON2_PWRSV 0x20
#define ECON2_VRPS 0x08

#define ECON1_TXRST 0x80
#define ECON1_RXRST 0x40
#define ECON1_DMAST 0x20
#define ECON1_CSUMEN 0x10
#define ECON1_TXRTS 0x08
#define ECON1_RXEN 0x04
#define ECON1_BSEL1 0x02
#define ECON1_BSEL0 0x01

#define EWOLIE_UCWOLIE 0x80
#define EWOLIE_AWOLIE 0x40
#define EWOLIE_PMWOLIE 0x10
#define EWOLIE_MPWOLIE 0x08
#define EWOLIE_HTWOLIE 0x04
#define EWOLIE_MCWOLIE 0x02
#define EWOLIE_BCWOLIE 0x01

#define EWOLIR_UCWOLIF 0x80
#define EWOLIR_AWOLIF 0x40
#define EWOLIR_PMWOLIF 0x10
#define EWOLIR_MPWOLIF 0x08
#define EWOLIR_HTWOLIF 0x04
#define EWOLIR_MCWOLIF 0x02
#define EWOLIR_BCWOLIF 0x01

#define ERXFCON_UCEN 0x80
#define ERXFCON_ANDOR 0x40
#define ERXFCON_CRCEN 0x20
#define ERXFCON_PMEN 0x10
#define ERXFCON_MPEN 0x08
#define ERXFCON_HTEN 0x04
#define ERXFCON_MCEN 0x02
#define ERXFCON_BCEN 0x01

#define MACON1_LOOPBK 0x10
#define MACON1_TXPAUS 0x08
#define MACON1_RXPAUS 0x04
#define MACON1_PASSALL 0x02
#define MACON1_MARXEN 0x01

#define MACON2_MARST 0x80
#define MACON2_RNDRST 0x40
#define MACON2_MARXRST 0x08
#define MACON2_RFUNRST 0x04
#define MACON2_MATXRST 0x02
#define MACON2_TFUNRST 0x01

#define MACON3_PADCFG2 0x80
#define MACON3_PADCFG1 0x40
#define MACON3_PADCFG0 0x20
#define MACON3_TXCRCEN 0x10
#define MACON3_PHDRLEN 0x08
#define MACON3_HFRMEN 0x04
#define MACON3_FRMLNEN 0x02
#define MACON3_FULDPX 0x01

#define MACON4_DEFER 0x40
#define MACON4_BPEN 0x20
#define MACON4_NOBKOFF 0x10
#define MACON4_LONGPRE 0x02
#define MACON4_PUREPRE 0x01

#define MAPHSUP_RSTINTFC 0x80
#define MAPHSUP_RSTRMII 0x08

#define MICON_RSTMII 0x80

#define MICMD_MIISCAN 0x02
#define MICMD_MIIRD 0x01
 
#define EBSTCON_PSV2 0x80
#define EBSTCON_PSV1 0x40
#define EBSTCON_PSV0 0x20
#define EBSTCON_PSEL 0x10
#define EBSTCON_TMSEL1 0x08
#define EBSTCON_TMSEL0 0x04
#define EBSTCON_TME 0x02
#define EBSTCON_BISTST 0x01

#define MISTAT_NVALID 0x04
#define MISTAT_SCAN 0x02
#define MISTAT_BUSY 0x01

#define ECOCON_COCON2 0x04
#define ECOCON_COCON1 0x02
#define ECOCON_COCON0 0x01

#define EFLOCON_FULDPXS 0x04
#define EFLOCON_FCEN1 0x02
#define EFLOCON_FCEN0 0x01

//PHY Parameters

#define PHCON1_PRST 0x8000
#define PHCON1_PLOOPBK 0x4000
#define PHCON1_PPWRSV 0x0800
#define PHCON1_PDPXMD 0x0100

#define PHSTAT1_PFDPX 0x1000
#define PHSTAT1_PHDPX 0x0800
#define PHSTAT1_LLSTAT 0x0004
#define PHSTAT1_JBSTAT 0x0002

#define PHCON2_FRCLNK 0x4000
#define PHCON2_TXDIS 0x2000
#define PHCON2_JABBER 0x0400
#define PHCON2_HDLDIS 0x0100

#define PHSTAT2_TXSTAT 0x2000
#define PHSTAT2_RXSTAT 0x1000
#define PHSTAT2_COLSTAT 0x0800
#define PHSTAT2_LSTAT 0x0400
#define PHSTAT2_DPXSTAT 0x0200
#define PHSTAT2_PLRITY 0x0010

#define PHIE_PLNKIE 0x0010
#define PHIE_PGEIE 0x0002

#define PHIR_PLNKIF 0x0010
#define PHIR_PGIF 0x0004

#endif