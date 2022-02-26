#ifndef KALMAN_H
#define KALMAN_H

#include "Arduino.h"

class Kalman
{
private:
    float state;
    float uncertainty;
    int num_iter;
    float time_interval;
    float vel;
    float vel_uncertainty;
    float noise_var;
    float measure_uncertainty;

public:
    Kalman(float x, float p, int n, float dt, float v, float pv, float var, float pm)
    {
        state = x;
        uncertainty = p;
        num_iter = n;
        time_interval = dt;
        vel = v;
        vel_uncertainty = pv;
        noise_var = var;
        measure_uncertainty = pm;
    }
    void predict()
    {
        state = state + time_interval * vel; // State transition equation based on dynamic model
        uncertainty = uncertainty + (pow(time_interval, 2) * vel_uncertainty) + noise_var;
    }
    void update(float measurement)
    {
        float kalman_gain = uncertainty / (uncertainty + measure_uncertainty);
        state = state + kalman_gain * (measurement - state);
        uncertainty = (1 - kalman_gain) * uncertainty;
    }
    float run(float measurement)
    {
        for (int i = 0; i < num_iter; i++)
        {
            predict();
            update(measurement);
        }
        return state;
    }
};

#endif