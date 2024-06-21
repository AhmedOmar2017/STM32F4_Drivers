#ifndef HAL_H_
#define HAL_H_

#include "Mcal.h"

#if (STM32F401 == 1)

/*============================= This is Configration Structure For a GPIO PIN ==========================*/
typedef struct 
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;                               /*<It is GPIO port mode register  @GPIO_PIN_MODES    >*/
    uint8_t GPIO_PinSpeed;                              /*<It is GPIO port output @GPIO_PIN_SPEED register   >*/
    uint8_t GPIO_PinPuPdControl;                        /*<It is GPIO port @pullup and pulldown              >*/            
    uint8_t GPIO_PinOPType;                             /*<It is GPIO port @Type of output                   >*/
    uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t; /* End Configration Structure For a GPIO PIN*/


/*============================= This is handle Structure For a GPIO PIN ==========================*/


typedef struct{
    GPIO_RegDef_t *pGPIOx;                  /*< THIS HOLD  THE BASE ADDRESS OF THE GPIO  TO WHICH PIN BELONG >*/
    GPIO_PinConfig_t GPIO_PinConfig;        /*< THIS HOLD  THE GPIO PIN CONFEGRATION SETTING  >*/
}GPIO_Handle;  /* End Configration Structure For a GPIO PIN*/






#if (SPI == 1)
/*============================= This is Configration Structure For a SPI protucool ==========================*/
typedef struct 
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;                               /*<It is           >*/
    uint8_t SPI_sclkSpeed;                               /*<It is          >*/
    uint8_t SPI_DFF;                                    /*<It is Data frame format                                   >*/            
    uint8_t SPI_CPOL;                                   /*<It is Clock polarity                                      >*/
    uint8_t SPI_CPHA;                                   /*<It is Clock phase                                         >*/
    uint8_t SPI_SSM;                                    /*<It is Software slave management                           >*/             

}SPI_Config_t; /* End Configration Structure For a SPI protucool*/


/*============================= This is handle Structure For a SPI protucool ==========================*/


typedef struct{
    SPI_RegDef_t *pSPIx;                  /*< THIS HOLD  THE BASE ADDRESS OF THE SPI  TO WHICH PIN BELONG >*/
    SPI_Config_t SPI_Config;              /*< THIS HOLD  THE SPI CONFEGRATION SETTING  >*/
}SPI_Handle_t;  /* End Configration Structure For a SPI*/


#endif







/*************************************************************************************************************
 *                                  APIs supported by the driver
 *                  For more information about the APIs check the function definitions                         
 * 
****************************************************************************************************************/
/* ======================== GPIO APIs =============================*/


/*
 * Periphral Clock Setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *PGPIOx, uint8_t EnorDi);

/*
 * Intializion & Deintializing GPIO
 */
void GPIO_INIT(GPIO_Handle *pGPIO_Handle);
void GPIO_DE_INIT(GPIO_RegDef_t *pGPIOx);


/*
 * Read & Write GPIO pin & port
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);


/*
 *  IRQ configration and ISR handling 
 */
void GPIO_IRQConfig(uint8_t GPIO_IRQNumber, uint32_t IRQPriorty, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);

/* ======================== SPI APIs =============================*/
#if (SPI == 1)

/*
 * Periphral Clock Setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * Intializion & Deintializing GPIO
 */
void SPI_INIT(SPI_Handle_t *pSPIO_Handle);
void SPI_DE_INIT(SPI_RegDef_t *pSPIOx);



/*
 * Data send and Recieve.
*/
void SPI_SendData(SPI_RegDef_t *pSPIOx, uint8_t *pTxBuffer, uint32_t Len); 
void SPI_RecieveData(SPI_RegDef_t *pSPIOx, uint8_t *pTxBuffer, uint32_t Len); 
uint8_t Spi_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);     
/*
 *  IRQ configration and ISR handling 
 */
void SPI_IRQConfig(uint8_t IRQNumber, uint32_t IRQPriorty, uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi); 
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
#endif /*END SPI  API*/

#endif/*END STM32F401*/


#endif /*end HAL.H FILE*/
