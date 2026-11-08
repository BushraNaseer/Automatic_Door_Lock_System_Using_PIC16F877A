
#include <xc.h>
#include <stdint.h>
#include <string.h>

//==================================================
// CONFIGURATION BITS
//==================================================

#pragma config FOSC = HS        // High-speed crystal oscillator
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = ON       // Power-up Timer enabled
#pragma config BOREN = OFF      // Brown-out Reset disabled
#pragma config LVP = OFF        // Low-voltage programming disabled
#pragma config CPD = OFF        // Data EEPROM code protection disabled
#pragma config WRT = OFF        // Flash program memory write protection off
#pragma config CP = OFF         // Program memory code protection off

#define _XTAL_FREQ 20000000UL   // Assumed 20 MHz crystal

//==================================================
// USER CONFIGURATION
//==================================================

// Replace this example with the password used in
// your actual project, if it was different.
#define PASSWORD "12345"

#define PASSWORD_LENGTH       5
#define MAX_ATTEMPTS          3

// Motor travel times are initial estimates.
// Calibrate these according to your actual mechanism.
#define MOTOR_OPEN_TIME_MS    2000
#define MOTOR_CLOSE_TIME_MS   2000

// Door remains open for 10 seconds.
#define DOOR_OPEN_DELAY_MS    10000

// Buzzer alarm duration after three wrong attempts.
#define BUZZER_DURATION_SEC   60

//==================================================
// LCD PIN CONNECTIONS
//==================================================

// LCD RS -> RD0
// LCD EN -> RD1
// LCD D4 -> RD4
// LCD D5 -> RD5
// LCD D6 -> RD6
// LCD D7 -> RD7

#define LCD_RS RD0
#define LCD_EN RD1

//==================================================
// KEYPAD PIN CONNECTIONS
//==================================================

// Keypad rows    -> RB0, RB1, RB2, RB3
// Keypad columns -> RB4, RB5, RB6

//==================================================
// MOTOR DRIVER PIN CONNECTIONS
//==================================================

// L293D Enable 1,2 -> RC0
// L293D Input 1    -> RC1
// L293D Input 2    -> RC2
//
// Buzzer           -> RC3

#define MOTOR_EN RC0
#define MOTOR_IN1 RC1
#define MOTOR_IN2 RC2
#define BUZZER RC3

//==================================================
// FUNCTION PROTOTYPES
//==================================================

void system_init(void);

void lcd_init(void);
void lcd_command(unsigned char command);
void lcd_data(unsigned char data);
void lcd_send_nibble(unsigned char nibble);
void lcd_string(const char *text);
void lcd_clear(void);
void lcd_goto(unsigned char row, unsigned char column);

char keypad_getkey(void);

void motor_open(void);
void motor_close(void);
void motor_stop(void);

void buzzer_on(void);
void buzzer_off(void);

void unlock_door(void);
void security_lockout(void);

void delay_ms(unsigned int milliseconds);

//==================================================
// LCD FUNCTIONS
//==================================================

void lcd_send_nibble(unsigned char nibble)
{
    PORTD = (PORTD & 0x0F) | (nibble & 0xF0);

    LCD_EN = 1;
    __delay_us(1);

    LCD_EN = 0;
    __delay_us(100);
}

void lcd_command(unsigned char command)
{
    LCD_RS = 0;

    lcd_send_nibble(command & 0xF0);
    lcd_send_nibble((command << 4) & 0xF0);

    if (command == 0x01 || command == 0x02)
    {
        __delay_ms(2);
    }
    else
    {
        __delay_us(50);
    }
}

void lcd_data(unsigned char data)
{
    LCD_RS = 1;

    lcd_send_nibble(data & 0xF0);
    lcd_send_nibble((data << 4) & 0xF0);

    __delay_us(50);
}

