FROM node:alpine
RUN apk update && apk add yarn
RUN yarn global add @nestjs/cli
WORKDIR /my-app
RUN yarn install
