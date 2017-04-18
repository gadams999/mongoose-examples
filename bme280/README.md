# BME280 via I2C

This is an example of communicating with the BME280 via I2C. The `lib/bme280.*` files are derived from the Adafruit library (see Credits for more details) and are demoed via `src/main.cpp`.


# Project Configuration
The `src/conf_schema.yaml` needs to be created (ignored as it is where you can configure WiFi credentials and other sensitive information). By default, it should contain the following:

    [
      ["i2c.enable", true],
      ["i2c.sda_gpio", 14],
      ["i2c.scl_gpio", 12],
    ]

Changing the GPIO pins as needed to enable I2C. For debugging, the following lines can be added:
    [
      ["i2c.debug", true],
      ["debug.level", 3],
    ]

Build and flash as with other sources (`mos build && mos console`).


When running, the following should appear on the console:

    $ mos console
    ... 
    mgos_i2c_create      I2C GPIO init ok (SDA: 14, SCL: 12)
    mgos_sys_config_init HTTP server started on [80]
    mg_rpc_channel_mqtt  0x3fff083c esp8266_33BFD5/rpc/#
    mg_rpc_channel_uart  0x3fff08ec UART0
    mgos_init            Init done, RAM: 45728 free, 45112 min free
    mongoose_poll        New heap free LWM: 43936
    bme280_cb            Temp: 24.21C, Humidity: 43.17%, Pressure: 983.2679mb
    bme280_cb            Temp: 24.21C, Humidity: 43.00%, Pressure: 983.2145mb
    bme280_cb            Temp: 24.19C, Humidity: 43.00%, Pressure: 983.1545mb

# Notes / TODO
## Notes
1. `main.cpp` uses C++ as that made it easier to reuse the Adafruit Library
2. Only support for I2C included, requires I2C enabled at Mongoose OS level
3. Library work started on Adafruit pull from 2017-04-10; changes or corrections since then have not bee included.

## TODO
1. Add back in SPI support
2. Refactor to remove uneeded functions or support
3. Add license details for Cesanta


# License

BSD License.

# Credits

This application uses Open Source components. You can find the source code of their open source projects along with license information below. We acknowledge and are grateful to these developers for their contributions to open source.

Project: [Library for the Adafruit BME280 Humidity, Barometric Pressure + Temp sensor](https://github.com/adafruit/Adafruit_BME280_Library)

    This is a library for the Adafruit BME280 Humidity, Barometric Pressure + Temp sensor

    Designed specifically to work with the Adafruit BME280 Breakout
     * http://www.adafruit.com/products/2652

    These sensors use I2C or SPI to communicate, up to 4 pins are required to interface

    Use of this library also requires [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)
    to be installed on your local system.

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    Check out the links above for our tutorials and wiring diagrams

    Written by Limor Fried/Ladyada for Adafruit Industries.  
    BSD license, all text above must be included in any redistribution
