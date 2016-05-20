# `LEDrum`
Arduino code for triggering LED lights<i>(in my case, inside a drumset)</i>

Using Digital Neo Pixels by adafruit. 

Your mileage may vary depending on which piezo buzzer you're using; with some that are more sensitive you may have to do something like:

```c
  FIRST = analogRead(PIEZO);

  if (FIRST > THRESHOLD) {
    delay(1); // Let noise pass.
    SECOND = analogRead(PIEZO);
    if (SECOND > FIRST) {
      // We know that we're ascending in amplitude, so this is a hit and not
      // just post noise after a hit.
      coroutines.start(blink);
    }
  }


```

We're using an Arduino coroutine, `#include <Coroutines.h>`, library found here:

[https://github.com/renaudbedard/littlebits-arduino/tree/master/Libraries/Coroutines](https://github.com/renaudbedard/littlebits-arduino/tree/master/Libraries/Coroutines)

We're using the Adafruit Neopixel library, `#include <Adafruit_NeoPixel.h>`, found here:

[https://github.com/adafruit/Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)


Additional resources:

[https://learn.adafruit.com/adafruit-neopixel-uberguide/overview](https://learn.adafruit.com/adafruit-neopixel-uberguide/overview)

[http://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/](http://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/)

[https://www.arduino.cc/en/Tutorial/Knock](https://www.arduino.cc/en/Tutorial/Knock)
