#ifndef MACROS_H_
#define MACROS_H_

#include "configration.h"

/**************************************************************************************************
 * 
 *                                              Generic Macros
 * 
****************************************************************************************************/

#define ENABLE                          1
#define DISABLE                         0
#define SET                             ENABLE
#define RESET                           DISABLE
#define NO_PR_BITS_IMPLEMENTED          4





/**************************************************************************************************
    * 
    *                                              GPIO Pin possible Configration Macros
    * 
   ****************************************************************************************************/

   /*
   * @GPIO_PIN_NUMBERS
   * GPIO PIN NUMBERS
   * 
   */

   #define GPIO_PIN_NO_0      0
   #define GPIO_PIN_NO_1      1
   #define GPIO_PIN_NO_2      2
   #define GPIO_PIN_NO_3      3
   #define GPIO_PIN_NO_4      4
   #define GPIO_PIN_NO_5      5
   #define GPIO_PIN_NO_6      6
   #define GPIO_PIN_NO_7      7
   #define GPIO_PIN_NO_8      8
   #define GPIO_PIN_NO_9      9
   #define GPIO_PIN_NO_10     10
   #define GPIO_PIN_NO_11     11
   #define GPIO_PIN_NO_12     12
   #define GPIO_PIN_NO_13     13
   #define GPIO_PIN_NO_14     14
   #define GPIO_PIN_NO_15     15






#if STM32F401 == 1



    /*
    * @ GPIO_PIN_MODES
    * Mode Configration 
    * 
    * */



    #define GPIO_MODE_IN                0
    #define GPIO_MODE_OUT               1
    #define GPIO_MODE_ALTFN             2
    #define GPIO_MODE_ANALOG            3
    #define GPIO_MODE_IT_FT             4
    #define GPIO_MODE_IT_RT             5
    #define GPIO_MODE_IT_RFT            6



    /*
    *  @Type of output
    * output type Configration 
    * 
    * */



    #define GPIO_OP_TYPE_PP            0
    #define GPIO_OP_TYOE_PP            1



    /*
    * @ GPIO_PIN_SPEED register 
    * output speed Configration 
    * 
    * */

    #define GPIO_SPEED_LOW           0      
    #define GPIO_SPEED_MEDIUM        1
    #define GPIO_SPEED_FAST          2
    #define GPIO_SPEED_HIGH          3

    /*
    * @pullup and pulldown
    * Pull up and pull down Configration 
    * 
    * */

    #define GPIO_NO_PUPD              0
    #define GPIO_PIN_PU               1
    #define GPIO_PIN_PD               2
/* =======================  Spi macros ==========================*/
#if SPI == 1
/*
 * @SPI_DeviceMode
*/
#define SPI_DEVICE_MODE_MASTER         1
#define SPI_DEVICE_MODE_SLAVE          0

/*
 * @SPI_BusConfig
*/
#define SPI_fULL_DUPLEX                 1
#define SPI_HALF_DUPLEX                 2
#define SPI_SIMPLE_RXONLY               3



/*
 * SPI_sclkSpeed
*/

#define SPI_CLK_SPEED_DIV2              0
#define SPI_CLK_SPEED_DIV4              1
#define SPI_CLK_SPEED_DIV8              2
#define SPI_CLK_SPEED_DIV16             3
#define SPI_CLK_SPEED_DIV32             4
#define SPI_CLK_SPEED_DIV64             5
#define SPI_CLK_SPEED_DIV128            6
#define SPI_CLK_SPEED_DIV256            7



/*
 * @SPI_DFF
*/

#define SPI_DFF_8BIT                    0
#define SPI_DFF_16BIT                   1


/*
 *@SPI_CPOL
*/

#define SPI_CPOL_HIGH                   0
#define SPI_CPOL_LOW                    1



/*
 *@SPI_CPHA
*/

#define SPI_CPHA_HIGH                   0
#define SPI_CPHA_LOW                    1


/*
 *@SPI_SSM
*/
#define SPI_SSM_EN                      1
#define SPI_SSM_DI                      0


/***************************************  BIT FILED FOR SPI_RC1 **********************/

#define SPI_CR1_CPHA                    0
#define SPI_CR1_CPOL                    1
#define SPI_CR1_MSTR                    2
#define SPI_CR1_BR                      3
#define SPI_CR1_SPE                     6
#define SPI_CR1_LSBFIRST:               7
#define SPI_CR1_SSI                     8
#define SPI_CR1_SSM                     9
#define SPI_CR1_RXONLY                  10
#define SPI_CR1_DFF                     11
#define SPI_CR1_CRCNEXT                 12
#define SPI_CR1_CRCEN                   13
#define SPI_CR1_BIDION                  14
#define SPI_CR1_BDIMODE                 15



/***************************************  BIT FILED FOR SPI_RC2 **********************/

#define SPI_CR2_RXDMAEN                 0
#define SPI_CR2_TXDMAEN                 1
#define SPI_CR2_SSOE                    2
#define SPI_CR2_FRF                     4
#define SPI_CR2_ERRIE                   5
#define SPI_CR2_RXNEIE                  6
#define SPI_CR2_TXEIE                   7


/***************************************  BIT FILED FOR SPI_SR **********************/
#define SPI_SR_RXNE                     0
#define SPI_SR_TXE                      1
#define SPI_SR_CHSIDE                   2
#define SPI_SR_UDR                      3
#define SPI_SR_CRCERR                   4
#define SPI_SR_MODF                     5
#define SPI_SR_OVR                      6
#define SPI_SR_BSY                      7
#define SPI_SR_FRE                      8

#endif /* end Spi macros */

#endif/*end STM32F401*/




#endif /* End macros file */