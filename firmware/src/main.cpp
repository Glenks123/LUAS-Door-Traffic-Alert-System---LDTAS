#include <Arduino.h>
#include <array>
#include <algorithm>
#include <numeric>
#include <vector>


namespace {
    // Ultrasonic sensor pin configuration
    constexpr int TRIG_PIN = 25;
    constexpr int ECHO_PIN = 12;

    // Speed of sound in cm/microseconds
    constexpr float SPEED_OF_SOUND = 0.034f;

     // Filter window sizes
    constexpr size_t MEDIAN_WINDOW_SIZE = 10;
    constexpr size_t MEDIAN_AVERAGE_SIZE = 5;

    // Function that reads sensor data and computes distance
    float readDistance(int trig_pin, int echo_pin) {
        digitalWrite(trig_pin, LOW);
        delayMicroseconds(2);
        digitalWrite(trig_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig_pin, LOW);

        const unsigned long duration  = pulseIn(echo_pin, HIGH);
        return SPEED_OF_SOUND * (duration / 2);
    }

    // Compute median from window of raw inputs
    template <size_t N>
    float computeMedianFilter(const std::array<float, N>& values){ // copying by reference (modifies original array)
        const float sum = std::accumulate(values.begin(), values.end(), 0.0f);
        return sum / N;
    }

    // Compute smoothing average from window of median values
    template <size_t N>
    float computeAverageFilter(std::array<float, N> values){ // copying by value (creates copy of array)
        std::sort(values.begin(), values.end());
        if (N % 2 == 0) {
            return (values[N / 2] + values[N / 2 + 1]) / 2.0f;
        } else {
            return values[N / 2];
        }
    }
}

void setup() {
    Serial.begin(115200); // Starts the serial communication at 115200 bits per second
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop() {
    std::vector<float> filteredReadings;

    //float averageWindow[MEDIAN_AVERAGE_SIZE];
    std::array<float, MEDIAN_AVERAGE_SIZE> averageWindow{};
    for (size_t i=0; i<MEDIAN_AVERAGE_SIZE; i++){

        //float medianWindow[MEDIAN_WINDOW_SIZE];
        std::array<float, MEDIAN_WINDOW_SIZE> medianWindow{}; // resolved: no instance of function template "<unnamed>::computeMedianFilter" matches the argument listC/C++(304) test.cpp(66, 29): argument types are: (float [10])
        for (size_t i=0; i<MEDIAN_WINDOW_SIZE; i++){
            const unsigned long distanceCm = readDistance(TRIG_PIN, ECHO_PIN);
            medianWindow[i] = distanceCm;
            Serial.print(F("Distance (cm): "));
            Serial.println(distanceCm);
        }

        float medianValue = computeMedianFilter(medianWindow);
        averageWindow[i] = medianValue;
    }
    float averageValue = computeAverageFilter(averageWindow);
    filteredReadings.push_back(averageValue);

    delay(1000);
}
