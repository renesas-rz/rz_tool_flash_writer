#include "common.h"

#ifndef DMAC_H_
#define DMAC_H_

typedef enum {
	DMAC_ERRCODE_SUCCESS = 0,
	DMAC_ERRCODE_ERROR = 1
} dmac_errcode_t;

typedef struct {
	uint8_t		ch;
	uint64_t	axi_base;
	uint64_t	src_addr;
	uint64_t	dst_addr;
	uint32_t	transfer_byte;
	uint8_t		non_secure_flag;
	uint8_t		rsel;
} dmac_setting_t;

void dmac_init(dmac_setting_t *setting);
dmac_errcode_t dmac_transfer_endless(dmac_setting_t *setting);
dmac_errcode_t dmac_transfer_single(dmac_setting_t *setting);

#endif /* DMAC_H_ */
