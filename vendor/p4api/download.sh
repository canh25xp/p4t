curl -Lo p4api.tgz https://filehost.perforce.com/perforce/r25.1/bin.linux26x86_64/p4api-glibc2.3-openssl3.tgz
# tar xvf p4api.tgz --strip-components=1 -C vendor/p4api/linux
tar xvf p4api.tgz
rm p4api.tgz
