/* Copyright 2011-2018 Tyler Gilbert; 
 * This file is part of Stratify OS.
 *
 * Stratify OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stratify OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stratify OS.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 */

/*! \addtogroup ENET Ethernet
 * @{
 *
 * \ingroup IFACE_DEV
 *
 * \details
 *
 */

/*! \file
 * \brief Ethernet Header File
 *
 */

#ifndef MCU_ETH_H_
#define MCU_ETH_H_

#include "sos/dev/eth.h"

#include "sos/fs/devfs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MCU_PACK {
    eth_attr_t attr; //default attributes
} eth_config_t;

int mcu_eth_open(const devfs_handle_t * handle) MCU_ROOT_CODE;
int mcu_eth_read(const devfs_handle_t * handle, devfs_async_t * rop) MCU_ROOT_CODE;
int mcu_eth_write(const devfs_handle_t * handle, devfs_async_t * wop) MCU_ROOT_CODE;
int mcu_eth_ioctl(const devfs_handle_t * handle, int request, void * ctl) MCU_ROOT_CODE;

int mcu_eth_close(const devfs_handle_t * handle) MCU_ROOT_CODE;
int mcu_eth_getinfo(const devfs_handle_t * handle, void * ctl) MCU_ROOT_CODE;
int mcu_eth_setattr(const devfs_handle_t * handle, void * ctl) MCU_ROOT_CODE;
int mcu_eth_setaction(const devfs_handle_t * handle, void * ctl) MCU_ROOT_CODE;
int mcu_eth_setregister(const devfs_handle_t * handle, void * ctl) MCU_ROOT_CODE;
int mcu_eth_getregister(const devfs_handle_t * handle, void * ctl) MCU_ROOT_CODE;

#ifdef __cplusplus
}
#endif


#endif /* MCU_ETH_H_ */

/*! @} */