/*
 * Copyright (c) 2016, Intel Corporation
 * All rights reserved.
 *
 * Author: Jérémy Compostella <jeremy.compostella@intel.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <interface.h>

#include "protocol/SdHostIo.h"
#include "sdio.h"

typedef struct sdio {
	EFI_SD_HOST_IO_PROTOCOL interface;
	storage_t *s;
} sdio_t;

static EFIAPI EFI_STATUS
sdio_send_command(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
		  __attribute__((__unused__)) UINT16 CommandIndex,
		  __attribute__((__unused__)) UINT32 Argument,
		  __attribute__((__unused__)) TRANSFER_TYPE DataType,
		  __attribute__((__unused__)) UINT8 *Buffer,
		  __attribute__((__unused__)) UINT32 BufferSize,
		  __attribute__((__unused__)) RESPONSE_TYPE ResponseType,
		  __attribute__((__unused__)) UINT32 TimeOut,
		  __attribute__((__unused__)) UINT32 *ResponseData)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_set_clock_frequency(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
			 __attribute__((__unused__)) UINT32 MaxFrequency)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_set_bus_width(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
		   __attribute__((__unused__)) UINT32 BusWidth)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_set_host_voltage(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
		      __attribute__((__unused__)) UINT32 Voltage)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_set_host_speed_mode(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
			 __attribute__((__unused__)) UINT32 HighSpeed)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_set_host_ddr_mode(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
		       __attribute__((__unused__)) UINT32 DdrMode)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_reset_sd_host(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
		   __attribute__((__unused__)) RESET_TYPE ResetType)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_enable_auto_stop_cmd(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
			  __attribute__((__unused__)) BOOLEAN Enable)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_detect_card_and_init_host(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_set_block_length(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This,
		      __attribute__((__unused__)) UINT32 BlockLength)
{
	return EFI_UNSUPPORTED;
}

static EFIAPI EFI_STATUS
sdio_setup_device(__attribute__((__unused__)) EFI_SD_HOST_IO_PROTOCOL *This)
{
	return EFI_UNSUPPORTED;
}

static EFI_GUID sdio_guid = EFI_SD_HOST_IO_PROTOCOL_GUID;

EFI_STATUS sdio_init(EFI_SYSTEM_TABLE *st, EFI_HANDLE handle, storage_t *s)
{
	EFI_STATUS ret;
	static sdio_t sdio_default = {
		.interface = {
			.Revision = 0x1,
			.HostCapability = {
				.BoundarySize = 8
			},
			.SendCommand = sdio_send_command,
			.SetClockFrequency = sdio_set_clock_frequency,
			.SetBusWidth = sdio_set_bus_width,
			.SetHostVoltage = sdio_set_host_voltage,
			.SetHostDdrMode = sdio_set_host_ddr_mode,
			.ResetSdHost = sdio_reset_sd_host,
			.EnableAutoStopCmd = sdio_enable_auto_stop_cmd,
			.DetectCardAndInitHost =sdio_detect_card_and_init_host,
			.SetBlockLength = sdio_set_block_length,
			.SetupDevice = sdio_setup_device,
			.SetHostSpeedMode = sdio_set_host_speed_mode
		}
	};
	sdio_t *sdio;

	ret = interface_init(st, &sdio_guid, &handle,
			     &sdio_default, sizeof(sdio_default),
			     (void **)&sdio);
	if (EFI_ERROR(ret))
		return ret;

	sdio->s = s;

	return EFI_SUCCESS;
}

EFI_STATUS sdio_get_storage(EFI_SD_HOST_IO_PROTOCOL *This, storage_t **storage_p)
{
	sdio_t *sdio = (sdio_t *)This;

	if (!This)
		return EFI_INVALID_PARAMETER;

	*storage_p = sdio->s;

	return EFI_SUCCESS;
}

EFI_STATUS sdio_free(EFI_SYSTEM_TABLE *st, EFI_HANDLE handle)
{
	return interface_free(st, &sdio_guid, handle);
}
