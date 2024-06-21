#include "HAL.h"

#if (STM32F401 == 1)
/*************************************************************************************************************
 *                                  APIs supported by the driver
 *                                    the function definitions                         
 * 
****************************************************************************************************************/

/* ======================== GPIO APIs =============================*/


/*
 * Periphral Clock Setup
 */

/************************************************************************
 * @fn              -GPIO_PeriClockControl
 * 
 * @brief            - This function use to enable OR disable clock for GPIO PORT
 * @Param[in]        -  Base address of GPIO Peripheral.{GPIOA,GPIOB, GPIOC, GPIOD, GPIOE, GPIOH}
 * @Param[in]        -  ENABLE or DISABLE Macro
 *
 * 
 * @return           -  None
 *  
 * @Note             -  None
 * 
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)

{
    if(EnorDi == ENABLE){
        if(pGPIOx == GPIOA){
             GPIOA_PCLK_EN();
        }else if(pGPIOx == GPIOB){
            GPIOB_PCLK_EN();
        }else if(pGPIOx == GPIOC){
            GPIOC_PCLK_EN();
        }else if(pGPIOx == GPIOD){
            GPIOD_PCLK_EN();
        }else if(pGPIOx == GPIOE){
            GPIOE_PCLK_EN();
        }else if(pGPIOx == GPIOH){
            GPIOH_PCLK_EN();
        }
    }else{
        if(pGPIOx == GPIOA){
            GPIOA_PCLK_DI();
        }else if(pGPIOx == GPIOB){
            GPIOB_PCLK_DI();
        }else if(pGPIOx == GPIOC){
            GPIOC_PCLK_DI();
        }else if(pGPIOx == GPIOD){
            GPIOD_PCLK_DI();
        }else if(pGPIOx == GPIOE){
            GPIOE_PCLK_DI();
        }else if(pGPIOx == GPIOH){
            GPIOH_PCLK_DI();
        }

    }

}



/*
 * Intializion & Deintializing GPIO
 */

/************************************************************************
 * @fn              -GPIO_Init
 * 
 * @brief            - This function use to initialazing port  
 * @Param[in]        -  Configration .{mode,speed, pull up /pull down, alt_function}
 *
 * 
 * @return           -  None
 *  
 * @Note             -  None
 * 
 */

void GPIO_INIT(GPIO_Handle *pGPIO_Handle)
{
    uint32_t temp = 0;
    //0. Enable_prepheral_clock
    GPIO_PeriClockControl(pGPIO_Handle->pGPIOx, ENABLE);
    //1. Configure the mode of gpio pin
    if(pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
        // non intruppt mode
        temp = (pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIO_Handle->pGPIOx->MODER &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);                                           /*<It's clearing two bits before writing on it>*/
        pGPIO_Handle->pGPIOx->MODER |= temp;

    }else{
	// interrupt mode
    	    if(pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
				EXTI->FTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->RTSR &= ~(1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
			}else if (pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
				EXTI->RTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->FTSR &= ~(1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
			}else if(pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode ==GPIO_MODE_IT_RFT){
				EXTI->FTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->RTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
			}

			uint8_t temp1 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber / 4;
			uint8_t temp2 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber % 4;
			uint8_t PORTCODE = GPIO_BASE_ADDR_TO_CODE(pGPIO_Handle->pGPIOx);
			SYSCFG->EXTICR[temp1] = PORTCODE << (temp2 * 4);                                                                            /*<It is GPIO port output @GPIO_PIN_SPEED register   >*/

			EXTI->IMR |= 1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber;
    	    }

    temp = 0;

    // configure the speed
    temp = (pGPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIO_Handle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);                                          /*<It's clearing two bits before writing on it>*/
    pGPIO_Handle->pGPIOx->OSPEEDR |= temp;
    temp = 0;

    //3. configration the pupd
    temp = (pGPIO_Handle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIO_Handle->pGPIOx->PUPDR &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);                                            /*<It's clearing two bits before writing on it>*/
    pGPIO_Handle->pGPIOx->PUPDR |= temp;

    //4. configuration the optype.
    temp = 0; 
    temp = (pGPIO_Handle->GPIO_PinConfig.GPIO_PinOPType << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIO_Handle->pGPIOx->OTYPER &= ~(0x1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);                                           /*<It's clearing two bits before writing on it>*/
    pGPIO_Handle->pGPIOx->OTYPER |= temp;

    // 5. configure the alt function reg
    if(pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
        uint8_t temp1, temp2;
        temp1 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIO_Handle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));                                                                   /*<It's clearing two bits before writing on it>*/
        pGPIO_Handle->pGPIOx->AFR[temp1] |= (pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));

    }
}


