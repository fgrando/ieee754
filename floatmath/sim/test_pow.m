

dx = 0.001;
off = 300;
start=-0.00003;
x = 0:dx:2*pi;


y0 = power(x,x);
y1 = mex_pow(x,x);

%dy = y0-y1 ; % error
%abs_dy = abs(y0-y1) ;   % absolute error
%relerr = abs(y0-y1)./y0 ;  % relative error
%pererr = abs(y0-y1)./y0*100 ;   % percentage error
%mean_err = mean(abs(y0-y1)) ;    % mean absolute error
%MSE = mean((y0-y1).^2) ;        % Mean square error
%RMSE = sqrt(mean((y0-y1).^2)) ; % Root mean square error

figure;
subplot 131;
plot(x,y0,      x,y1);
legend('exp', 'fmexp');
title('curves')

subplot 132;
plot(x,abs(y0-y1));
legend('exp - fmexp');
title('abs error')

subplot 133;
plot(x, abs(y0-y1)./y0*100);
legend('exp - fmexp');
title('% error')
