FROM b01t/raspbian

ARG SERVER_IP=""
ENV SERVER_IP $SERVER_IP

RUN mkdir /workdir
WORKDIR /workdir

COPY . /workdir

RUN apt-get update 
RUN apt-get -y install wiringpi && apt-get -y install libcurl4-gnutls-dev &&\
apt-get -y install make && apt-get -y install g++
RUN cd /workdir && make

CMD cd /workdir && su root && ./hello "$SERVER_IP"