void GPIO_DE_INIT(GPIO_RegDef_t *pGPIOx)
{
   
    if(pGPIOx == GPIOA){
       GPIOA_PCLK_DI();
    }else if(pGPIOx == GPIOB){
        GPIOB_PCLK_DI();
    }else if(pGPIOx == GPIOC){
        GPIOC_PCLK_DI();
    }else if(pGPIOx == GPIOD){
        GPIOD_PCLK_DI();
    }else if(pGPIOx == GPIOE){
        GPIOE_PCLK_DI();
    }else if(pGPIOx == GPIOH){
        GPIOH_PCLK_DI();
    }
}


/*
 * Read & Write GPIO pin & port
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)  ((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}



uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t) pGPIOx->IDR ;
	return value;
}



void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == 1){
		pGPIOx->ODR |= (1<<PinNumber);
	}else{
		pGPIOx->ODR &= ~(1<<PinNumber);
	}
}


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<< PinNumber);
}


/*
 *  IRQ configration and ISR handling 
 */
void GPIO_IRQConfig(uint8_t GPIO_IRQNumber, uint32_t IRQPriorty, uint8_t EnorDi)
{
    if(EnorDi == ENABLE){
        if(GPIO_IRQNumber <= 31){
            *NVIC_ISER0 |= 1<<  (GPIO_IRQNumber);
        }else if(GPIO_IRQNumber > 31 && GPIO_IRQNumber <= 64){
            *NVIC_ISER1 |= 1<<  (GPIO_IRQNumber % 32);
        }else if(GPIO_IRQNumber > 64 && GPIO_IRQNumber <= 96)
            *NVIC_ISER2 |= 1<<  (GPIO_IRQNumber % 64);
    }else{
        if(GPIO_IRQNumber <= 31){
            *NVIC_ICER0 |= 1<<  (GPIO_IRQNumber);
        }else if(GPIO_IRQNumber > 31 && GPIO_IRQNumber <= 64){
            *NVIC_ICER1 |= 1<<  (GPIO_IRQNumber % 32);
        }else if(GPIO_IRQNumber > 64 && GPIO_IRQNumber <= 96)
            *NVIC_ICER2 |= 1<<  (GPIO_IRQNumber % 64);
    }

    uint8_t iprx = GPIO_IRQNumber/ 4;
    uint8_t iprx_section =  GPIO_IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
    *( iprx + NVIC_PR_BASE_ADDR) |= (IRQPriorty << shift_amount);
}


void GPIO_IRQHandling(uint8_t PinNumber)
{
    if(EXTI-> PR & (1 << PinNumber)){
        EXTI->PR |= (1 << PinNumber);
    }
}









/* ======================== SPI APIs =============================*/
#if (SPI == 1)

/************************************************************************
 * @fn              -SPI_PeriClockControl
 * 
 * @brief            - This function use to enable OR disable clock for SPI PORT
 * @Param[in]        -  Base address of GPIO Peripheral.{SPI1,SPI2, SPI3, SPI4}
 * @Param[in]        -  ENABLE or DISABLE Macro
 *
 * 
 * @return           -  None
 *  
 * @Note             -  None
 * 
 */
/*
 * Periphral Clock Setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){

      if(EnorDi == ENABLE){
        if(pSPIx == SPI1){
             SPI1_PCLK_EN();
        }else if(pSPIx == SPI2){
            SPI2_PCLK_EN();
        }else if(pSPIx == SPI3){
            SPI3_PCLK_EN();
        }else if(pSPIx == SPI4){
            SPI4_PCLK_EN();
        }
    }else{
        if(pSPIx == SPI1){
             SPI1_PCLK_DI();
        }else if(pSPIx == SPI2){
            SPI2_PCLK_DI();
        }else if(pSPIx == SPI3){
            SPI3_PCLK_DI();
        }else if(pSPIx == SPI4){
            SPI4_PCLK_DI();
        }
    }

}

/************************************************************************
 * @fn              -SPI_INIT
 * 
 * @brief            - This function use to Intialze  SPI PORT
 * @Param[in]        -  Base address of GPIO Peripheral.{SPI1,SPI2, SPI3, SPI4}
 * @Param[in]        -  ENABLE or DISABLE Macro
 *
 * 
 * @return           -  None
 *  
 * @Note             -  None
 * 
 */
/*
 * Periphral Clock Setup
 */
