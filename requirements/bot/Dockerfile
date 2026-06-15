FROM debian:latest


RUN apt update && apt upgrade -y
RUN apt install -y pkg-config
RUN apt install cmake -y
RUN apt install build-essential -y
RUN apt install libopus0 -y
RUN apt install wget; wget -O dpp.deb https://dl.dpp.dev/; dpkg -i dpp.deb

COPY ./Makefile .
COPY ./src ./src

RUN make prepare
RUN make build
RUN rm -r build

CMD [./target/jimmybott]