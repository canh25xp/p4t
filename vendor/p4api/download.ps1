curl.exe -Lo p4api.zip https://filehost.perforce.com/perforce/r25.1/bin.mingw64x64/p4api-openssl3_gcc8_win32_seh.zip
7z x p4api.zip
Move-Item p4api-2025.1.2761706/* .
Remove-Item p4api-2025.1.2761706 -Recurse
Remove-Item p4api.zip
