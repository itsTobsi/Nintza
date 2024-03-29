/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Variables
char CChar[17];
char char_arr[16];
//int Index[17]; // Was used for screen refresh testing
//int IndexChar; // Was used for screen refresh testing

int BtnInPin = 2;
int val = 0;

int CurrentMillis;
int CurrentSec;

void setup() // Start/before main loop
{
    // For debugging
    Serial.begin(9600);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.

    //lcd.print("     Nintza     "); // Only 16 char!!!
    //lcd.print("x--==Nintza==--x"); // Other Header/Titels
    //lcd.print(" --==Nintza==-- ");
    //lcd.print("--== Nintza ==--");
    //lcd.print("--==:Nintza:==--");

    //lcd.print("     NINTZA     ");
    //lcd.print("x--==NINTZA==--x");
    //lcd.print(" --==NINTZA==-- ");
    //lcd.print("--== NINTZA ==--");

    lcd.print("--== Nintza ==--"); // William
    //lcd.print("--== NINTZA ==--"); // Alex & Marcus

    pinMode(BtnInPin, INPUT); // Read form Digital 2
}

void loop()
{
    // Bool for start
    bool IsON = false;

    // Read input from Digital 2
    IsON = digitalRead(BtnInPin);

    // Prints it to the "debug screen"
    Serial.println(IsON);

    // Waits for input, and starts the timer
    if (IsON == 1)
    {
        ResetBottom();

        // Countdown Starts
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.write("3");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.write("2");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.write("1");
        delay(1000);

        // RESETS MILLIS()
        CurrentMillis = (millis() / 100);
        CurrentSec = (millis() / 1000);
    }

    // Timer while-loop
    while (IsON)
    {
        val = digitalRead(BtnInPin); // Off button input

        // Prints to bottom part of the LCD screen
        lcd.setCursor(0, 1);
        //lcd.print(((millis() / 100) - CurrentMillis));

        /*========================== TOBSI'S TIMER ==========================*/
        // This is the "clock"
        int min = (((millis() / 1000) - CurrentSec));     // Minutes
        min = min / 60;                                   // Minutes
        int sec = (((millis() / 1000) - CurrentSec));     // Seconds
        sec = sec % 60;                                   // Seconds
        int milli = (((millis() / 100) - CurrentMillis)); // Milliseconds
        milli = milli % 10;                               // Milliseconds

        /*
         I need all of these, because i can't add multiple numbers 
         (Minutes, Seconds and Milliseconds) into one string. 
         This works for some reason ¯\_(ツ)_/¯ .
        */
        String str;           // Minutes
        str = String(min);    // Minutes
        String str2;          // Seconds
        str2 = String(sec);   // Seconds
        String str3;          // Seconds
        str3 = String(milli); // Seconds

        lcd.print(str + ":" + str2 + "," + str3);

        // The OFF Switch
        if (val == 1)
        {
            IsON = false;
            delay(1000); // 1 Second delay. Without it, the user might start a new "Run" accidentally.
        }
        else
        {
            IsON = true;
        }
    }
}

// Resets the bottom screen
void ResetBottom()
{
    for (int i = 0; i < 16; i++)
    {
        CChar[i] = ' ';
    }

    lcd.setCursor(0, 1);
    lcd.print(CChar);
}
