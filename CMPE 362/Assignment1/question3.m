[soundEngine,fs] = audioread("enginesound.m4a");
% sound(soundEngine, fs);

filterPoint = 50;
lenghtsoundEngine = size(soundEngine, 1);
filteredSoundEngine = zeros(lenghtsoundEngine, 1);
for k = filterPoint/2:lenghtsoundEngine-filterPoint/2
   filteredSoundEngine(k) = sum(soundEngine(k-filterPoint/2+1:k+filterPoint/2)) / filterPoint;
end

audiowrite('filteredSoundEngine.wav', filteredSoundEngine.', fs);

[soundFiltered,fs] = audioread("filteredSoundEngine.wav");
sound(soundFiltered * 2, fs);

% y = movmean(soundEngine,50);
% % sound(y, fs);
% 
% % s = spectogram(soundFaulty);
% T = 1/fs;
% lengthSound = length(soundEngine);
% t = (0:lengthSound-1) * T;
% % plot(t, soundFaulty);
spectrogram(soundFaulty,'yaxis')
% spectrogram(soundEngine,[],[],[],fs,'yaxis')
% 
N = size(soundEngine, 1);
df = fs/N;
w = (-(N/2):(N/2)-1) * df;
y = fft(soundEngine) / N;
y2 = fftshift(y);
figure; plot(w, abs(y2));
