#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 1000

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define USER_BUTTON_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(USER_BUTTON_NODE, gpios);

int main(void)
{
   int ret = 0;
   // Check if the GPIO device is ready
   // if (!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1) || gpio_is_ready_dt(&button))
   // {
   //       return -1;
   // }

   ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
   ret |= gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
   ret |= gpio_pin_configure_dt(&button, GPIO_INPUT);

   // if(ret<0)
   // {
   //    return -1;
   // }

   while (1)
   {
      // Toggle the LED basis the current status of USER button
      bool val = gpio_pin_get_dt(&button);
      // Set the GPIO value as per determined value of USER button
      gpio_pin_set_dt(&led1, val);
      // Keep toggeling the other led
      gpio_pin_toggle_dt(&led0);
      // Put the thread to sleep
      k_msleep(SLEEP_TIME_MS);
    }

   return 0;
}