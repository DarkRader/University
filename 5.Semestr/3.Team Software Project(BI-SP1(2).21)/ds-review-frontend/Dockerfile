#stage 1 build the application
FROM docker.io/node:16 as node

WORKDIR /app

COPY . .

RUN npm install

RUN npm run build --prod

#stage 2 build the nginx server
FROM docker.io/nginx:alpine

# copy the custom nginx configuration file to the container in the 
# default location
COPY nginx.conf /etc/nginx/nginx.conf

COPY --from=node /app/dist/frontend_application /usr/share/nginx/html
