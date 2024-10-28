#include "main.h"
#include "debug.h"

/* Global typedef */
/* Global define */
#define MaxConversion 64

/* Global Variable */
u8 i = 0;
u32 contador = 0;
u16 TxBuf[MaxConversion];
s16 Calibrattion_Val = 0;

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 * @brief   Initializes GPIOA.0
 * @return  none
 */
void GPIO_Toggle_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LED1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LED2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      ADC_Function_Init
 * @brief   Initializes ADC collection.
 * @return  none
 */
void ADC_Function_Init(void) {
    ADC_InitTypeDef ADC_InitStructure = { 0 };
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_DMACmd(ADC1, ENABLE); // Habilita DMA para ADC
    ADC_Cmd(ADC1, ENABLE);
    ADC_BufferCmd(ADC1, DISABLE); // Disable buffer
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    Calibrattion_Val = Get_CalibrationValue(ADC1);
}

/*********************************************************************
 * @fn      Get_ADC_Val
 * @brief   Returns ADCx conversion result data.
 * @param   ch - ADC channel.
 *            ADC_Channel_0 - ADC Channel0 selected.
 *            ADC_Channel_1 - ADC Channel1 selected.
 * @return  none
 */
u16 Get_ADC_Val(u8 ch) {
    u16 val;
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    val = ADC_GetConversionValue(ADC1);
    return val;
}

/*********************************************************************
 * @fn      DMA_Tx_Init
 * @brief   Initializes the DMAy Channelx configuration.
 * @param   DMA_CHx - x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 * @return  none
 */
void DMA_Tx_Init(DMA_Channel_TypeDef* DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize) {
    DMA_InitTypeDef DMA_InitStructure = { 0 };
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE);
    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // Cambia a Circular para continuas conversiones
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);
}

/*********************************************************************
 * @fn      Get_ConversionVal
 * @brief   Get Conversion Value.
 * @param   val - Sampling value
 * @return  val+Calibrattion_Val - Conversion Value.
 */
u16 Get_ConversionVal(s16 val) {
    if ((val + Calibrattion_Val) < 0 || val == 0)
        return 0;
    if ((Calibrattion_Val + val) > 4095 || val == 4095)
        return 4095;
    return (val + Calibrattion_Val);
}

/*********************************************************************
 * @fn      main
 * @brief   Main program.
 * @return  none
 */
int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    GPIO_Toggle_INIT();
    ADC_Function_Init();
    printf("CalibrattionValue:%d\n", Calibrattion_Val);
    DMA_Tx_Init(DMA1_Channel1, (u32) &ADC1->RDATAR, (u32) TxBuf, MaxConversion);
    DMA_Cmd(DMA1_Channel1, ENABLE);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    printf("GPIO Toggle TEST\r\n");
    while(1)
    {
        contador++;
        // ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);
        // ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        printf("[Conversion N..%d]   ", contador);
        u32 sumaConversion = 0;
        for(int u = 0; u < MaxConversion; u++)
        {
            sumaConversion += Get_ConversionVal(TxBuf[u]);
        }
        // No es necesario detener la conversi¨®n ya que el DMA est¨¢ en modo circular
        u32 valorConvertidoPromedio = sumaConversion / MaxConversion;
        printf("Valor Convertido = %d\r\n", valorConvertidoPromedio);
        GPIO_WriteBit(GPIOA, LED1, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
        GPIO_WriteBit(GPIOB, LED2, !i);
        Delay_Ms(100);
    }
}


