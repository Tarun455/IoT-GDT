% --- Site (Solan/Nauni) baseline ---
site.lat = 30.85; site.lon = 77.18; site.alt_m = 1350;

Ts = 1;                    % sample time [s]
simDays = 3;               % keep short while building
StopTime = simDays*86400;  % seconds

% --- Realistic ranges (Solan, Nov) ---
T_mean = 16;               % °C
T_amp  = 7;                % °C diurnal swing
RH_mean = 65;              % %
RH_amp  = 20;              % %

% Sensor dynamics (first-order lag ~2s)
tau_s = 2;                 % s
a = exp(-Ts/tau_s);

% Noise (1-sigma)
noise.T  = 0.1;            % °C
noise.RH = 0.5;            % %RH
noise.VWC= 0.7;            % %VWC

% Soil moisture model
VWC_init = 28;             % % volumetric water content
VWC_min  = 8; VWC_max = 45;
evap_per_hour = 0.2;      % %VWC drop per hour (drying)
rain_pulse = 6;            % %VWC added per irrigation event
rain_every_hours = 36;     % periodic irrigation
evap_rate = evap_per_hour/3600;

% --- Soil temperature parameters ---
Tsoil_mean   = T_mean - 2;   % soil usually a bit cooler
Tsoil_amp    = 3;            % smaller swing than air
Tsoil_lag_h  = 4;            % soil peak ~4h after air
tau_s_soil   = 6;            % slower sensor/thermal response [s]
a_soil       = exp(-Ts/tau_s_soil);
noise.Tsoil  = 0.05;         % °C, smoother than air sensor
