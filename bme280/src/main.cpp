#include <stdio.h>

extern "C" {
  #include "common/platform.h"
  #include "fw/src/mgos_app.h"
  #include "fw/src/mgos_gpio.h"
  #include "fw/src/mgos_sys_config.h"
  #include "fw/src/mgos_timers.h"
  #include "fw/src/mgos_i2c.h"
  #include "fw/src/mgos_hal.h"
}

#include "lib/bme280.h"

#if CS_PLATFORM == CS_P_ESP8266
/* On ESP-12E there is a blue LED connected to GPIO2 (aka U1TX). */
#define LED_GPIO 2
#elif CS_PLATFORM == CS_P_ESP32
/* Unfortunately, there is no LED on DevKitC, so this is random GPIO. */
#define LED_GPIO 17
#else
#error Unknown platform
#endif

Generic_BME280 bme;

static void blink_timer_cb(void *arg) {
  mgos_gpio_toggle(LED_GPIO);
  (void) arg;
}

static void bme280_cb(void *arg){
  LOG (LL_INFO, ("Temp: %2.2fC, Humidity: %2.2f%%, Pressure: %2.4fmb",
                 bme.readTemperature(),
                 bme.readHumidity(),
                 (float)(bme.readPressure()/100)));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) {
  /* equiv of Setup section */
  //Generic_BME280 bme;
  bool status;
  status = bme.begin();
  if (!status) {
    LOG (LL_INFO, ("Could not find BME280 on I2C, check wiring or I2C config"));
  }

  /* ************* event loop section (setup callbacks and execute) */
  { /* Set up the blinky timer. */
    mgos_gpio_set_mode(LED_GPIO, MGOS_GPIO_MODE_OUTPUT);
    mgos_set_timer(1000 /* ms */, true /* repeat */, blink_timer_cb, NULL);
  }
  { /* Read and report on BME280 sensor */
    mgos_set_timer(5000, true /* repeat */, bme280_cb, NULL);
  }

  return MGOS_APP_INIT_SUCCESS;
}
