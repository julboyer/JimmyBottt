FROM debian:latest

RUN apt update && apt upgrade
RUN apt install nodejs \
				npm

# Map /app as working directory in container.
WORKDIR /app

# Copy local package files to container and install those dependencies.
COPY ./app/package*.json ./
RUN npm install

# Copy the other local app files and build the application.
COPY ./app/ .
RUN npm run build

# Run NPM.
CMD ["npm", "run", "start"]