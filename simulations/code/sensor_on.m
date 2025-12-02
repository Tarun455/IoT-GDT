function on = sensor_on(t)
% t is simulation time in seconds
period = 31*60;   % total cycle: 31 minutes = 60s on + 30min off
awake  = 60;      % 60 seconds active

phase = mod(t, period);   % position within each 31-min cycle
if phase < awake
    on = 0;    % sensor awake (1 min)
else
    on = 1;    % sensor sleeping (30 min)
end
end