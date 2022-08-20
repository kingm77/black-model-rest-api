FROM gcc:latest

RUN apt-get update

RUN apt-get install -y libcpprest-dev
RUN apt-get install -y cmake
RUN apt-get install -y  libssl-dev
WORKDIR /black-scholes-model

EXPOSE 34566

COPY . .
RUN cmake  .
RUN cmake  --build  . 

CMD ./app $PORT