# firstorderFilter — First-Order Low-Pass Filter (Tustin/Bilinear)

## Overview

A minimal, embedded-friendly first-order low-pass IIR filter implemented using the
**Tustin (bilinear) transform**. The filter discretizes the continuous-time pole
using numerically robust formulas suitable for real-time systems.

### Continuous-time transfer function

$$H(s) = \frac{\omega_c}{s + \omega_c}$$

### Discrete-time (Tustin) form

$$y[k] = a\,(u[k] + u[k-1]) - b\,y[k-1]$$

where:

$$a = \frac{T_s\,\omega_c}{T_s\,\omega_c + 2}, \quad b = \frac{T_s\,\omega_c - 2}{T_s\,\omega_c + 2}$$

---

## Features

- First-order low-pass IIR filter using the Tustin (bilinear) transform
- Deterministic, allocation-free implementation
- No dynamic memory
- Stable for all valid cutoff frequencies and sampling times
- Portable to any C++ project (Arduino not required)
- Suitable for sensor filtering, signal smoothing, and embedded control

---

## Usage

### Include the library

```cpp
#include "firstorderFilter.h"
```

### Create and initialize the filter

```cpp
firstorderFilter myFilter;

float cutOff = 2.5f;   // cutoff frequency (rad/s)
float Ts     = 0.01f;  // sampling time (s)

myFilter.setup(cutOff, Ts);
```

### Compute the filtered output each loop

```cpp
float raw      = readSensor();
float filtered = myFilter.filteredValue(raw);
```

---

## API

| Method | Description |
|---|---|
| `void setup(float cutOff, float Ts)` | Initialize filter with cutoff frequency (rad/s) and sampling time (s) |
| `float filteredValue(float u)` | Compute and return filtered output for current input sample |

---

## Parameter Notes

- `cutOff` is the cutoff frequency in **rad/s** (ω_c). To convert from Hz: `ω_c = 2π f_c`
- `Ts` is the sampling time in **seconds**
- If either parameter is ≤ 0, `setup()` returns without modifying state
- The filter attenuates frequencies above `cutOff` at −20 dB/decade

---

## Example Sketch

```cpp
#include "firstorderFilter.h"
#include <math.h>

firstorderFilter myFilter;

float Ts           = 0.01f;   // 10 ms sample time (100 Hz)
float omega_signal = 10.0f;   // signal frequency (rad/s)
uint32_t loopTimer;
uint32_t Ts_us;

void setup() {
    Serial.begin(38400);
    Ts_us = (uint32_t)(Ts * 1000000.0f);
    myFilter.setup(omega_signal / 4.0f, Ts);  // cutoff = 2.5 rad/s
    loopTimer = micros();
}

void loop() {
    float t          = loopTimer / 1000000.0f;
    float y          = sinf(omega_signal * t);
    float filtered_y = myFilter.filteredValue(y);

    Serial.print(y);
    Serial.print(", ");
    Serial.println(filtered_y);

    loopTimer += Ts_us;
    while (micros() < loopTimer);
}
```

---

## Portability

Although originally written for Arduino, the class uses only standard C++ features.
To use it outside Arduino, include `<cmath>` instead of `Arduino.h`. No other
changes are required.

Compatible with:
- Arduino AVR / SAMD / Mega
- ESP32
- Teensy
- STM32
- Desktop C++ simulation

---

## References

- [Bilinear (Tustin) Transform](https://en.wikipedia.org/wiki/Bilinear_transform)
- [Discrete-time filter derivations](https://spinlab.wpi.edu/courses/ece503_2014/10-3bilinear_transform.pdf)

---

## License

MIT License. See LICENSE for details.
