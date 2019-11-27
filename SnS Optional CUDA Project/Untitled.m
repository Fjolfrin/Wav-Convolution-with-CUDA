[y1, F1] = audioread("sample_audio.wav");
[y2, F2] = audioread("pink_noise.wav");
[y3, F3] = audioread("pinkNoise_sampleAudio.wav");
y4 = conv(y1, y2)./50;

subplot(3, 1, 1), stem(y3)
subplot(3, 1, 2), stem(y4)
subplot(3, 1, 3), stem(y3-y4);