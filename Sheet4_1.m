clear 
clc
%FM  Tx
Ac=1;
Am=10;
kf=100;
fm=100;
%fm=100;
%fc=10*1000;
fc=10000;
ts=0.1/fc; %sampling m(t)
T=2/fm; % 2 cycles of m(t)
N=ceil(T/ts);
t=0:ts:(N-1)*ts;
fs=1/ts;
df=fs/N; % frequency step
if(rem(N,2)==0)
    f=(-fs/2):df:(fs/2)-df;
else 
    f=((-fs/2)+0.5*df):df:((fs/2)-0.5*df);
end
%% baseband time domain  
m_t= Am*sin(2*pi.*fm.*t);
subplot(2,2,1);
 plot(t,m_t,'-b','linewidth',1);
 xlabel('Time(sec)');
 ylabel('m(t)');
 title('message');
 %% passband signal frequency domain
  m_f=fftshift(fft(m_t))/N;
  subplot(2,2,3)
  plot(f,abs(m_f),'-r');
  xlabel('Frequency (Hz)');
  ylabel('S(f)');
  title('Massege Frequency Spectrum');
 
 %%
s_t=cos(2*pi*fc*t+2*pi*kf*cumtrapz(t,m_t));
figure(2);
subplot(2,1,1);
 plot(t,s_t,'-r');
 xlabel('Time(sec)')
 ylabel('s(t)')
 title('Modulated Signal');
 
 %% analytical spectrum
 beta=kf*Am/fm;
 n=-100:100;
 S_analytical=0.5*besselj(n,beta);
 f_analytical=fc+n*fm;
 ff_analytical=-fc+n*fm;
 figure(5)
 stem(f_analytical,abs(S_analytical));
 hold on
 stem(ff_analytical,abs(S_analytical));

%% passband signal frequency domain
  s_f=fftshift(fft(s_t))/N;
  figure(4);
  %subplot(2,1,2)
  
  stem(f,abs(s_f),'-r');
  xlabel('Frequency (Hz)');
  ylabel('S(f)');
  title('Modulated Signal Frequency Spectrum');
  %% BW
  %using carson 
  DF=kf*Am;
  BW_Carson=2*fm*(1+beta);
  %%
 % universal
  Index_fc=find(f==fc);

   for c_index=length(f):-1:Index_fc
     if (abs(s_f(c_index))>=0.5*Ac*0.01)
         BW_universal = 2*abs(fc-f(c_index));
         break 
     end
 end
