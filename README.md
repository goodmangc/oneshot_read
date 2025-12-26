| Supported Target(s) | ESP32-S3 |
| ------------------- | -------- |

# ADC Single Read Example

This example demonstrates the following:

- How to obtain a oneshot ADC reading from a GPIO pin using the ADC oneshot mode driver
- How to use the ADC Calibration functions to obtain a calibrated result (in mV)

## How to use example

### Hardware Required

* A development board with ESP SoC
* A USB cable for power supply and programming

In this example, you need to connect a voltage source (e.g. a DC power supply) to the GPIO pins specified in `oneshot_read_main.c` (see the macros defined on the top of the source file). Feel free to modify the pin setting.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

Running this example, you will see the following output on the terminal:

```
I (239) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (245) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (252) main_task: Started on CPU0
I (262) main_task: Calling app_main()
I (262) EXAMPLE: calibration scheme version is Curve Fitting
I (262) EXAMPLE: Calibration Success
ADC1 Channel[4] Raw Data: 2336  Voltage: 1973 mV
ADC1 Channel[4] Raw Data: 2347  Voltage: 1981 mV
ADC1 Channel[4] Raw Data: 2346  Voltage: 1982 mV
ADC1 Channel[4] Raw Data: 2343  Voltage: 1978 mV
ADC1 Channel[4] Raw Data: 2345  Voltage: 1980 mV
ADC1 Channel[4] Raw Data: 2342  Voltage: 1977 mV
ADC1 Channel[4] Raw Data: 2341  Voltage: 1977 mV
ADC1 Channel[4] Raw Data: 2341  Voltage: 1977 mV
ADC1 Channel[4] Raw Data: 2346  Voltage: 1982 mV
ADC1 Channel[4] Raw Data: 2347  Voltage: 1981 mV
ADC1 Channel[4] Raw Data: 2345  Voltage: 1980 mV
ADC1 Channel[4] Raw Data: 2351  Voltage: 1985 mV
ADC1 Channel[4] Raw Data: 2339  Voltage: 1974 mV
ADC1 Channel[4] Raw Data: 2341  Voltage: 1977 mV
ADC1 Channel[4] Raw Data: 2341  Voltage: 1977 mV
ADC1 Channel[4] Raw Data: 2341  Voltage: 1977 mV
ADC1 Channel[4] Raw Data: 2345  Voltage: 1980 mV
ADC1 Channel[4] Raw Data: 2345  Voltage: 1980 mV
ADC1 Channel[4] Raw Data: 2339  Voltage: 1974 mV
ADC1 Channel[4] Raw Data: 2345  Voltage: 1980 mV
ADC1 Channel[4] Raw Data: 2343  Voltage: 1978 mV
...
```