void SPI_INIT(SPI_Handle_t *pSPI_Handle){
    //0. Enable_prepheral_clock
    SPI_PeriClockControl(pSPI_Handle->pSPIx, ENABLE);
    // the first lets configure the Sip_cr1 reg
    uint32_t tempreg = 0;
    //1. configure the device mode 
    tempreg |= pSPI_Handle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR;

    //2. configure the bus config 
    if(pSPI_Handle->SPI_Config.SPI_BusConfig == SPI_fULL_DUPLEX){
        // bidiraction mode should be cleared
        tempreg &= ~(1 << SPI_CR1_BDIMODE);
    }else if (pSPI_Handle->SPI_Config.SPI_BusConfig == SPI_HALF_DUPLEX){
       // bidiraction mode should be set
        tempreg |= (1 << SPI_CR1_BDIMODE);
    }else if (pSPI_Handle->SPI_Config.SPI_BusConfig == SPI_SIMPLE_RXONLY){
         // bidiraction mode should be cleared
         tempreg &= ~(1 << SPI_CR1_BDIMODE);
         // RXONLY bit mast be set.
         tempreg |= (1 << SPI_CR1_RXONLY);
    }
    //3.configure SPI_sclkSpeed
      tempreg |= pSPI_Handle->SPI_Config.SPI_sclkSpeed << SPI_CR1_BR;
    // 4. configure SPI_DFF
      tempreg |= pSPI_Handle->SPI_Config.SPI_DFF << SPI_CR1_DFF;
    // 5. configure SPI_CPOL
      tempreg |= pSPI_Handle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL;
    // 6. configure SPI_CPHA  
      tempreg |= pSPI_Handle->SPI_Config.SPI_CPHA <<  SPI_CR1_CPHA;
     //7. configure SPI_SSM
      tempreg |= pSPI_Handle->SPI_Config.SPI_SSM << SPI_CR1_SSM;

      // initialzation for CR1
      pSPI_Handle->pSPIx->SPI_CR1 = tempreg;
}
void SPI_DE_INIT(SPI_RegDef_t *pSPIOx);
/*
 * Data send and Recieve.
*/


uint8_t Spi_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
    if(pSPIx ->SPI_SR & FlagName){
        return FLAG_SET;
    }
    return FLAG_RESET;
}




/************************************************************************
 * @fn              -SPI_SendData
 * 
 * @brief            - This function use to send  SPI PORT
 * @Param[in]        -  Base address of GPIO Peripheral.{SPI1,SPI2, SPI3, SPI4}
 * @Param[in]        -  ENABLE or DISABLE Macro
 *
 * 
 * @return           -  None
 *  
 * @Note             -  This blocking call 
 * 
 */
/*
 * Periphral Clock Setup
 */



void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){
     while(Len > 0){
        //1. wait until TXE Is set
        while(Spi_GetFlagStatus(pSPIx, SPI_SR_TXE_FLAG) == FLAG_RESET);  // first method
       // while(!(pSPIx -> SPI_SR & (SPI_SR_TXE << 1)));                // secand method
       // 2. CHECK DFF bit in cr1
       if ((pSPIx -> SPI_CR1 & (1 << SPI_CR1_DFF))){
        // 16 BIT DFF
        // 1. load the data in the dr register
        pSPIx -> SPI_DR = *((uint16_t*)pTxBuffer);
        Len--;
        Len--;
        (uint16_t*)pTxBuffer++;
       }else{
        // 8 bit DFF
        pSPIx -> SPI_DR = *pTxBuffer;
         Len--;
         pTxBuffer++;
       }
       
     }
} 
void SPI_RecieveData(SPI_RegDef_t *pSPIOx, uint8_t *pTxBuffer, uint32_t Len); 


void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
    if(EnorDi == ENABLE){
        pSPIx->SPI_CR1 |= (1<< SPI_CR1_SPE);
    }else{
        pSPIx->SPI_CR1 &= ~(1<< SPI_CR1_SPE);
    }
}
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
    if(EnorDi == ENABLE){
        pSPIx->SPI_CR1 |= (1<< SPI_CR1_SSI);
    }else{
        pSPIx->SPI_CR1 &= ~(1<< SPI_CR1_SSI);
    }
}



void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
    if(EnorDi == ENABLE){
        pSPIx->SPI_CR2 |= (1<< SPI_CR2_SSOE);
    }else{
        pSPIx->SPI_CR2 &= ~(1<< SPI_CR2_SSOE);
    }
}

/*
 *  IRQ configration and ISR handling 
 */
void SPI_IRQConfig(uint8_t IRQNumber, uint32_t IRQPriorty, uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pHandle);


#endif /*END SPI  API*/





#endif/*END STM32F401*/
