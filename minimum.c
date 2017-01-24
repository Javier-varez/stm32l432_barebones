
#include <stdint.h>

#define GPIOB_BASE		0x48000400
#define GPIOA_BASE		0x48000000
#define GPIO_MODER_OFFSET	0x00
#define GPIO_OTYPER_OFFSET	0x04
#define GPIO_OSPEEDR_OFFSET	0x08
#define GPIO_PUPDR_OFFSET	0x0C
#define GPIO_IDR_OFFSET		0x10
#define GPIO_ODR_OFFSET		0x14
#define GPIO_BSRR_OFFSET	0x18
#define GPIO_LCKR_OFFSET	0x1C
#define GPIO_AFRL_OFFSET	0x20
#define GPIO_AFRH_OFFSET	0x24

#define RCC_BASE   0x40021000
#define RCC_AHB2ENR_OFFSET 0x4C

void button_test() {
	*(uint32_t*)(RCC_BASE + RCC_AHB2ENR_OFFSET) = (1<<1) | (1<<0); // EN CLK FOR GPIO B and A
	*(uint32_t*)(GPIOB_BASE + GPIO_MODER_OFFSET) = (0x01<<6) | 0xABFFFF3F; // OUT LED
	*(uint32_t*)(GPIOB_BASE + GPIO_BSRR_OFFSET) = (0x01<<3); // Turn on LED

	while(1) {
		uint32_t data = *(uint32_t*)(GPIOA_BASE + GPIO_IDR_OFFSET);
		*(uint32_t*)(GPIOB_BASE + GPIO_ODR_OFFSET) = ((data & (1<<12)) >> 12) << 3;
	}
}

void led_flash() {
	*(uint32_t*)(RCC_BASE + RCC_AHB2ENR_OFFSET) = (1<<1) | (1<<0); // EN CLK FOR GPIO B and A
	*(uint32_t*)(GPIOB_BASE + GPIO_MODER_OFFSET) = (0x01<<6) | 0xABFFFF3F; // OUT LED
	*(uint32_t*)(GPIOB_BASE + GPIO_BSRR_OFFSET) = (0x01<<3); // Turn on LED

	while(1) {
		for(int i = 0; i < 1000000; i++);
	*(uint32_t*)(GPIOB_BASE + GPIO_BSRR_OFFSET) = (0x01<<19); // Turn on LED
		for(int i = 0; i < 1000000; i++);
	*(uint32_t*)(GPIOB_BASE + GPIO_BSRR_OFFSET) = (0x01<<3); // Turn on LED
	}
}

void main()
{
	//button_test();	
	led_flash();
}
