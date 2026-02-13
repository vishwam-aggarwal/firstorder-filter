#include "firstorderFilter.h"
#include <math.h>

firstorderFilter myFilter;

uint32_t loopTimer;          // Time‑keeping variable (microseconds)
float omega_signal = 10.0f;  // Signal frequency in rad/s  (~1.59 Hz)
float Ts = 0.01f;            // Sample time (10 ms → 100 Hz loop)
uint32_t Ts_us;              // Sample time in microseconds

float y;                     // Raw signal
float filtered_y;            // Filtered signal

void setup() {
  Serial.begin(38400);

  // Precompute sample time in microseconds (avoids float math in the loop)
  Ts_us = (uint32_t)(Ts * 1000000.0f);

  // Cutoff = omega_signal / 4 = 2.5 rad/s (~0.4 Hz)
  myFilter.setup(omega_signal / 4.0f, Ts);

  // Initialize loop timer
  loopTimer = micros();
}

void loop() {
  // Generate sine wave: sin(ω * t)
  float t = loopTimer / 1000000.0f;  // Convert micros to seconds
  y = sinf(omega_signal * t);

  // Filter the signal
  filtered_y = myFilter.filteredValue(y);

  // Output both signals for Serial Plotter
  Serial.print(y);
  Serial.print(", ");
  Serial.println(filtered_y);

  // Maintain fixed sample period
  loopTimer += Ts_us;
  while (micros() < loopTimer);
}