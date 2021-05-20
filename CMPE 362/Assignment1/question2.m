[soundFaulty,fs] = audioread("faultyphone.wav");
% sound(soundFaulty, fs);

lenghtSoundFaulty = size(soundFaulty, 1);

freqStep = fs/lenghtSoundFaulty;
t = (-(lenghtSoundFaulty/2):(lenghtSoundFaulty/2)-1) * freqStep;
fourierOut = fft(soundFaulty) / lenghtSoundFaulty;
fourierShiftOut = fftshift(fourierOut);
figure;
plot(t, abs(fourierShiftOut));

for k = ceil(lenghtSoundFaulty / 2 - 530 / freqStep):ceil(lenghtSoundFaulty / 2 - 370 / freqStep)
    fourierShiftOut(k) = 0;
end

for k = ceil(lenghtSoundFaulty / 2 + 370 / freqStep):ceil(lenghtSoundFaulty / 2 + 530 / freqStep)
    fourierShiftOut(k) = 0;
end

figure;
plot(t, abs(fourierShiftOut));

inverseShiftOut = ifftshift(fourierShiftOut);
inverseOut = ifft(inverseShiftOut) * lenghtSoundFaulty;

audiowrite('inverseOut.wav', inverseOut.', fs);

[soundFiltered,fs] = audioread("inverseOut.wav");
sound(soundFiltered, fs);






% n=7;
% beginFreq=1200/(fs/2);
% endFreq=(20000/(fs/2));
% [b,a]=butter(n,[beginFreq,endFreq],'bandpass');
% [H,W]=freqz(b,a,n);
% % figure(3);
% % plot(angle(H))
% % figure(4);
% % plot(20*log10(abs(H)))
% %%Filter the signal
% fout=filter(b,a,soundFaulty);
% 
% %%construct audioplayer object and play
% p=audioplayer(fout *2 , fs);
% p.play;
