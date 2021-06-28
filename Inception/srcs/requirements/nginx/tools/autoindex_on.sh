echo "server {
    listen 443 ssl;
    listen [::]:443 ssl;
    
    server_name localhost www.localhost;
    root        /var/www/html;
    index       index.html index.nginx-debian.html index.php;
    autoindex   on;

    ssl_certificate /etc/ssl/pino.pem;
    ssl_certificate_key /etc/ssl/pino.key;

    # hardening ssl security
        ssl_prefer_server_ciphers On;
        ssl_protocols TLSv1.2;

        # ssl cyphers suggested by ssllabs
        ssl_ciphers EECDH+ECDSA+AESGCM:EECDH+aRSA+AESGCM:EECDH+ECDSA+SHA384:EECDH+ECDSA+SHA256:EECDH+aRSA+SHA384:EECDH+aRSA+SHA256:EECDH+aRSA+RC4:EECDH:EDH+aRSA:RC4:!aNULL:!eNULL:!LOW:!3DES:!MD5:!EXP:!PSK:!SRP:!DSS;

    location / {
        try_files \$uri \$uri/ /index.php?\$args;
    }
    location ~ ^/(images|javascript|js|css|flash|media|static)/  {
        root    /var/www/html/index/;
        expires max;
    }
    location ~ \.php$ {
    include snippets/fastcgi-php.conf;
    fastcgi_pass php:9000;
    }
}" >  ../etc/nginx/sites-available/default
