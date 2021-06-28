rm /etc/vsftpd.conf
mv /tmp/vsftpd.conf /etc/vsftpd.conf

adduser admin --gecos "First Last,RoomNumber,WorkPhone,HomePhone" --disabled-password
echo "admin:blabla" | chpasswd
echo "admin" | tee -a /etc/vsftpd.userlist

service vsftpd restart
bash