void lcd_init(void)
{
    __delay_ms(20);

    LCD_RS = 0;
    LCD_EN = 0;

    // Initialize LCD in 4-bit mode.
    lcd_send_nibble(0x30);
    __delay_ms(5);

    lcd_send_nibble(0x30);
    __delay_us(150);

    lcd_send_nibble(0x30);
    lcd_send_nibble(0x20);

    lcd_command(0x28);  // 4-bit, 2-line, 5x8 font
    lcd_command(0x0C);  // Display ON, cursor OFF
    lcd_command(0x06);  // Increment cursor
    lcd_command(0x01);  // Clear display
}

void lcd_string(const char *text)
{
    while (*text != '\0')
    {
        lcd_data(*text);
        text++;
    }
}

void lcd_clear(void)
{
    lcd_command(0x01);
    __delay_ms(2);
}

void lcd_goto(unsigned char row, unsigned char column)
{
    unsigned char address;

    if (row == 1)
    {
        address = 0x80 + column - 1;
    }
    else
    {
        address = 0xC0 + column - 1;
    }

    lcd_command(address);
}

//==================================================
// KEYPAD FUNCTION
//==================================================

char keypad_getkey(void)
{
    const char keymap[4][3] =
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
    };

    unsigned char row;
    unsigned char column;
    unsigned char column_value;

    while (1)
    {
        for (row = 0; row < 4; row++)
        {
            // Set all rows HIGH, then pull one row LOW.
            PORTB = (PORTB & 0xF0) |
                    (0x0F & ~(1 << row));

            __delay_ms(2);

            column_value = PORTB & 0x70;

            for (column = 0; column < 3; column++)
            {
                if (!(column_value & (1 << (column + 4))))
                {
                    __delay_ms(25);  // Debounce

                    column_value = PORTB & 0x70;

                    if (!(column_value & (1 << (column + 4))))
                    {
                        char key = keymap[row][column];

                        // Wait until the key is released.
                        while ((PORTB & 0x70) != 0x70)
                        {
                            __delay_ms(10);
                        }

                        __delay_ms(20);

                        return key;
                    }
                }
            }
        }
    }
}

//==================================================
// MOTOR CONTROL FUNCTIONS
//==================================================

void motor_open(void)
{
    // Rotate motor in opening direction.
    MOTOR_EN = 1;
    MOTOR_IN1 = 1;
    MOTOR_IN2 = 0;

    delay_ms(MOTOR_OPEN_TIME_MS);

    motor_stop();
}

void motor_close(void)
{
    // Reverse motor direction to close the door.
    MOTOR_EN = 1;
    MOTOR_IN1 = 0;
    MOTOR_IN2 = 1;

    delay_ms(MOTOR_CLOSE_TIME_MS);

    motor_stop();
}

void motor_stop(void)
{
    MOTOR_EN = 0;
    MOTOR_IN1 = 0;
    MOTOR_IN2 = 0;
}

//==================================================
// BUZZER CONTROL FUNCTIONS
//==================================================

void buzzer_on(void)
{
    BUZZER = 1;
}

void buzzer_off(void)
{
    BUZZER = 0;
}

//==================================================
// DELAY FUNCTION
//==================================================

void delay_ms(unsigned int milliseconds)
{
    while (milliseconds > 0)
    {
        __delay_ms(1);
        milliseconds--;
    }
}

//==================================================
// DOOR UNLOCKING SEQUENCE
//==================================================

void unlock_door(void)
{
    lcd_clear();
    lcd_goto(1, 1);
    lcd_string("Password Correct");

    lcd_goto(2, 1);
    lcd_string("Door Opening...");

    // Open the door.
    motor_open();

    lcd_clear();
    lcd_goto(1, 1);
    lcd_string("Door Unlocked");

    lcd_goto(2, 1);
    lcd_string("Wait 10 Seconds");

    // Keep the door open for 10 seconds.
    delay_ms(DOOR_OPEN_DELAY_MS);

    lcd_clear();
    lcd_goto(1, 1);
    lcd_string("Closing Door...");

    // Reverse motor direction to close the door.
    motor_close();

    lcd_clear();
    lcd_goto(1, 1);
    lcd_string("Door Closed");

    __delay_ms(2000);
}

