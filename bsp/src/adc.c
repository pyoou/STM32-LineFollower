//
// Created by pyoou on 22.03.2026.
//

#include "adc.h"

static ADC_HandleTypeDef hadc1 = {0};
static DMA_HandleTypeDef hdma_adc1 = {0};

static uint16_t adc_raw_values[SENSOR_COUNT] = {0};

void BSP_ADC_Init(void)
{
  /* Clocks enable */
  __HAL_RCC_GPIOA_CLK_ENABLE(); // Port A enable
  __HAL_RCC_GPIOB_CLK_ENABLE(); // Port B enable
  __HAL_RCC_ADC1_CLK_ENABLE();  // ADC
  __HAL_RCC_DMA2_CLK_ENABLE();  // DMA2 Controller

  /* GPIO Config */
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  /* GPIO A */
  GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // /* GPIO B */
  // GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  // HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* DMA2 Config */
  hdma_adc1.Instance = DMA2_Stream0;
  hdma_adc1.Init.Channel = DMA_CHANNEL_0;
  hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY; // from ADC to RAM
  hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE; // ADC register is NOT changing
  hdma_adc1.Init.MemInc =
      DMA_MINC_ENABLE; // Increase array index by one after each measurement
  hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; // 16 bits ADC
  hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;    // 16 bits RAM
  hdma_adc1.Init.Mode = DMA_CIRCULAR; // Repeat after last array cell
  hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

  if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
  {
    // pass
  }

  __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);

  /* Inverter Config */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B; // Measure from 0 to 4095
  hadc1.Init.ScanConvMode = ENABLE;           // Read multicount one by one
  hadc1.Init.ContinuousConvMode = ENABLE;     // Repeat after last read cell
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = SENSOR_COUNT; // Convert [SENSOR_COUNT] channels
  hadc1.Init.DMAContinuousRequests = ENABLE; // Allow continuous measurement
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;

  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    // ADC Initialize Handler
  }

  /* Reading Queue */
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.SamplingTime =
      ADC_SAMPLETIME_84CYCLES; // Average sample time (stable)

  /* Pin Assignment */
  const uint32_t channels[SENSOR_COUNT] = {ADC_CHANNEL_0, ADC_CHANNEL_5,
                                           ADC_CHANNEL_6, ADC_CHANNEL_7,
                                           ADC_CHANNEL_8, ADC_CHANNEL_9};

  for (uint32_t i = 0; i < SENSOR_COUNT; i++)
  {
    sConfig.Channel = channels[i];
    sConfig.Rank = i + 1;

    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      HAL_ADC_ErrorCallback(&hadc1);
    }
  }

  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_raw_values, SENSOR_COUNT);
}

uint16_t BSP_ADC_GetValue(uint8_t sensor_index)
{
  if (sensor_index >= SENSOR_COUNT)
  {
    return 0;
  }
  return adc_raw_values[sensor_index];
}

uint16_t *BSP_ADC_GetValues(void) { return adc_raw_values; }
