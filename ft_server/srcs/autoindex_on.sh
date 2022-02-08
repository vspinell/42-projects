echo " server {
    listen      80 default_server;
    listen      [::]:80 default_server;
    autoindex   on;
    server_name localhost www.localhost; 
    return 301 https://\$server_name\$request_uri;
}
server {
    listen 443 ssl;
    listen [::]:443 ssl;
    server_name localhost www.localhost;
    root        /var/www/html;
    index       index.html index.php;
    autoindex   on;
    ssl_certificate /etc/ssl/pino.pem;
    ssl_certificate_key /etc/ssl/pino.key;
    location / {
    try_files \$uri \$uri/ /index.php?\$args;
    }
    location ~ \.php$ {
    include snippets/fastcgi-php.conf;
    fastcgi_pass unix:/run/php/php7.3-fpm.sock;
    }
}" >  ../etc/nginx/sites-available/default
service nginx restart
