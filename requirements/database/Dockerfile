FROM debian:latest

EXPOSE 3306
RUN apt update && apt upgrade -y
RUN apt install mariadb-server -y
COPY ./script/db-init.sh /
# RUN sh db-init.sh

CMD ["sh", "/db-init.sh"]