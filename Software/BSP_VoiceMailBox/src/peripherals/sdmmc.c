#include "peripherals/sdmmc.h"
#include "main.h"     // for SPI handle and GPIO
#include "spi.h"      // for hspi1 or your SPI handle

#define SD_CS_GPIO_Port GPIOA
#define SD_CS_Pin GPIO_PIN_4

#define SD_CS_LOW() HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET)
#define SD_CS_HIGH() HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET)

#define SD_BLOCK_SIZE 512

static DSTATUS Stat = STA_NOINIT;

// Helper function: send a single byte over SPI
static uint8_t spi_send(uint8_t b) 
{
    uint8_t r;
    HAL_SPI_TransmitReceive(&hspi1, &b, &r, 1, HAL_MAX_DELAY);
    return r;
}

// Helper: wait until card is ready (returns 0xFF)
static int wait_ready(void) 
{
    uint32_t t = HAL_GetTick();
    while (HAL_GetTick() - t < 500) {
        if (spi_send(0xFF) == 0xFF) return 1;
    }
    return 0;
}

// Helper: send CMD to card
static uint8_t send_cmd(uint8_t cmd, uint32_t arg, uint8_t crc) 
{
    uint8_t buf[6];
    buf[0] = 0x40 | cmd;
    buf[1] = arg >> 24;
    buf[2] = arg >> 16;
    buf[3] = arg >> 8;
    buf[4] = arg;
    buf[5] = crc;

    SD_CS_LOW();
    wait_ready();

    for (int i = 0; i < 6; i++) spi_send(buf[i]);

    // Skip dummy bytes
    for (int i = 0; i < 10; i++) {
        uint8_t r = spi_send(0xFF);
        if ((r & 0x80) == 0) return r;
    }

    return 0xFF;
}

// Disk initialization
DSTATUS MMC_disk_initialize(void) 
{
    uint8_t r;
    uint8_t i;

    SD_CS_HIGH();
    for (i = 0; i < 10; i++) spi_send(0xFF);  // 80 clock pulses

    // CMD0: go to idle
    r = send_cmd(0, 0, 0x95);
    if (r != 0x01) {
        SD_CS_HIGH();
        return STA_NOINIT;
    }

    // CMD1: initiate initialization process
    for (i = 0; i < 100; i++) {
        r = send_cmd(1, 0, 0xFF);
        if (r == 0x00) break;
        HAL_Delay(10);
    }

    SD_CS_HIGH();
    spi_send(0xFF);

    if (r == 0x00) {
        Stat &= ~STA_NOINIT;
    }
    else {
        Stat = STA_NOINIT;
    }

    return Stat;
}

DSTATUS MMC_disk_status(void) 
{
    return Stat;
}

DRESULT MMC_disk_read(BYTE* buff, DWORD  sector, UINT count)
{
    if (!count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;

    SD_CS_LOW();
    if (send_cmd(17, sector * SD_BLOCK_SIZE, 0xFF) != 0x00) {
        SD_CS_HIGH();
        return RES_ERROR;
    }

    // Wait for data token (0xFE)
    for (int i = 0; i < 10000; i++) {
        uint8_t token = spi_send(0xFF);
        if (token == 0xFE) break;
    }

    for (int i = 0; i < SD_BLOCK_SIZE; i++) {
        buff[i] = spi_send(0xFF);
    }

    // Read CRC
    spi_send(0xFF);
    spi_send(0xFF);

    SD_CS_HIGH();
    spi_send(0xFF);

    return RES_OK;
}

DRESULT MMC_disk_write(const BYTE* buff, DWORD  sector, UINT count)
{
    if (!count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;

    SD_CS_LOW();
    if (send_cmd(24, sector * SD_BLOCK_SIZE, 0xFF) != 0x00) {
        SD_CS_HIGH();
        return RES_ERROR;
    }

    spi_send(0xFE);  // Start token

    for (int i = 0; i < SD_BLOCK_SIZE; i++) {
        spi_send(buff[i]);
    }

    spi_send(0xFF);  // Dummy CRC
    spi_send(0xFF);

    uint8_t resp = spi_send(0xFF);
    if ((resp & 0x1F) != 0x05) {
        SD_CS_HIGH();
        return RES_ERROR;
    }

    while (spi_send(0xFF) == 0);

    SD_CS_HIGH();
    spi_send(0xFF);

    return RES_OK;
}

DRESULT MMC_disk_ioctl(BYTE cmd, void* buff) 
{
    switch (cmd) {
    case CTRL_SYNC:
        return RES_OK;
    case GET_SECTOR_SIZE:
        *(WORD*)buff = SD_BLOCK_SIZE;
        return RES_OK;
    case GET_BLOCK_SIZE:
        *(DWORD*)buff = 1;
        return RES_OK;
    case GET_SECTOR_COUNT:
        *(DWORD*)buff = 32768; // Example: 16MB
        return RES_OK;
    }
    return RES_PARERR;
}
