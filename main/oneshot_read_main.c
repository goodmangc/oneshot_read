/*
* SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
*
* SPDX-License-Identifier: Apache-2.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

const static char *TAG = "EXAMPLE";

/*---------------------------------------------------------------
ADC General Macros
---------------------------------------------------------------*/
//ADC1 Channel
#define EXAMPLE_ADC1_CHAN           ADC_CHANNEL_4
#define EXAMPLE_ADC_ATTEN           ADC_ATTEN_DB_12

static int adc_raw;
static int voltage;
// static float m = 0.774114;      // Bits to mV slope (mV/bit)
// static float b = 1.5;           // Bits to mV offset (mV)

// Function prototype
static bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle);

void app_main(void)
{
    //-------------ADC1 Init---------------//
    adc_oneshot_unit_handle_t adc1_handle;

    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    
    adc_oneshot_new_unit(&init_config1, &adc1_handle);
    
    //-------------ADC1 Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .atten = EXAMPLE_ADC_ATTEN,
        .bitwidth = ADC_BITWIDTH_12,
    };
    
    adc_oneshot_config_channel(adc1_handle, EXAMPLE_ADC1_CHAN, &config);
    
    //-------------ADC1 Calibration Init---------------//
    adc_cali_handle_t adc1_cali_chan_handle = NULL;
    // bool do_calibration1_chan = example_adc_calibration_init(ADC_UNIT_1, EXAMPLE_ADC1_CHAN, EXAMPLE_ADC_ATTEN, &adc1_cali_chan_handle);
    example_adc_calibration_init(ADC_UNIT_1, EXAMPLE_ADC1_CHAN, EXAMPLE_ADC_ATTEN, &adc1_cali_chan_handle);
    
    //-------------Loop forever-------------//
    while (1) {
        adc_oneshot_read(adc1_handle, EXAMPLE_ADC1_CHAN, &adc_raw);
        
        adc_cali_raw_to_voltage(adc1_cali_chan_handle, adc_raw, &voltage);
        
        printf("ADC%d Channel[%d] Raw Data: %d  Voltage: %d mV\n", ADC_UNIT_1 + 1, EXAMPLE_ADC1_CHAN, adc_raw, voltage);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}


/*---------------------------------------------------------------
ADC Calibration
---------------------------------------------------------------*/
static bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;
    
    if (!calibrated) {
        ESP_LOGI(TAG, "calibration scheme version is %s", "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .chan = channel,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
    
    *out_handle = handle;
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else {
        ESP_LOGE(TAG, "Invalid arg or no memory");
    }
    
    return calibrated;
}
