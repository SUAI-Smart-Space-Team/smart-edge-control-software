FROM b01t/raspbian

RUN mkdir /workdir
WORKDIR /workdir

COPY . /workdir

RUN apt-get update 
RUN apt-get -y install wiringpi && apt-get -y install libcurl4-gnutls-dev &&\
apt-get -y install make && apt-get -y install g++

CMD cd /workdir && make && su root && ./hello