FROM debian:latest

RUN apt update && apt upgrade -y
RUN apt install -y nodejs \
				npm



# Map /app as working directory in container.
WORKDIR /app

# Copy local package files to container and install those dependencies.
COPY ./app/ .
RUN npm install
RUN node deploy-commands.js

# Run NPM.
CMD ["npm", "run", "start"]