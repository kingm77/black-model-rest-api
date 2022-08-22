FROM nginx:latest

RUN apt-get update
RUN apt-get install dos2unix
RUN apt-get install -y build-essential gcc
RUN apt-get install -y libcpprest-dev
RUN apt-get install -y cmake
RUN apt-get install -y  libssl-dev
RUN apt-get upgrade -y 
WORKDIR /black-scholes-model


COPY . .
RUN cmake  . 
RUN cmake  --build  .

RUN rm /etc/nginx/conf.d/default.conf
COPY nginx.conf /etc/nginx/conf.d/default.conf
RUN cat /etc/nginx/conf.d/default.conf
RUN dos2unix launch.sh

EXPOSE 80

ENTRYPOINT ["/bin/bash", "launch.sh"]
