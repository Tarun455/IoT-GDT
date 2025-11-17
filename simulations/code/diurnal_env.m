function [T_air_raw, RH_raw, T_soil_raw] = diurnal_env( ...
    t, T_mean, T_amp, RH_mean, RH_amp, ...
    Tsoil_mean, Tsoil_amp, Tsoil_lag_h)

hr = mod(t/3600, 24);

% Air temperature
T_air_raw = T_mean + T_amp * sin(2*pi*(hr - 5)/24);

% Relative humidity
RH_raw = RH_mean + RH_amp * sin(2*pi*(hr + 7)/24);

% Soil temperature: delayed & smaller swing
T_soil_raw = Tsoil_mean + Tsoil_amp * ...
             sin(2*pi*(hr - 5 - Tsoil_lag_h)/24);
end
