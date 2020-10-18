/*************************************************************************\
  rpi_gpio_test_simple.c
************************************************************************/

//module simple qui met à 1 la pin GPIO 23

#include <linux/module.h>
#include <linux/gpio.h>


// La sortie va sur la broche 16 (GPIO 23).
#define RPI_IRQ_GPIO_OUT 23


// Chargement du module .
static int __init rpi_gpio_init(void)
{


    printk(KERN_INFO "------------- On initialise le module -------------\n");

    int err;

    // Demander l’accès au GPIO de sortie.
    if ((err = gpio_request(RPI_IRQ_GPIO_OUT, THIS_MODULE->name)) != 0)
        return err;

    // Configurer la direction du GPIO de sortie.
    if ((err = gpio_direction_output(RPI_IRQ_GPIO_OUT,1)) != 0) {
        gpio_free(RPI_IRQ_GPIO_OUT);
        return err;
    }
    gpio_set_value(RPI_IRQ_GPIO_OUT, 1);
    printk(KERN_INFO "------------- On met la GPIO 23 a 1 -------------\n");

    return 0;
}
// Déchargement du module.
static void __exit rpi_gpio_exit(void)
{
    // Liberation des GPIO.
    printk(KERN_INFO "------------- On libere les GPIO -------------\n");
    gpio_free(RPI_IRQ_GPIO_OUT);
}
module_init(rpi_gpio_init);
module_exit(rpi_gpio_exit);
MODULE_LICENSE("GPL");
