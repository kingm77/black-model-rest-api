FROM gcc:latest

RUN apt-get update
RUN apt-get install -y libcpprest-dev
RUN apt-get install -y cmake
RUN apt-get install -y  libssl-dev
RUN apt-get upgrade -y 
WORKDIR /black-scholes-model


COPY ./src .
RUN cmake . 
RUN cmake  --build  .

CMD ./app $PORT
