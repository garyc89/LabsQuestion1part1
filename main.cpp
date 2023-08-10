#include "mbed.h"

// Error: If the `button_pressed` variable isn't declared as `volatile`, the compiler might optimize 
// it away, causing the main loop to not notice changes made inside the ISR.
// Solution: Declare the flag as `volatile` to ensure it isn't optimized away and its changes are 
// immediately visible across different contexts.

InterruptIn button(USER_BUTTON);
volatile bool button_pressed = false;  // Declare flag as volatile

void button_isr() {
    button_pressed = true;
}

int main() {
    button.fall(&button_isr);

    while (1) {
        if (button_pressed) {
            printf("Button pressed\r\n");
            button_pressed = false;  // Reset the flag
        }
        ThisThread::sleep_for(10ms);
    }
}
