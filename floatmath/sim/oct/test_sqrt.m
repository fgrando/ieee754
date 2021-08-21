%mkoctfile oct_sqrt.cpp -I../../ ../../fm_util.c ../../fm_sqrt.c

dx = 0.1;
x = 0:dx:3*pi;


y0 = sqrt(x);
y1 = oct_sqrt(x);

%dy = y0-y1 ; % error
%abs_dy = abs(y0-y1) ;   % absolute error
%relerr = abs(y0-y1)./y0 ;  % relative error
%pererr = abs(y0-y1)./y0*100 ;   % percentage error
%mean_err = mean(abs(y0-y1)) ;    % mean absolute error
%MSE = mean((y0-y1).^2) ;        % Mean square error
%RMSE = sqrt(mean((y0-y1).^2)) ; % Root mean square error

figure;
% rows,cols.index
subplot (1, 3, 1)
plot(x,y0,      x,y1);
legend('sqrt', 'fmsqrt');
title('curves')

subplot (1, 3, 2)
plot(x,abs(y0-y1));
legend('sqrt - fmsqrt');
title('abs error')

subplot (1, 3, 3)
plot(x, log10(abs(y0-y1)./y0));
legend('sqrt - fmsqrt');
title('log(abs error)')
