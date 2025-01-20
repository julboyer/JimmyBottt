FROM debian:latest

RUN apt update && apt upgrade -y
RUN apt install -y nodejs \
				npm



# Map /app as working directory in container.
WORKDIR /app
# COPY ../../.env .

# Copy local package files to container and install those dependencies.
COPY ./app/ .
RUN npm install


# Run NPM.
CMD ["npm", "run", "start"]