//==================================================
// SECURITY LOCKOUT FUNCTION
//==================================================

void security_lockout(void)
{
    unsigned char seconds;

    motor_stop();

    lcd_clear();
    lcd_goto(1, 1);
    lcd_string("INTRUDER");

    lcd_goto(2, 1);
    lcd_string("DETECTED!");

    // Activate buzzer continuously for 60 seconds.
    buzzer_on();

    for (seconds = 0;
         seconds < BUZZER_DURATION_SEC;
         seconds++)
    {
        __delay_ms(1000);
    }

    buzzer_off();

    // Keep the system locked until reset or power cycle.
    lcd_clear();
    lcd_goto(1, 1);
    lcd_string("SYSTEM LOCKED");

    lcd_goto(2, 1);
    lcd_string("Reset Required");

    while (1)
    {
        motor_stop();
        buzzer_off();
    }
}

//==================================================
// SYSTEM INITIALIZATION
//==================================================

void system_init(void)
{
    // Configure analog-capable pins as digital I/O.
    ADCON1 = 0x06;

    // LCD port configuration.
    TRISD = 0x00;
    PORTD = 0x00;

    // Keypad configuration:
    // RB0-RB3 = outputs (rows)
    // RB4-RB7 = inputs (columns/unused)
    TRISB = 0xF0;

    // Enable PORTB weak pull-up resistors.
    OPTION_REGbits.nRBPU = 0;

    PORTB = 0x0F;

    // Motor and buzzer outputs.
    TRISC = 0xF0;
    PORTC = 0x00;

    motor_stop();
    buzzer_off();

    lcd_init();
}

//==================================================
// MAIN PROGRAM
//==================================================

void main(void)
{
    char entered_password[PASSWORD_LENGTH + 1];

    unsigned char password_index = 0;
    unsigned char attempts = 0;

    char key;

    system_init();

    lcd_clear();
    lcd_goto(1, 1);
    lcd_string("Automatic Door");

    lcd_goto(2, 1);
    lcd_string("Lock System");

    __delay_ms(2000);

    while (1)
    {
        password_index = 0;

        // Clear the password buffer.
        memset(entered_password, 0,
               sizeof(entered_password));

        lcd_clear();
        lcd_goto(1, 1);
        lcd_string("Enter Password:");

        lcd_goto(2, 1);

        // Collect five password digits.
        while (password_index < PASSWORD_LENGTH)
        {
            key = keypad_getkey();

            // '*' clears the current entry.
            if (key == '*')
            {
                password_index = 0;

                memset(entered_password, 0,
                       sizeof(entered_password));

                lcd_clear();
                lcd_goto(1, 1);
                lcd_string("Enter Password:");

                lcd_goto(2, 1);
            }

            // Accept numeric keys only.
            else if (key >= '0' && key <= '9')
            {
                entered_password[password_index] = key;

                lcd_data('*');

                password_index++;
            }
        }

        entered_password[PASSWORD_LENGTH] = '\0';

        // Compare entered password with stored password.
        if (strcmp(entered_password, PASSWORD) == 0)
        {
            attempts = 0;

            unlock_door();
        }
        else
        {
            attempts++;

            lcd_clear();
            lcd_goto(1, 1);
            lcd_string("Wrong Password!");

            lcd_goto(2, 1);
            lcd_string("Attempts: ");

            lcd_data('0' + attempts);
            lcd_data('/');
            lcd_data('0' + MAX_ATTEMPTS);

            __delay_ms(2000);

            // Trigger security alarm after three failures.
            if (attempts >= MAX_ATTEMPTS)
            {
                security_lockout();
            }
        }
    }
}