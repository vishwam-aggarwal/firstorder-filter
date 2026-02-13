/**
@file README.md
@brief Discrete‑time PID controller using the Tustin (bilinear) transform.

This library implements a lightweight, real‑time‑safe PID controller using
the Tustin (bilinear) transform for both the integrator and the derivative
filter. It is designed for embedded control applications such as motor
control, robotics, and real‑time feedback loops.

The controller uses:

- Tustin (trapezoidal) integrator
- Tustin filtered differentiator
- Integrator freeze anti‑windup when output saturates
- Deterministic, allocation‑free state updates

Although originally written for Arduino, the implementation is fully
portable to any C++ environment.
*/

# TustinPID — Discrete‑Time PID Controller (Tustin/Bilinear)

## @brief Overview

A minimal, stable, embedded‑friendly PID controller implemented using the
**Tustin (bilinear) transform**. The controller computes proportional,
integral, and derivative terms using numerically robust discrete‑time
formulas suitable for real‑time systems.

The discrete‑time control law is:

\[
u[k] = K_p e[k] + I[k] + D[k]
\]

with:

### Tustin Integrator
\[
I[k] = I[k-1] + \frac{K_i T_s}{2}(e[k] + e[k-1])
\]

### Tustin Filtered Derivative
\[
D[k] = a D[k-1] + b (e[k] - e[k-1])
\]

where:

\[
a = \frac{2\tau - T_s}{2\tau + T_s}, \quad
b = \frac{2K_d}{2\tau + T_s}
\]

### Anti‑Windup (Integrator Freeze)
When the output saturates, the integrator is **frozen**, preventing
windup. The `getI()` method always returns the *actual* integrator
contribution used in the last control output.

---

## @section features Features

- Discrete‑time PID using Tustin (bilinear) transform  
- Tustin filtered derivative for noise‑robust differentiation  
- Integrator freeze anti‑windup  
- Deterministic, allocation‑free implementation  
- No dynamic memory  
- Stable for all valid gains and sampling times  
- Portable to any C++ project (Arduino not required)  
- Suitable for motor control, robotics, and real‑time embedded systems  

---

## @section usage Usage

### Include the library

```cpp
#include "TustinPID.h"

Create and initialize the controller

TustinPID pid;

float Kp  = 7.58;
float Ki  = 82.79;
float Kd  = 0.155;
float tau = 0.005;   // derivative filter time constant (s)
float Ts  = 0.01;    // sampling time (s)

pid.setup(Kp, Ki, Kd, tau, Ts);

Compute control output each loop

float error = reference - measurement;

// With saturation limits
float u = pid.getControl(error, -100.0f, 100.0f);

// Or without saturation
float u = pid.getControl(error);

Access the integrator contribution

float Iterm = pid.getI();   // returns the value actually used

@section params Parameter Notes

Kp, Ki, Kd are standard PID gains

tau is the derivative filter time constant (seconds)

Ts is the sampling time (seconds)

The derivative filter behaves as a first‑order low‑pass

The integrator uses the trapezoidal (Tustin) rule

@section numeric Numerical Notes

Tustin discretization preserves stability for all valid parameters

The derivative filter reduces noise amplification

Integrator freeze prevents windup when output saturates

If Ts <= 0, the controller ignores updates to prevent invalid math

@section portability Portability

Although originally written for Arduino, the class uses only standard C++ features. To use it outside Arduino:

Include <cmath> instead of Arduino.h

No other changes are required

The library is compatible with:

Arduino AVR / SAMD / Mega

ESP32

Teensy

STM32

Desktop C++ simulation

@section example Example Sketch

#include "TustinPID.h"

TustinPID pid;

void setup() {
    pid.setup(7.58, 82.79, 0.155, 0.005, 0.01);
}

void loop() {
    float ref = 1.0f;
    float y   = readSensor();
    float e   = ref - y;

    float u = pid.getControl(e, -100.0f, 100.0f);
    applyActuator(u);
}

@section refs References

Bilinear (Tustin) Transformhttps://en.wikipedia.org/wiki/Bilinear_transform

Discrete‑time filter derivationshttps://spinlab.wpi.edu/courses/ece503_2014/10-3bilinear_transform.pdf

License

MIT License. See LICENSE for details.


---
