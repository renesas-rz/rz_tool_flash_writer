/*
 * dmac_reg.h
 *
 *  Created on: 2021/03/16
 *      Author:
 */
#ifndef DMAC_REG_H_
#define DMAC_REG_H_

/* AXI */
#define DMAC_N0SA	        (0x0000)
#define DMAC_N0DA	        (0x0004)
#define DMAC_N0TB	        (0x0008)
#define DMAC_N1SA	        (0x000C)
#define DMAC_N1DA	        (0x0010)
#define DMAC_N1TB	        (0x0014)
#define DMAC_CRSA	        (0x0018)
#define DMAC_CRDA	        (0x001C)
#define DMAC_CRTB	        (0x0020)
#define DMAC_CHSTAT	        (0x0024)
#define DMAC_CHSTAT_ER		(0x01 << 4)
#define DMAC_CHSTAT_TACT	(0x01 << 2)
#define DMAC_CHSTAT_EN		(0x01 << 0)
#define DMAC_CHCTRL	        (0x0028)
#define DMAC_CHCTRL_SWRST	(0x01 << 3)
#define DMAC_CHCTRL_STG		(0x01 << 2)
#define DMAC_CHCTRL_SETEN	(0x01 << 0)
#define DMAC_CHCFG	        (0x002C)
#define DMAC_CHCFG_DMS	    (0x01 << 31)
#define DMAC_CHCFG_REN	    (0x01 << 30)
#define DMAC_CHCFG_RSW	    (0x01 << 29)
#define DMAC_CHCFG_RSEL	    (0x01 << 28)
#define DMAC_CHCFG_DEM	    (0x01 << 24)
#define DMAC_CHCFG_TM	    (0x01 << 22)
#define DMAC_CHCFG_DAD	    (0x01 << 21)
#define DMAC_CHCFG_SAD	    (0x01 << 20)
#define DMAC_CHCFG_DDS_SHIFT	(16)
#define DMAC_CHCFG_DDS	    (0x0F << DMAC_CHCFG_DDS_SHIFT)
#define DMAC_CHCFG_SDS_SHIFT	(12)
#define DMAC_CHCFG_SDS	    (0x0F << DMAC_CHCFG_SDS_SHIFT)
#define DMAC_CHCFG_AM_SHIFT	(8)
#define DMAC_CHCFG_AM	    (0x07 << DMAC_CHCFG_AM_SHIFT)
#define DMAC_CHCFG_LVL	    (0x01 << 6)
#define DMAC_CHCFG_HIEN	    (0x01 << 5)
#define DMAC_CHCFG_LOEN	    (0x01 << 4)
#define DMAC_CHCFG_REQD	    (0x01 << 3)
#define DMAC_CHCFG_SEL_SHIFT	    (0)
#define DMAC_CHCFG_SEL	    (0x07 << DMAC_CHCFG_SEL_SHIFT)
#define DMAC_CHITVL	        (0x0030)
#define DMAC_CHEXT	        (0x0034)
#define DMAC_NXLA	        (0x0038)
#define DMAC_CRLA	        (0x003C)

/* AXI (Common for 0 to 7) */
#define DMAC_DCTRL_0_7      (0x0300)
#define DMAC_DSTAT_EN_0_7   (0x0310)
#define DMAC_DSTAT_ER_0_7   (0x0314)
#define DMAC_DSTAT_END_0_7  (0x0318)
#define DMAC_DSTAT_TC_0_7   (0x031C)
#define DMAC_DSTAT_SUS_0_7  (0x0320)

/* AXI (Common for 8 to 15) */
#define DMAC_DCTRL_8_15     (0x0700)
#define DMAC_DSTAT_EN_8_15  (0x0710)
#define DMAC_DSTAT_ER_8_15  (0x0714)
#define DMAC_DSTAT_END_8_15 (0x0718)
#define DMAC_DSTAT_TC_8_15  (0x071C)
#define DMAC_DSTAT_SUS_8_15 (0x0720)

/* APB */
#define DMAC_DMARS0	        (0x0000)
#define DMAC_DMARS1	        (0x0004)
#define DMAC_DMARS2	        (0x0008)
#define DMAC_DMARS3	        (0x000C)
#define DMAC_DMARS4	        (0x0010)
#define DMAC_DMARS5	        (0x0014)
#define DMAC_DMARS6	        (0x0018)
#define DMAC_DMARS7	        (0x001C)

#endif /* DMAC_REG_H_ */
